/*=========================================================================

  Program:   Visualization Toolkit
  Module:    TestTemporalDataToMultiDimensionalArray.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDSPDataModelTestingUtilities.h"
#include "vtkDataSet.h"
#include "vtkDoubleArray.h"
#include "vtkIOSSReader.h"
#include "vtkInformation.h"
#include "vtkMultiDimensionalArray.h"
#include "vtkMultiDimensionalImplicitBackend.h"
#include "vtkPartitionedDataSet.h"
#include "vtkPartitionedDataSetCollection.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkTestUtilities.h"

#include <memory>
#include <vector>

int TestTemporalDataToMultiDimensionalArray(int argc, char* argv[])
{
  // Read can.ex2 using ioss reader
  char* fileNameC = vtkTestUtilities::ExpandDataFileName(argc, argv, "Testing/Data/can.ex2");
  vtkNew<vtkIOSSReader> readerIOSS;
  readerIOSS->AddFileName(fileNameC);
  delete[] fileNameC;

  // Retrieve all timesteps
  readerIOSS->Update();
  vtkInformation* info = readerIOSS->GetOutputInformation(0);
  if (!info->Has(vtkStreamingDemandDrivenPipeline::TIME_STEPS()))
  {
    cerr << "Unable to retrieve time steps from test data." << endl;
    return EXIT_FAILURE;
  }

  std::vector<double> timeSteps;
  const int nbOfTimesteps = info->Length(vtkStreamingDemandDrivenPipeline::TIME_STEPS());
  const double* timeStepsPtr = info->Get(vtkStreamingDemandDrivenPipeline::TIME_STEPS());

  for (int ts = 0; ts < nbOfTimesteps; ts++)
  {
    timeSteps.emplace_back(timeStepsPtr[ts]);
  }

  // Retrieve info about point data array "VEL" to test at timestep 0.
  auto retrieveOutArray = [&](const std::string& arrayName) -> vtkAOSDataArrayTemplate<double>* {
    auto* outputData =
      vtkPartitionedDataSetCollection::SafeDownCast(readerIOSS->GetOutputDataObject(0));
    if (!outputData)
    {
      cerr << "Unable to retrieve output data as vtkPartitionedDataSetCollection." << endl;
      return nullptr;
    }

    auto* outputDS = outputData->GetPartition(0, 0);
    if (!outputDS)
    {
      cerr << "Unable to retrieve first partition of output data." << endl;
      return nullptr;
    }

    auto* pointData = outputDS->GetPointData();
    if (!pointData)
    {
      cerr << "Unable to retrieve point data in partition." << endl;
      return nullptr;
    }

    auto* outArray =
      vtkAOSDataArrayTemplate<double>::SafeDownCast(pointData->GetAbstractArray(arrayName.c_str()));
    if (!outArray)
    {
      cerr << "Unable to retrieve " << arrayName << " array as vtkDoubleArray." << endl;
      return nullptr;
    }

    return outArray;
  };

  const std::string outArrayName = "VEL";
  vtkAOSDataArrayTemplate<double>* outArray = retrieveOutArray(outArrayName);
  if (!outArray)
  {
    return EXIT_FAILURE;
  }

  const vtkIdType nbOfPoints = outArray->GetNumberOfTuples();
  const int nbOfComponents = outArray->GetNumberOfComponents();

  // Now that we have all information needed, prepare the array vector for multi-dimensional
  // implicit array.
  std::vector<vtkSmartPointer<vtkAOSDataArrayTemplate<double>>> arrays;
  arrays.reserve(nbOfPoints);
  for (int ptId = 0; ptId < nbOfPoints; ptId++)
  {
    vtkSmartPointer<vtkAOSDataArrayTemplate<double>> array =
      vtkSmartPointer<vtkAOSDataArrayTemplate<double>>::New();
    array->SetNumberOfComponents(nbOfComponents);
    array->SetNumberOfTuples(nbOfTimesteps);
    arrays.emplace_back(array);
  }

  // Iterate over timesteps to fill arrays in the vector. At each timestep, we should have the same
  // composite structure and the same number of points in the temporal dataset.
  for (int ts = 0; ts < nbOfTimesteps; ts++)
  {
    readerIOSS->UpdateTimeStep(timeSteps[ts]);

    outArray = retrieveOutArray(outArrayName);
    if (!outArray)
    {
      return EXIT_FAILURE;
    }

    if (outArray->GetNumberOfTuples() != nbOfPoints ||
      outArray->GetNumberOfComponents() != nbOfComponents)
    {
      cerr << "Number of tuples and components should be equal over all timesteps in the"
           << outArrayName << " array." << endl;
      return EXIT_FAILURE;
    }

    for (int ptId = 0; ptId < nbOfPoints; ptId++)
    {
      std::vector<double> tuple(nbOfComponents, 0.);
      outArray->GetTypedTuple(ptId, tuple.data());
      arrays[ptId]->SetTypedTuple(ts, tuple.data());
    }
  }

  // Construct the multi-dimensional array
  vtkNew<vtkMultiDimensionalArray<double>> mdArray;
  mdArray->ConstructBackend(arrays);

  // Finally, iterate over timesteps and check equivalence between "VEL" array values and those of
  // the multi-dimensional implicit array.
  for (int ts = 0; ts < nbOfTimesteps; ts++)
  {
    readerIOSS->UpdateTimeStep(timeSteps[ts]);

    outArray = retrieveOutArray(outArrayName);
    if (!outArray)
    {
      return EXIT_FAILURE;
    }

    for (int ptId = 0; ptId < nbOfPoints; ptId++)
    {
      mdArray->SetIndex(ptId);

      for (int comp = 0; comp < nbOfComponents; comp++)
      {
        if (!vtkDSPDataModelTestingUtilities::testValue(mdArray->GetTypedComponent(ts, comp),
              outArray->GetTypedComponent(ptId, comp), ptId, ts, comp, "multi-dimensional array"))
        {
          return EXIT_FAILURE;
        }
      }
    }
  }

  return EXIT_SUCCESS;
};
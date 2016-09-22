/*=========================================================================

  Program:   ParaView
  Module:    vtkPConvertSelection.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPConvertSelection - parallel aware vtkConvertSelection subclass.
// .SECTION Description
// vtkPConvertSelection is a parallel aware vtkConvertSelection subclass.

#ifndef vtkPConvertSelection_h
#define vtkPConvertSelection_h

#include "vtkConvertSelection.h"
#include "vtkPVClientServerCoreCoreModule.h" //needed for exports

class vtkMultiProcessController;

class VTKPVCLIENTSERVERCORECORE_EXPORT vtkPConvertSelection : public vtkConvertSelection
{
public:
  static vtkPConvertSelection* New();
  vtkTypeMacro(vtkPConvertSelection, vtkConvertSelection);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get/Set the parallel controller.
  void SetController(vtkMultiProcessController*);
  vtkGetObjectMacro(Controller, vtkMultiProcessController);

protected:
  vtkPConvertSelection();
  ~vtkPConvertSelection();

  virtual int RequestData(
    vtkInformation *,
    vtkInformationVector **,
    vtkInformationVector *);

  vtkMultiProcessController* Controller;
private:
  vtkPConvertSelection(const vtkPConvertSelection&) VTK_DELETE_FUNCTION;
  void operator=(const vtkPConvertSelection&) VTK_DELETE_FUNCTION;

};

#endif // vtkPConvertSelection_h

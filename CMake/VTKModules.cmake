#########################################################################
# This file is included in ParaView/ParaViewCore/ServerManager/Default
# to ensure all ParaView needed modules are turned on when building the complete
# application.

set(_vtk_mpi_modules
  vtkParallelMPI
  vtkFiltersParallelImaging
  vtkIOMPIImage
  vtkFiltersParallelMPI
  # Note: Not in ParaViewXXX.xml but required by a test.
  # Needed for:
  #  vtkPStreamTracer

  vtkIOParallelNetCDF
  # Needed for:
  #  vtkPNetCDFPOPReader
  )

set(_vtk_modules
  # VTK modules which ParaView has a explicity compile
  # time dependency on
  vtkRenderingVolume
  vtkRenderingLabel
  vtkRenderingFreeType
  vtkRenderingFreeTypeOpenGL
  vtkRenderingVolumeOpenGL
  vtkRenderingOpenGL
  vtkRenderingLOD
  vtkRenderingHybridOpenGL
  vtkRenderingContext2D
  vtkRenderingAnnotation
  vtkInteractionStyle
  vtkInteractionWidgets
  vtkRenderingParallel
  vtkFiltersParallel
  vtkIOParallelExodus
  vtkFiltersParallelStatistics
  vtkIOParallel
  vtkFiltersGeneric
  vtkFiltersHyperTree
  vtkImagingFourier
  vtkImagingMorphological
  vtkIOImport
  vtkIOXML
  vtkIOImage
  vtkIOGeometry
  vtklibxml2
  vtkViewsContext2D
  vtkIOExport
  vtkIOInfovis
  vtkFiltersAMR
  vtkChartsCore
  vtkIOEnSight
  vtkTestingRendering
  # Needed to for tests that are built even with BUILD_TESTING off!
  vtkInteractionImage
  # Modules that are required a runtime generated from:
  #
  # ParaViewFilters.xml
  # ParaViewReaders.xml
  # ParaViewSources.xml
  # ParaViewWriters.xml
  #

  vtkCommonExecutionModel
  # Needed for:
  #  vtkUniformGridPartitioner

  vtkFiltersCore
  # Needed for:
  #  vtkThreshold
  #  vtkAppendPolyData
  #  vtkCellDataToPointData
  #  vtkCleanPolyData
  #  vtkDecimatePro
  #  vtkDelaunay2D
  #  vtkDelaunay3D
  #  vtkElevationFilter
  #  vtkFeatureEdges
  #  vtkMaskPoints
  #  vtkPointDataToCellData
  #  vtkPolyDataNormals
  #  vtkQuadricClustering
  #  vtkSmoothPolyDataFilter
  #  vtkStripper
  #  vtkStructuredGridOutlineFilter
  #  vtkThreshold
  #  vtkTriangleFilter
  #  vtkTubeFilter
  #  vtkDataObjectGenerator

  vtkFiltersExtraction
  # Needed for:
  #  vtkExtractGrid
  #  vtkExtractSelection
  #  vtkExtractBlock
  #  vtkExtractEdges
  #  vtkExtractGeometry
  #  vtkExtractGrid
  #  vtkExtractSelection

  vtkFiltersGeneral
  # Needed for:
  #  vtkWarpVector
  #  vtkTemporalStatistics
  #  vtkBlockIdScalars
  #  vtkBrownianPoints
  #  vtkCellCenters
  #  vtkCellDerivatives
  #  vtkClipClosedSurface
  #  vtkCurvatures
  #  vtkDataSetTriangleFilter
  #  vtkImageDataToPointSet
  #  vtkLevelIdScalars
  #  vtkQuadraturePointInterpolator
  #  vtkQuadraturePointsGenerator
  #  vtkQuadratureSchemeDictionaryGenerator
  #  vtkRectilinearGridToPointSet
  #  vtkReflectionFilter
  #  vtkShrinkFilter
  #  vtkTemporalStatistics
  #  vtkTessellatorFilter
  #  vtkTransformFilter
  #  vtkWarpScalar
  #  vtkWarpVector
  #  vtkYoungsMaterialInterface
  #  vtkTableToPolyData
  #  vtkTableToStructuredGrid
  #  vtkAxes

  vtkFiltersGeneric
  # Needed for:
  #  vtkGenericClip
  #  vtkGenericStreamTracer
  #  vtkGenericGeometryFilter

  vtkFiltersGeometry
  # Needed for:
  #  vtkDataSetSurfaceFilter

  vtkFiltersHybrid
  # Needed for:
  #  vtkFacetReader
  #  vtkTemporalInterpolator
  #  vtkTemporalSnapToTimeStep
  #  vtkTemporalShiftScale
  #  vtkTemporalInterpolator
  #  vtkTemporalSnapToTimeStep
  #  vtkTemporalShiftScale

  vtkFiltersModeling
  # Needed for:
  #  vtkLinearExtrusionFilter
  #  vtkLoopSubdivisionFilter
  #  vtkOutlineFilter
  #  vtkRibbonFilter
  #  vtkRotationalExtrusionFilter

  vtkFiltersParallel
  # Needed for:
  #  vtkProcessIdScalars

  vtkFiltersProgrammable
  # Needed for:
  #  vtkProgrammableFilter
  #  vtkProgrammableFilter

  vtkFiltersSources
  # Needed for:
  #  vtkOutlineCornerFilter
  #  vtkGlyphSource2D
  #  vtkArrowSource
  #  vtkCubeSource
  #  vtkConeSource
  #  vtkCylinderSource
  #  vtkDiskSource
  #  vtkLineSource
  #  vtkOutlineSource
  #  vtkPlaneSource
  #  vtkPointSource
  #  vtkProgrammableSource
  #  vtkSphereSource
  #  vtkSuperquadricSource
  #  vtkTextSource

  vtkFiltersStatistics
  # Needed for:
  #  vtkContingencyStatistics
  #  vtkDescriptiveStatistics
  #  vtkMultiCorrelativeStatistics
  #  vtkPCAStatistics

  vtkFiltersTexture
  # Needed for:
  #  vtkTextureMapToCylinder
  #  vtkTextureMapToPlane
  #  vtkTextureMapToSphere

  vtkFiltersFlowPaths
  # Needed for:
  #  vtkStreamTracer
  #  Plugins/SciberQuestToolKit/vtkSQFieldTracer

  vtkFiltersVerdict
  # Needed for:
  #  vtkMeshQuality

  vtkImagingCore
  # Needed for:
  #  vtkRTAnalyticSource

  vtkImagingHybrid
  # Needed for:
  #  vtkGaussianSplatter

  vtkImagingSources
  # Needed for:
  #  vtkImageMandelbrotSource

  vtkIOExodus
  # Needed for:
  #  vtkExodusIIReader

  vtkIOGeometry
  # Needed for:
  #  vtkTecplotReader
  #  vtkBYUReader
  #  vtkOBJReader
  #  vtkProStarReader
  #  vtkPDBReader
  #  vtkSTLReader
  #  vtkSESAMEReader
  #  vtkMFIXReader
  #  vtkFLUENTReader
  #  vtkOpenFOAMReader
  #  vtkParticleReader
  #  vtkDataSetWriter

  vtkIOImage
  # Needed for:
  #  vtkDEMReader
  #  vtkGaussianCubeReader
  #  vtkImageReader
  #  vtkMetaImageReader
  #  vtkMetaImageWriter
  #  vtkPNGWriter
  #  vtkNrrdReader

  vtkIONetCDF
  # Needed for:
  #  vtkNetCDFReader
  #  vtkSLACReader
  #  vtkSLACParticleReader
  #  vtkNetCDFCAMReader
  #  vtkNetCDFPOPReader
  #  vtkMPASReader

  vtkIOParallel
  # Needed for:
  #  vtkWindBladeReader
  #  vtkPNetCDFPOPReader
  #  vtkPDataSetWriter
  #  vtkExodusIIWriter
  #  vtkEnSightWriter

  vtkIOPLY
  # Needed for:
  #  vtkPLYReader

  vtkIOVPIC
  # Needed for:
  #  vtkVPICReader

  vtkIOXML
  # Needed for:
  #  vtkXMLPolyDataReader
  #  vtkXMLUnstructuredGridReader
  #  vtkXMLImageDataReader
  #  vtkXMLStructuredGridReader
  #  vtkXMLRectilinearGridReader
  #  vtkXMLPPolyDataReader
  #  vtkXMLPUnstructuredGridReader
  #  vtkXMLPImageDataReader
  #  vtkXMLPStructuredGridReader
  #  vtkXMLPRectilinearGridReader
  #  vtkXMLMultiBlockDataReader
  #  vtkXMLHierarchicalBoxDataReader
  #  vtkXMLHyperOctreeWriter
  #  vtkXMLPolyDataWriter
  #  vtkXMLUnstructuredGridWriter
  #  vtkXMLStructuredGridWriter
  #  vtkXMLRectilinearGridWriter
  #  vtkXMLImageDataWriter
  #  vtkXMLPPolyDataWriter
  #  vtkXMLPUnstructuredGridWriter
  #  vtkXMLPStructuredGridWriter
  #  vtkXMLPRectilinearGridWriter
  #  vtkXMLPImageDataWriter
  #  vtkXMLMultiBlockDataWriter
  #  vtkXMLHierarchicalBoxDataWriter

  vtkIOXdmf2
  #  Needed for xdmf support.

  vtkRenderingFreeType
  # Needed for:
  #  vtkVectorText

  vtkFiltersCosmo
  # Note: Not in ParaViewXXX.xml but required by a test.
  # Needed for:
  #  vtkPCosmoReader

  vtkIOParallelLSDyna
  # Note: Not in ParaViewXXX.xml but required by a test.
  # Needed for:
  #  vtkPLSDynaReader

  vtkDomainsChemistry
  # Needed for:
  #  vtkMoleculeRepresentation
  )

if(PARAVIEW_USE_PISTON)
  list(APPEND _vtk_modules vtkAcceleratorsPiston)
endif() 

if (PARAVIEW_USE_MPI)
  list (APPEND _vtk_modules ${_vtk_mpi_modules})
endif()

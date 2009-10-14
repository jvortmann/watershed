# CMakeLists.txt for the vtkFlRWI Cone3 example
# copyright 2004 by Charl P. Botha http://cpbotha.net/
# $Id: CMakeLists.txt,v 1.2 2004/06/08 12:48:33 cpbotha Exp $

# Use cmake on any platform supported by VTK to create a build environment
# for this example.  Alternatively, but not recommended, modify and make use
# of the Makefile.vtk3 or Makefile.vtk4 example makefiles for GNU C++

PROJECT(Watershed)

# first we have to find ITK
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ENDIF(ITK_FOUND)

# then FLTK
#FIND_PACKAGE(FLTK)
#IF(FLTK_FOUND)
#  INCLUDE_DIRECTORIES(${FLTK_INCLUDE_DIR})
#ENDIF(FLTK_FOUND)

# then vtkFlRenderWindowInteractor.h and .cxx
#FIND_PATH(VTK_FL_RWI_H_PATH vtkFlRenderWindowInteractor.h)
#FIND_PATH(VTK_FL_RWI_CXX_PATH vtkFLRenderWindowInteractor.cxx)

#path to vtkAnalyzeReader.h vtkAnalyzeReader.cxx
#FIND_PATH(VTK_ANALYZE_READER_H_PATH vtkAnalyzeReader.h)
#FIND_PATH(VTK_ANALYZE_READER_CXX_PATH vtkAnalyzeReader.cxx)

#IF(NOT VTK_ANALYZE_READER_H_PATH)
#   MESSAGE(FATAL_ERROR "Please enter the path of vtkAnalyzeReader.h")
#ENDIF(NOT VTK_ANALYZE_READER_H_PATH)

#IF(NOT VTK_ANALYZE_READER_CXX_PATH)
#   MESSAGE(FATAL_ERROR "Please enter the path of vtkAnalyzeReader.cxx")
#ENDIF(NOT VTK_ANALYZE_READER_CXX_PATH)

#IF(NOT VTK_FL_RWI_H_PATH)
#   MESSAGE(FATAL_ERROR "Please enter the path of vtkFlRenderWindowInteractor.h")
#ENDIF(NOT VTK_FL_RWI_H_PATH)

#IF(NOT VTK_FL_RWI_CXX_PATH)
#   MESSAGE(FATAL_ERROR "Please enter the path of vtkFlRenderWindowInteractor.cxx")
#ENDIF(NOT VTK_FL_RWI_CXX_PATH)

# add the vtkFlRenderWindowInteractor.h path to the include directories
#INCLUDE_DIRECTORIES(${VTK_FL_RWI_H_PATH})
#INCLUDE_DIRECTORIES(${VTK_ANALYZE_READER_H_PATH})

# remember to actually build and link with vtkFlRenderWindowInteractor.cxx
ADD_EXECUTABLE(watershed watershed.cxx) 

TARGET_LINK_LIBRARIES(watershed ITKIO ITKAlgorithms ITKBasicFilters ITKStatistics)

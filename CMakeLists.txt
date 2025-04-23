cmake_minimum_required(VERSION 3.12)
project(Qt_VTK_OCC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########
# Qt
##########
find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL Gui)
if(Qt5_FOUND)
    message(STATUS "Qt5_DIR = ${Qt5_DIR}")
    message(STATUS "Qt5_INCLUDE_DIR = ${Qt5_INCLUDE_DIR}")
    message(STATUS "Qt5_LIBRARY_DIR = ${Qt5_LIBRARY_DIR}")
    message(STATUS "Qt5_LIBRARIES = ${Qt5_LIBRARIES}")
    message(STATUS "Qt5_FOUND = ${Qt5_FOUND}")
    message(STATUS "Qt5_VERSION = ${Qt5_VERSION}")
    message(STATUS "Qt5_VERSION_MAJOR = ${Qt5_VERSION_MAJOR}")
    message(STATUS "Qt5_VERSION_MINOR = ${Qt5_VERSION_MINOR}")
    message(STATUS "Qt5_VERSION_PATCH = ${Qt5_VERSION_PATCH}")      
    message(STATUS "Qt5_INCLUDE_DIRS = ${Qt5_INCLUDE_DIRS}")
    message(STATUS "Qt5_LIBRARIES = ${Qt5_LIBRARIES}")
else()
    message(FATAL_ERROR "Qt5_FOUND not found")
endif()

##########
# OpenCascade
##########
#option(OpenCASCADE_DIR "" CACHE PATH "Path to OpenCASCADE installation")
# 7.7.0 COMPONENTS not found in CMakeLists.txt
find_package(OpenCASCADE REQUIRED )
if(OpenCASCADE_FOUND)
    message(STATUS "OpenCASCADE_DIR = ${OpenCASCADE_DIR}")
    message(STATUS "OpenCASCADE_INCLUDE_DIR = ${OpenCASCADE_INCLUDE_DIR}")
    message(STATUS "OpenCASCADE_LIBRARY_DIR = ${OpenCASCADE_LIBRARY_DIR}")
    message(STATUS "OpenCASCADE_LIBRARIES = ${OpenCASCADE_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenCASCADE not found")
endif()


##########
# VTK
##########
#option(VTK_DIR "" CACHE PATH "Path to VTK installation")
find_package(VTK REQUIRED COMPONENTS
    GUISupportQt
    RenderingCore
    InteractionStyle
    RenderingOpenGL2
    CommonCore
    CommonDataModel
    FiltersSources
    FiltersGeometry
    FiltersCore
    RenderingQt
    GUISupportQt
    RenderingCore
    IOCore
    IOLegacy 
)
if(VTK_FOUND)
    message(STATUS "VTK_INCLUDE_DIRS = ${VTK_INCLUDE_DIRS}")
    message(STATUS "VTK_LIBRARIES = ${VTK_LIBRARIES}")
    message(STATUS "VTK_DIR = ${VTK_DIR}")
else()
    message(FATAL_ERROR "VTK_DIR not found")
endif()

##########
# OpenCascade
##########
#option(OpenCASCADE_DIR "" CACHE PATH "Path to OpenCASCADE installation")
# 7.7.0 COMPONENTS not found in CMakeLists.txt
find_package(OpenCASCADE REQUIRED )
if(OpenCASCADE_FOUND)
    message(STATUS "OpenCASCADE_DIR = ${OpenCASCADE_DIR}")
    message(STATUS "OpenCASCADE_INCLUDE_DIR = ${OpenCASCADE_INCLUDE_DIR}")
    message(STATUS "OpenCASCADE_LIBRARY_DIR = ${OpenCASCADE_LIBRARY_DIR}")
    message(STATUS "OpenCASCADE_LIBRARIES = ${OpenCASCADE_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenCASCADE not found")
endif()


##########
# VTK
##########
#option(VTK_DIR "" CACHE PATH "Path to VTK installation")
find_package(VTK REQUIRED COMPONENTS
    GUISupportQt
    RenderingCore
    InteractionStyle
    RenderingOpenGL2
    CommonCore
    CommonDataModel
    FiltersSources
    FiltersGeometry
    FiltersCore
    RenderingQt
    GUISupportQt
    RenderingCore
    IOCore
    IOLegacy 
)
if(VTK_FOUND)
    include(${VTK_USE_FILE})
    message(STATUS "VTK_DIR = ${VTK_DIR}")
    message(STATUS "VTK_INCLUDE_DIRS = ${VTK_INCLUDE_DIRS}")
    message(STATUS "VTK_LIBRARIES = ${VTK_LIBRARIES}")
    message(STATUS "VTK_VERSION = ${VTK_VERSION}")
else()
    message(FATAL_ERROR "VTK_DIR not found")
endif()



##########
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(SOURCES
    src/MainWindow.h
    src/MainWindow.cpp
    src/VtkOccView.h
    src/VtkOccView.cpp
    src/main.cpp
)

add_executable(Qt_VTK_OCC ${SOURCES})

target_link_libraries(Qt_VTK_OCC
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Gui
    VTK::GUISupportQt
    VTK::RenderingQt
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
    VTK::FiltersSources
    VTK::FiltersGeometry
    VTK::FiltersCore
    VTK::CommonCore
    VTK::CommonDataModel
    VTK::IOCore
    VTK::IOLegacy
    # FoundationClasses
    ${OpenCASCADE_LIBRARY_DIR}/TKernel.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKMath.lib
    # ModelingData
    ${OpenCASCADE_LIBRARY_DIR}/TKG2d.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKG3d.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKGeomBase.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKBRep.lib
    # ModelingAlgorithms
    ${OpenCASCADE_LIBRARY_DIR}/TKBO.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKBool.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKGeomAlgo.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKHLR.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKMesh.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKPrim.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKShHealing.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKTopAlgo.lib
    # Visualization
    #${OpenCASCADE_LIBRARY_DIR}/TKMeshVS.lib
    #${OpenCASCADE_LIBRARY_DIR}/TKOpenGl.lib
    #${OpenCASCADE_LIBRARY_DIR}/TKService.lib
    #${OpenCASCADE_LIBRARY_DIR}/TKV3d.lib
    # ApplicationFramework
    ${OpenCASCADE_LIBRARY_DIR}/TKBin.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKBinL.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKBinXCAF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKCAF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKCDF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKLCAF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKVCAF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKXml.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKXmlL.lib
    # DataExchange
    ${OpenCASCADE_LIBRARY_DIR}/TKXCAF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKXmlXCAF.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKXSBase.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKSTEP.lib
    ${OpenCASCADE_LIBRARY_DIR}/TKSTEPBase.lib
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCASCADE_INCLUDE_DIR}
)

install(TARGETS Qt_VTK_OCC DESTINATION bin)
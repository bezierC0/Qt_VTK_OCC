cmake_minimum_required(VERSION 3.12)
project(CADViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########
# Qt
##########
find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL Gui)


##########
# OpenCascade
##########
find_package(OpenCASCADE REQUIRED )
if(OpenCASCADE_FOUND)
    message(STATUS "OpenCASCADE found")
    message(STATUS "OpenCASCADE_LIBRARY_DIR = ${OpenCASCADE_LIBRARY_DIR}")
    message(STATUS "OpenCASCADE_LIBRARIES = ${OpenCASCADE_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenCASCADE not found")
endif()


##########
# VTK
##########
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



set(CMAKE_AUTOMOC ON)
include(${VTK_USE_FILE}) 
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OpenCASCADE_INCLUDE_DIR}
    ${VTK_INCLUDE_DIRS}
)

set(SOURCES
    src/MainWindow.h
    src/MainWindow.cpp
    src/VtkOccView.h
    src/VtkOccView.cpp
    src/main.cpp
)

add_executable(CADViewer ${SOURCES})

target_link_libraries(CADViewer
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

foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} debug ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
  target_link_libraries(${PROJECT_NAME} optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:DEBUG>:${OpenCASCADE_BINARY_DIR}>$<$<NOT:$<CONFIG:DEBUG>>:${OpenCASCADE_BINARY_DIR}>;%PATH%")

install(TARGETS CADViewer DESTINATION bin)
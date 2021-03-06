# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#    Kathleen Biagas, Tue Feb 5 15:15:27 PST 2013
#    Removed GUISupport, we use VTK's version now.
#
#    Kevin Griffin, Tue Apr 25 11:43:15 PDT 2017
#    Added Cocoa framework for OSX helper function.
#
#****************************************************************************

set(VTKQT_SOURCES
    vtkQtRenderWindow.C
    vtkQtImagePrinter.C
)

if(APPLE)
    list(APPEND VTKQT_SOURCES osxHelper.mm)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${VISIT_BINARY_DIR}/include
    ${VISIT_SOURCE_DIR}/include
    ${VISIT_SOURCE_DIR}/vtkqt
    ${VISIT_SOURCE_DIR}/common/utility
    ${VTK_INCLUDE_DIRS}
)

add_library(vtkqt ${VTKQT_SOURCES})

# Specify the libraries to link against on Windows & Mac
target_link_libraries(vtkqt 
    vtkCommonCore vtkGUISupportQt vtkGUISupportQtOpenGL vtkIOImage
    vtkRenderingOpenGL2 vtkRenderingFreeType ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${OPENGL_LIBRARIES})

if(HAVE_OSMESA)
    target_link_libraries(vtkqt ${OSMESA_LIBRARIES})
elseif(HAVE_EGL)
    target_link_libraries(vtkqt ${EGL_LIBRARIES})
endif()

if(APPLE)
    set_target_properties(vtkqt PROPERTIES
        LINK_FLAGS "-framework Cocoa"
    )
endif()

VISIT_INSTALL_TARGETS(vtkqt)


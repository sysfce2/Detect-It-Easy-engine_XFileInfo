include_directories(${CMAKE_CURRENT_LIST_DIR})

if (NOT DEFINED XFILEINFO_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/xfileinfo.cmake)
    set(XFILEINFOWIDGET_SOURCES ${XFILEINFOWIDGET_SOURCES} ${XFILEINFO_SOURCES})
endif()
if (NOT DEFINED XDIALOGPROCESS_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/../FormatDialogs/xdialogprocess.cmake)
    set(XFILEINFOWIDGET_SOURCES ${XFILEINFOWIDGET_SOURCES} ${XDIALOGPROCESS_SOURCES})
endif()

set(XFILEINFOWIDGET_SOURCES
    ${XFILEINFOWIDGET_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfowidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfowidget.h
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfowidget.ui
    ${CMAKE_CURRENT_LIST_DIR}/dialogxfileinfoprocess.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dialogxfileinfoprocess.h
    ${CMAKE_CURRENT_LIST_DIR}/dialogxfileinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dialogxfileinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/dialogxfileinfo.ui
)

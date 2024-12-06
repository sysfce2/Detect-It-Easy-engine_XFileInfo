include_directories(${CMAKE_CURRENT_LIST_DIR})

if (NOT DEFINED XFORMATS_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/../Formats/xformats.cmake)
    set(XFILEINFO_SOURCES ${XFILEINFO_SOURCES} ${XFORMATS_SOURCES})
endif()
if (NOT DEFINED XDEX_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/../XDEX/xdex.cmake)
    set(XFILEINFO_SOURCES ${XFILEINFO_SOURCES} ${XDEX_SOURCES})
endif()
if (NOT DEFINED XPDF_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/../XPDF/xpdf.cmake)
    set(XFILEINFO_SOURCES ${XFILEINFO_SOURCES} ${XPDF_SOURCES})
endif()

include(${CMAKE_CURRENT_LIST_DIR}/../XArchive/xarchives.cmake)

set(XFILEINFO_SOURCES
    ${XFILEINFO_SOURCES}
    ${XFORMATS_SOURCES}
    ${XDEX_SOURCES}
    ${XPDF_SOURCES}
    ${XARCHIVES_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfoitem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfoitem.h
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfomodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xfileinfomodel.h
)

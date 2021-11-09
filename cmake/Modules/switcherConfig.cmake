INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SWITCHER switcher)

FIND_PATH(
    SWITCHER_INCLUDE_DIRS
    NAMES switcher/api.h
    HINTS $ENV{SWITCHER_DIR}/include
        ${PC_SWITCHER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SWITCHER_LIBRARIES
    NAMES gnuradio-switcher
    HINTS $ENV{SWITCHER_DIR}/lib
        ${PC_SWITCHER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/switcherTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SWITCHER DEFAULT_MSG SWITCHER_LIBRARIES SWITCHER_INCLUDE_DIRS)
MARK_AS_ADVANCED(SWITCHER_LIBRARIES SWITCHER_INCLUDE_DIRS)

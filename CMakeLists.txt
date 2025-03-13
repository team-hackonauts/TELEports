project(teleports C CXX)
cmake_minimum_required(VERSION 3.0.0)
include(FindPkgConfig)

# Use CCache speed up build process
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Quick)
find_package(Qt5Concurrent)
find_package(Qt5QuickControls2)

# Automatically create moc files
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Components PATH
execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE ARCH_TRIPLET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_IMPORTS_DIR "lib/${ARCH_TRIPLET}")

set(PROJECT_NAME "teleports")
set(FULL_PROJECT_NAME "teleports.ubports")
set(DATA_DIR ${CMAKE_INSTALL_PREFIX})
set(DESKTOP_FILE_NAME ${PROJECT_NAME}.desktop)
set(CURRENT_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs)

# Sets BUILD_VERSION: Either tag of the current git HEAD or devel build version with git hash
execute_process(
  COMMAND git describe --tags --abbrev=0 --exact-match
  OUTPUT_VARIABLE BUILD_VERSION_RAW
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
  )
if(NOT BUILD_VERSION_RAW)
  execute_process(
    COMMAND git describe --tags --abbrev=0
    OUTPUT_VARIABLE LAST_VERSION_RAW
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    )
  execute_process(
    COMMAND git rev-parse --short HEAD
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    )
  string(TIMESTAMP BUILD_VERSION_RAW "${LAST_VERSION_RAW}.%y%m%d%H%M%S" UTC)
  message(STATUS "Development build. Git hash is: ${GIT_HASH}")
endif(NOT BUILD_VERSION_RAW)
string(SUBSTRING ${BUILD_VERSION_RAW} 1 -1 BUILD_VERSION)
message(STATUS "Build version is: ${BUILD_VERSION}")

#Version for the app is set in app/CMakeLists.txt
configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json DESTINATION ${DATA_DIR})
install(FILES ${PROJECT_NAME}.apparmor DESTINATION ${DATA_DIR})
install(FILES ${PROJECT_NAME}.content-hub DESTINATION ${DATA_DIR})
install(FILES ${PROJECT_NAME}.url-dispatcher DESTINATION ${DATA_DIR})
install(DIRECTORY assets DESTINATION ${DATA_DIR})

# Translations
file(GLOB_RECURSE I18N_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/po push/*.cpp libs/qtdlib/*.cpp app/qml/*.qml app/qml/*.js)
list(APPEND I18N_SRC_FILES ${DESKTOP_FILE_NAME}.in.h)

find_program(INTLTOOL_MERGE intltool-merge)
if(NOT INTLTOOL_MERGE)
    message(FATAL_ERROR "Could not find intltool-merge, please install the intltool package")
endif()
find_program(INTLTOOL_EXTRACT intltool-extract)
if(NOT INTLTOOL_EXTRACT)
    message(FATAL_ERROR "Could not find intltool-extract, please install the intltool package")
endif()

add_custom_target(${DESKTOP_FILE_NAME} ALL
    COMMENT "Merging translations into ${DESKTOP_FILE_NAME}..."
    COMMAND LC_ALL=C ${INTLTOOL_MERGE} -d -u ${CMAKE_SOURCE_DIR}/po ${CMAKE_SOURCE_DIR}/${DESKTOP_FILE_NAME}.in ${DESKTOP_FILE_NAME}
    COMMAND sed -i 's/${PROJECT_NAME}-//g' ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_NAME}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_NAME} DESTINATION ${DATA_DIR})

add_subdirectory(po)
add_subdirectory(libs)
add_subdirectory(app)
add_subdirectory(push)
add_subdirectory(common)

# Make source files visible in qtcreator
# We don't need to add plugin sources here as they get exposed
# via the library target.
file(GLOB_RECURSE PROJECT_SRC_FILES
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    qml/*.qml
    qml/*.js
    *.json
    *.json.in
    *.apparmor
    *.desktop.in
)

add_custom_target(${PROJECT_NAME}_FILES ALL SOURCES ${PROJECT_SRC_FILES})

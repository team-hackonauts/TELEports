cmake_minimum_required(VERSION 3.5)
set(PLUGIN "rLottieQml")
project(${PLUGIN} VERSION 0.1 LANGUAGES C CXX)

set(
    SRC
    src/plugin.cpp
    src/qlottieframeprovider.cpp
    # qml/qml.qrc
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# qt5_add_resources(SRC qml/qml.qrc)
add_library(${PLUGIN} MODULE ${SRC})
# set_target_properties(${PLUGIN} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGIN})
# qt5_use_modules(${PLUGIN} Qml Quick DBus Multimedia)

find_package(Qt5 COMPONENTS Core Qml Quick Multimedia CONFIG REQUIRED)
# set(rlottie_DIR "${CMAKE_CURRENT_BINARY_DIR}/../rlottie/install/lib/cmake/rlottie")
find_package(rlottie REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(QuaZip REQUIRED)

target_include_directories(${PLUGIN} SYSTEM PRIVATE ${QUAZIP_INCLUDE_DIR})
target_link_libraries(${PLUGIN} ${QUAZIP_LIBRARIES} rlottie::rlottie)
target_link_libraries(${PLUGIN}
  # PUBLIC
  Qt5::Qml
  Qt5::Quick
  Qt5::Core
  Qt5::Multimedia
)


execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE ARCH_TRIPLET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_IMPORTS_DIR "/lib/${ARCH_TRIPLET}")


##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/rLottieQml)
install(TARGETS ${PLUGIN}
    EXPORT rLottieQmlExport
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
  EXPORT rLottieQmlExport
  DESTINATION ${INSTALL_CONFIGDIR}
  NAMESPACE rLottieQml::
  FILE rLottieQmlExport.cmake
)

install(TARGETS ${PLUGIN} DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN}/QLottieFrameProvider/)
install(FILES src/qmldir DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN}/QLottieFrameProvider/)
install(FILES qml/LottieAnimation.qml DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN}/QLottieFrameProvider/)

export(EXPORT rLottieQmlExport FILE ${CMAKE_BINARY_DIR}/rLottieQmlExport.cmake)

#####################
# ConfigVersion file
##
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/rLottieQmlConfigVersion.cmake
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/rLottieQmlConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/rLottieQmlConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install all the helper files
install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/rLottieQmlConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/rLottieQmlConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
# configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#     ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#     COPYONLY)

export(EXPORT rLottieQmlExport
    FILE ${CMAKE_CURRENT_BINARY_DIR}/rLottieQmlExport.cmake
    NAMESPACE rLottieQml::)

#Register package in the User Package Registry
export(PACKAGE rLottieQml)

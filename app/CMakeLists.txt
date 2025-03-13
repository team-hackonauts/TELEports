find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)

find_package(QuickFlux REQUIRED)
find_package(rlottie REQUIRED)
find_package(rLottieQml REQUIRED)

#"qtdclient.cpp" "qtdthread.cpp" "qml.qrc"
add_definitions(-DBUILD_VERSION="${BUILD_VERSION}" -DGIT_HASH="${GIT_HASH}" -DQT_MESSAGELOGCONTEXT)
add_executable(${PROJECT_NAME} "main.cpp" "messagedelegatemap.cpp" "messagecontentdelegatemap.cpp" "ui-tools/offloadingimageprovider.cpp" "qml/qml.qrc" "qml/icons/icons.qrc")
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::QuickControls2 QuickFlux::quickflux QTdlib rLottieQml::rLottieQml)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

list(APPEND QML_DIRS "plugins")
set(QML_IMPORT_PATH "${QML_DIRS}")

find_package(Qt5Gui REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(SOURCES
    push.cpp
    pushhelper.cpp)

add_executable(push ${SOURCES} )

target_link_libraries(push Qt5::Core Qt5::Widgets Qt5::Network Qt5::DBus Qt5::Sql auxdb)

install(FILES push-apparmor.json DESTINATION push)
install(FILES push-helper.json DESTINATION push)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/push DESTINATION push)

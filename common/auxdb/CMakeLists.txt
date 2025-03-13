find_package(Qt5Sql REQUIRED)
find_package(Qt5DBus REQUIRED)

set(SOURCES
    auxdb.cpp
    avatarmaptable.cpp
    postal-client.cpp
)

add_library(auxdb STATIC ${SOURCES} )
target_link_libraries(auxdb Qt5::Core Qt5::Sql Qt5::DBus)

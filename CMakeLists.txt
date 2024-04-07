cmake_minimum_required(VERSION 3.14)

project(code-challenge-ubuntu VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(HEADERS UbuntuReleaseInfoProvider.h)
set(SOURCES UbuntuReleaseInfoProvider.cpp main.cpp)

add_executable(code-challenge-ubuntu ${HEADERS} ${SOURCES})
target_link_libraries(code-challenge-ubuntu Qt6::Core Qt6::Network)

include(GNUInstallDirs)
install(TARGETS code-challenge-ubuntu
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

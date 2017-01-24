project(nterm CXX)
cmake_minimum_required(VERSION 3.0)

include(FindPkgConfig)

pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)
pkg_check_modules(VTE REQUIRED vte-2.91)

set(CMAKE_CXX_FLAGS "-std=c++1z -O3 -Wall -Wextra -pedantic -Werror -DNDEBUG")
add_definitions(-DNTERM_VERSION="0.1")

include_directories(${GTK3_INCLUDE_DIRS} ${VTE_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${VTE_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp src/terminal.cpp src/config.cpp src/nterm.cpp)
target_link_libraries(${PROJECT_NAME} ${VTE_LIBRARIES} ${GTK3_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)


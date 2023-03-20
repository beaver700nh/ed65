cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "ed65")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

project(${PROJECT_NAME})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/common.cpp
  src/bar.cpp
  src/text.cpp
)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

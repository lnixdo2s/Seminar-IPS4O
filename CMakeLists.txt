cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Seminar-IPS4O)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(${PROJECT_NAME}
  src/first_test.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/ips4o)
target_link_libraries(${PROJECT_NAME} PRIVATE ips4o)

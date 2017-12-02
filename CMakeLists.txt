cmake_minimum_required (VERSION 3.0)
project(Anamoly)
if (CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-std=c++11)
  set(CMAKE_CXX_FLAGS "-std=c++11  -O3 ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-std=c++11)
  set(CMAKE_CXX_FLAGS "-std=c++11 -O3 ${CMAKE_CXX_FLAGS}")
endif()
add_executable (Anamoly
  main.cpp
  Memory.cpp
  Memory.hpp
)

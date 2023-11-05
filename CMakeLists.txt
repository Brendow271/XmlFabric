cmake_minimum_required(VERSION 3.24)
project(XmlFabric)

set(CMAKE_CXX_STANDARD 17)

add_executable(XmlFabric main.cpp xml.h xml.cpp XMLResource.h XMLResource.cpp)

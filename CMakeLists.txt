cmake_minimum_required(VERSION 3.21.3)

project(tree)

set(sashka3_src main.cpp CVector.cpp)
set(sashka3_hdr clist.h buf.h)

add_executable(${PROJECT_NAME} ${sashka2_src} ${sashka2_hdr})
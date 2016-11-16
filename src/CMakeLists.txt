cmake_minimum_required(VERSION 2.8.6)
project(le)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Freetype REQUIRED)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR})


set(LE_SRCS
  render_text.cc
  model/text_run.cc
  model/paragraph.cc
  controller/paragraph_controller.cc)


add_library(le SHARED ${LE_SRCS})







cmake_minimum_required(VERSION 2.8.6)
project(le_web)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories( 
  ${CMAKE_CURRENT_LIST_DIR}
  "/usr/include/"
  )

link_directories( 
  "/usr/local/lib/"
  )


set(LE_WEB_SRCS
  server.cc
  )


add_library(le_web SHARED ${LE_WEB_SRCS})
target_link_libraries(le_web LINK_PUBLIC websockets le jsoncpp)

add_executable(webserver main.cc)
target_link_libraries(webserver LINK_PUBLIC le_web)

configure_file(index.html index.html copyonly)

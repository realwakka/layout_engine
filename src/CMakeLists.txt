cmake_minimum_required(VERSION 2.8.6)
project(le)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

find_package(Freetype REQUIRED)

MESSAGE( STATUS "FREETYPE_INC_DIRS:" ${FREETYPE_INCLUDE_DIR_freetype2} )

if(FREETYPE_FOUND)
  set(FREETYPE2_INCLUDE ${FREETYPE_INCLUDE_DIR_freetype2})
else()
  message( FATAL_ERROR "cannot build without freetype" )
endif()

include_directories( 
    ${CMAKE_CURRENT_LIST_DIR}
    ${FREETYPE2_INCLUDE}
    "/usr/include/"
)

set(LE_SRCS
  render_text.cc
  model/text_run.cc
  model/enter_run.cc
  model/paragraph.cc
  model/character.cc
  model/word.cc
  model/glyph/glyph.cc
  controller/paragraph_controller.cc)


add_library(le SHARED ${LE_SRCS})



add_executable(test test.cc)
target_link_libraries(test LINK_PUBLIC le)








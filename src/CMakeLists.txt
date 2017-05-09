cmake_minimum_required(VERSION 2.8.6)
project(le)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

find_package(Freetype REQUIRED)

MESSAGE( STATUS "FREETYPE_INC_DIRS:" ${FREETYPE_INCLUDE_DIR_freetype2} )

if(FREETYPE_FOUND)
  set(FREETYPE2_INCLUDE ${FREETYPE_INCLUDE_DIRS})
else()
  message( FATAL_ERROR "cannot build without freetype" )
endif()

include_directories( 
    ${CMAKE_CURRENT_LIST_DIR}
    ${FREETYPE_INCLUDE_DIRS}
    "/usr/include/"
)

set(LE_SRCS
  render_text.cc
  model/text_run.cc
  model/enter_run.cc
  model/paragraph.cc
  model/character/character.cc
  model/character/basic_character.cc
  model/character/space_character.cc
  model/character/enter_character.cc
  model/word.cc
  model/glyph/glyph.cc
  model/glyph/span.cc
  model/face/face.cc
  model/face/face_manager.cc
  model/run.cc
  model/prop/run_prop.cc
  model/prop/paragraph_prop.cc
  model/prop/font.cc
  model/prop/underline/single_underline.cc
  model/prop/section_prop.cc
  model/selection/caret_selection.cc
  model/selection/block_selection.cc
  model/selection/selection_util.cc
  model/document.cc

  view/view.cc
  view/document_view.cc
  view/paragraph_view.cc
  view/line_view.cc
  view/word_view.cc
  view/character/character_view.cc
  view/character/space_character_view.cc
  view/selection/caret_selection_view.cc
  view/selection/block_selection_view.cc
  view/character/enter_character_view.cc
  view/run/run_view.cc
  view/page/page_view.cc
  view/page/column_view.cc
  view/layer.cc
  view/hititem.cc

  view/linebreaker/word_linebreaker.cc
  
  controller/enter_char_controller.cc
  controller/block_selection_controller.cc
  controller/event/mouse_event.cc
  controller/event/key_event.cc
  controller/event/event.cc
  controller/command/insert_char_command.cc
  controller/command/delete_char_command.cc
  controller/command/set_selection_command.cc

  controller/command/commit.cc
  controller/command/commit_tree.cc
  
  graphic/canvas.cc
  graphic/bitmap_canvas.cc
  graphic/svg_canvas.cc
  graphic/point.cc
  graphic/matrix.cc
  graphic/bitmap.cc
  graphic/paint.cc
  )


add_library(le SHARED ${LE_SRCS})
target_link_libraries(le LINK_PUBLIC freetype fontconfig)


add_executable(test_driver test.cc)
target_link_libraries(test_driver LINK_PUBLIC le)

add_subdirectory(web)








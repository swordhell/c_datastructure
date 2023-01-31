
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h" )

add_executable( test_merkle_tree ${SRC})

set_target_properties(test_merkle_tree PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../bin"
)

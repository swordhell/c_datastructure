
file(GLOB_RECURSE SRC "src/*.c" "src/*.h" )

add_executable( test_hash ${SRC})
add_dependencies(test_hash common )

set_target_properties(test_hash PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../bin"
)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(test_hash common )
ELSE ()
    target_link_libraries(test_hash common )
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

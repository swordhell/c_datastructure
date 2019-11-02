
file(GLOB_RECURSE SRC "src/*.c" "src/*.h" )
add_library(common STATIC ${SRC})

set_target_properties(common PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../bin"
)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")

    target_link_libraries( common )

ELSE ()
    target_link_libraries(common )
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

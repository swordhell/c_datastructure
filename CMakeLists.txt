cmake_minimum_required (VERSION 3.2)
project (learn_c)

set(CMAKE_BUILD_TYPE Debug)


IF (CMAKE_SYSTEM_NAME MATCHES "Windows")

    add_definitions(-DWIN32)
    add_definitions(-DLUA_BUILD_AS_DLL)
    add_definitions(-DLUA_LIB)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

ELSE ()
    add_definitions(-DLinux)
    set(CMAKE_C_FLAGS "-std=c99")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

include_directories( ${CMAKE_CURRENT_LIST_DIR}/common/src )

#add_subdirectory(common)
#add_subdirectory(test_hash)
#add_subdirectory(test_list)
#add_subdirectory(test_heapsort)
add_subdirectory(test_rbtree)


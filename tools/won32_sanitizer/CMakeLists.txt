# won32_sanitizer.exe
add_executable(won32_sanitizer won32_sanitizer.cpp)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(won32_sanitizer PROPERTIES OUTPUT_NAME "won32_sanitizer64")
endif()
target_link_libraries(won32_sanitizer TypeSystem)

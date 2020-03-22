# cparser.exe
add_executable(cparser Main.cpp mzc2mini.cpp)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(cparser PROPERTIES OUTPUT_NAME "cparser64")
endif()
target_link_libraries(cparser TypeSystem)

add_executable(dllexpdumper dllexpdumper.cpp)
target_link_libraries(dllexpdumper PRIVATE comdlg32 imagehlp)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(dllexpdumper PROPERTIES OUTPUT_NAME "dllexpdumper64")
endif()

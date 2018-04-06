file(GLOB source_files "*.cpp" "*.h")
add_library(nwnx_ee SHARED ${common_source_files} ${source_files})
target_link_libraries(nwnx_ee)

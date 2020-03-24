
add_library(thirdparty_catch2 INTERFACE)
target_include_directories(thirdparty_catch2 INTERFACE catch2/inc)
add_library(Catch2::Catch2 ALIAS thirdparty_catch2)

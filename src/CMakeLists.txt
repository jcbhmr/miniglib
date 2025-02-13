add_library(miniglib)
add_library(miniglib::miniglib ALIAS miniglib)
target_sources(miniglib PRIVATE
    "./garray.c"
    "./ghashtable.c"
    "./gstring.c"
)
target_include_directories(miniglib PUBLIC "../include/")
target_compile_features(miniglib PUBLIC c_std_23)

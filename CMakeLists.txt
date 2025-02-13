cmake_minimum_required(VERSION 3.30)

project(miniglib
    VERSION "2.81.0"
    DESCRIPTION "📄 Just the core GLib types: GString, GArray, and GHashTable"
    HOMEPAGE_URL "https://github.com/jcbhmr/miniglib"
    LANGUAGES C
)

add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_GENERATOR "ZIP")
include(CPack)

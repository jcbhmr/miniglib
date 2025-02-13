create_test_sourcelist(tests "tests_driver.c"
    "garray_test.c"
    "ghashtable_test.c"
    "gstring_test.c"
)
add_executable(tests ${tests})
add_executable(miniglib::tests ALIAS tests)
unset(tests)
target_link_libraries(tests PRIVATE miniglib)
add_test(NAME garray_test COMMAND tests garray_test)
add_test(NAME ghashtable_test COMMAND tests ghashtable_test)
add_test(NAME gstring_test COMMAND tests gstring_test)

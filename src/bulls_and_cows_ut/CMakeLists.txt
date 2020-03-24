
add_executable(bulls_and_cows_ut
    board_test.cpp
    bulls_and_cows_ut_main.cpp
    game_options_test.cpp
    game_solver_test.cpp
    input_test.cpp
    main_menu_test.cpp
    random_test.cpp
    )

add_test(NAME bulls_and_cows_ut COMMAND bulls_and_cows_ut)

target_link_libraries(bulls_and_cows_ut PRIVATE Catch2::Catch2 bulls_and_cows_lib)

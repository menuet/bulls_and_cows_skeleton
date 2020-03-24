
add_library(bulls_and_cows_lib
    board.cpp
    board.hpp
    game.cpp
    game.hpp
    game_options.cpp
    game_options.hpp
    game_solver.cpp
    game_solver.hpp
    input.cpp
    input.hpp
    main_menu.cpp
    main_menu.hpp
    random.cpp
    random.hpp
    )

target_include_directories(bulls_and_cows_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")


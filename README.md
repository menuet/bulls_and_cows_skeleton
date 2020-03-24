# How To Start

## Generate the Visual Studio solution

This is a one-time task.

In a terminal, type:
```
mkdir out
```

```
cd out
```

```
cmake ..
```

## Work with the solution in Visual Studio

Open the file **bulls_and_cows.sln** in the newly created sub-directory **out**.

# Projects Organization

- **bulls_and_cows_lib** is the library that contains most of the code
- **bulls_and_cows_prg** is the executable program that uses the library and launches the game
- **bulls_and_cows_ut** is the executable program that uses the library and runs the unit tests

# Work to Do

## Useful links

- https://en.wikipedia.org/wiki/Mastermind_(board_game)
- https://en.wikipedia.org/wiki/Bulls_and_Cows
- https://en.wikipedia.org/wiki/Mastermind_(board_game)#Algorithms

## Minimal Work

- In the sub-directory **src/bulls_and_cows_lib**:
  - In the file **game.cpp**, implement the body of the function **bulls_and_cows::user_plays_against_computer**
  - In the file **board.cpp** define the functions that are declared in **board.hpp** and use them to implement **bulls_and_cows::user_plays_against_computer**
- In the sub-directory **src/bulls_and_cows_ut**:
  - In the file **board_test.cpp**, try enabling/modifying the unit tests that were disabled
  - Try adding some additional unit tests

## Intermediate Bonuses

- In the sub-directory **src/bulls_and_cows_lib**:
  - In the file **game.cpp**, implement the body of the function **bulls_and_cows::configure_game_options**
  - In the file **game_options.cpp** define the functions that are declared in **game_options.hpp** and use them to implement **bulls_and_cows::configure_game_options**
- In the sub-directory **src/bulls_and_cows_ut**:
  - In the file **game_options_test.cpp**, try enabling/modifying the unit tests that were disabled
  - Try adding some additional unit tests
- Use a **github** account and save your work history in a public github repository
- Check with github actions that your work compiles on Windows and Linux and Mac

## Expert Bonuses

- In the sub-directory **src/bulls_and_cows_lib**:
  - In the file **game.cpp**, implement the body of the function **bulls_and_cows::computer_plays_against_computer**
  - In the file **game_solver.cpp** define the functions that are declared in **game_solver.hpp** and use them to implement **bulls_and_cows::computer_plays_against_computer**
- In the sub-directory **src/bulls_and_cows_ut**:
  - In the file **game_solver_test.cpp**, try enabling/modifying the unit tests that were disabled
  - Try adding some additional unit tests
- Try adding colors ([see ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors))
- Add anything you think about...

# Evaluation

- Readability
- Correctness
- Sources Organization
- Comments
- Unit tests
- ....

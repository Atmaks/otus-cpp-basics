cmake_minimum_required(VERSION 3.12)

project(03.guessing_game)

add_executable(main 
    main.cpp
)

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

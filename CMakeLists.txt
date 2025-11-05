cmake_minimum_required(VERSION 3.24)

project(a_simple_todo_list)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(todolist_test tests/todolist_test.cpp src/todolist.cpp)
add_executable(main main.cpp src/todolist.cpp)

target_link_libraries(todolist_test PRIVATE Catch2::Catch2WithMain)

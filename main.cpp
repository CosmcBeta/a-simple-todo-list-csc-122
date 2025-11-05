#include "src/todolist.hpp"

#include <iostream>

int main()
{
    ToDoList list {};

    list.add("Buy milk");
    list.add("Buy eggs");
    list.add("Prepare a lesson for CSC 122");
    list.add("Sow beet seeds");

    list.markComplete("Buy eggs");

    // Pretty prints a list of each of the four tasks above
    std::cout << list.getAll() << std::endl;

    // Pretty prints the task "Buy eggs"
    std::cout << list.getComplete() << std::endl;

    // Pretty prints the tasks "Buy milk",
    // "Prepare a lesson for CSC 122", and "Sow beet seeds"
    std::cout << list.getIncomplete() << std::endl;

    // Clears the to-do list
    list.clear();

    // Pretty prints a message saying that the list is empty
    std::cout << list.getAll() << std::endl;
}

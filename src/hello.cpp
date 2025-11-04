#include "hello.hpp"

#include <iostream>
#include <string>

void ToDoList::add(std::string name)
{
    toDoList[name] = false;
}

void ToDoList::markComplete(std::string name)
{
    toDoList[name] = true;
}

void ToDoList::printAll()
{
    std::cout << "To Do List:\n";
    for (const auto& [name, complete] : toDoList)
    {
        std::cout << name << "\n";
    }
}

void ToDoList::printComplete()
{
    std::cout << "Completed:\n";
    for (const auto& [name, complete] : toDoList)
    {
        if (complete)
        {
            std::cout << name << "\n";
        }
    }
}

void ToDoList::printIncomplete()
{
    std::cout << "Incomplete:\n";
    for (const auto& [name, complete] : toDoList)
    {
        if (!complete)
        {
            std::cout << name << "\n";
        }
    }
}

void ToDoList::clear()
{
    toDoList.clear();
}

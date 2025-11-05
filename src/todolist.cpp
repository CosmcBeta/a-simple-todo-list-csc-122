#include "todolist.hpp"

#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

void ToDoList::add(std::string name)
{
    toDoList[name] = false;
}

void ToDoList::markComplete(std::string name)
{
    try
    {
        toDoList.at(name) = true;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::string ToDoList::getAll() const
{
    if (toDoList.empty())
    {
        return "List is empty.";
    }

    std::stringstream ss {};
    ss << "To Do List:\n";
    for (const auto& [name, complete] : toDoList)
    {
        ss << name << "\n";
    }
    return ss.str();
}

std::string ToDoList::getComplete() const
{
    std::stringstream ss {};
    ss << "Completed:\n";
    for (const auto& [name, complete] : toDoList)
    {
        if (complete)
        {
            ss << name << "\n";
        }
    }
    if (ss.str() == "Completed:\n")
    {
        return "List is empty.";
    }
    else
    {
        return ss.str();
    }
}

std::string ToDoList::getIncomplete() const
{
    std::stringstream ss {};
    ss << "Incomplete:\n";
    for (const auto& [name, complete] : toDoList)
    {
        if (!complete)
        {
            ss << name << "\n";
        }
    }
    if (ss.str() == "Incomplete:\n")
    {
        return "List is empty.";
    }
    else
    {
        return ss.str();
    }
}

void ToDoList::clear()
{
    toDoList.clear();
}

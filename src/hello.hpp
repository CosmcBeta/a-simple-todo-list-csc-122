#pragma once

#include <string>
#include <map>

class ToDoList
{
public:
    ToDoList() = default;

    void add(std::string name);
    void markComplete(std::string name);

    void printAll();
    void printComplete();
    void printIncomplete();

    void clear();

private:
    std::map<std::string, bool> toDoList;
};

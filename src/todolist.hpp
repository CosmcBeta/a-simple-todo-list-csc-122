#pragma once

#include <string>
#include <map>

class ToDoList
{
public:
    ToDoList() = default;

    void add(std::string name);
    void markComplete(std::string name);
    void clear();

    std::string getAll() const;
    std::string getComplete() const;
    std::string getIncomplete() const;

private:
    std::map<std::string, bool> toDoList;
};

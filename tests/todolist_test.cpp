#include "../src/todolist.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

TEST_CASE("ToDoList starts empty")
{
    ToDoList list {};

    REQUIRE(list.getAll() == "List is empty.");
    REQUIRE(list.getComplete() == "List is empty.");
    REQUIRE(list.getIncomplete() == "List is empty.");
}

TEST_CASE("Adding a single task makes it appear in all and incomplete lists")
{
    ToDoList list {};
    list.add("Buy groceries");

    REQUIRE(list.getAll() == "To Do List:\nBuy groceries\n");
    REQUIRE(list.getIncomplete() == "Incomplete:\nBuy groceries\n");
    REQUIRE(list.getComplete() == "List is empty.");
}

TEST_CASE("Adding multiple tasks shows them all")
{
    ToDoList list {};
    list.add("Buy groceries");
    list.add("Walk the dog");
    list.add("Do laundry");

    std::string allTasks = list.getAll();
    REQUIRE(allTasks.find("Buy groceries") != std::string::npos);
    REQUIRE(allTasks.find("Walk the dog") != std::string::npos);
    REQUIRE(allTasks.find("Do laundry") != std::string::npos);

    std::string incompleteTasks = list.getIncomplete();
    REQUIRE(incompleteTasks.find("Buy groceries") != std::string::npos);
    REQUIRE(incompleteTasks.find("Walk the dog") != std::string::npos);
    REQUIRE(incompleteTasks.find("Do laundry") != std::string::npos);
}

TEST_CASE("Marking a task complete moves it to completed list")
{
    ToDoList list {};
    list.add("Buy groceries");
    list.markComplete("Buy groceries");

    REQUIRE(list.getAll() == "To Do List:\nBuy groceries\n");
    REQUIRE(list.getComplete() == "Completed:\nBuy groceries\n");
    REQUIRE(list.getIncomplete() == "List is empty.");
}

TEST_CASE("Marking multiple tasks complete shows them in completed list")
{
    ToDoList list {};
    list.add("Buy groceries");
    list.add("Walk the dog");
    list.add("Do laundry");

    list.markComplete("Buy groceries");
    list.markComplete("Do laundry");

    std::string completedTasks = list.getComplete();
    REQUIRE(completedTasks.find("Buy groceries") != std::string::npos);
    REQUIRE(completedTasks.find("Do laundry") != std::string::npos);
    REQUIRE(completedTasks.find("Walk the dog") == std::string::npos);

    std::string incompleteTasks = list.getIncomplete();
    REQUIRE(incompleteTasks.find("Walk the dog") != std::string::npos);
    REQUIRE(incompleteTasks.find("Buy groceries") == std::string::npos);
    REQUIRE(incompleteTasks.find("Do laundry") == std::string::npos);
}

TEST_CASE("Clear removes all tasks from the list")
{
    ToDoList list {};
    list.add("Buy groceries");
    list.add("Walk the dog");
    list.markComplete("Buy groceries");

    list.clear();

    REQUIRE(list.getAll() == "List is empty.");
    REQUIRE(list.getComplete() == "List is empty.");
    REQUIRE(list.getIncomplete() == "List is empty.");
}

TEST_CASE("Adding duplicate task names overwrites the previous task")
{
    ToDoList list {};
    list.add("Buy groceries");
    list.markComplete("Buy groceries");
    list.add("Buy groceries");

    REQUIRE(list.getIncomplete() == "Incomplete:\nBuy groceries\n");
    REQUIRE(list.getComplete() == "List is empty.");
}

TEST_CASE("Marking a non-existent task complete does not add it")
{
    ToDoList list {};
    list.markComplete("Non-existent task");

    REQUIRE(list.getComplete() == "List is empty.");
    REQUIRE(list.getIncomplete() == "List is empty.");
    REQUIRE(list.getAll() == "List is empty.");
}

TEST_CASE("Adding task with empty string")
{
    ToDoList list {};
    list.add("");

    std::string allTasks = list.getAll();
    REQUIRE(allTasks == "To Do List:\n\n");
}

TEST_CASE("Tasks with special characters are handled correctly")
{
    ToDoList list {};
    list.add("Buy milk & eggs");
    list.add("Read \"1984\"");
    list.add("Calculate 2+2=4");

    std::string allTasks = list.getAll();
    REQUIRE(allTasks.find("Buy milk & eggs") != std::string::npos);
    REQUIRE(allTasks.find("Read \"1984\"") != std::string::npos);
    REQUIRE(allTasks.find("Calculate 2+2=4") != std::string::npos);
}

TEST_CASE("Clear on empty list has no effect")
{
    ToDoList list {};
    list.clear();

    REQUIRE(list.getAll() == "List is empty.");
}

TEST_CASE("Marking same task complete multiple times keeps it complete")
{
    ToDoList list {};
    list.add("Buy groceries");
    list.markComplete("Buy groceries");
    list.markComplete("Buy groceries");

    REQUIRE(list.getComplete() == "Completed:\nBuy groceries\n");
    REQUIRE(list.getIncomplete() == "List is empty.");
}

TEST_CASE("All tasks completed shows empty incomplete list")
{
    ToDoList list {};
    list.add("Task 1");
    list.add("Task 2");
    list.markComplete("Task 1");
    list.markComplete("Task 2");

    REQUIRE(list.getIncomplete() == "List is empty.");
    std::string completedTasks = list.getComplete();
    REQUIRE(completedTasks.find("Task 1") != std::string::npos);
    REQUIRE(completedTasks.find("Task 2") != std::string::npos);
}

TEST_CASE("Mixed complete and incomplete tasks")
{
    ToDoList list {};
    list.add("Task 1");
    list.add("Task 2");
    list.add("Task 3");
    list.add("Task 4");
    list.markComplete("Task 2");
    list.markComplete("Task 4");

    std::string allTasks = list.getAll();
    REQUIRE(allTasks.find("Task 1") != std::string::npos);
    REQUIRE(allTasks.find("Task 2") != std::string::npos);
    REQUIRE(allTasks.find("Task 3") != std::string::npos);
    REQUIRE(allTasks.find("Task 4") != std::string::npos);

    std::string completedTasks = list.getComplete();
    REQUIRE(completedTasks.find("Task 2") != std::string::npos);
    REQUIRE(completedTasks.find("Task 4") != std::string::npos);
    REQUIRE(completedTasks.find("Task 1") == std::string::npos);
    REQUIRE(completedTasks.find("Task 3") == std::string::npos);

    std::string incompleteTasks = list.getIncomplete();
    REQUIRE(incompleteTasks.find("Task 1") != std::string::npos);
    REQUIRE(incompleteTasks.find("Task 3") != std::string::npos);
    REQUIRE(incompleteTasks.find("Task 2") == std::string::npos);
    REQUIRE(incompleteTasks.find("Task 4") == std::string::npos);
}

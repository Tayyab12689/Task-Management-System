#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Task {
private:
    int id;
    std::string description;
    std::string dueDate;
    bool isCompleted;

public:
    Task(int taskId, const std::string& desc, const std::string& date)
        : id(taskId), description(desc), dueDate(date), isCompleted(false) {}

    int getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getDueDate() const { return dueDate; }
    bool getStatus() const { return isCompleted; }

    void setDescription(const std::string& desc) { description = desc; }
    void setDueDate(const std::string& date) { dueDate = date; }
    void markComplete() { isCompleted = true; }
    void markIncomplete() { isCompleted = false; }
};

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;

public:
    TaskManager() : nextId(1) {}

    void addTask(const std::string& description, const std::string& dueDate) {
        tasks.push_back(Task(nextId++, description, dueDate));
        std::cout << "Task added successfully.\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks found.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            const Task& task = tasks[i];
            std::cout << "ID: " << task.getId()
                      << ", Desc: " << task.getDescription()
                      << ", Due: " << task.getDueDate()
                      << ", Status: " << (task.getStatus() ? "Complete" : "Incomplete") << "\n";
        }
    }

    void editTask(int id) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].getId() == id) {
                std::string newDesc, newDate;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter new description: ";
                std::getline(std::cin, newDesc);
                std::cout << "Enter new due date: ";
                std::getline(std::cin, newDate);
                tasks[i].setDescription(newDesc);
                tasks[i].setDueDate(newDate);
                std::cout << "Task updated.\n";
                return;
            }
        }
        std::cout << "Task ID not found.\n";
    }

    void deleteTask(int id) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].getId() == id) {
                tasks.erase(tasks.begin() + i);
                std::cout << "Task deleted.\n";
                return;
            }
        }
        std::cout << "Task ID not found.\n";
    }

    void markTask(int id, bool complete) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].getId() == id) {
                if (complete)
                    tasks[i].markComplete();
                else
                    tasks[i].markIncomplete();
                std::cout << "Task status updated.\n";
                return;
            }
        }
        std::cout << "Task ID not found.\n";
    }
};

void displayMenu() {
    std::cout << "\n---- Task Manager ----\n"
              << "1. Add Task\n"
              << "2. View Tasks\n"
              << "3. Edit Task\n"
              << "4. Delete Task\n"
              << "5. Mark Task Complete\n"
              << "0. Exit\n"
              << "Select option: ";
}

int main() {
    TaskManager manager;
    int choice, id;
    std::string desc, dueDate;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter description: ";
                std::getline(std::cin, desc);
                std::cout << "Enter due date: ";
                std::getline(std::cin, dueDate);
                manager.addTask(desc, dueDate);
                break;

            case 2:
                manager.viewTasks();
                break;

            case 3:
                std::cout << "Enter task ID to edit: ";
                std::cin >> id;
                manager.editTask(id);
                break;

            case 4:
                std::cout << "Enter task ID to delete: ";
                std::cin >> id;
                manager.deleteTask(id);
                break;

            case 5:
                std::cout << "Enter task ID to mark complete: ";
                std::cin >> id;
                manager.markTask(id, true);
                break;

            case 0:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }
}


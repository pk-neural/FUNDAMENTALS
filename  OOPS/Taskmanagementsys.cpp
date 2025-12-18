// =======================================================
// MINI PROJECT: Task Management System
// Language: C++
// Description:
// A menu-driven task manager that allows users
// to create, update, delete, and track tasks.
// =======================================================

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// ---------------- CLASS: Task ----------------
class Task {
private:
    int taskId;
    string title;
    string description;
    int priority;      // 1 = High, 2 = Medium, 3 = Low
    bool completed;

public:
    Task(int id, string t, string d, int p) {
        taskId = id;
        title = t;
        description = d;
        priority = p;
        completed = false;
    }

    int getId() const {
        return taskId;
    }

    int getPriority() const {
        return priority;
    }

    bool isCompleted() const {
        return completed;
    }

    void markCompleted() {
        completed = true;
    }

    void display() const {
        cout << "Task ID     : " << taskId << endl;
        cout << "Title       : " << title << endl;
        cout << "Description : " << description << endl;
        cout << "Priority    : ";
        if (priority == 1) cout << "High";
        else if (priority == 2) cout << "Medium";
        else cout << "Low";
        cout << endl;
        cout << "Status      : " 
             << (completed ? "Completed" : "Pending") << endl;
        cout << "-----------------------------------\n";
    }
};

// ---------------- CLASS: TaskManager ----------------
class TaskManager {
private:
    vector<Task> tasks;
    map<int, int> taskIndex;   // TaskID -> index in vector
    int nextId;

public:
    TaskManager() {
        nextId = 1;
    }

    void addTask() {
        string title, desc;
        int priority;

        cin.ignore();
        cout << "Enter Task Title: ";
        getline(cin, title);

        cout << "Enter Description: ";
        getline(cin, desc);

        cout << "Enter Priority (1-High, 2-Medium, 3-Low): ";
        cin >> priority;

        Task t(nextId, title, desc, priority);
        tasks.push_back(t);
        taskIndex[nextId] = tasks.size() - 1;

        cout << "Task Added Successfully with ID " << nextId << endl;
        nextId++;
    }

    void markTaskCompleted() {
        int id;
        cout << "Enter Task ID: ";
        cin >> id;

        if (taskIndex.find(id) != taskIndex.end()) {
            tasks[taskIndex[id]].markCompleted();
            cout << "Task marked as completed.\n";
        } else {
            cout << "Task not found.\n";
        }
    }

    void deleteTask() {
        int id;
        cout << "Enter Task ID to delete: ";
        cin >> id;

        if (taskIndex.find(id) == taskIndex.end()) {
            cout << "Task not found.\n";
            return;
        }

        int index = taskIndex[id];
        tasks.erase(tasks.begin() + index);
        taskIndex.erase(id);

        // Rebuild index map
        for (int i = 0; i < tasks.size(); i++) {
            taskIndex[tasks[i].getId()] = i;
        }

        cout << "Task deleted successfully.\n";
    }

    void showAllTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        for (const auto& t : tasks) {
            t.display();
        }
    }

    void showPendingTasks() const {
        bool found = false;
        for (const auto& t : tasks) {
            if (!t.isCompleted()) {
                t.display();
                found = true;
            }
        }
        if (!found)
            cout << "No pending tasks.\n";
    }

    void showCompletedTasks() const {
        bool found = false;
        for (const auto& t : tasks) {
            if (t.isCompleted()) {
                t.display();
                found = true;
            }
        }
        if (!found)
            cout << "No completed tasks.\n";
    }
};

// ---------------- MAIN FUNCTION ----------------
int main() {
    TaskManager manager;
    int choice;

    cout << "==============================\n";
    cout << "   TASK MANAGEMENT SYSTEM\n";
    cout << "==============================\n";

    do {
        cout << "\n1. Add Task";
        cout << "\n2. Mark Task as Completed";
        cout << "\n3. Delete Task";
        cout << "\n4. Show All Tasks";
        cout << "\n5. Show Pending Tasks";
        cout << "\n6. Show Completed Tasks";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manager.addTask();
            break;
        case 2:
            manager.markTaskCompleted();
            break;
        case 3:
            manager.deleteTask();
            break;
        case 4:
            manager.showAllTasks();
            break;
        case 5:
            manager.showPendingTasks();
            break;
        case 6:
            manager.showCompletedTasks();
            break;
        case 0:
            cout << "Exiting Task Manager...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

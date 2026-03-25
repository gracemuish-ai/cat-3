#include <iostream>
#include <string>
using namespace std;

#define MAX 5

// Base Task class
class Task {
protected:
    string name;
    int priority;

public:
    Task(string n = "", int p = 0) {
        name = n;
        priority = p;
    }

    virtual ~Task() {
        cout << "Task destroyed" << endl;
    }

    void setTask(string n) {
        name = n;
    }

    void setTask(string n, int p) {
        name = n;
        priority = p;
    }

    bool operator>(Task t) {
        return priority > t.priority;
    }

    virtual void display() {
        cout << "Task Name: " << name << endl;
        cout << "Priority: " << priority << endl;
    }

    int getPriority() {
        return priority;
    }
};

class AcademicTask : public Task {
protected:
    string unit;

public:
    AcademicTask(string n = "", int p = 0, string u = "") : Task(n, p) {
        unit = u;
    }

    void display() override {
        cout << "Academic Task: " << name << endl;
        cout << "Unit: " << unit << endl;
        cout << "Priority: " << priority << endl;
    }
};
class ExamTask : public Task {
private:
    string examDate;

public:
    ExamTask(string n = "", int p = 0, string d = "") : Task(n, p) {
        examDate = d;
    }

    void display() override {
        cout << "Exam: " << name << endl;
        cout << "Date: " << examDate << endl;
        cout << "Priority: " << priority << endl;
    }
};
class Student {
private:
    string name;
    int stress;

public:
    Student(string n = "") {
        name = n;
        stress = 0;
    }

    void setStress(int s) {
        if (s < 0 || s > 10) {
            throw "Invalid stress level!";
        }
        stress = s;
    }

    int getStress() {
        return stress;
    }
};
class SystemManager {
private:
    Task* tasks[MAX];
    int count;
    Student student;
    int matrix[2][2];

public:
    SystemManager(string name) : student(name) {
        count = 0;
    
        matrix[0][0] = 1; matrix[0][1] = 2;
        matrix[1][0] = 3; matrix[1][1] = 4;
    }
    ~SystemManager() {
        for (int i = 0; i < count; i++) {
            delete tasks[i];
        }
    }
    void addTask() {
        if (count >= MAX) {
            cout << "Tasks full" << endl;
            return;
        }

        int choice;
        cout << "1. Academic Task\n2. Exam Task\nChoice: ";
        cin >> choice;

        string name, unit, date;
        int priority;

        cout << "Enter name: ";
        cin >> name;
        cout << "Enter priority: ";
        cin >> priority;

        if (choice == 1) {
            cout << "Enter unit: ";
            cin >> unit;
            tasks[count] = new AcademicTask(name, priority, unit);
        } else {
            cout << "Enter exam date: ";
            cin >> date;
            tasks[count] = new ExamTask(name, priority, date);
        }

        count++;
    }
    void viewTasks() {
        for (int i = 0; i < count; i++) {
            tasks[i]->display();
        }
    }
    void stressControl() {
        int stressLevel;
        cout << "Enter stress (0-10): ";
        cin >> stressLevel;

        try {
            student.setStress(stressLevel);
            (student.getStress() > 7) ?
                cout << "High stress" << endl :
                cout << "Normal stress" << endl;
        } catch (const char* error) {
            cout <<"error" << endl;
        }
    }
    void loopDemo() {
        int i = 0;
        while (i < count) {
            if (tasks[i]->getPriority() < 2) {
                i++;
                continue; 
            }
            cout << "Important Task: " << endl;
            tasks[i]->display();
            if (i == 3)
                break; 
            i++;
        }
        int j = 0;
        do {
            cout << "Matrix Value: " << matrix[0][0] << endl;
            j++;
        } while (j < 1);
    }
};
int main() {
    SystemManager sys("Grace");
    int choice = 0;

    while (choice != 5) {
        cout << "\n1.Add Task\n2.View Tasks\n3.Stress\n4.Loop Demo\n5.Exit\n";
        cin >> choice;

        if (choice == 1) sys.addTask();
        else if (choice == 2) sys.viewTasks();
        else if (choice == 3) sys.stressControl();
        else if (choice == 4) sys.loopDemo();
        else if (choice == 5) cout << "Exiting..." << endl;
        else cout << "Invalid choice! Try again." << endl;
    }

    return 0;
}

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    std::string group;

public:
    void setDetails() {
        std::cout << "Enter student's name: ";
        std::cin >> name;

        std::cout << "Enter student's age: ";
        std::cin >> age;

        std::cout << "Enter student's group: ";
        std::cin >> group;
    }

    void displayDetails() {
        std::cout << "\nStudent Details:" << std::endl;
        std::cout << "----------------\n";
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Group: " << group << std::endl;
    }
};

int main() {
    Student student;

    student.setDetails();
    student.displayDetails();

    return 0;
}

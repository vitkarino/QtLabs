#include "Student.h"
#include <iostream>

void Student::setDetails() {
    std::cout << "Enter student's name: ";
    std::cin >> name;

    std::cout << "Enter student's age: ";
    std::cin >> age;

    std::cout << "Enter student's group: ";
    std::cin >> group;
}

void Student::displayDetails() {
    std::cout << "\nStudent Details:" << std::endl;
    std::cout << "----------------\n";
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Group: " << group << std::endl;
}

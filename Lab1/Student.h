#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string name;
    int age;
    std::string group;

public:
    void setDetails();
    void displayDetails();
};

#endif // STUDENT_H

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    int rollNumber;
    std::string name;
    int age;
    float cgpa;

public:
    Student(int r, const std::string &n, int a, float c)
        : rollNumber(r), name(n), age(a), cgpa(c) {}

    // Getters
    int getRollNumber() const { return rollNumber; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    float getCgpa() const { return cgpa; }

    // ✅ SETTERS 
    void setName(const std::string &n) { name = n; }
    void setAge(int a) { age = a; }
    void setCgpa(float c) { cgpa = c; }

    void display() const {
        std::cout << "Roll: " << rollNumber
                  << ", Name: " << name
                  << ", Age: " << age
                  << ", CGPA: " << cgpa << '\n';
    }
};

#endif

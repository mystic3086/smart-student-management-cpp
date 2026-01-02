// src/Student.h
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
    // Constructor
    Student(int r, std::string n, int a, float c): rollNumber(r), name(n), age(a), cgpa(c) {}

    // Getter functions
    int getRollNumber() const { 
        return rollNumber; 
    }
    std::string getName() const { 
        return name;
     }
    int getAge() const { 
        return age;
     }
    float getCgpa() const { 
        return cgpa; 
    }

    // Display student info
    void display() const {
        std::cout << "Roll No: " << rollNumber
                  << ", Name: " << name
                  << ", Age: " << age
                  << ", CGPA: " << cgpa << std::endl;
    }
};

#endif

// src/Database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class Database {
private:
    std::string filename;

public:
    Database(const std::string &file) : filename(file) {}

    // Save all students to file
    void save(const std::vector<Student> &students) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto &s : students) {
        int roll = s.getRollNumber();
        int age = s.getAge();
        float cgpa = s.getCgpa();
        std::string name = s.getName();
        size_t nameLen = name.size();

        out.write(reinterpret_cast<const char*>(&roll), sizeof(int));
        out.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
        out.write(name.c_str(), nameLen);
        out.write(reinterpret_cast<const char*>(&age), sizeof(int));
        out.write(reinterpret_cast<const char*>(&cgpa), sizeof(float));
    }

    out.close();
}

    // Load students from file
    void load(std::vector<Student> &students) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) return;

        while (!in.eof()) {
            int roll, age;
            float cgpa;
            size_t nameLen;
            in.read(reinterpret_cast<char*>(&roll), sizeof(int));
            if (in.eof()) break;
            in.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t));

            std::string name(nameLen, ' ');
            in.read(&name[0], nameLen);

            in.read(reinterpret_cast<char*>(&age), sizeof(int));
            in.read(reinterpret_cast<char*>(&cgpa), sizeof(float));

            students.push_back(Student(roll, name, age, cgpa));
        }
        in.close();
    }

    // Search by roll number
    bool search(const std::vector<Student> &students, int roll) {
        for (const auto &s : students) {
            if (s.getRollNumber() == roll) {
                s.display();
                return true;
            }
        }
        return false;
    }
};

#endif

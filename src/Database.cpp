#include "Database.h"
#include <fstream>
#include <iostream>
#include <limits>

Database::Database(const std::string &file) : filename(file) {}

// Save to file
void Database::save(const std::vector<Student> &students) {
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
}

// Load from file
void Database::load(std::vector<Student> &students) {
    students.clear();
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;

    while (true) {
        int roll, age;
        float cgpa;
        size_t nameLen;

        in.read(reinterpret_cast<char*>(&roll), sizeof(int));
        if (!in) break;

        in.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t));
        std::string name(nameLen, ' ');
        in.read(&name[0], nameLen);

        in.read(reinterpret_cast<char*>(&age), sizeof(int));
        in.read(reinterpret_cast<char*>(&cgpa), sizeof(float));

        students.emplace_back(roll, name, age, cgpa);
    }
}

// Search by roll
bool Database::searchByRoll(const std::vector<Student> &students, int roll) {
    for (const auto &s : students) {
        if (s.getRollNumber() == roll) {
            s.display();
            return true;
        }
    }
    return false;
}

// Search by name (partial match)
bool Database::searchByName(const std::vector<Student> &students, const std::string &name) {
    bool found = false;
    for (const auto &s : students) {
        if (s.getName().find(name) != std::string::npos) {
            s.display();
            found = true;
        }
    }
    return found;
}

// Update student
bool Database::updateStudent(std::vector<Student>& students, int roll) {
    for (auto &s : students) {
        if (s.getRollNumber() == roll) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string name;
            int age;
            float cgpa;

            std::cout << "New name: ";
            std::getline(std::cin, name);

            std::cout << "New age: ";
            std::cin >> age;

            std::cout << "New CGPA: ";
            std::cin >> cgpa;

            s.setName(name);
            s.setAge(age);
            s.setCgpa(cgpa);

            return true;
        }
    }
    return false;
}

// Delete student
bool Database::deleteStudent(std::vector<Student>& students, int roll) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNumber() == roll) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

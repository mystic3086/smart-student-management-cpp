#include <iostream>
#include <vector>
#include "Student.h"
#include "Database.h"

int main() {
    std::vector<Student> students;
    Database db("data/students.dat");

    // Load existing students
    db.load(students);

    int choice;
    do {
        std::cout << "\n1. Add Student\n2. Display Students\n3. Search by Roll Number\n4. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            int r, a; float c; std::string n;
            std::cout << "Roll: "; std::cin >> r;
            std::cout << "Name: "; std::cin.ignore(); std::getline(std::cin, n);
            std::cout << "Age: "; std::cin >> a;
            std::cout << "CGPA: "; std::cin >> c;

            students.push_back(Student(r, n, a, c));
            db.save(students); // Save after every addition
        }
        else if (choice == 2) {
            for (const auto &s : students) s.display();
        }
        else if (choice == 3) {
            int r;
            std::cout << "Enter roll number to search: "; std::cin >> r;
            if (!db.search(students, r))
                std::cout << "Student not found.\n";
        }

    } while (choice != 4);

    return 0;
}

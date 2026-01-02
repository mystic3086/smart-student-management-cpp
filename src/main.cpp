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
    int role;
    std::cout << "Login as:\n1. Admin\n2. Student\nChoice: ";
    std::cin >> role;
    do {
        // ===== MENU =====
        if (role == 1) { // ADMIN
            std::cout << "\n1. Add Student"
                    << "\n2. Display Students"
                    << "\n3. Search Student"
                    << "\n4. Update Student"
                    << "\n5. Delete Student"
                    << "\n6. Exit"
                    << "\nChoice: ";
        } else { // STUDENT
            std::cout << "\n1. Display Students"
                    << "\n2. Search Student"
                    << "\n3. Exit"
                    << "\nChoice: ";
        }

        std::cin >> choice;

        // ===== ADMIN ACTIONS =====
        if (role == 1) {
            if (choice == 1) {
                // ADD STUDENT
                int r, a;
                float c;
                std::string n;

                std::cout << "Roll: ";
                std::cin >> r;

                bool exists = false;
                for (const auto &s : students) {
                    if (s.getRollNumber() == r) {
                        exists = true;
                        break;
                    }
                }

                if (exists) {
                    std::cout << "Roll number already exists!\n";
                } else {
                    std::cout << "Name: ";
                    std::cin.ignore();
                    std::getline(std::cin, n);

                    std::cout << "Age: ";
                    std::cin >> a;

                    std::cout << "CGPA: ";
                    std::cin >> c;

                    students.push_back(Student(r, n, a, c));
                    db.save(students);
                    std::cout << "Student added successfully.\n";
                }
            }
            else if (choice == 2) {
                // DISPLAY
                for (const auto &s : students)
                    s.display();
            }
            else if (choice == 3) {
                // SEARCH
                int r;
                std::cout << "Enter roll number: ";
                std::cin >> r;

                if (!db.search(students, r))
                    std::cout << "Student not found.\n";
            }
            else if (choice == 4) {
                // UPDATE
                int r;
                std::cout << "Enter roll to update: ";
                std::cin >> r;

                if (db.updateStudent(students, r)) {
                    db.save(students);
                    std::cout << "Student updated.\n";
                } else {
                    std::cout << "Student not found.\n";
                }
            }
            else if (choice == 5) {
                // DELETE
                int r;
                std::cout << "Enter roll to delete: ";
                std::cin >> r;

                if (db.deleteStudent(students, r)) {
                    db.save(students);
                    std::cout << "Student deleted.\n";
                } else {
                    std::cout << "Student not found.\n";
                }
            }
        }

        // ===== STUDENT ACTIONS =====
        else {
            if (choice == 1) {
                // DISPLAY
                for (const auto &s : students)
                    s.display();
            }
            else if (choice == 2) {
                // SEARCH
                int r;
                std::cout << "Enter roll number: ";
                std::cin >> r;

                if (!db.search(students, r))
                    std::cout << "Student not found.\n";
            }
        }

    } while ((role == 1 && choice != 6) || (role == 2 && choice != 3));



    return 0;
}

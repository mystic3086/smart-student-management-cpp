#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

#include "Student.h"
#include "Database.h"

// ======= UTILITY FUNCTIONS =======
int readInt(const std::string &prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (!std::cin.fail()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Enter a number.\n";
    }
    return value;
}

float readFloat(const std::string &prompt) {
    float value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (!std::cin.fail()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Enter a decimal number.\n";
    }
    return value;
}

void displaySortedByCGPA(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students to display.\n";
        return;
    }

    std::vector<Student> copy = students;
    std::sort(copy.begin(), copy.end(), [](const Student &a, const Student &b) {
        return a.getCgpa() > b.getCgpa();
    });

    std::cout << "\n--- STUDENTS SORTED BY CGPA ---\n";
    for (const auto &s : copy)
        s.display();

    // Display top student
    std::cout << "\nTop Student:\n";
    copy.front().display();
}

// ======= FUNCTION DECLARATIONS =======
void adminMenu(Database& db, std::vector<Student>& students);
void studentMenu(Database& db, const std::vector<Student>& students);

// ======= MAIN =======
int main() {
    Database db("students.dat");
    std::vector<Student> students;

    db.load(students);

    std::cout << "Login as:\n1. Admin\n2. Student\n";
    int role = readInt("Choice: ");

    if (role == 1)
        adminMenu(db, students);
    else if (role == 2)
        studentMenu(db, students);
    else
        std::cout << "Invalid choice. Exiting.\n";

    return 0;
}

// ======= ADMIN MENU =======
void adminMenu(Database& db, std::vector<Student>& students) {
    int choice;

    do {
        std::cout << "\n--- ADMIN MENU ---\n"
                  << "1. Add Student\n"
                  << "2. Display Students\n"
                  << "3. Search by Roll\n"
                  << "4. Search by Name\n"
                  << "5. Update Student\n"
                  << "6. Delete Student\n"
                  << "7. Display Sorted by CGPA\n"
                  << "8. Exit\n";

        choice = readInt("Choice: ");

        switch (choice) {
            case 1: {
                int roll = readInt("Roll: ");
                bool exists = false;
                for (const auto &s : students)
                    if (s.getRollNumber() == roll) { exists = true; break; }

                if (exists) {
                    std::cout << "Roll number exists!\n";
                    break;
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string name;
                std::cout << "Name: ";
                std::getline(std::cin, name);

                int age = readInt("Age: ");
                float cgpa = readFloat("CGPA: ");

                students.emplace_back(roll, name, age, cgpa);
                db.save(students);
                std::cout << "Student added.\n";
                break;
            }

            case 2:
                if (students.empty()) std::cout << "No students.\n";
                else for (const auto &s : students) s.display();
                break;

            case 3: {
                int roll = readInt("Enter roll: ");
                if (!db.searchByRoll(students, roll))
                    std::cout << "Student not found.\n";
                break;
            }

            case 4: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string name;
                std::cout << "Enter name (partial allowed): ";
                std::getline(std::cin, name);

                if (!db.searchByName(students, name))
                    std::cout << "No matching student.\n";
                break;
            }

            case 5: {
                int roll = readInt("Enter roll to update: ");
                if (db.updateStudent(students, roll)) {
                    db.save(students);
                    std::cout << "Updated successfully.\n";
                } else std::cout << "Student not found.\n";
                break;
            }

            case 6: {
                int roll = readInt("Enter roll to delete: ");
                if (db.deleteStudent(students, roll)) {
                    db.save(students);
                    std::cout << "Deleted successfully.\n";
                } else std::cout << "Student not found.\n";
                break;
            }

            case 7:
                displaySortedByCGPA(students);
                break;

            case 8:
                std::cout << "Exiting admin menu.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 8);
}

// ======= STUDENT MENU =======
void studentMenu(Database& db, const std::vector<Student>& students) {
    int choice;

    do {
        std::cout << "\n--- STUDENT MENU ---\n"
                  << "1. Display Students\n"
                  << "2. Search by Roll\n"
                  << "3. Search by Name\n"
                  << "4. Display Sorted by CGPA\n"
                  << "5. Exit\n";

        choice = readInt("Choice: ");

        switch (choice) {
            case 1:
                if (students.empty()) std::cout << "No students.\n";
                else for (const auto &s : students) s.display();
                break;

            case 2: {
                int roll = readInt("Enter roll: ");
                if (!db.searchByRoll(students, roll))
                    std::cout << "Student not found.\n";
                break;
            }

            case 3: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string name;
                std::cout << "Enter name (partial allowed): ";
                std::getline(std::cin, name);
                if (!db.searchByName(students, name))
                    std::cout << "No matching student.\n";
                break;
            }

            case 4:
                displaySortedByCGPA(students);
                break;

            case 5:
                std::cout << "Exiting student menu.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 5);
}

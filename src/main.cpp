#include <iostream>
#include <vector>
#include "Student.h"

int main() {
    std::vector<Student> students;
    int choice;
    //loop for choices
    do {
        std::cout << "\n1. Add Student\n2. Display Students\n3. Exit\nChoice: ";
        std::cin >> choice;//inp

        if (choice == 1) {
            int r, a; float c; std::string n;
            std::cout << "Roll: "; std::cin >> r;
            std::cout << "Name: "; std::cin >> n;
            std::cout << "Age: "; std::cin >> a;
            std::cout << "CGPA: "; std::cin >> c;
            students.push_back(Student(r, n, a, c));
        } else if (choice == 2) {
            for (const auto &s : students) s.display();//const -> dosent change stuff,auto -> Non-const reference
        }

    } while (choice != 3);

    return 0;
}
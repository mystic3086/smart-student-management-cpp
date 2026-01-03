# Smart Student Management System (C++)

A console-based **Student Management System** written in C++ with **binary file storage** and **OOP structure**. This project demonstrates **C++ classes, file I/O, input validation, and practical programming skills**.

---

## Features(role based)

### Admin commands
- Add, update, delete students
- Search by **roll number** or **name** (partial matches allowed)
- Display all students
- Display students **sorted by CGPA**
- Automatically highlights the **top student**

### Student commands
- Display all students
- Search by **roll number** or **name**
- View students **sorted by CGPA**
- Robust **input validation** to prevent crashes

---

## Project Structure

```
src/
├── Student.h          # Student class (properties, getters, setters)
├── Student.cpp        # Empty, all inline
├── Database.h         # Database class (file operations, search/update/delete)
├── Database.cpp       # Database functions implementation
└── main.cpp           # Main program with Admin & Student menus
.gitignore             # Exclude binaries
README.md
students.dat           # Binary file (generated automatically)
```

---

## Features / concepts 
- **OOP concepts**: Classes, Encapsulation, Getters/Setters  
- **Binary file I/O** for persistent data storage  
- **Admin and Student menus** with input validation  
- **Search, update, delete, and sort functionality**  
- Fully **modular and professional** C++ project  

---

## Future additions
- Add **grades** based on CGPA  
- Implement **login system** for Admin vs Student  
- Export students to **CSV or text file**  
- Add **statistics**: Average CGPA, top performers, etc.  
- GUI version using **Qt** or **SFML**


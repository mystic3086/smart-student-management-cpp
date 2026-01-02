#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <vector>
#include <string>

class Database {
private:
    std::string filename;

public:
    Database(const std::string &file);

    void save(const std::vector<Student> &students);
    void load(std::vector<Student> &students);
    bool searchByRoll(const std::vector<Student> &students, int roll);
    bool searchByName(const std::vector<Student> &students, const std::string &name);
    bool updateStudent(std::vector<Student>& students, int roll);
    bool deleteStudent(std::vector<Student>& students, int roll);
};

#endif

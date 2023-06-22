#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"

class Teacher {
private:
    int teacherId;
    std::string username;
    std::string firstName;
    std::string lastName;
    int age;
    
public:
    // Constructor
    Teacher(int id,  std::string uname, std::string fName, std::string lName, int teacherAge);

    // Add a student
    void addStudent(Student student);

    // Remove a student
    void removeStudent(Student student);

    // Display the students
    void displayStudents();

    // Setters
    void setTeacherId(int id);
    void setUsername(std::string uname);
    void setFirstName(std::string fName);
    void setLastName(std::string lName);
    void setAge(int teacherAge);

    // Getters
    int getTeacherId() ;
    std::string getUsername() ;
    std::string getFirstName() ;
    std::string getLastName() ;
    int getAge() ;
};

#endif  // TEACHER_H

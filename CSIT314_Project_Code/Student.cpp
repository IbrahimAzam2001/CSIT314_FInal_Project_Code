#include "Student.h"
#include <iostream>

Student::Student()
    : studentId(0), age(0) {}

// Parameterized constructor
Student::Student(int id, std::string uname, std::string fName, std::string lName, int studentAge)
    : studentId(id), userName(uname), firstName(fName), lastName(lName), age(studentAge) {}

// Getters and Setters
int Student::getStudentId() const {
    return studentId;
}

void Student::setStudentId(int id) {
    studentId = id;
}

std::string Student::getUsername() const {
    return userName;
}

void Student::setUsername(std::string uname) {
    userName = uname;
}

std::string Student::getFirstName() const {
    return firstName;
}

void Student::setFirstName(std::string fName) {
    firstName = fName;
}

std::string Student::getLastName() const {
    return lastName;
}

void Student::setLastName(std::string lName) {
    lastName = lName;
}

int Student::getAge() const {
    return age;
}

void Student::setAge(int studentAge) {
    age = studentAge;
}

void Student::addSubject(std::string subject) {
    subjects.push_back(subject);
}

// Display the subjects
void Student::displaySubjects() const {
    std::cout << "Subjects taken by " << firstName << " " << lastName << ":" << std::endl;
    for (const auto& subject : subjects) {
        std::cout << subject << std::endl;
    }
}

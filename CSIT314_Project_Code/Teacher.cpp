#include "teacher.h"

// Constructor
Teacher::Teacher(int id, std::string uname, std::string fName, std::string lName, int teacherAge)
    : teacherId(id), username(uname), firstName(fName), lastName(lName), age(teacherAge) {}



// Remove a student


// Display the students
//void Teacher::displayStudents() const {
    //std::cout << "Students taught by " << firstName << " " << lastName << ":" << std::endl;
    //for (const auto& student : students) {
    //    std::cout << student.firstName << " " << student.lastName << std::endl;
    //}
//}

// Setters
void Teacher::setTeacherId(int id) {
    teacherId = id;
}

void Teacher::setUsername(std::string uname) {
    username = uname;
}

void Teacher::setFirstName(std::string fName) {
    firstName = fName;
}

void Teacher::setLastName(std::string lName) {
    lastName = lName;
}

void Teacher::setAge(int teacherAge) {
    age = teacherAge;
}

// Getters
int Teacher::getTeacherId() {
    return teacherId;
}

std::string Teacher::getUsername() {
    return username;
}

std::string Teacher::getFirstName() {
    return firstName;
}

std::string Teacher::getLastName() {
    return lastName;
}

int Teacher::getAge() {
    return age;
}

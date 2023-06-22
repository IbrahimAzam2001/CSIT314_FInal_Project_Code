#ifndef STUDENT_H
#define STUDENT_H



#include <string>
#include <vector>

class Student {


private:
    int studentId;
    std::string userName;
    std::string firstName;
    std::string lastName;
    int age;
    std::vector<std::string> subjects;

public:
    // Constructor
    Student();
    Student(int id, std::string uname, std::string fName, std::string lName, int studentAge);

    // Getters and Setters
    int getStudentId() const;
    void setStudentId(int id);
    std::string getUsername() const;
    void setUsername(std::string uname);
    std::string getFirstName() const;
    void setFirstName(std::string fName);
    std::string getLastName() const;
    void setLastName(std::string lName);
    int getAge() const;
    void setAge(int studentAge);

    void addSubject(std::string subject);
    void displaySubjects() const;


};

#endif // !STUDENT_H
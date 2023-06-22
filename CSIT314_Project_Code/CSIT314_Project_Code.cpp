#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include <vector>
#include <sstream>
#include <ctime>
#include <random>
#include <map>
#include <algorithm>
#include "Teacher.h"

#define ifstream std::ifstream
#define vector std::vector
#define stringstream std::stringstream
#define cout std::cout
#define endl std::endl
#define cin std::cin
#define string std::string
#define ifstream std::ifstream
#define vector std::vector

void showStudentDetails(string user) {
    ifstream inputFile("students.txt");
    if (!inputFile) {
        cout << "Error opening the file." << endl;
        return;
    }

    vector<Student> students;
    string line;
    while (std::getline(inputFile, line)) {
        stringstream ss(line);
        string studentUsername;
        int studentId;
        string firstName;
        string lastName;
        int age;
        vector<string> subjects;

        // Extract student data from the line
        ss >> studentUsername >> studentId >> firstName >> lastName >> age;

        string subjectsStr;
        std::getline(ss, subjectsStr);  // Read the remaining line containing subjects
        stringstream subjectsStream(subjectsStr);
        string subject;
        while (subjectsStream >> subject) {
            subjects.push_back(subject);
        }

        // Create a Student object with the extracted data
        Student student(studentId, studentUsername, firstName, lastName, age);

        for (int k = 0; k < subjects.size(); k++) {
            student.addSubject(subjects.at(k));
        }

        // Add the student to the vector
        students.push_back(student);
    }

    inputFile.close();

    // Find the student with the entered username
    bool found = false;
    for (int m = 0; m < students.size(); m++) {
        if (students.at(m).getUsername() == user) {
            cout << "Username: " << students.at(m).getUsername() << endl;
            cout << "Student ID: " << students.at(m).getStudentId() << endl;
            cout << "First Name: " << students.at(m).getFirstName() << endl;
            cout << "Last Name: " << students.at(m).getLastName() << endl;
            cout << "Age: " << students.at(m).getAge() << endl;
            students.at(m).displaySubjects();

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with the username " << user << " not found." << endl;
    }
}

void showTeacherDetails(string teacherUsername) {
    ifstream inputFile("teachers.txt");
    if (!inputFile) {
        cout << "Error opening the file." << endl;
        return;
    }

    string line;
    while (std::getline(inputFile, line)) {
        stringstream ss(line);
        string teacherData;
        vector<string> studentUsernames;

        // Split the line by ","
        while (std::getline(ss, teacherData, ',')) {
            studentUsernames.push_back(teacherData);
        }

        // Extract teacher details from the first part
        stringstream teacherStream(studentUsernames[0]);
        string username;
        int teacherId;
        string firstName;
        string lastName;
        int age;

        teacherStream >> username >> teacherId >> firstName >> lastName >> age;

        // Check if the username matches
        if (username == teacherUsername) {
            // Display teacher details
            cout << "Username: " << username << endl;
            cout << "Teacher ID: " << teacherId << endl;
            cout << "First Name: " << firstName << endl;
            cout << "Last Name: " << lastName << endl;
            cout << "Age: " << age << endl;

            // Display student usernames from the second part
            cout << "Student Usernames: ";
            for (int i = 1; i < studentUsernames.size(); i++) {
                cout << studentUsernames[i] << " ";
            }
            cout << endl;

            cout << endl;

            inputFile.close();
            return;
        }
    }

    inputFile.close();

    // Teacher not found
    cout << "Teacher with the username " << teacherUsername << " not found." << endl;
}


bool logInStudent(string uname, string pass) {

    ifstream file("passwordStudent.txt"); // Open the passwords file

    if (!file) {
        std::cerr << "Failed to open the file." << endl;
        return false;
    }

    vector<string> usernames;
    vector<string> passwords;

    string username;
    string password;

    while (file >> username >> password) {
        usernames.push_back(username);
        passwords.push_back(password);
    }

    file.close(); // Close the file

    for (int i = 0; i < usernames.size();i++) {
        if ((usernames.at(i) == uname) && (passwords.at(i)==pass)) {
            return true;
        }
    }
    return false;
}

int generateStudentId() {
    std::mt19937 rng(static_cast<unsigned int>(time(0))); // Seed the random number generator
    std::uniform_int_distribution<int> dist(1000000, 9999999); // Define the range of 7-digit numbers
    return dist(rng); // Generate a random 7-digit student ID
}

void signUpStudent() {//ask first and last name, then ask age, generate a random 7 digit number for student id, for username
    
    string firstName = "", lastName = "";
    int age = 0, studentId = 0;
    
    cout << "First Name : ";
    cin >> firstName;
    cout << "Last Name : ";
    cin >> lastName;

    cout << "Age (4-18) : ";
    cin >> age;
    if (age < 4 or age>18) {
        cout << "Students of below age 4 and above 18 aren't allowed to make a student account" << endl;
        return;
    }
    
    studentId = generateStudentId();
    
    char firstNameChar = firstName.at(0);
    char lastNameChar = lastName.at(0);
    string idSubstring = std::to_string(studentId).substr(0, 3);
    string userName = string(1, firstNameChar) + string(1, lastNameChar) + idSubstring;
    cout << userName << endl;
    cout << studentId << endl;
    
    cout << "Password : ";
    string password = "";
    cin >> password;
    string passwordFile = userName + " " + password;
    cout << "This will be a part of password file = " << passwordFile << endl;

    std::ofstream passFile("passwordStudent.txt", std::ios::app);

    if (passFile.is_open()) {

        passFile << endl << passwordFile; // Append line of data with newline character

        passFile.close(); // Close the file
        cout << "Password added to the file." << endl;
    }
    else {
        cout << "Failed to open the file." << endl;
    }

    cout << "Whenever students sign up, they are recommended to take 2-3 courses." << endl;
    //MATH042, ARA101, INE301, CSIT314, CSCI262, CSCI369
    cout << "These are some of the courses that are being offered now.\nChoose from the following." << endl
        << "1) MATH042" << endl
        << "2) ARA101" << endl
        << "3) INE301" << endl
        << "4) CSIT314" << endl
        << "5) CSCI262" << endl
        << "6) CSCI369" << endl;
    
    vector<string>subjectsOffered = { "MATH042", "ARA101", "INE301", "CSIT314", "CSCI262", "CSCI369" };
    vector<string>subjectsFinalized;
    int numberOfCourses = 0;
    int minCourses = 2;
    int maxCourses = 3;

    while (numberOfCourses < minCourses || numberOfCourses > maxCourses) {
        cout << "Enter the number of courses that you would like to take (" << minCourses << "-" << maxCourses << ") = ";
        cin >> numberOfCourses;

        if (numberOfCourses < minCourses || numberOfCourses > maxCourses) {
            cout << "Invalid input. Please enter a valid number of courses." << endl;
        }
    }
    cout << "Enter your course numbers" << endl;
    for (int i = 0; i < numberOfCourses; i++) {
        int number = 0;
        cin >> number;

        // Check if the selected number is within a valid range
        if (number >= 1 && number <= subjectsOffered.size()) {
            // Check if the subject has already been selected
            if (std::find(subjectsFinalized.begin(), subjectsFinalized.end(), subjectsOffered[number - 1]) == subjectsFinalized.end()) {
                subjectsFinalized.push_back(subjectsOffered[number - 1]);
            }
            else {
                cout << "You have already selected that subject. Please choose a different one." << endl;
                i--; // Decrement i to prompt for input again
            }
        }
        else {
            cout << "Invalid input. Please enter a valid subject number." << endl;
            i--; // Decrement i to prompt for input again
        }
    }

    // Print the selected subjects
    cout << "Selected courses: ";
    for (const string& subject : subjectsFinalized) {
        cout << subject << " ";
    }
    cout << endl;



    string finalInput = userName + " " + std::to_string(studentId) + " " + firstName + " " + lastName + " " + std::to_string(age);
    for (int l = 0; l < subjectsFinalized.size(); l++) {
        finalInput += " " + subjectsFinalized.at(l);
    }
    cout << finalInput << endl;

    std::ofstream outputFile("students.txt", std::ios::app);

    if (outputFile.is_open()) {

        outputFile << endl << finalInput; // Append line of data with newline character

        outputFile.close(); // Close the file
        cout << "Student added to the file." << endl;
    }
    else {
        cout << "Failed to open the file." << endl;
    }
}

void changeCourses(string username) {
    ifstream inputFile("students.txt");
    if (!inputFile) {
        std::cerr << "Failed to open the input file." << endl;
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cerr << "Failed to create the temporary file." << endl;
        inputFile.close();
        return;
    }

    string line;
    string deletedLine;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        string currentUsername;
        iss >> currentUsername;

        if (currentUsername != username) {
            tempFile << line << endl;
        }
        else {
            deletedLine = line; // Store the deleted line
        }
    }

    inputFile.close();
    tempFile.close();

    // Delete the original file
    if (std::remove("students.txt") != 0) {
        std::cerr << "Failed to delete the original file." << endl;
        return;
    }

    // Rename the temporary file to the original file name
    if (std::rename("temp.txt", "students.txt") != 0) {
        std::cerr << "Failed to rename the temporary file." << endl;
        return;
    }

    vector<string> splittedWords;
    std::istringstream iss(deletedLine);

    string word;
    while (getline(iss, word, ' ')) {
        splittedWords.push_back(word);
    }
    vector<string> subjects(splittedWords.begin() + 5, splittedWords.end());

    cout << "Current subjects: " << endl;
    for (int i = 0; i < subjects.size();i++) {
        cout << i + 1 << ") " << subjects[i] << endl;
    }
    cout << endl;

    if (subjects.size() < 2 || subjects.size() > 3) {
        cout << "Invalid number of courses for the student." << endl;
        return;
    }

    vector<string> subjectsOffered = { "MATH042", "ARA101", "INE301", "CSIT314", "CSCI262", "CSCI369" };

    cout << "Subjects offered for replacement: " << endl;
    for (int i = 0; i < subjectsOffered.size(); ++i) {
        cout << i + 1 << ") " << subjectsOffered[i] << endl;
    }

    int subjectIndex;
    int newSubjectIndex;
    bool isValidInput = false;

    while (!isValidInput) {
        cout << "Enter the index of the subject to replace (1-" << subjects.size() << "): ";
        cin >> subjectIndex;

        if (subjectIndex >= 1 && subjectIndex <= subjects.size()) {
            isValidInput = true;
        }
        else {
            cout << "Invalid subject index. Please enter a valid index." << endl;
        }
    }

    isValidInput = false;

    while (!isValidInput) {
        cout << "Enter the index of the new subject: ";
        cin >> newSubjectIndex;

        if (newSubjectIndex >= 1 && newSubjectIndex <= subjectsOffered.size()) {
            // Check if the new subject is the same as any existing subject
            if (find(subjects.begin(), subjects.end(), subjectsOffered[newSubjectIndex - 1]) != subjects.end()) {
                cout << "The new subject is the same as an existing subject." << endl;
            }
            else {
                isValidInput = true;
            }
        }
        else {
            cout << "Invalid new subject index. Please enter a valid index." << endl;
        }
    }

    // Replace the specified subject with the new subject
    subjects[subjectIndex - 1] = subjectsOffered[newSubjectIndex - 1];

    cout << "Updated subjects: ";
    for (const string& subject : subjects) {
        cout << subject << " ";
    }
    cout << endl;

    deletedLine = "";
    for (int i = 0; i < splittedWords.size() - subjects.size(); ++i) {
        deletedLine += splittedWords[i] + " ";
    }

    for (const string& subject : subjects) {
        deletedLine += subject + " ";
    }

    std::ofstream outputFile("students.txt", std::ios::app);

    if (outputFile.is_open()) {
        outputFile << deletedLine << endl;
        outputFile.close();
        cout << "Course updated for the student." << endl;
    }
    else {
        cout << "Failed to open the file." << endl;
    }
}


bool logInTeacher(string user, string pass) {
    ifstream file("passwordTeacher.txt"); // Open the passwords file

    if (!file) {
        std::cerr << "Failed to open the file." << endl;
        return false;
    }

    vector<string> usernames;
    vector<string> passwords;

    string username;
    string password;

    while (file >> username >> password) {
        usernames.push_back(username);
        passwords.push_back(password);
    }

    file.close(); // Close the file

    for (int i = 0; i < usernames.size(); i++) {
        if ((usernames.at(i) == user) && (passwords.at(i) == pass)) {
            return true;
        }
    }
    return false;
}

void addStudentToTeacher(string teacherUsername) {
    // Open the teachers.txt file
    ifstream teachersFile("teachers.txt");
    if (!teachersFile) {
        std::cerr << "Failed to open the teachers file." << endl;
        return;
    }

    string teacherLine;
    string line;
    while (getline(teachersFile, line)) {
        // Split the line into tokens
        std::istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // Check if the first token (username) matches the function parameter
        if (!tokens.empty() && tokens[0] == teacherUsername) {
            teacherLine = line;
            break;
        }
    }

    teachersFile.close();

    if (teacherLine.empty()) {
        cout << "Teacher with username " << teacherUsername << " does not exist." << endl;
        return;
    }

    // Extract the student usernames from the teacher's line after the comma
    vector<string> studentUsernames;
    size_t commaPos = teacherLine.find(',');
    if (commaPos != string::npos) {
        string usernamesStr = teacherLine.substr(commaPos + 1);
        std::istringstream iss(usernamesStr);
        string username;
        while (iss >> username) {
            studentUsernames.push_back(username);
        }
    }

    cout << "Teacher line: " << teacherLine << endl;
    if (studentUsernames.empty()) {
        cout << "No students for this teacher." << endl;
    }
    else {
        cout << "Student usernames: ";
        for (const string& username : studentUsernames) {
            cout << username << " ";
        }
        cout << endl;
    }

    // Open the students.txt file
    ifstream studentsFile("students.txt");
    if (!studentsFile) {
        std::cerr << "Failed to open the students file." << endl;
        return;
    }

    std::map<string, vector<string>> studentData;  // Mapping of student usernames to their information
    while (getline(studentsFile, line)) {
        std::istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            string username = tokens[0];
            vector<string> info(tokens.begin() + 1, tokens.end());
            studentData[username] = info;
        }
    }

    studentsFile.close();

    // Display the list of students
    cout << "List of students:" << endl;
    int index = 1;
    for (const auto& student : studentData) {
        cout << index << ") " << student.first << " - ";
        for (const string& info : student.second) {
            cout << info << " ";
        }
        cout << endl;
        index++;
    }

    // Ask the user to select a student to add
    string selectedStudent;
    while (true) {
        cout << "Enter the username of the student to add (or 'done' to finish): ";
        cin >> selectedStudent;

        if (selectedStudent == "done") {
            break;
        }

        // Check if the selected student is already assigned to the teacher
        if (find(studentUsernames.begin(), studentUsernames.end(), selectedStudent) != studentUsernames.end()) {
            cout << "Student with username " << selectedStudent << " is already assigned to the teacher." << endl;
        }
        // Check if the selected student is valid
        else if (studentData.find(selectedStudent) == studentData.end()) {
            cout << "Invalid student username. Please enter a valid username." << endl;
        }
        else {
            // Add the student to the teacher's list
            studentUsernames.push_back(selectedStudent);
            cout << "Student with username " << selectedStudent << " added." << endl;
        }
    }

    // Update the teacher's line with the selected students
    string updatedTeacherLine = teacherLine.substr(0, commaPos + 1);
    for (const string& username : studentUsernames) {
        updatedTeacherLine += " " + username;
    }

    // Create a temporary file for writing the updated data
    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cerr << "Failed to create the temporary file." << endl;
        return;
    }

    // Open the teachers.txt file again for reading
    ifstream teachersInputFile("teachers.txt");
    if (!teachersInputFile) {
        std::cerr << "Failed to open the teachers input file." << endl;
        return;
    }

    // Write the updated data to the temporary file
    while (getline(teachersInputFile, line)) {
        if (line == teacherLine) {
            tempFile << updatedTeacherLine << endl;
        }
        else {
            tempFile << line << endl;
        }
    }

    // Close the input and temporary files
    teachersInputFile.close();
    tempFile.close();

    // Remove the original teachers.txt file
    remove("teachers.txt");

    // Rename the temporary file to teachers.txt
    if (rename("temp.txt", "teachers.txt") != 0) {
        std::cerr << "Failed to rename the temporary file." << endl;
        return;
    }

    cout << "Teacher with username " << teacherUsername << " updated successfully." << endl;
}


void removeStudentFromTeacher(const string& teacherUsername) {
    // Open the teachers.txt file
    ifstream teachersFile("teachers.txt");
    if (!teachersFile) {
        std::cerr << "Failed to open the teachers file." << endl;
        return;
    }

    string teacherLine;
    string line;
    while (getline(teachersFile, line)) {
        // Split the line into tokens
        std::istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // Check if the first token (username) matches the function parameter
        if (!tokens.empty() && tokens[0] == teacherUsername) {
            teacherLine = line;
            break;
        }
    }

    teachersFile.close();

    if (teacherLine.empty()) {
        cout << "Teacher with username " << teacherUsername << " does not exist." << endl;
        return;
    }

    // Extract the student usernames from the teacher's line after the comma
    vector<string> studentUsernames;
    size_t commaPos = teacherLine.find(',');
    if (commaPos != string::npos) {
        string usernamesStr = teacherLine.substr(commaPos + 1);
        std::istringstream iss(usernamesStr);
        string username;
        while (iss >> username) {
            studentUsernames.push_back(username);
        }
    }

    if (studentUsernames.empty()) {
        cout << "No students associated with teacher " << teacherUsername << "." << endl;
        return;
    }

    // Display the students associated with the teacher
    cout << "Students associated with " << teacherUsername << ":" << endl;
    int index = 1;
    for (const string& username : studentUsernames) {
        cout << index << ") " << username << endl;
        index++;
    }

    // Ask the user to select a student to remove
    int selectedStudentIndex;
    while (true) {
        cout << "Enter the index of the student to remove (or 0 to cancel): ";
        cin >> selectedStudentIndex;

        if (selectedStudentIndex == 0) {
            return;
        }

        // Validate the selected student index
        if (selectedStudentIndex < 1 || selectedStudentIndex > studentUsernames.size()) {
            cout << "Invalid student index. Please enter a valid index." << endl;
        }
        else {
            // Remove the selected student from the list
            string selectedStudent = studentUsernames[selectedStudentIndex - 1];
            studentUsernames.erase(studentUsernames.begin() + selectedStudentIndex - 1);
            cout << "Student " << selectedStudent << " removed from teacher " << teacherUsername << "." << endl;
            break;
        }
    }

    // Update the teacher's line with the remaining students
    string updatedTeacherLine = teacherLine.substr(0, commaPos + 1);
    for (const string& username : studentUsernames) {
        updatedTeacherLine += " " + username;
    }

    // Create a temporary file for writing the updated data
    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cerr << "Failed to create the temporary file." << endl;
        return;
    }

    // Open the teachers.txt file again for reading
    ifstream teachersInputFile("teachers.txt");
    if (!teachersInputFile) {
        std::cerr << "Failed to open the teachers input file." << endl;
        return;
    }

    // Write the updated data to the temporary file
    while (getline(teachersInputFile, line)) {
        if (line == teacherLine) {
            tempFile << updatedTeacherLine << endl;
        }
        else {
            tempFile << line << endl;
        }
    }

    // Close the input and temporary files
    teachersInputFile.close();
    tempFile.close();

    // Remove the original teachers.txt file
    remove("teachers.txt");

    // Rename the temporary file to teachers.txt
    if (rename("temp.txt", "teachers.txt") != 0) {
        std::cerr << "Failed to rename the temporary file." << endl;
        return;
    }

    cout << "Teacher with username " << teacherUsername << " updated successfully." << endl;
}


int main()
{
    cout << "Welcome to iLearn learning platform" << endl;
    cout << "Sign up function" << endl;

    while (true){
        int choice;
        cout << "Login Menu:\n";
        cout << "1. Student login\n";
        cout << "2. Student Signup\n";
        cout << "3. Teacher login\n";
        cout << "9. Quit the program\n";
        cout << "Enter your choice: ";
        cin >> choice;
        string user = "";
        string pass = "";
        bool output = false;
        if (choice == 9) {
            cout << "This program has been ended" << endl;
            break;
        }

        switch (choice) {

            case 1:
                cout << "You selected Option 1.\n";
                cout << "Enter username = ";
                cin >> user;
                cout << "Enter password = ";
                cin >> pass;
                output = (logInStudent(user, pass)) ? true : false;
                if (output == true) {
                    cout << "Successfully logged in\nWelcome!!!" << endl;
                    while (true) {
                        cout << "Enter which of these functionalities you would like to do?" << endl;
                        cout << "1) Change 1 of your course" << endl;
                        cout << "2) Check all of your information" << endl;
                        cout << "3) Sign out" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 3) {
                            cout << "You have logged out" << endl;
                            cout << endl;
                            break;
                        }
                        switch (choice) {
                        case 1:
                            cout << "Here you are changing your course : " << endl;
                            changeCourses(user);
                            cout << endl;
                            break;
                        case 2:
                            cout << "Here you are checking your information : " << endl;
                            showStudentDetails(user);
                            cout << endl;
                            break;
                        default:
                            cout << "Kindly choose a valid option" << endl;
                            cout << endl;
                            break;
                        }
                    }
                    
                }
                else {
                    cout << "Looks like you entered invalid creditionals or you might wanna sign up" << endl;
                    cout << "Kindly choose another option for sign up as a student" << endl;
                }   
                
                break;

            case 2:
                cout << "You selected Option 2.\n";
                // Perform actions for Option 2
                signUpStudent();
                break;
            
            case 3:
                cout << "You selected Option 3.\n";
                cout << "Enter username = ";
                cin >> user;
                cout << "Enter password = ";
                cin >> pass;
                output = (logInTeacher(user, pass)) ? true : false;
                if (output == true) {
                    cout << "Successfully logged in\nWelcome!!!" << endl;
                    
                    while (true) {
                        cout << "Enter which of these functionalities you would like to do?" << endl;
                        cout << "1) Add a student in your class" << endl;
                        cout << "2) Remove a student from your class" << endl;
                        cout << "3) See your details" << endl;
                        cout << "4) Sign out" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 4) {
                            cout << "You have logged out" << endl;
                            cout << endl;
                            break;
                        }
                        switch (choice) {
                        case 1:
                            cout << "Here you are adding a student to your class : " << endl;
                            addStudentToTeacher(user);
                            cout << endl;
                            break;
                        case 2:
                            cout << "Here you are removing a student from your class : " << endl;
                            removeStudentFromTeacher(user);
                            cout << endl;
                            break;
                        case 3:
                            cout << "Here you are checking all of your information : " << endl;
                            showTeacherDetails(user);
                            break;
                        default:
                            cout << "Kindly choose a valid option" << endl;
                            cout << endl;
                            break;
                        }
                    }
                }
                else {
                    cout << "Looks like you entered invalid creditionals." << endl;
                    cout << "Or you might wanna head over to our office to apply as a Teacher/Professor" << endl;
                }
                
                break;;

            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
    
}

//make add/remove student, teacher should be able to see her information and the students that she is teaching as well.
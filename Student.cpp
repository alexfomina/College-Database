#include "Student.h"

/// @brief Default constructor for student object
Student::Student()
{
    id = -1;
    name = "";
    level = "";
    major = "";
    gpa = 1.0;
    advisor = -1;
}
/// @brief Default destructor for student object
Student::~Student()
{}

/// @brief Overloaded constructor for student object
/// @param id 
/// @param name 
/// @param level 
/// @param gpa 
/// @param advisor 
/// @param major 
Student::Student(int id, string name, string level, double gpa, int advisor, string major)
{
    this->id = id;
    this->name = name;
    this->level = level;
    this->major = major;
    this->gpa = gpa;
    this->advisor = advisor;
}

/// @brief Gets student ID
/// @return integer representation of student ID
int Student::getID()
{
    return id;
}

/// @brief Gets student name
/// @return string representation of student name
string Student::getName()
{
    return name;
}

/// @brief gets student year/level
/// @return string representation of student's year
string Student::getStudentLevel()
{
    return level;
}

/// @brief gets student's major
/// @return string representation of student's 
string Student::getStudentMajor()
{
    return major;
}

/// @brief gets student GPA
/// @return double representation of student GPA
double Student::getStudentGPA()
{
    return gpa;
}

/// @brief gets student advisor
/// @return integer representation of student's advisor
int Student::getStudentAdvisor()
{
    return advisor;
}

/// @brief Prints out student's name, major, their level, gpa and advisor
void Student::printInfo()
{
    cout << "ID: " << id << "\n Name: " << name << "\n Major: " << major << "\n Level: "
    << level << "\n GPA: " << gpa << "\nAdvisor: " << advisor << endl;;
}
/// @brief String representation of student's information
/// @return string
string Student::information()
{
    string s = "";
    s += "ID: " + to_string(id) + "\n Name: " + name + "\n Major: " + major + "\n Level: "
    + level + "\n GPA: " + to_string(gpa) + "\nAdvisor: " + to_string(advisor);
    return s;
}

/// @brief Changes studentAdvisor to a new faculty ID
/// @param ID 
void Student::setStudentAdvisor(int ID)
{
    advisor = ID;
}
/// @brief compares 2 students to see if they are equal
/// @param other
/// @return true if the students have the same ID, otherwise false
bool Student::operator==(const Student& other) const {
    return id == other.id;
}

/// @brief compares 2 students to see if they aren't equal
/// @param other 
/// @return true if the students do not have the same ID
bool Student::operator!=(const Student& other) const{
    return !(*this == other);
}

/// @brief checks to see if one student is smaller than the other
/// @param other 
/// @return true if the student_id is smaller, otherwise false
bool Student::operator<(const Student& other) const{
    return id < other.id;
}

/// @brief checks to see if one student is greater than the other
/// @param other 
/// @return true if the student_id is greater, otherwise false
bool Student::operator>(const Student& other) const{
    return id > other.id;
}

/// @brief checks to see if one student is smaller or equal to than the other
/// @param other 
/// @return true if the student_id is smaller or equal, otherwise false
bool Student::operator<=(const Student& other) const{
    return id <= other.id;
}

/// @brief checks to see if one student is greater or equal to than the other
/// @param other 
/// @return true if the student_id is greater or equal, otherwise false
bool Student::operator>=(const Student& other) const{
    return id >= other.id;
}


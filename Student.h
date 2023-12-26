#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

class Student
{
    public:
    Student();
    Student(int id, string name, string level, double gpa, int advisor, string major);
    virtual ~Student();
    int getID();
    string getName();
    string getStudentLevel();
    string getStudentMajor();
    int getStudentAdvisor();
    double getStudentGPA();
    void setStudentAdvisor(int ID);
    void printInfo();
    string information();

    //overloaded operators
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;

    private:
        int id;
        string name;
        string level;
        string major;
        double gpa;
        int advisor;

};

#endif
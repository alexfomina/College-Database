#ifndef FACULTY_H
#define FACULTY_H
#include "DblList.h"
#include "Student.h"
#include <iostream>
using namespace std;

class Faculty
{
    public:
    Faculty();
    Faculty(int id, string name, string level, string department);
    virtual ~Faculty();
    int getID();
    string getName();
    string getFacultyLevel();
    string getFacultyDepartment();
    void addAdvisee(Student* newStudent);
    void removeAdvisee(int id);
    int getAdviseeListSize();
    int getAdvisee(int i);
    void printInfo();
    void printAdvisees();
    string stringAdvisees();
    string information();

    //overloaded operators
    bool operator==(const Faculty& other) const;
    bool operator!=(const Faculty& other) const;
    bool operator<(const Faculty& other) const;
    bool operator>(const Faculty& other) const;
    bool operator<=(const Faculty& other) const;
    bool operator>=(const Faculty& other) const;

    private:
        int id;
        string name;
        string level;
        string department;
        DblList<int>* advisees;

};

#endif
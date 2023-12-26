#ifndef DATABASE_H
#define DATABASE_H
#include "Faculty.h"
#include "Student.h"
#include "LazyBST.h"

class Database{
    public:
        Database();
        virtual ~Database();
        //option 1 in database
        void printStudents();
        //option 2 in database
        void printFaculty();

        //one method used to print Faculty or Student by ID, option 3 & 4
        void findAndDisplay(int id, char C);

        //option 5
        void addNewStudent(Student* student);
        void addNewStudent();

        //option 7
        void addNewFacultyMember(Faculty* faculty);
        void addNewFacultyMember();

        //option 6 & 8, one method used to delete Faculty or Student by ID
        void deleteFromDataBase(int id, char C);

        //option 9
        void changeStudentAdvisor(int studentID, int facultyID);
        //option 10
        void removeAdvisee(int studentID, int facultyID);

        bool IDInTable(int id, char C);

        void printMenu();

        string stringStudents();
        string stringFaculty();
        
        
    private:
        LazyBST<Student*>* studentTable;
        LazyBST<Faculty*>* facultyTable;
};
#endif
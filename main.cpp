#include "Database.h"
#include <iostream>
#include <fstream>
int main()
{
    Database* myData = new Database();
    while (true)
    {
        cout << endl;
        myData->printMenu();
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            myData->printStudents();
        }
        else if (choice == 2)
        {
            myData->printFaculty();
        }
        else if (choice == 3)
        {
            cout << "Enter the student id" << endl;
            int id;
            cin >> id;
            myData->findAndDisplay(id, 'S');
        }
        else if (choice == 4)
        {
            cout << "Enter the faculty id" << endl;
            int id;
            cin >> id;
            myData->findAndDisplay(id, 'F');
        }
        else if (choice == 5)
        {
            myData->addNewStudent();
        }
        else if (choice == 6)
        {
            cout << "Enter student id: " << endl;
            int id;
            cin >> id;
            myData->deleteFromDataBase(id, 'S');
        }
        else if (choice == 7)
        {
            myData->addNewFacultyMember();
        }
        else if (choice == 8)
        {
            cout << "Enter faculty id: " << endl;
            int id;
            cin >> id;
            myData->deleteFromDataBase(id, 'F');
        }
        else if (choice == 9)
        {
            cout << "Enter student id: " << endl;
            int sID;
            cin >> sID;
            cout << "Enter faculty id: " << endl;
            int fID;
            cin >> fID;
            myData->changeStudentAdvisor(sID, fID);
        }
        else if (choice == 10)
        {
            cout << "Enter student id: " << endl;
            int sID;
            cin >> sID;
            cout << "Enter faculty id: " << endl;
            int fID;
            cin >> fID;
            myData->removeAdvisee(sID, fID);
        }
        else if (choice == 11)
        {
            cout << "Exiting program." << endl;
            string s = "";
            s += myData->stringStudents() + "\n" + myData->stringFaculty();
            //cout << "string s is " << s << endl;
            fstream outputFile("runLog.txt", ios::out);
            if (outputFile.is_open()) {
            // Write the string to the file
            outputFile << s << endl;
            // Close the file
            outputFile.close();}
            break;
        }
        else
        {
            cout << "Please enter a valid menu option" << endl;
        }
    }
}
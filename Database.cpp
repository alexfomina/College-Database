#include "Database.h"
#include <limits>

/// @brief Default constructor for Database
Database::Database()
{
    studentTable = new LazyBST<Student*>();
    facultyTable = new LazyBST<Faculty*>();
}
/// @brief Default destructor for Database
Database::~Database()
{
    delete studentTable;
    delete facultyTable;
}

/// @brief Method to add new faculty member, will prompt user for information
void Database::addNewFacultyMember()
{
    string name;
    int ID;
    string department;
    string level;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Name: " << endl;
    getline(cin, name);
    cout << "ID: " << endl;
    cin >> ID;
    while (IDInTable(ID, 'F'))
    {
        cout << "This ID already belongs to a faculty member. Please enter a unique ID." << endl;
        cin >> ID;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Department: " << endl;
    getline(cin,department);
    cout << "Level: " << endl;
    getline(cin,level);
    Faculty* newFaculty= new Faculty(ID, name, level, department);
    facultyTable->insert(newFaculty);
}

/// @brief Overloaded method to add a new Faculty member to database
/// @param newFaculty 
void Database::addNewFacultyMember(Faculty* newFaculty)
{
    facultyTable->insert(newFaculty);
}

/// @brief Adds a new student to the table, prompts user for student info
void Database::addNewStudent()
{
    string name;
    int ID;
    string major;
    string level;
    double gpa;
    int advisor;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Name: " << endl;
    getline(cin, name);
    cout << "ID: " << endl;
    cin >> ID;
    //check to make sure user isn't adding a duplicate ID
    while (IDInTable(ID, 'S'))
    {
        cout << "This ID already belongs to a student. Please enter a unique ID." << endl;
        cin >> ID;
    }
    // Clear the newline character left in the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Get major
    cout << "Major: " << endl;
    getline(cin, major);
    // Get level
    cout << "Level: " << endl;
    getline(cin, level);
    // Get GPA
    cout << "GPA: " << endl;
    cin >> gpa;
    // Get advisor
    cout << "Advisor ID: " << endl;
    cin >> advisor;
    //A student will have a -1 value for their advisor if one has not yet been assigned
    Student* newStudent = new Student(ID,name,level, gpa, -1, major);
    studentTable->insert(newStudent);
    changeStudentAdvisor(ID, advisor);
}

/// @brief Adds a new student from a preexisting student object
/// @param newStudent 
void Database::addNewStudent(Student* newStudent)
{
    studentTable->insert(newStudent);
}

/// @brief Creates an array and pulls elements from the BST in order from smallest to largest
void Database::printFaculty()
{
    int size = facultyTable->getSize();
    if (size != 0)
    {
        facultyTable->printTreeInOrder();
    }
    else{
        cout << "No faculty records to print." << endl;
    }
}

/// @brief String representation of all information about the facultyTable
/// @return string
string Database::stringFaculty()
{
    string s = "";
    int size = facultyTable->getSize();
    if (size != 0)
    {
        Faculty** facultyArr = new Faculty*[size];
        int index = 0;
        facultyTable->extractValuesInOrder(facultyTable->getRoot(), facultyArr, index);
        for (int i = 0; i < size; ++i)
        {
            s+= facultyArr[i]->information() + "\n";
        }
        delete[] facultyArr;
        s+= "-----------------------------------------";

    }
    else{
        s+= "No faculty records to print.";
    }
    return s;
}

/// @brief Prints all of the students in the database by ascending IDs
void Database::printStudents()
{
    int size = studentTable->getSize();
    if (size != 0)
    {
       studentTable->printTreeInOrder();
    }
    else
    {
        cout << "No student records to print." << endl;
    }
}
/// @brief Returns a string full of information about all members of studentTable
/// @return string
string Database::stringStudents()
{
    string s = "";
    int size = studentTable->getSize();
    if (size != 0)
    {
        Student** studentArr = new Student*[size];
        int index = 0;
        studentTable->extractValuesInOrder(studentTable->getRoot(), studentArr, index);
        for (int i = 0; i < size; ++i)
        {
            s+= studentArr[i]->information() + "\n";
        }
        s += "-----------------------------------------------";
        delete[] studentArr;
    }
    else
    {
        s+= "No student records to print.";
    }
    return s;
}

/// @brief Finds and print information from a given ID, based on the character entered: either F or S, calling faculty or student
/// databases, respectively
/// @param id 
/// @param C 
void Database::findAndDisplay(int id, char C)
{
    //Checks to see if it should call the faculty table or the student table
    if (C == 'F')
    {
        TreeNode<Faculty*>* result = facultyTable->findElement(id);
        if (result != nullptr)
        //aka the element actually exists
        {
            result->m_data->printInfo();
        }
        else
        {
            cout << "ID: " << id << " does not exist in the database" << endl;
        }      
    }
    else
    {
        TreeNode<Student*>* result = studentTable->findElement(id);
        if (result != nullptr)
        //aka the element actually exists
        {
            result->m_data->printInfo();
        }
        else
        {
            cout << "ID: " << id << " does not exist in the database" << endl;
        }
    }
    
}

/// @brief Removes either student or faculty object from databse based on given char, either F or S, based on the object's ID
/// @param id 
/// @param C 
void Database::deleteFromDataBase(int id, char C)
{
    //First check to see if we need to call faculty data or student data
    if (C == 'F')
    {
        TreeNode<Faculty*>* result = facultyTable->findElement(id);
        if (result != nullptr)
        //aka the element actually exists
        {
            Faculty* facDelete = result->m_data;
            //check to see if the faculty member has any advisees
            for (int i = 0; i < facDelete->getAdviseeListSize(); ++i)
            {
                studentTable->findElement(facDelete->getAdvisee(i))->m_data->setStudentAdvisor(-1);
            }
            facultyTable->remove(facDelete);
            cout << "Successfully deleted. " << endl;
        }
        else
        {
            cout<< "You cannot delete a faculty member that does not exist in the database." << endl;
            return;
        }      

    }
    //Call the studentTable to find the element
    else
    {
        TreeNode<Student*>* result = studentTable->findElement(id);
        if (result != nullptr)
        {
            Student* studDelete = result->m_data;
            //update the student's advisor and remove the student from their list
            //check to see if the student has a valid advisor
            if (studDelete->getStudentAdvisor() != -1)
            {
                facultyTable->findElement(studDelete->getStudentAdvisor())->m_data->removeAdvisee(studDelete->getID());
                
            }
            
            studentTable->remove(studDelete);
            cout << "Successfully deleted" << endl;
        }
        else{
            cout << "You cannot delete a student that does not exist in the database." << endl;
            return;
        }
    }
}

/// @brief Changes a studentAdvisor to new facultyID
/// @param studID 
/// @param facID 
void Database::changeStudentAdvisor(int studID, int facID)
{
    //first check that the studentID and facultyID are valid ID's inside the database
    cout << "Setting student advisor." << endl;
    TreeNode<Faculty*>* resultF = facultyTable->findElement(facID);
    TreeNode<Student*>* resultS = studentTable->findElement(studID);
    if (resultF == nullptr && resultS != nullptr)
    {
        cout << "Change unsuccessful. This faculty member does not exist in the database." << endl;
        Student* currentStudent = resultS->m_data;
        currentStudent->setStudentAdvisor(-1);
        return;
    }
    else if (resultS == nullptr)
    {
        cout << "Change unsuccessful. This student does not exist in the database" << endl;
        return;
    }
    else
    {
        //find the current Student object
        Student* currentStudent = resultS->m_data;
        //find the faculty object to add new student advisee to
        Faculty* facultyToAddStudent = resultF->m_data;
        //remove the student from the old advisor's list
        if (currentStudent->getStudentAdvisor() != -1)
        {
            facultyTable->findElement(currentStudent->getStudentAdvisor())->m_data->removeAdvisee(currentStudent->getID());
        }
        //add the new student as an advisee
        facultyToAddStudent->addAdvisee(currentStudent);
        //change the currentStudent's faculty ID to the new faculty member
        currentStudent->setStudentAdvisor(facultyToAddStudent->getID());
    }
}

/// @brief Removes a student from Faculty member's advisee list based on respective IDs
/// @param studID 
/// @param facID 
void Database::removeAdvisee(int studID, int facID)
{
    TreeNode<Faculty*>* resultF = facultyTable->findElement(facID);
    TreeNode<Student*>* resultS = studentTable->findElement(studID);
    if (resultF == nullptr)
    {
        cout << "You cannot remove an advisee from a faculty member that does not exist in the database." << endl;
    }
    else if (resultS == nullptr)
    {
        cout << "Removal unsuccessful. This student does not exist in the database." << endl;
    }
    else{
        //find the faculty object
        Faculty* currFac = resultF->m_data;
        //find the student object
        Student* currStud = resultS->m_data;
        currStud->setStudentAdvisor(-1);
        currFac->removeAdvisee(studID);
        cout << "Student was removed from advisee list." << endl;
    }
}

/// @brief Checks whether an ID is in student/faculty table based on given character
/// @param id 
/// @param C 
/// @return bool
bool Database::IDInTable(int id, char C)
{
    if (C == 'F')
    {
        if (facultyTable->findElement(id) != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (studentTable->findElement(id) != nullptr)
        {
            return true;
        }
        else{
            return false;
        }
    }
}

/// @brief Prints the menu for users to see
void Database::printMenu()
{
    cout << "|--------------------------------------------|" << endl;
    cout << "Enter 1 to print all students" << endl;
    cout << "Enter 2 to print all faculty" << endl;
    cout << "Enter 3 to find a specific student" << endl;
    cout << "Enter 4 to find a specific faculty member" << endl;
    cout << "Enter 5 to add a new student" << endl;
    cout << "Enter 6 to delete a specifc student" << endl;
    cout << "Enter 7 to add a new faculty member" << endl;
    cout << "Enter 8 to delete a faculty member" << endl;
    cout << "Enter 9 to change a student's advisor" << endl;
    cout << "Enter 10 to remove a faculty's advisee" << endl;
    cout << "Enter 11 to quit" << endl;
    cout << "|--------------------------------------------|" << endl;

}

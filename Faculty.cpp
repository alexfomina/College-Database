#include "Faculty.h"

/// @brief Default Constructor for Faculty Object
Faculty::Faculty()
{
    id = -1;
    name = "";
    level = "";
    department = "";
    advisees = new DblList<int>();
}

/// @brief Default destructor for Faculty object;
Faculty::~Faculty()
{
    delete advisees;
}

/// @brief Overloaded constructor for Faculty object
/// @param id 
/// @param name 
/// @param level 
/// @param department 
Faculty::Faculty(int id, string name, string level, string department)
{
    this->id = id;
    this->name = name;
    this->level = level;
    this->department = department;
    advisees = new DblList<int>();
}

/// @brief Gets Faculty ID
/// @return integer representation of Faculty ID
int Faculty::getID()
{
    return id;
}

/// @brief Gets Faculty name
/// @return string representation of Faculty name
string Faculty::getName()
{
    return name;
}

/// @brief gets student year/level
/// @return string representation of student's year
string Faculty::getFacultyLevel()
{
    return level;
}

/// @brief gets student's major
/// @return string representation of student's 
string Faculty::getFacultyDepartment()
{
    return department;
}

/// @brief Adds a Student Object to advisee list
/// @param newStudent 
void Faculty::addAdvisee(Student* newStudent)
{
    int newStudentID = newStudent->getID();

    //If the list is empty or this student ID is smaller than curr front
    // add to front of list
    if (advisees->getSize() == 0 || newStudentID < advisees->get(0))
    {
        advisees->addFront(newStudent->getID());
    }
    else
    {
        int index = 0;
        while (index < advisees->getSize() && newStudentID > advisees->get(index))
        {
            ++index;
        }
        advisees->add(index, newStudent->getID());
    }
}

/// @brief Print's advisee list with student information
void Faculty::printAdvisees()
{
    int size = advisees->getSize();
    if (size == 0)
    {
        cout << "This faculty member has no advisees" << endl;
    }
    else
    {
        cout << "Advisees: " << endl;
        for (int i = 0; i < size; ++i)
        {
            cout << "Student: ";
            cout << advisees->get(i) << ", ";
        }
        cout << endl;
    }
}

/// @brief String representation of advisee list
/// @return string
string Faculty::stringAdvisees()
{
    //cout << "inside method" << endl;
    string s = "";
    int size = advisees->getSize();
    if (size == 0)
    {
        s =  "Advisees: This faculty member has no advisees";
    }
    else
    {
        s = "Advisees: ";
        for (int i = 0; i < size; ++i)
        {
            s+= "Student: " + to_string(advisees->get(i)) + " ";
        }
        s += "\n";
    } 
    return s;
}

/// @brief Print's out faculty information, including ID, name, department, and level
void Faculty::printInfo()
{
    cout << "ID: " << id << "\n Name: " << name << "\n Department: " << department << "\n Level: "
    << level << endl;
    printAdvisees();
}

/// @brief String representaiton of individual faculty object private member variables
/// @return string
string Faculty::information()
{
    string s = "";
    s += "ID: " + to_string(id) + "\n Name: " + name + "\n Department: " + department + "\n Level: "
    + level + "\n" + stringAdvisees();
    return s;
}

/// @brief Returns size of advisee list
/// @return int
int Faculty::getAdviseeListSize()
{
    return advisees->getSize();
}

/// @brief Returns a student advisee's ID based on index
/// @param i 
/// @return int representation of student ID
int Faculty::getAdvisee(int i)
{
    if (i < advisees->getSize())
    {
        return advisees->get(i);
    }
    return -1;
}
/// @brief Deletes a student based on ID from advisee list
/// @param ID 
void Faculty::removeAdvisee(int ID)
{
    int size = advisees->getSize();
    for (int i = 0; i < size; ++i)
    {
        //we found the correct position in the list
        if (advisees->get(i) == ID)
        {
            advisees->remove(i);
            return;
        }
    }
}
/// @brief compares 2 Faculty to see if they are equal
/// @param other
/// @return true if the Faculty have the same ID, otherwise false
bool Faculty::operator==(const Faculty& other) const {
    return id == other.id;
}

/// @brief compares 2 Faculty to see if they aren't equal
/// @param other 
/// @return true if the Faculty do not have the same ID
bool Faculty::operator!=(const Faculty& other) const{
    return !(*this == other);
}

/// @brief checks to see if one Faculty ID is smaller than the other
/// @param other 
/// @return true if the faculty_id is smaller, otherwise false
bool Faculty::operator<(const Faculty& other) const{
    return id < other.id;
}

/// @brief checks to see if one faculty is greater than the other
/// @param other 
/// @return true if the faculty_id is greater, otherwise false
bool Faculty::operator>(const Faculty& other) const{
    return id > other.id;
}

/// @brief checks to see if one Faculty id is smaller or equal to than the other
/// @param other 
/// @return true if the student_id is smaller or equal, otherwise false
bool Faculty::operator<=(const Faculty& other) const{
    return id <= other.id;
}

/// @brief checks to see if one faculty is greater or equal to than the other
/// @param other 
/// @return true if the faculty_id is greater or equal, otherwise false
bool Faculty::operator>=(const Faculty& other) const{
    return id >= other.id;
}
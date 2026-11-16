#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};

struct CourseRecord
{
    string code;
    double credits;
    int score;
};

struct GradeBand
{
    int minScore;
    string letter;
    double points;
};

const int numBands = 8;
const GradeBand gradeBands[numBands] = {
    {80, "A", 4.0},
    {75, "B+", 3.5},
    {70, "B", 3.0},
    {65, "C+", 2.5},
    {60, "C", 2.0},
    {55, "D+", 1.5},
    {50, "D", 1.0},
    {0, "F", 0.0}};

GradeBand lookupGrade(int score)
{
    for (int i = 0; i < numBands; i++)
    {
        if (score >= gradeBands[i].minScore)
        {
            return gradeBands[i];
        }
    }
    return gradeBands[7];
}

// Class Transcript that stores courses
class Transcript
{
private:
    CourseRecord *courses;
    int size;     // how many courses are stored
    int capacity; // size of the array

public:
    Transcript()
    {
        capacity = 2;
        size = 0;
        courses = new CourseRecord[capacity];
    }

    ~Transcript()
    {
        delete[] courses;
    }

    Transcript(const Transcript &) = delete;
    Transcript &operator=(const Transcript &) = delete;

    void addCourse(const CourseRecord &c)
    {
        if (size == capacity)
        {
            CourseRecord *capacity2 = new CourseRecord[capacity * 2];
            for (int i = 0; i < size; i++)
            {
                capacity2[i] = courses[i];
            }
            delete[] courses;
            courses = capacity2;
            capacity = capacity * 2;
        }
        courses[size] = c;
        size++;
    }
};

// base class Student
class Student
{
protected:
    string ID;
    string name;
    Date admissionDate;
    Transcript transcript;

public:
    Student(const string &ID, const string &name, const Date &admitted)
        : ID(ID), name(name), admissionDate(admitted)
    {
    }

    void printHeader() const
    {
        cout << "Name: " << name << " ID: " << ID << " Admitted: "
             << setfill('0') << setw(2) << admissionDate.day << "/"
             << setw(2) << admissionDate.month << "/"
             << admissionDate.year << setfill(' ') << endl;
    }
};

// Derived class UndergraduateStudent
class UndergraduateStudent : public Student
{
private:
    string major;
    int level;

public:
    UndergraduateStudent(const string &ID, const string &name, const Date &admitted,
                         const string &major, int level)
        : Student(ID, name, admitted), major(major), level(level)
    {
    }

    void printHeader() const
    {
        Student::printHeader();
        cout << "Programme: " << major << " Level: " << level << endl;
    }
};

int main()
{
    UndergraduateStudent ama("61242027", "Ama Serwaa Mensah", {12, 8, 2024},
                             "Computer Science", 200);
    ama.printHeader();
    return 0;
}
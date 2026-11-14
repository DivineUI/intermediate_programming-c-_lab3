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
class Student
{
private:
    string ID;
    string name;
    Date admissionDate;
    CourseRecord courses[10];
    int numCourses;
    static int count;

public:
    Student(const string &ID, const string &name, const Date &admitted)
        : ID(ID), name(name), admissionDate(admitted), numCourses(0)
    {
        count++;
    }

    string getID() const
    {
        return ID;
    }
    string getName() const
    {
        return name;
    }
    Date getAdmissionDate() const
    {
        return admissionDate;
    }
    int getNumCourses() const
    {
        return numCourses;
    }
    static int getCount()
    {
        return count;
    }
};

int Student::count = 0; // Initialize number of students to 0

int main()
{
    Student s1("68352028", "Efua Owusu", {12, 8, 2024});
    Student s2("61242027", "Ama Mensah", {12, 8, 2024});

    cout << s1.getName() << " " << s1.getID() << endl;
    cout << "Students: " << Student::getCount() << endl;
    return 0;
}
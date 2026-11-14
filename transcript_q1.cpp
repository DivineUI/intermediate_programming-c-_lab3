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
    // Initializing data members
    Student(string &ID, string &name, Date &admitted)
        : ID(ID), name(name), admissionDate(admitted), numCourses(0)
    {
        count++;
    }

    // Getters
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
    // Function to add a course
    void addCourse(CourseRecord &c)
    {
        if (numCourses < 10)
        {
            courses[numCourses] = c;
            numCourses++;
        }
    }
    // Function to calculate GPA
    double calculateGPA() const
    {
        double totalPoints = 0;
        double totalCredits = 0;
        for (int i = 0; i < numCourses; i++)
        {
            GradeBand g = lookupGrade(courses[i].score);
            totalPoints += g.points * courses[i].credits;
            totalCredits += courses[i].credits;
        }
        if (totalCredits == 0)
        {
            return 0;
        }
        double gpa = totalPoints / totalCredits;
        return gpa;
    }
    // Function to count credits earned
    double creditsEarned() const
    {
        double totalCredits = 0;
        for (int i = 0; i < numCourses; i++)
        {
            if (courses[i].score >= 50)
            {
                totalCredits += courses[i].credits;
            }
        }
        return totalCredits;
    }
};

int Student::count = 0; // Initialize number of students to 0

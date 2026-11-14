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
};

int main()
{
    cout << lookupGrade(84).letter << endl;
    cout << lookupGrade(75).letter << endl;
    cout << lookupGrade(47).letter << endl;
    return 0;
}
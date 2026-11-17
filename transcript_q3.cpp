#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

struct GradeBand
{
    int minScore;
    string letter;
    double points;
};

const int numBands = 8;
const GradeBand gradeBands[numBands] = {{80, "A", 4.0}, {75, "B+", 3.5}, {70, "B", 3.0}, {65, "C+", 2.5}, {60, "C", 2.0}, {55, "D+", 1.5}, {50, "D", 1.0}, {0, "F", 0.0}};

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

// Structs and exceptions
struct Course
{
    string code;
    string title;
    double credits;
    int score;
};

struct StudentRecord
{
    string id;
    string name;
    vector<Course> courses;
};

class InvalidScoreException : public invalid_argument
{
public:
    InvalidScoreException(const string &msg) : invalid_argument(msg) {}
};

class UnknownStudentException : public runtime_error
{
public:
    UnknownStudentException(const string &msg) : runtime_error(msg) {}
};

void processLine(const string &line, vector<StudentRecord> &students)
{
    istringstream iss(line);
    string type;
    iss >> type;

    if (type == "STUDENT")
    {
        StudentRecord s;
        if (!(iss >> s.id >> quoted(s.name)))
        {
            throw runtime_error("Invalid STUDENT record");
        }

        students.push_back(s);
    }
    else if (type == "COURSE")
    {
        string id;
        Course c;

        if (!(iss >> id >> c.code >> quoted(c.title) >> c.credits >> c.score))
        {
            throw runtime_error("Invalid COURSE record");
        }
        if (c.score < 0 || c.score > 100)
        {
            throw InvalidScoreException("Invalid score " + to_string(c.score) + " for " + c.code);
        }
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].id == id)
            {
                students[i].courses.push_back(c);
                return;
            }
        }

        throw UnknownStudentException("Unknown student ID " + id);
    }
    else
    {
        throw runtime_error("Invalid line type " + type);
    }
}

// Transcript file
void writeTranscript(const StudentRecord &s)
{
    ofstream out("transcript_" + s.id + ".txt");

    double totalPoints = 0;
    double totalCredits = 0;
    double earned = 0;

    out << "Name: " << s.name << "   ID: " << s.id << endl;
    out << left << setw(10) << "Code" << setw(36) << "Title" << setw(9) << "Credits" << setw(7) << "Score"
        << string(20, ' ') << "Grade" << endl;
    out << fixed << setprecision(1);

    for (size_t i = 0; i < s.courses.size(); i++)
    {
        const Course &c = s.courses[i];
        GradeBand g = lookupGrade(c.score);

        out << left << setw(10) << c.code << setw(36) << c.title << setw(9) << c.credits << setw(7) << c.score
            << string(20, ' ') << g.letter << endl;

        totalPoints += g.points * c.credits;
        totalCredits += c.credits;
        if (c.score >= 50)
        {
            earned += c.credits;
        }
    }

    double gpa = 0;
    if (totalCredits > 0)
    {
        gpa = totalPoints / totalCredits;
    }

    out << "GPA: " << setprecision(2) << gpa << " Credits earned: " << setprecision(1) << earned
        << " Standing: " << (gpa < 2.00 ? "Academic Probation" : "Good Standing") << endl;
}

int main()
{
    ifstream in("records.txt");
    if (!in)
    {
        cout << "Could not open records.txt" << endl;
        return 1;
    }
    ofstream errorLog("errors.log");

    vector<StudentRecord> students;
    string line;
    int lineNumber = 0;

    while (getline(in, line))
    {
        lineNumber++;
        try
        {
            processLine(line, students);
        }
        catch (const InvalidScoreException &e)
        {
            errorLog << "Line " << lineNumber << ": " << e.what() << endl;
        }
        catch (const UnknownStudentException &e)
        {
            errorLog << "Line " << lineNumber << ": " << e.what() << endl;
        }
        catch (const runtime_error &e)
        {
            errorLog << "Line " << lineNumber << ": " << e.what() << endl;
        }
    }

    for (size_t i = 0; i < students.size(); i++)
    {
        writeTranscript(students[i]);
    }

    return 0;
}
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

    // += adds a course and returns the transcript itself
    Transcript &operator+=(const CourseRecord &c)
    {
        addCourse(c);
        return *this;
    }

    double calculateGPA() const
    {
        double totalPoints = 0;
        double totalCredits = 0;
        for (int i = 0; i < size; i++)
        {
            GradeBand g = lookupGrade(courses[i].score);
            totalPoints += g.points * courses[i].credits;
            totalCredits += courses[i].credits;
        }
        if (totalCredits == 0)
        {
            return 0;
        }
        return totalPoints / totalCredits;
    }

    double creditsEarned() const
    {
        double total = 0;
        for (int i = 0; i < size; i++)
        {
            if (courses[i].score >= 50)
            {
                total += courses[i].credits;
            }
        }
        return total;
    }

    // Prints only the courses for which keep() returns true
    void printWhere(bool (*keep)(const CourseRecord &)) const
    {
        cout << left << fixed << setprecision(1);
        for (int i = 0; i < size; i++)
        {
            if (keep(courses[i]))
            {
                GradeBand g = lookupGrade(courses[i].score);
                cout << setw(10) << courses[i].code
                     << setw(9) << courses[i].credits
                     << setw(7) << courses[i].score
                     << setw(7) << g.letter
                     << setprecision(2) << g.points << setprecision(1) << endl;
            }
        }
    }

    friend ostream &operator<<(ostream &, const Transcript &t);
};

// Friend function: defined outside the class, no Transcript:: in front
ostream &operator<<(ostream &out, const Transcript &t)
{
    out << left << fixed << setprecision(1);
    out << setw(10) << "Course" << setw(9) << "Credits"
        << setw(7) << "Score" << setw(7) << "Grade" << "Points" << endl;

    for (int i = 0; i < t.size; i++)
    {
        GradeBand g = lookupGrade(t.courses[i].score);
        out << setw(10) << t.courses[i].code
            << setw(9) << t.courses[i].credits
            << setw(7) << t.courses[i].score
            << setw(7) << g.letter
            << setprecision(2) << g.points << setprecision(1) << endl;
    }
    out << "GPA: " << setprecision(2) << t.calculateGPA()
        << " Credits earned: " << setprecision(1) << t.creditsEarned();
    return out;
}

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

    string getName() const
    {
        return name;
    }

    const Transcript &getTranscript() const
    {
        return transcript;
    }

    // Uses += and returns *this so calls can be chained
    Student &addCourse(const CourseRecord &c)
    {
        transcript += c;
        return *this;
    }

    // Compares GPAs
    bool operator<(const Student &other) const
    {
        return transcript.calculateGPA() < other.transcript.calculateGPA();
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

    int getLevel() const
    {
        return level;
    }

    // ++a : raise level by 100 (max 400), return the student
    UndergraduateStudent &operator++()
    {
        if (level < 400)
        {
            level += 100;
        }
        return *this;
    }

    // a++ : same, but return the old level as an int
    int operator++(int)
    {
        int old = level;
        if (level < 400)
        {
            level += 100;
        }
        return old;
    }

    void printHeader() const
    {
        Student::printHeader();
        cout << "Programme: " << major << " Level: " << level << endl;
    }
};

bool isFailing(const CourseRecord &c)
{
    return c.score < 50;
}

int main()
{
    UndergraduateStudent ama("61242027", "Ama Serwaa Mensah", {12, 8, 2024},
                             "Computer Science", 200);
    UndergraduateStudent kwame("75112027", "Kwame Boateng", {14, 8, 2023},
                               "Business Administration", 300);

    // chained addCourse calls
    ama.addCourse({"CS313", 1.0, 84})
        .addCourse({"MATH221", 1.0, 72})
        .addCourse({"CS341", 1.0, 47});
    kwame.addCourse({"ECON101", 1.0, 63})
        .addCourse({"BUSA221", 1.0, 58});

    ama.printHeader();
    cout << ama.getTranscript() << endl;

    kwame.printHeader();
    cout << kwame.getTranscript() << endl;

    if (kwame < ama)
    {
        cout << "Higher GPA: " << ama.getName() << endl;
    }
    else
    {
        cout << "Higher GPA: " << kwame.getName() << endl;
    }

    cout << "Ama's failed courses:" << endl;
    ama.getTranscript().printWhere(isFailing);

    ++ama;
    cout << "After ++ama, level is " << ama.getLevel() << endl;

    int old = ama++;
    cout << "ama++ returned " << old << "; level is now " << ama.getLevel() << endl;

    return 0;
}
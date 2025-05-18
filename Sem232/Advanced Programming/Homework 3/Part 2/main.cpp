#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cstdlib>

using namespace std;

class Student;
class StudentFactory 
{
    public:
        static Student * createStudent (string type, string name, string dob, string schoolName, string courseName);
};

class Student 
{
    protected:
        string name;
        string dob;
        string schoolName;
        string courseName;

    public:
        Student (string name, string dob, string schoolName, string courseName)
            : name (name), dob (dob), schoolName (schoolName), courseName (courseName) {}

        virtual void displayInfo() = 0;
        virtual void DoAssignment() = 0;
        virtual void TakeTest() = 0;
        virtual void TakeExam() = 0;
        virtual void assignScore() = 0;
        virtual int totalScore() = 0;
};

class UniStudent : public Student 
{
    protected:
        vector<int> assignment;
        vector<int> test;
        vector<int> exam;

    public:
        UniStudent (string name, string dob, string schoolName, string courseName)
            : Student (name, dob, schoolName, courseName) {}

        void displayInfo() override 
        {
            cout << "University Student: " << name << ", DOB: " << dob << ", School: " << schoolName << ", Course: " << courseName << endl;
        }

        void DoAssignment() override
        {
            for (int i = 0; i < 8 * 4 * 3; i++)
                assignment.push_back (rand() % 101);
        }

        void TakeTest() override 
        {
            for (int i = 0; i < 8 * 4 * 2; i++)
                test.push_back (rand() % 101);
        }

        void TakeExam() override 
        {
            for (int i = 0; i < 8 * 4 * 1; i++)
                exam.push_back (rand() % 101);
        }

        void assignScore() override 
        {
            DoAssignment();
            TakeTest();
            TakeExam();
        }

        int totalScore() override 
        {
            int totalAss  = accumulate (assignment.begin(), assignment.end(), 0);
            int totalTest = accumulate (test.begin(), test.end(), 0);
            int totalExam = accumulate (exam.begin(), exam.end(), 0);
            return totalAss + totalTest + totalExam;
        }
};

class CollegeStudent : public Student 
{
    protected:
        vector<int> assignment;
        vector<int> test;
        vector<int> exam;

    public:
        CollegeStudent (string name, string dob, string schoolName, string courseName)
            : Student (name, dob, schoolName, courseName) {}

        void displayInfo() override 
        {
            cout << "College Student: " << name << ", DOB: " << dob << ", School: " << schoolName << ", Course: " << courseName << endl;
        }

        void DoAssignment() override 
        {
            for (int i = 0; i < 4 * 3 * 1; i++)
                assignment.push_back (rand() % 101);
        }

        void TakeTest() override {
            for (int i = 0; i < 4 * 3 * 1; i++)
                test.push_back (rand() % 101);
        }

        void TakeExam() override 
        {
            for (int i = 0; i < 4 * 3 * 1; i++)
                exam.push_back(rand() % 101);
        }

        void assignScore() override 
        {
            DoAssignment();
            TakeTest();
            TakeExam();
        }

        int totalScore() override 
        {
            int totalAss  = accumulate (assignment.begin(), assignment.end(), 0);
            int totalTest = accumulate (test.begin(), test.end(), 0);
            int totalExam = accumulate (exam.begin(), exam.end(), 0);
            return totalAss + totalTest + totalExam;
        }
};

// Factory method implementation
Student * StudentFactory::createStudent (string type, string name, string dob, string schoolName, string courseName) 
{
    if (type == "University")
        return new UniStudent (name, dob, schoolName, courseName);
    else if (type == "College")
        return new CollegeStudent (name, dob, schoolName, courseName);
    else 
    {
        cout << "Invalid student type" << endl;
        return nullptr;
    }
}

int main() 
{
    srand (time (nullptr) );

    Student* uniStudent = StudentFactory::createStudent ("University", "Khoa", "2000-01-01", "University B", "Computer Science");
    Student* collegeStudent = StudentFactory::createStudent ("College", "Khoi", "2001-01-01", "College L", "Mechanical Engineering");

    uniStudent->assignScore();
    collegeStudent->assignScore();

    uniStudent->displayInfo();
    cout << "Total score for University Student: " << uniStudent->totalScore() << endl;

    collegeStudent->displayInfo();
    cout << "Total score for College Student: " << collegeStudent->totalScore() << endl;

    delete uniStudent;
    delete collegeStudent;

    return 0;
}
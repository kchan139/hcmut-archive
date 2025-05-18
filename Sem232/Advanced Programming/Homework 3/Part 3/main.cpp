#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <memory> // For smart pointers

using namespace std;

class Student;
class StudentFactory 
{
    public:
        static unique_ptr<Student> createStudent(string type, string name, string dob, string schoolName, string courseName);
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

        virtual void displayInfo()  = 0;
        virtual void DoAssignment() = 0;
        virtual void TakeTest()     = 0;
        virtual void TakeExam()     = 0;
        virtual void assignScore()  = 0;
        virtual int  totalScore()   = 0;
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
            auto generateScore = []() { return rand() % 101; };
            assignment = vector<int> (8 * 4 * 3, generateScore());
        }

        void TakeTest() override {
            auto generateScore = []() { return rand() % 101; };
            test = vector<int> (8 * 4 * 2, generateScore());
        }

        void TakeExam() override {
            auto generateScore = []() { return rand() % 101; };
            exam = vector<int> (8 * 4 * 1, generateScore());
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
            auto generateScore = []() { return rand() % 101; };
            assignment = vector<int>(4 * 3 * 1, generateScore());
        }

        void TakeTest() override 
        {
            auto generateScore = []() { return rand() % 101; };
            test = vector<int>(4 * 3 * 1, generateScore());
        }

        void TakeExam() override 
        {
            auto generateScore = []() { return rand() % 101; };
            exam = vector<int>(4 * 3 * 1, generateScore());
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
unique_ptr<Student> StudentFactory::createStudent (string type, string name, string dob, string schoolName, string courseName) {
    if (type == "University")
        return make_unique<UniStudent> (name, dob, schoolName, courseName);
    else if (type == "College")
        return make_unique<CollegeStudent> (name, dob, schoolName, courseName);
    else 
    {
        cout << "Invalid student type" << endl;
        return nullptr;
    }
}

int main() 
{
    srand (time (nullptr));

    auto uniStudent = StudentFactory::createStudent ("University", "Khoa", "2000-01-01", "University B", "Computer Science");
    auto collegeStudent = StudentFactory::createStudent ("College", "Khoi", "2001-01-01", "College L", "Mechanical Engineering");

    uniStudent->assignScore();
    collegeStudent->assignScore();

    uniStudent->displayInfo();
    cout << "Total score for University Student: " << uniStudent->totalScore() << endl;

    collegeStudent->displayInfo();
    cout << "Total score for College Student: " << collegeStudent->totalScore() << endl;

    return 0;
}
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

class Student
{
    public:
        string name;
        string dob;
        string schoolName;
        string courseName;

        Student (string name, string dob, string schoolName, string courseName)
            : name (name), dob (dob), schoolName (schoolName), courseName (courseName) {}

        virtual void displayInfo () = 0; // Pure virtual function
        virtual void DoAssignment () = 0;
        virtual void TakeTest () = 0;
        virtual void TakeExam () = 0;
        virtual void assignScore ()
        {
            this->TakeExam ();
            this->TakeTest ();
            this->DoAssignment ();
        }

        virtual int totalScore () = 0;
};

class UniStudent : public Student
{
    private:
        int assignment[8 * 4 * 3];
        int test[8 * 4 * 2];
        int exam[8 * 4 * 1];

        int totalAss = 0;
        int totalTest = 0;
        int totalExam = 0;

    public:
        UniStudent (string name, string dob, string schoolName, string courseName)
            : Student (name, dob, schoolName, courseName) {}

        void displayInfo () override
        {
            cout << "University Student: " << name << ", DOB: " << dob << ", School: " << schoolName << ", Course: " << courseName << endl;
        }
        void DoAssignment () override
        {
            int size = sizeof (assignment) / sizeof (assignment[0]);
            for (int i = 0; i < size; i++)
            {
                assignment[i] = rand() % 101;
                totalAss += assignment[i];
            }
        }

        void TakeTest () override
        {
            int size = sizeof (test) / sizeof (test[0]);
            for (int i = 0; i < size; i++)
            {
                test[i] = rand() % 101;
                totalTest += test[i];
            }
        }

        void TakeExam () override
        {
            int size = sizeof (exam) / sizeof (exam[0]);
            for (int i = 0; i < size; i++)
            {
                exam[i] = rand() % 101;
                totalExam += exam[i];
            }
        }

        int totalScore()
        {
            return totalAss + totalTest + totalExam;
        }
};

class CollegeStudent : public Student
{
    private:
        int assignment[4 * 3 * 1];
        int test[4 * 3 * 1];
        int exam[4 * 3 * 1];

        int totalAss = 0;
        int totalTest = 0;
        int totalExam = 0;

    public:
        CollegeStudent (string name, string dob, string schoolName, string courseName)
            : Student (name, dob, schoolName, courseName) {}

        void displayInfo () override
        {
            cout << "College Student: " << name << ", DOB: " << dob << ", School: " << schoolName << ", Course: " << courseName << endl;
        }

        void DoAssignment () override
        {
            int size = sizeof (assignment) / sizeof (assignment[0]);
            for (int i = 0; i < size; i++)
            {
                assignment[i] = rand() % 101;
                totalAss += assignment[i];
            }
        }

        void TakeTest() override
        {
            int size = sizeof (test) / sizeof (test[0]);
            for (int i = 0; i < size; i++)
            {
                test[i] = rand() % 101;
                totalTest += test[i];
            }
        }

        void TakeExam() override
        {
            int size = sizeof (exam) / sizeof (exam[0]);
            for (int i = 0; i < size; i++)
            {
                exam[i] = rand() % 101;
                totalExam += exam[i];
            }
        }

        int totalScore()
        {
            return totalAss + totalTest + totalExam;
        }
};
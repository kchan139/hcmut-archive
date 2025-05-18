#include <iostream>
#include <string>
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

        virtual void displayInfo() = 0;
        virtual void DoAssignment() = 0;
        virtual void TakeTest() = 0;
        virtual void TakeExam() = 0;
        virtual void assignScore()
        {
            this->TakeExam();
            this->TakeTest();
            this->DoAssignment();
        }

        virtual int totalScore() = 0;
        virtual ~Student() {}
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

        void displayInfo() override
        {
            cout << "University Student: " << name << ", DOB: " << dob << ", School: " << schoolName << ", Course: " << courseName << endl;
        }

        void DoAssignment() override
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

        int totalScore() override
        {
            return totalAss + totalTest + totalExam;
        }

        ~UniStudent() {}
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

        void displayInfo() override 
        {
            cout << "College Student: " << name << ", DOB: " << dob << ", School: " << schoolName << ", Course: " << courseName << endl;
        }

        void DoAssignment() override
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

        int totalScore() override
        {
            return totalAss + totalTest + totalExam;
        }
};

class University
{
    private:
        string name;
        Student *students[100];
        int studentCount;

    public:
        University (string name) : name (name), studentCount (0) {}

        void addStudent()
        {
            if (studentCount >= 100)
            {
                cout << "\nUnable to add student. Student list is full.\n";
                return;
            }
            string studentName;
            string dob;
            string schoolName;
            string courseName;
            int studentType;

            cout << "\nEnter the name of the student: ";
            getline (cin, studentName);
            cout << "Enter the day of birth of the student: ";
            getline (cin, dob);
            cout << "Enter the name of the school: ";
            getline (cin, schoolName);
            cout << "Enter the name of the course: ";
            getline (cin, courseName);
            cout << "Enter the type of the student (University 1, college 2): ";
            cin >> studentType;

            cin.ignore();

            if (studentType == 1)
                students[studentCount] = new UniStudent(studentName, dob, schoolName, courseName);
            else
                students[studentCount] = new CollegeStudent(studentName, dob, schoolName, courseName);

            students[studentCount]->assignScore();

            studentCount++;
            cout << "\nStudent added successfully.\n";
        }

        void displayStudents()
        {
            cout << "\nList of students and scores:\n";
            for (int i = 0; i < studentCount; i++)
            {
                students[i]->displayInfo();
            }
        }

        void displayBestStudents()
        {
            int highestScore = 0;
            for (int i = 0; i < studentCount; i++)
            {
                if (students[i]->totalScore() > highestScore)
                {
                    highestScore = students[i]->totalScore();
                }
            }
            cout << "\nBest student(s) with overall score of " << highestScore << ":\n";
            for (int i = 0; i < studentCount; i++)
            {
                if (students[i]->totalScore() == highestScore)
                {
                    students[i]->displayInfo();
                }
            }
        }

        void removeStudent()
        {
            string name;
            cout << "\nEnter the name of the student to remove: ";
            getline (cin, name);

            for (int i = 0; i < studentCount; i++)
            {
                if (students[i]->name == name)
                {
                    delete students[i]; // Delete the student object
                    for (int j = i; j < studentCount - 1; j++)
                    {
                        students[j] = students[j + 1];
                    }
                    studentCount--;
                    cout << "\nStudent: " << name << " removed successfully.\n";

                    return;
                }
            }
            cout << "\nStudent not found.\n";
        }
};

int main()
{
    University university ("My University");
    int choice;
    while (true)
    {
        cout << "\n-----------------------------\n";
        cout << "Student Management Program\n";
        cout << "-----------------------------\n";
        cout << "1. Add student\n";
        cout << "2. Display students\n";
        cout << "3. Display best students\n";
        cout << "4. Remove students by name\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice)
        {
            case 1:
                university.addStudent();
                break;

            case 2:
                university.displayStudents();
                break;

            case 3:
                university.displayBestStudents();
                break;

            case 4:
                university.removeStudent();
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
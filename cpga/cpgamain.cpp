#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class CGPA {
private:
    int numberOfCourses;
    vector<double> grades;
    vector<int> credits;
    double grade;
    int credit;
    static int studentId;

public:
    void addGrades();
    void listGrades() const;
    double calculateGPA() const;
    double calculateCGPA() const;
};

// Initialize static member
int CGPA::studentId = 0;

void CGPA::addGrades() {
    fstream coursesData("coursesdata.txt", ios::out | ios::app);
    if (!coursesData.is_open()) {
        cout << "ERROR OPENING THE FILE !!\n";
        return;
    }

    cout << "Enter the number of courses: ";
    cin >> numberOfCourses;

    for (int i = 0; i < numberOfCourses; i++) {
        cout << "Enter the course grade for course " << i + 1 << ": ";
        cin >> grade;
        cout << "Enter the credit hours for course " << i + 1 << ": ";
        cin >> credit;
        grades.push_back(grade);
        credits.push_back(credit);
    }

    studentId++;
    coursesData << "Student " << studentId << ": ";
    for (int i = 0; i < numberOfCourses; i++) {
        coursesData << "Grade: " << grades[i] << " Credit: " << credits[i] << " | ";
    }
    coursesData << "\n";
    coursesData.close();
}

void CGPA::listGrades() const {
    fstream coursesData("coursesdata.txt", ios::in);
    if (!coursesData.is_open()) {
        cout << "ERROR OPENING THE FILE !!\n";
        return;
    }

    string line;
    cout << "========== Student Grades ==========\n";
    while (getline(coursesData, line)) {
        cout << line << endl;
    }
    coursesData.close();
}

double CGPA::calculateGPA() const {
    double totalGradePoints = 0;
    int totalCredits = 0;

    for (size_t i = 0; i < grades.size(); i++) {
        totalGradePoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }

    if (totalCredits == 0) return 0;

    return totalGradePoints / totalCredits;
}

double CGPA::calculateCGPA() const {
    
    return calculateGPA();
}

int main() {
    CGPA student1;
    student1.addGrades();
    student1.listGrades();

    cout << fixed << setprecision(2);
    cout << "GPA for the semester: " << student1.calculateGPA() << endl;
    cout << "Cumulative GPA (CGPA): " << student1.calculateCGPA() << endl;

    return 0;
}

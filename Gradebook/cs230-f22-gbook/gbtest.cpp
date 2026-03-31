/*
Anthony Pepe
CSCI 230
Gradebook
*/


#include <iostream>
#include <fstream>
#include "Gradebook.h"
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
  StudentT student[MAX_STUDENTS];
  GradebookT gradebook[MAX_GRADEBOOK];
  MathT math[MAX_MATH];
  int numStudents {0};
  int numGradebook {0};
  int numInput {0};
  
  ifstream gradebookFile;
  string filename {""};
  
  cout << "Name of file with grade data: ";
  cin >> filename; 
  gradebookFile.open(filename);
  if (!gradebookFile) {
    cout << "Unable to open file " << filename << endl;
  } else {
   
    ReadFromFile(gradebookFile, student, gradebook, numStudents, numGradebook);
    gradebookFile.close();

    GetStudentTestAverages(student, gradebook, math, numStudents);
    GetStudentHomeworkAverages(student, gradebook, math, numStudents);
    GetClassAverages(student, gradebook, math, numStudents);
    GetClassSDs(student, gradebook, math, numStudents);
    GetCourseGrades(gradebook, math, numStudents);
    
    cout << endl;
    PrintMenu();
    cin >> numInput;
  
    while (cin and numInput != 4) {
      if (numInput == 1) {
        PrintClassStats(gradebook, math);
      }
      if (numInput == 2) {
        PrintAllStudents(student, gradebook, math, numStudents);
      }
      if (numInput == 3) {
        PrintPassingStudents(student, gradebook, math, numStudents);
      }
      if (numInput != 4) {
        cout << endl;
        PrintMenu();
        cin >> numInput;
      }
    }
  }
  cout << endl;
  return 0;
}
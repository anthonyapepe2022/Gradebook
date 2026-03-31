#include <iostream>
#include <fstream>
#include "Gradebook.h"
#include <cmath>
#include <iomanip>


using namespace std;

void ReadFromFile(ifstream& inputFile, 
  StudentT student[], 
  GradebookT gradebook[], 
  int& numStudents, 
  int& numGradebook) {
  numStudents = 0;
  numGradebook = 0;
  getline(inputFile, gradebook[numGradebook].cName);
  inputFile >> gradebook[numGradebook].numTests;
  inputFile >> gradebook[numGradebook].numHomework;

  inputFile.ignore();

  getline(inputFile, student[numStudents].sName);
  while (inputFile and numStudents < MAX_STUDENTS) {
    inputFile >> student[numStudents].classLevel;
    for (int i = 0; i < MAX_TEST_GRADES; i++) {
      inputFile >> student[numStudents].testGrades[i];
    }
    for (int i = 0; i < MAX_HWK_GRADES; i++) {
      inputFile >> student[numStudents].hwkGrades[i];
    }
    numStudents++;

    if (numStudents < MAX_STUDENTS) {
      inputFile.ignore();
      getline(inputFile, student[numStudents].sName);
    } 
  }
}

void PrintMenu() {
  cout << "Menu: (Enter 1-4) " << endl << endl;
  cout << "1: Show class statistics " << endl;
  cout << "2: List students " << endl;
  cout << "3: List passing students " << endl;
  cout << "4: Exit " << endl << endl;
  cout << "Please enter your selection: ";
}

void GetClassAverages(StudentT student[], GradebookT gradebook[], MathT math[], int numStudents) {
  double cTestAverage {0.0};
  double cHwkAverage {0.0};
  double sum {0.0};
  for (int i = 0; i < gradebook[0].numTests; i++) {
    for (int j = 0; j < numStudents; j++) {
      sum += student[j].testGrades[i];
    }
    cTestAverage = sum/numStudents;
    sum = 0.0;
    math[i].cTestAverages = cTestAverage;
    cTestAverage = 0.0;
  }
  for (int i = 0; i < gradebook[0].numHomework; i++) {
    for (int j = 0; j < numStudents; j++) {
      sum += student[j].hwkGrades[i];
    }
    cHwkAverage = sum/numStudents;
    sum = 0.0;
    math[i].cHwkAverages = cHwkAverage;
    cHwkAverage = 0.0;
  }
}

void GetClassSDs(StudentT student[], GradebookT gradebook[], MathT math[], int numStudents) {
  double cTestSD {0.0};
  double cHwkSD {0.0};
  double quotient {0.0};
  double sum {0.0};

  for (int i = 0; i < gradebook[0].numTests; i++) {
    for (int j = 0; j < numStudents; j++) {
      sum += pow ((student[j].testGrades[i] - math[i].cTestAverages[i]), 2);
      if (j < numStudents and i < gradebook[0].numTests) {
        sum = 0.0;
        sum += pow ((student[j].testGrades[i] - math[i+1].cTestAverages[i+1]), 2);
      }
    }
    quotient = sum/(gradebook[0].numTests - 1);
    sum = 0.0;
    cTestSD = sqrt (quotient);
    quotient = 0.0; 
    math[i].cTestSDs[i] = cTestSD;
    cTestSD = 0.0;
  }
  for (int i = 0; i < gradebook[0].numHomework; i++) {
    for (int j = 0; j < numStudents; j++) {
      if (j < numStudents) {
        sum = 0.0;
        sum += pow ((student[j].hwkGrades[i] - math[i+1].cHwkAverages[i+1]), 2);
      }
    }
    quotient = sum/(gradebook[0].numTests - 1);
    sum = 0.0;
    cHwkSD = sqrt (quotient);
    quotient = 0.0;
    math[i].cHwkSDs[i] = cHwkSD;
    cHwkSD = 0.0;
  }
}

void GetStudentTestAverages(StudentT student[], GradebookT gradebook[], MathT math[], int numStudents) {
  double tAverage {0.0};
  double sum {0.0};
  for (int i = 0; i < numStudents; i++) {
    for (int j = 0; j < gradebook[0].numTests; j++) {
      if (j < gradebook[0].numTests) {
        sum += student[i].testGrades[j];
      }
    }
    tAverage = sum/gradebook[0].numTests;
    sum = 0.0;
    math[i].sTestAverages[i] = tAverage;
  }
}

void GetStudentHomeworkAverages(StudentT student[], GradebookT gradebook[], MathT math[], int numStudents) {
  double hAverage {0.0};
  double sum {0.0};
  for (int i = 0; i < numStudents; i++) {
    for (int j = 0; j < gradebook[0].numHomework; j++) {
      if (j < gradebook[0].numHomework) {
        sum += student[i].hwkGrades[j];
      }
    }
    hAverage = sum/gradebook[0].numHomework;
    sum = 0.0;
    math[i].sHwkAverages[i] = hAverage;
  }
}

void GetCourseGrades(GradebookT gradebook[], MathT math[], int numStudents) {
  double cGrade {0.0};
  for (int i = 0; i < numStudents; i++) {
    cGrade = (math[i].sTestAverages[gradebook[0].numTests] * .4) + (math[i].sHwkAverages[gradebook[0].numHomework] * .6);
    math[i].sCourseGrades[i] = cGrade;
    cGrade = 0.0;
  }
}


void PrintClassStats(GradebookT gradebook[], MathT math[]) {
  cout << "Statistics for class: " << gradebook[0].cName << endl << endl;
  cout << setw(10) << left << "Test";
  cout << setw(7) << right << "Average";
  cout << setw(6) << right << "SD" << endl;
  for (int i = 0; i < gradebook[0].numTests; i++) {
    cout << left << setw(10) << (i+1);
    cout << right << fixed << setw(7) << setprecision(1) << math[i].cTestAverages[i];
    cout << right << fixed << setw(6) << setprecision(1) << math[i].cTestSDs[i] << endl;
  }
  cout << endl;
  cout << setw(10) << left << "Homework";
  cout << setw(7) << right << "Average";
  cout << setw(6) << right << "SD" << endl;
  for (int i = 0; i < gradebook[0].numHomework; i++) {
    cout << left << setw(10) << (i+1);
    cout << right << fixed << setw(7) << setprecision(1) << math[i].cHwkAverages[i];
    cout << right << fixed << setw(6) << setprecision(1) << math[i].cHwkSDs[i] << endl;
  }
  cout << endl;
}

void PrintAllStudents (StudentT student[], GradebookT gradebook[], MathT math[], int numStudents) {
  for(int i = 0; i < numStudents; i++) {
    cout << "Name: " << student[i].sName << "\t" << "Level: " << student[i].classLevel << endl;
    cout << "Test Average: ";
    cout << setprecision(1) << math[i].sTestAverages[gradebook[0].numTests];
    cout << "\t" << "Homework Average: ";
    cout << setprecision(1) << math[i].sHwkAverages[gradebook[0].numHomework] << endl;
    cout << "Course Average: ";
    cout << setprecision(1) << math[i].sCourseGrades[i] << endl;
    if (i < numStudents) {
      cout << endl;
    }
  }
}

void PrintPassingStudents(StudentT student[], GradebookT gradebook[], MathT math[], int numStudents) {
  for(int i = 0; i < numStudents; i++) {
    if (math[i].sCourseGrades[i] >= 70.0) {
      cout << "Name: " << student[i].sName << "\t" << "Level: " << student[i].classLevel << endl;
      cout << "Test Average: ";
      cout << setw(4) << setprecision(1) << math[i].sTestAverages[gradebook[0].numTests];
      cout << "\t" << "Homework Average: ";
      cout << setw(4) << setprecision(1) << math[i].sHwkAverages[gradebook[0].numHomework] << endl;
      cout << "Course Average: ";
      cout << setw(4) << setprecision(1) << math[i].sCourseGrades[i] << endl;
    }
      if (i < numStudents) {
        cout << endl;
      }
  }
}

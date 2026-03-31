#ifndef GRADEBOOK
#define GRADEBOOK

#include <string>

const int MAX_TEST_GRADES = 3;
const int MAX_HWK_GRADES = 7;

const int MAX_STUDENTS = 40;
const int MAX_GRADEBOOK = 1;

const int MAX_MATH = 7;
const int MAX_ROWS = 8;
struct StudentT {
  std::string sName = "";
  int classLevel;
  double testGrades[MAX_TEST_GRADES];
  double hwkGrades[MAX_HWK_GRADES];
};

struct GradebookT {
  std::string cName = "";
  int numTests;
  int numHomework;
  StudentT students[MAX_STUDENTS];
};

struct MathT {
  double cTestAverages[MAX_TEST_GRADES];
  double cHwkAverages[MAX_HWK_GRADES];
  double cTestSDs[MAX_TEST_GRADES];
  double cHwkSDs[MAX_HWK_GRADES];
  double sTestAverages[MAX_STUDENTS];
  double sHwkAverages[MAX_STUDENTS];
  double sCourseGrades[MAX_STUDENTS];
};

void ReadFromFile(std::ifstream&, StudentT[], GradebookT[], int&, int&);

void PrintMenu();

void GetClassAverages(StudentT[], GradebookT[], MathT[], int);

void GetClassSDs(StudentT[], GradebookT[], MathT[], int);

void GetStudentTestAverages(StudentT[], GradebookT[], MathT[], int);

void GetStudentHomeworkAverages(StudentT[], GradebookT[], MathT[], int);

void GetCourseGrades(GradebookT[], MathT[], int);

void PrintClassStats(GradebookT[], MathT[]);

void PrintAllStudents(StudentT[], GradebookT[], MathT[], int);

void PrintPassingStudents(StudentT[], GradebookT[], MathT[], int);

#endif
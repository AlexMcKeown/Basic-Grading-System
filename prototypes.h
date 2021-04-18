#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>

struct Student
{
    std::string name, stdCode;
    int ability, consistency;
    std::string programName;
    std::vector<int> subjectList;
};

struct Subject
{
    std::string name;
    int difficulty, variability;
};

struct Teacher
{
    std::string name;
    int toughness, variability;
    std::vector<int> subjectList;
};

std::string removeSpaces(std::string str); // Removes Spaces from strings

std::string grader(int mark);    // Grades exams
std::string graderSup(int mark); // Grades sup exams
int checkRange(int &mark);       // Stop marks from exceeding the min(0) and max(100)

int stringToInteger(std::string str); // Converts String to Int
bool positiveIntVer(std::string str); // Natural Numbers (+0) verifiy process
bool intVerify(std::string str);      // Integer verifiy process

double mean(double stuAbility, double subjectDifficulty, double teachToughness);
double stdDeviation(double studConsistency, double subjectVariability, double teachVariability);

//Adds data to appropriate object which is then returned and added to vector in readData()
Student stuData(std::string str, int studentsSize);
Subject subData(std::string str, int subjectsSize);
Teacher teachData(std::string str, int teachersSize);

void fullPrint(std::vector<Student> students, std::vector<Subject> subjects, std::vector<Teacher> teachers); // Prints out file information in a readable format

void readData(int argc, const char *argv[], std::vector<Student> &students, std::vector<Subject> &subjects, std::vector<Teacher> &teachers);
void writeData(std::string argv, std::vector<Student> students, std::vector<Teacher> teachers, std::vector<Subject> subjects);

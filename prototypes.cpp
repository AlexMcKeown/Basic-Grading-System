#include "prototypes.h"

std::string removeSpaces(std::string str)
{
    std::string noSpaces;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            noSpaces += str[i];
        }
    }
    return noSpaces;
}

std::string grader(int mark)
{
    std::string gpa = "F";

    if (mark >= 50 && mark <= 64)
    {
        gpa = "P";
    }
    else if (mark >= 65 && mark <= 74)
    {
        gpa = "C";
    }
    else if (mark >= 75 && mark <= 84)
    {
        gpa = "D";
    }
    else if (mark >= 85 && mark <= 100)
    {
        gpa = "HD";
    }
    return gpa;
}

std::string graderSup(int mark)
{
    std::string gpa = "F";

    if (mark >= 50)
    {
        gpa = "50-PS";
    }
    return gpa;
}

int checkRange(int &mark) // Stop marks from exceeding the min(0) and max(100)
{
    if (mark > 100)
    {
        mark = 100;
    }
    else if (mark < 0)
    {
        mark = 0;
    }
    return mark;
}

int stringToInteger(std::string str)
{
    int number;
    std::istringstream iss(str);
    iss >> number;
    return number;
}

bool positiveIntVer(std::string str)
{
    bool verify = true;
    str = removeSpaces(str);
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == 0) // isdigit returns 0 only if char is not a digit
        {
            verify = false;
            break;
        }
    }
    return verify;
}

bool intVerify(std::string str) // Integer verifiy process
{
    bool verify = true;
    str = removeSpaces(str);
    for (int i = 0; i < str.length(); i++)
    {
        if (i == 0 && str[0] == '-' && str.length() > 1)
        {
        }
        else if (isdigit(str[i]) == 0) // isdigit returns 0 only if char is not a digit
        {
            verify = false;
            break;
        }
    }
    return verify;
}

double mean(double stuAbility, double subjectDifficulty, double teachToughness)
{
    return stuAbility - subjectDifficulty - teachToughness;
}

double stdDeviation(double studConsistency, double subjectVariability, double teachVariability)
{
    return studConsistency + subjectVariability + teachVariability;
}

Student stuData(std::string str, int studentsSize)
{
    std::string temp;
    std::stringstream ss(str);
    Student stu;
    int i = 0;
    char checker = ',';

    while (std::getline(ss, temp, checker))
    {
        if (i == 3) // will stop at colon at the 5th iteration or when i == 4
        {
            checker = ':';
        }

        switch (i)
        {
        case 0:                           // Inputs Student name
            if (removeSpaces(temp) == "") // removes white spaces and compares it to an empty string
            {
                std::cerr << "Error: Row " << (studentsSize + 1) << " has a empty Student name!" << std::endl;
                exit(0);
            }
            else
            {
                stu.name = temp;
            }
            break;

        case 1:                                             // Inputs Student code
            if (positiveIntVer(temp) && temp.length() == 6) // Checks if positive int (including 0) and that it contains 6 elements
            {
                stu.stdCode = temp;
            }
            else if (temp.length() > 6 || temp.length() < 6)
            {
                std::cerr << "Error: Student " << stu.name << " student code is not 6 digits!"
                          << "\n\tStudent's code in question: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Student " << stu.name << " student code contains a non-numerical character"
                          << "\n\tStudent's code in question: " << temp << std::endl;
                exit(0);
            }
            break;

        case 2:                                                                                     // Inputs Student ability
            if (positiveIntVer(temp) && stringToInteger(temp) <= 100 && stringToInteger(temp) >= 0) // Checks if positive int (including 0) and set upper and lower bounds
            {
                stu.ability = stringToInteger(temp);
            }
            else if (positiveIntVer(temp) == false)
            {
                std::cerr << "Error: Student " << stu.name << " ability contains a non-numerical character that is outside 0-100 "
                          << "\n\tStudent's ability in question: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Student " << stu.name << " is outside the ability 0-100 inclusive range"
                          << "\n\tStudent's ability in question: " << temp << std::endl;
                exit(0);
            }
            break;

        case 3:                                                                                    // Inputs Student consistency
            if (positiveIntVer(temp) && stringToInteger(temp) <= 15 && stringToInteger(temp) >= 0) // Checks if positive int (including 0) and set upper and lower
            {
                stu.consistency = stringToInteger(temp);
            }
            else if (positiveIntVer(temp) == false)
            {
                std::cerr << "Error: Student " << stu.name << " consistency contains a non-numerical character that is outside 0-15"
                          << "\n\tStudent's consistency in quesiton: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Student " << stu.name << " is outside the consistency 0-15 inclusive range"
                          << "\n\tStudent's consistency in quesiton: " << temp << std::endl;
                exit(0);
            }
            break;

        case 4: // Inputs Student Program Name
            stu.programName = temp;
            checker = ',';
            break;

        default:                                                // Inputs Student 's Subjectlist
            if (intVerify(temp) && stu.subjectList.size() < 10) //Checks if int and limits the number of subjects to 10
            {
                stu.subjectList.push_back(stringToInteger(temp));
            }
            else if (stu.subjectList.size() >= 10)
            {
                std::cerr << "Error: Student " << stu.name << " is exceeding the max subject count of 10"
                          << "\n\tCannot enrol in : " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Student " << stu.name << " has given a subject that contains a non-numerical character"
                          << "\n\tCannot enrol in: " << temp << std::endl;
                exit(0);
            }
        }

        i++;
    }
    return stu;
}

Subject subData(std::string str, int subjectsSize)
{
    std::string temp;
    std::stringstream ss(str);
    Subject sub;
    int i = 0;

    while (std::getline(ss, temp, ','))
    {
        switch (i)
        {
        case 0:                           // Input Subject's Name
            if (removeSpaces(temp) == "") // removes white spaces and compares it to an empty string
            {
                std::cerr << "Error: Row " << (subjectsSize + 1) << " has a empty Subject name!" << std::endl;
                exit(0);
            }
            else
            {
                sub.name = temp;
            }
            break;

        case 1:                                                                                 // Input Subject's Difficulty
            if (intVerify(temp) && stringToInteger(temp) <= 15 && stringToInteger(temp) >= -15) // Checks if int and range +/- 15
            {
                sub.difficulty = stringToInteger(temp);
            }
            else if (intVerify(temp) == false)
            {
                std::cerr << "Error: Subject " << sub.name << " difficulty is non-numerical"
                          << "\n\tSubject's difficulty in quesiton: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Subject " << sub.name << " difficulty is outside the 15 +/- limit"
                          << "\n\tSubject's difficulty in quesiton: " << temp << std::endl;
                exit(0);
            }
            break;

        case 2:                                                                               // Input Subject's Variability
            if (intVerify(temp) && stringToInteger(temp) <= 3 && stringToInteger(temp) >= -3) // Checks if int and range +/- 13
            {
                sub.variability = stringToInteger(temp);
            }
            else if (intVerify(temp) == false)
            {
                std::cerr << "Error: Subject " << sub.name << " variability is non-numerical"
                          << "\n\tSubject's variability in quesiton: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Subject " << sub.name << " variability is outside the 3 +/- limit"
                          << "\n\tSubject's variability in quesiton: " << temp << std::endl;
                exit(0);
            }
            break;

        default:
            std::cerr << "Error: Too many values given for subject " << sub.name << std::endl;
            exit(0);
        }

        i++;
    }
    return sub;
}

Teacher teachData(std::string str, int teachersSize)
{
    std::string temp;
    std::stringstream ss(str);
    Teacher teach;
    int i = 0;
    char checker = ',';

    while (std::getline(ss, temp, checker))
    {
        if (i == 1) // will stop at colon at the 3rd iteration or when i == 2
        {
            checker = ':';
        }

        switch (i)
        {
        case 0:                           // Input Teacher's Name
            if (removeSpaces(temp) == "") // removes white spaces and compares it to an empty string
            {
                std::cerr << "Error: Row " << (teachersSize + 1) << " has a empty Teacher name!" << std::endl;
                exit(0);
            }
            else
            {
                teach.name = temp;
            }
            break;

        case 1:                                                                                 // Input Teacher's Toughness
            if (intVerify(temp) && stringToInteger(temp) <= 15 && stringToInteger(temp) >= -15) // Checks if int and range +/- 15
            {
                teach.toughness = stringToInteger(temp);
            }
            else if (intVerify(temp) == false)
            {
                std::cerr << "Error: Teacher " << teach.name << " toughness is non-numerical"
                          << "\n\tTeacher's toughness in quesiton: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Teacher " << teach.name << " toughness is outside the 15 +/- limit"
                          << "\n\tTeacher's toughness in quesiton: " << temp << std::endl;
                exit(0);
            }
            break;

        case 2:                                                                               // Input Teacher's Variability
            temp.substr(0, temp.length() - 1);                                                // remove the colon at the end of the string
            if (intVerify(temp) && stringToInteger(temp) <= 3 && stringToInteger(temp) >= -3) // Checks if int and the inclusive range of +/- 3
            {
                teach.variability = stringToInteger(temp);
                checker = ',';
            }
            else if (intVerify(temp) == false)
            {
                std::cerr << "Error: Teacher " << teach.name << " variability is non-numerical"
                          << "\n\tTeacher's variability in quesiton: " << temp << std::endl;
                exit(0);
            }
            else
            {
                std::cerr << "Error: Teacher " << teach.name << " variability is outside the 3 +/- limit"
                          << "\n\tTeacher's variability in quesiton: " << temp << std::endl;
                exit(0);
            }
            break;

        default:                                                  // Input Teacher's Subjectlist
            if (intVerify(temp) && teach.subjectList.size() < 10) //Checks if int and limits the number of subjects to 10
            {
                teach.subjectList.push_back(stringToInteger(temp));
            }
            else if (teach.subjectList.size() >= 10)
            {
                std::cerr << "Error: Teacher " << teach.name << " is exceeding the max subject count of 10"
                          << "\n\tCannot enrol in " << temp << std::endl;

                exit(0);
            }
            else
            {
                std::cerr << "Error: Teacher " << teach.name << " given subject contains a non-numerical character"
                          << "\n\tCannot enrol in " << temp << std::endl;
                exit(0);
            }
        }

        i++;
    }
    return teach;
}

void fullPrint(std::vector<Student> students, std::vector<Subject> subjects, std::vector<Teacher> teachers)
{
    std::cout << "\n-- List of Students --" << std::endl;

    for (int i = 0; i < students.size(); i++)
    {
        std::cout << "Student Name: " << students[i].name
                  << "\nStudent Code: " << students[i].stdCode
                  << "\nAbility: " << students[i].ability
                  << "\nConsistency: " << students[i].consistency
                  << "\nProgram name: " << students[i].programName
                  << "\nSubject list: ";

        for (int j = 0; j < students[i].subjectList.size(); j++)
        {
            if (j == 0)
            {
                std::cout << students[i].subjectList[j];
            }
            else
            {
                std::cout << ", " << students[i].subjectList[j];
            }
        }

        if (i == (students.size() - 1)) // On the last loop print this:
        {
            std::cout << "\n----------------------\n"
                      << std::endl;
        }
        else
        {
            std::cout << "\n"
                      << std::endl;
        }
    }

    std::cout << "-- List of Subjects --" << std::endl;
    for (int i = 0; i < subjects.size(); i++)
    {

        std::cout << "Subject Name: " << subjects[i].name
                  << "\nDifficulty: " << subjects[i].difficulty
                  << "\nVariability: " << subjects[i].variability;

        if (i == (subjects.size() - 1)) // On the last loop print this:
        {
            std::cout << "\n----------------------\n"
                      << std::endl;
        }
        else
        {
            std::cout << "\n"
                      << std::endl;
        }
    }

    std::cout << "-- List of Teachers --" << std::endl;
    for (int i = 0; i < teachers.size(); i++)
    {
        std::cout << "Teacher's Name: " << teachers[i].name
                  << "\nToughness: " << teachers[i].toughness
                  << "\nVariability: " << teachers[i].variability
                  << "\nSubject list: ";

        for (int j = 0; j < teachers[i].subjectList.size(); j++)
        {
            if (j == 0)
            {
                std::cout << teachers[i].subjectList[j];
            }
            else
            {
                std::cout << ", " << teachers[i].subjectList[j];
            }
        }
        if (i == (teachers.size() - 1)) // On the last loop print this:
        {
            std::cout << "\n----------------------\n"
                      << std::endl;
        }
        else
        {
            std::cout << "\n"
                      << std::endl;
        }
    }
}

void readData(int argc, const char *argv[], std::vector<Student> &students, std::vector<Subject> &subjects, std::vector<Teacher> &teachers)
{
    std::string str;
    std::ifstream inData;
    for (int i = 1; i < argc; i++)
    {
        inData.open(argv[i]);
        if (!inData) // check if opened successfully
        {
            std::cerr << "Error opening: " << argv[i] << std::endl;
            exit(0);
        }

        while (std::getline(inData, str))
        {
            switch (i)
            {
            case 1: // Adds Student object to Student list
                if (students.size() < 10)
                {
                    students.push_back(stuData(str, students.size()));
                }
                else
                {
                    std::cerr << "Error:  The maximum of 10 entries was reached " << std::endl;
                    exit(0);
                }
                break;

            case 2: // Adds Subject object to Subject list
                if (subjects.size() < 10)
                {
                    subjects.push_back(subData(str, subjects.size()));
                }
                else
                {
                    std::cerr << "Error:  The maximum of 10 entries was reached " << std::endl;
                    exit(0);
                }
                break;

            case 3: // Adds Teacher object to teacher list
                if (teachers.size() < 10)
                {
                    teachers.push_back(teachData(str, teachers.size()));
                }
                else
                {
                    std::cerr << "Error: The maximum of 10 entries was reached " << std::endl;
                    exit(0);
                }

                break;
            }
        }
        inData.close();
    }

    for (int i = 0; i < students.size(); i++) // Validating student's subjects with available subjects
    {
        for (int j = 0; j < students[i].subjectList.size(); j++)
        {
            if (students[i].subjectList[j] > subjects.size() || students[i].subjectList[j] == 0)
            {
                std::cerr << "Error: Student " << students[i].name << " cannot enrol in subject, as it doesn't exist"
                          << "\n\tStudent's course in question: " << students[i].subjectList[j] << std::endl;
                exit(0);
            }
        }
    }

    for (int i = 0; i < teachers.size(); i++) // Validating teacher's subjects with available subjects
    {
        for (int j = 0; j < teachers[i].subjectList.size(); j++)
        {
            if (teachers[i].subjectList[j] > subjects.size() || teachers[i].subjectList[j] == 0)
            {
                std::cerr << "Error: Teacher " << teachers[i].name << " cannot teach this subject, as it doesn't exist"
                          << "\n\tTeacher's course in question: " << teachers[i].subjectList[j] << std::endl;
                exit(0);
            }
        }
    }
}

void writeData(std::string argv, std::vector<Student> students, std::vector<Teacher> teachers, std::vector<Subject> subjects)
{
    bool pass; // Validator to check if the student passed
    double average;
    double deviation;
    int attempt; // The number of attempts to pass a subject made by a student (per subject)
    int mark;
    int supMark;
    std::string output; // stores the output of student progess
    std::string grade;
    std::string supGrade;

    std::default_random_engine randEng(time(0));
    std::uniform_int_distribution<unsigned> randTeach(0, teachers.size() - 1); // Used to randomise teachers teaching a subject
    std::ofstream outData;

    outData.open(argv);
    if (!outData) // Checks if output file is opened
    {
        std::cerr << "Error opening: " << argv << std::endl;
        exit(0);
    }

    for (int i = 0; i < students.size(); i++) // Runs each student independently
    {
        output = "\n=============================================================\nStudent Name: " + students[i].name +
                 "\nProgram Name: " + students[i].programName;

        std::cout << output << std::endl;
        outData << output << "\n";

        for (int j = 0; j < students[i].subjectList.size(); j++) // Runs each subject in the order listed in student's plan
        {
            attempt = 1; // resets as first attempt
            pass = false;

            while (attempt <= 3 && pass == false) // Can only attempt a subject that a) you failed and/or b) 1-3 times
            {
                int k = randTeach(randEng);
                grade = "F";
                for (int l = 0; l < teachers[k].subjectList.size(); l++) // Run a teacher randomly
                {
                    if (teachers[k].subjectList[l] == students[i].subjectList[j]) // looks for a teacher that teaches "x" subject
                    {
                        // gets the marks, average, deviation and then uses normal_distribution to generate a random number
                        average = mean((double)students[i].ability, (double)subjects[students[i].subjectList[j] - 1].difficulty, (double)teachers[k].toughness);
                        deviation = stdDeviation((double)students[i].consistency, (double)subjects[students[i].subjectList[j] - 1].variability, (double)teachers[k].variability);

                        std::normal_distribution<double> normal(average, deviation);
                        mark = 0;
                        mark = (int)(normal(randEng));

                        //Mark modifer
                        if (attempt == 2)
                        {
                            mark += 5;
                        }
                        else if (attempt == 3)
                        {
                            mark += 10;
                        }

                        grade = grader(checkRange(mark)); // Firsts checks the range of the mark (ensure max(100) and min(0)), then grades it.
                        supMark = 0;
                        supGrade = "";

                        if (mark >= 45 && mark <= 49)
                        {
                            supMark = normal(randEng) + 5;
                            supGrade = graderSup(checkRange(supMark));
                        }

                        output = "\n------------ " + subjects[students[i].subjectList[j] - 1].name + " | Attempt: " + std::to_string(attempt) + " -----------" +
                                 "\nStudent Name: " + students[i].name +
                                 "\nSubject: " + subjects[students[i].subjectList[j] - 1].name +
                                 "\nTeacher: " + teachers[k].name +
                                 "\nDistribution: " +
                                 "\n\tMean: " + std::to_string((int)normal.mean()) +
                                 "\n\tStandard deviation: " + std::to_string((int)normal.stddev()) +
                                 "\nStudent's Mark: " + std::to_string(mark) +
                                 "\nStudent's Grade: " + grade;

                        if (mark >= 45 && mark <= 49) // If Student did a supplementary print out the results of that supGrade
                        {
                            output += "\nStudent's Supplementary Mark: " + std::to_string(supMark) +
                                      "\nStudent's Supplementary Grade: " + supGrade + "\n";

                            grade = supGrade; // Transfers final grade to grade variable to verify if student passed
                        }
                        output += "\n----------------------------------------------\n";

                        std::cout << output << std::endl;
                        outData << output << "\n";

                        if (grade != "F") // If the student DIDN'T get a FAIL then proceed to the next subject
                        {
                            pass = true;
                            attempt = 1;
                            break; // breaks out of teacher for loop
                        }
                        attempt += 1;
                    }
                }
                if (pass == true) // Move to next subject
                {
                    break; // breaks out of while loop
                }
            }

            if (attempt == 4) // If the student has attempted a subject more then three times exlcude them from the college
            {
                output = "Student " + students[i].name + " has been excluded from the college due to failing a subject 3 times" +
                         "\n\n=============================================================\n";
                break;
            }
        }

        if (pass == true && attempt < 4) // If student passed and attempted a subject less then 4 times they graduate
        {
            output = "Congrats " + students[i].name + " you have graduated!" +
                     "\n\n=============================================================\n";
        }
        outData << output << "\n";
        std::cout << output << std::endl;
    }
    outData.close(); // Close writing file
}

#include "prototypes.h"

int main(int argc, const char *argv[])
{
    std::vector<Student> students;
    std::vector<Subject> subjects;
    std::vector<Teacher> teachers;

    switch (argc) // Checks the number of arguments stated in compile time
    {
    case 1:
        std::cerr << "Error: No Source/Output files linked" << std::endl;
        exit(0);
        break;

    case 2:
        std::cerr << "Error: Missing two source files and the output file" << std::endl;
        exit(0);
        break;

    case 3:
        std::cerr << "Error: Missing one source file and the output file" << std::endl;
        exit(0);
        break;

    case 4:
        std::cerr << "Error: Missing the output file" << std::endl;
        exit(0);
        break;

    case 5:
        readData(argc, argv, students, subjects, teachers);      // Reads given input files
        fullPrint(students, subjects, teachers);                 // Prints all the information to console
        writeData(argv[argc - 1], students, teachers, subjects); // Writes to given output file
        break;

    default:
        std::cerr << "Error: Too many files listed!" << std::endl;
        exit(0);
    }
    return 0;
}

#include <stdio.h>

// Structure to hold date of birth (dob)
struct dob
{
    int day;
    int month;
    int year;
};

// Structure to hold student information
struct student_info
{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

// Function to print student information using call-by-value
void printStudentInfoByValue(struct student_info student)
{
    printf("Student Information (Call-by-Value):\n");
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth: %d-%d-%d\n", student.age.day, student.age.month, student.age.year);
    printf("\n");
}

// Function to print student information using call-by-address
void printStudentInfoByAddress(struct student_info *student)
{
    printf("Student Information (Call-by-Address):\n");
    printf("Roll No: %d\n", student->roll_no);
    printf("Name: %s\n", student->name);
    printf("CGPA: %.2f\n", student->CGPA);
    printf("Date of Birth: %d-%d-%d\n", student->age.day, student->age.month, student->age.year);
    printf("\n");
}

int main()
{
    // Create a student_info structure and populate its members
    struct student_info student1 = {101, "John Doe", 3.75, {15, 7, 2000}};

    // Call the function using call-by-value
    printStudentInfoByValue(student1);

    // Call the function using call-by-address
    printStudentInfoByAddress(&student1);

    return 0;
}
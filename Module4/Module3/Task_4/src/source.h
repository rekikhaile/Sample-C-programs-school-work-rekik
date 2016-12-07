#include <string.h>
#include <stdlib.h>

typedef struct student Student;

struct student {
    char *name; // name of the student
    char id[8]; // null-terminated student ID
    unsigned char age;
    char course[16]; // null-terminated course code;
    float *points; // pointer to dynamic array of exercise points
    unsigned int numPoints; // length of the above array
};

typedef struct {
    unsigned int count; // size if the students array
    Student *array; // pointer to the first element in the array
} Students;

Student *create_student(Students *s, const char *name, const char *id,
        unsigned char age, const char *course);
Student *find_student(Students *s, const char *id, const char *course);
int delete_student(Students *s, const char *id, const char *course);
int set_points(Students *s, const char *id, const char *course, const float *points, int len);

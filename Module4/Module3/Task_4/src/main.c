#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "source.h"

// Gift for you: function to print the current list of students
void print_students(Students *s)
{
    Student *st = s->array;
    for (unsigned int i = 0; i < s->count; i++) {
        printf("%s (%s), Course: %s, Age: %d\n", st->name, st->id, st->course, st->age);
        if (st->numPoints) {
            printf(" -- Points: ");
            for (unsigned int j = 0; j < st->numPoints; j++)
                printf("%f  ", st->points[j]);
            printf("\n");
        } 
        st++;
    }
}

/* The TMC tests use the same student list. */
void initialize_reg(Students *reg) {
    assert(reg != NULL);
    reg->count = 0;
    reg->array = NULL;
    create_student(reg, "Teemu Teekkari", "00000A", 20, "ELEC-A1100");
    create_student(reg, "Matti Meikäläinen", "12345B", 28, "ELEC-A1100");
    create_student(reg, "Wow", "33333C", 28, "ELEC-A1100");
    create_student(reg, "Much Student", "98765H", 28, "ELEC-A1100");
    create_student(reg, "Such course", "12121R", 28, "ELEC-A1111");
    create_student(reg, "Amaze", "11111T", 28, "ELEC-A1111");
}

void release_memory(Students *s) {
  unsigned int i;
  if (s->array) {
    for (i = 0; i < s->count; i++) {
      Student *st = &(s->array[i]);
      if (st->name)
	free(st->name);
      if (st->points)
	free(st->points);
    }
    free(s->array);
  }
}

int main()
{
    /* testing exercise 3.4 */
    /* Feel free to modify */
    Students s;
    s.count = 0;
    s.array = NULL;
    
    // create a group of students using create_student
    initialize_reg(&s);

    // Try find_student (TMC tries the same calls)
    Student *sf3 = find_student(&s, "33333C", "ELEC-A1100");
    Student *sf6 = find_student(&s, "11111T", "ELEC-A1111");
    if (!sf3) {
        printf("Did not find existing student 33333C\n");
    } else if (strcmp(sf3->id, "33333C")) {
        printf("Incorrect student ID %s when should have been 33333C\n", sf3->id);
    }
    if (!sf6) {
        printf("Did not find existing student 11111T\n");
    } else if (strcmp(sf6->id, "11111T")) {
        printf("Incorrect student ID %s when should have been 11111T\n", sf6->id);
    }
    
    // Try delete_student with existing student
    if (!delete_student(&s, "11111T", "ELEC-A1111")) {
        printf("Delete student failed for existing student\n");
    }
    
    printf("-----\n");
    float p[] = {1, 2, 3};
    set_points(&s, "123456", "ELEC-A1100", p, 3);
    print_students(&s);
    printf("-----\n");
   
    // Try delete_student with non_existing student
    delete_student(&s, "444444", "ELEC-A1100");
    print_students(&s);
    
    // Implement code to release the memory allocated for remaining students
    release_memory(&s);
}

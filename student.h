#ifndef STUDENT_H
#define STUDENT_H

//define the student Struct
typedef struct student
{
    int classNum;                   //class order 1-6
    char className[20];
    classInfo* fiestClassOfWeek=NULL;
}student;


#endif  STUDENT_H

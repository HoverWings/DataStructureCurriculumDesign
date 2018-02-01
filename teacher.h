#ifndef TEACHERINFO_H
#define TEACHERINFO_H
#include<classScheduleLink.h>


//define the teacher info Struct
typedef struct teacher
{
    int teacherNum;              //class order 1-6
    char teacherName[20];
    int classNum[10];            //the class he teaching
    classInfo* fiestClassOfWeek=NULL;
}teacher;



#endif // TEACHERINFO_H

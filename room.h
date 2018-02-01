#ifndef ROOMINFO_H
#define ROOMINFO_H

//define the Room Struct
typedef struct room
{
    int classNum;                   //class order 1-6
    char className[20];
    classInfo* fiestClassOfWeek=NULL;
}room;

#endif  ROOMINFO_H

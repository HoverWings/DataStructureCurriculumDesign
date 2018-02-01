#ifndef CLASSSCHEDULELINK_H
#define CLASSSCHEDULELINK_H
#include<string>




//define the ClassInfo struct saved By LINK
typedef struct classInfo
{
    int order;              //class order 1-6 
    char className[20];     
    char teacherName[20];   
    int classNum[10];           
    classInfo* nextClassOfSameTime=NULL; //对于当前班级
    classInfo* nextClassOfDay=NULL;
    classInfo* nextClassOfTheTeacher=NULL;
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
    int num;                    //day order 1-7
    int totalClassNum;          //total num of a day  
    char dayName[20];           //day name
    classInfo* fiestClass=NULL; //
}dayInfo;

bool loadFromMat();
#endif  CLASSSCHEDULELINK_H

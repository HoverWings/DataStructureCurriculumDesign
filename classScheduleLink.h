#ifndef CLASSSCHEDULELINK_H
#define CLASSSCHEDULELINK_H
#include    <string>
#include    "teacher.h"

//define the ClassInfo struct saved By LINK  表示课表 对于当前班级
typedef struct classInfo
{
    int order;                                      //上课时间 1-6
    char className[20];                             //课程名称
    teacherInfo* teacher=NULL;                      //教师指针
    int studentNum[10];                             //上课班级编号
    classInfo* nextClassOfSameTime=NULL;            //对于当前班级 (当前如果课程变动) 不同周
    classInfo* nextSameClass=NULL;                  //下一次课的info
    classInfo* nextClassOfDay=NULL;                 //当天的下一节课
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
    int num;                    //day order 1-7
    int totalClassNum;          //total num of a day  
    char dayName[20];           //day name
    classInfo* fiestClass=NULL; //
}dayInfo;

//周结构体定义
typedef struct weekInfo
{
    int week;                    //day order 1-7
    int totalClassNum;          //total num of a day
    char dayName[20];           //day name
    classInfo* fiestClass=NULL; //
}dayInfo;


bool loadFromMat();
bool addClass();
#endif  CLASSSCHEDULELINK_H

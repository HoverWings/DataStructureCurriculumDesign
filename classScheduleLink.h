#ifndef CLASSSCHEDULELINK_H
#define CLASSSCHEDULELINK_H

#include<string>
#include<stdio.h>
#include<cstring>
#include"teacher.h"
#include"student.h"



//define the ClassInfo struct saved By LINK  表示课表 对于当前班级
typedef struct classInfo
{
	int week;										//当前周次 0-6
	int day;										//当前星期 1-20
    int order;                                      //上课时间 1-6
    char className[20];                             //课程名称
	int tchNum[10];									//教师编号
    int stuNum[10];									//上课班级编号
    struct classInfo* nextClassOfSameTime=NULL;            //对于当前班级 (当前如果课程变动) 不同周
    struct classInfo* preSameClass = NULL;                 //上一次课的info 双向链表
    struct classInfo* nextSameClass = NULL;                //下一次课的info 双向链表
	bool isEnd=false;								//是否是当天的最后一节课
    struct classInfo* nextClassOfDay=NULL;                 //当天的下一节课 如果是最后一节课指向第二天的第一节课
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
    int dayNum;						 //当前星期 0-6
	char dayName[20];				 //Mon. Tues. Wed. Tuhr. Fri. Sat. Sun.
    int dayClassNum;				 //当天课程数目
    classInfo* dayFirstClass=NULL;	 //当天第一节课
}dayInfo;

//周结构体定义
typedef struct weekInfo
{
    int week;							//当前周次
	bool isExamWeek=false;				//是否为考试周
    int weekClassNum;					//当天周次数目
	dayInfo days[7];		 			//日信息数组
	classInfo* weekFirstClass = NULL;	//当周第一节课
}weekInfo;

//当前course存在
//bool addClass(studentInfo* stu, int week, int day,int order,courseInfo* course);

//course不存在 需要维护course
//bool addClssses(studentInfo* stu, int weekBegin, int weekEnd, int day, int order, char* className, int* tchNum);

//classInfo* findFirstClassBySchedule(studentInfo* stu, char* className);//根据日程遍历找到当前班级当前课程的第一节课指针
//classInfo* findFirstClassInWeek(studentInfo* stu, char* className,int week);//需要查找当前课程的周次
//classInfo* isExistedClass(studentInfo* stu);

bool compareClass(classInfo* A, classInfo* B);




#endif  //CLASSSCHEDULELINK_H

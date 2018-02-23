#ifndef STUDENT_H
#define STUDENT_H

#include "classScheduleLink.h"

//define the student Struct 表示班级
static  struct studentInfo
{
    int stuNum;                   //班级编号
    char stuName[20];             //班级名称 如IOT1601
    struct studentInfo* nextStu=NULL;	  //下一个班级
	int beginWeek= 0;			  //开始有课周次 1-20
	int endWeek = 0;			  //开始无课周次 1-20
   // weekInfo weeks[25];		  //二十周的课表数组 1-20
};

typedef struct studentInfo studentInfo;

typedef struct stuLink
{
	studentInfo* headStu = NULL;
	int stuNum = 0;
}stuLink;

extern stuLink stuL;

bool addStu(studentInfo** headStu, studentInfo* stu);					//增加班级
bool deleteStu(studentInfo** headStu, char* stuName);					//删除班级
studentInfo* findStu(studentInfo* headStu, char* stuName);				//找到当前班级
studentInfo* findPreStu(studentInfo* headStu, char* stuName);			//找到当前班级的前驱

#endif  //STUDENT_H

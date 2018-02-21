#ifndef STUDENT_H
#define STUDENT_H

#include "classScheduleLink.h"

//define the student Struct 表示班级
typedef struct studentInfo
{
    int stuNum;                   //班级编号
    char stuName[20];             //班级名称 如IOT1601
	studentInfo* nextStu=NULL;		  //下一个班级
    classInfo* nextClass=NULL;    //当前周的第一节课/下一节课
}studentInfo;

studentInfo* headStu=NULL;
int stuNum=0;

bool addStu(studentInfo** headStu, studentInfo* stu);					//增加班级
bool deleteStu(studentInfo** headStu, char* stuName);					//删除班级
studentInfo* findStu(studentInfo* headStu, char* stuName);				//找到当前班级
studentInfo* findPreStu(studentInfo* headStu, char* stuName);			//找到当前班级的前驱

#endif  STUDENT_H

#ifndef TEACHER_H
#define TEACHER_H

#include "classScheduleLink.h"
#include "student.h"
#include "room.h"


//define the teacher info Struct
typedef struct teacherInfo
{
    int tchNum;					 //教师编号
    char tchName[20];			 //教师名称
    int classNums[10];            //上课班级编号
    //classInfo* nextClass=NULL;   //教师的《当前周》的第一节课/下一节课
	teacherInfo* nextTch=NULL;
}teacherInfo;



typedef struct tchLink
{
	teacherInfo* headTch = NULL;
	int tchNum = 0;
}tchLink;

extern tchLink tchL;

bool addTch(teacherInfo** headTch, teacherInfo* tch);					//增加教师
bool deleteTch(teacherInfo** headTch, char* tchName);					//删除教师
teacherInfo* findTch(teacherInfo* headTch, char* tchName);				//找到当前教师
teacherInfo* findPreTch(teacherInfo* headTch, char* tchName);			//找到当前教师的前驱

#endif // TEACHER_H

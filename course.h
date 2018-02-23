#ifndef COURSE_H
#define COURSE_H

#include"classScheduleLink.h"

typedef struct courseInfo
{
	int beginWeek;
	int endWeek;
	int courseHour;										//学时数
	char className[20];									//课程名称
	//int tchNum;
	//int tchNums[10];									//教师编号
	//int stuNum;
	//int stuNums[10];									//上课班级编号
	classInfo* firstClass = NULL;
}courseInfo;

#endif // COURSE_H

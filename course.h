#ifndef COURSE_H
#define COURSE_H

#include"classScheduleLink.h"

typedef struct courseInfo
{
	int beginWeek;
	int endWeek;
	int courseHour;										//ѧʱ��
	char className[20];									//�γ�����
	//int tchNum;
	//int tchNums[10];									//��ʦ���
	//int stuNum;
	//int stuNums[10];									//�Ͽΰ༶���
	classInfo* firstClass = NULL;
}courseInfo;

#endif // COURSE_H

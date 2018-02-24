#include<classScheduleLink.h>


//ClassInfo�Ƚϣ���B��A�󷵻�True,���򷵻�False
bool compareClass(classInfo* A, classInfo* B)
{
	if (A->week <= B->week)
	{
		if (A->day <= B->day)
		{
			if (A->order <= B->order)
			{
				return true;
			}
		}
	}
	return false;
}

classInfo * findFirstClassBySchedule(studentInfo * stu, char * className)
{
	int begin = stu->beginWeek;
	int end = stu->endWeek;
    //weekInfo* weeks = (stu->weeks);
	classInfo* classFirst=NULL;
	for (int i = begin; i <= end; i++)
	{
	//	classFirst=findFirstClassInWeek(stu, className, i);
		if (classFirst != NULL)
		{
			return classFirst;
		}
	}
	return NULL;
}

classInfo * findFirstClassInWeek(studentInfo * stu, char * className, int week)
{
	int begin = stu->beginWeek;
	int end = stu->endWeek;
    //weekInfo* weeks = &(stu->weeks)[week];
    //dayInfo* days = weeks->days;
    //classInfo* now = weeks->weekFirstClass;
    classInfo* now = NULL;
	if (now == NULL)//��ǰ�ܴ��޿�
	{
		return NULL;
	}
	while (now!=NULL)
	{
		if (strcmp(now->className, className) == 0)
		{
			return now;
		}
		now = now->nextClassOfDay;
	}
	return now;//��ǰ��δ�ҵ�
}


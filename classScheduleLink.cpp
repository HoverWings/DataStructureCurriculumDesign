#include<classScheduleLink.h>

bool addClass(studentInfo * stu, int week, int day, int order, courseInfo * course)
{
	return false;
}

//ClassInfo比较，若B比A大返回True,否则返回False
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

/*
typedef struct classInfo
{
int week;										//当前周次 0-6
int day;										//当前星期 1-20
int order;                                      //上课时间 1-6
char className[20];                             //课程名称
teacherInfo* tch=NULL;							//教师指针
int stuNum[10];									//上课班级编号
classInfo* nextClassOfSameTime=NULL;            //对于当前班级 (当前如果课程变动) 不同周
classInfo* nextSameClass=NULL;                  //下一次课的info
bool isEnd=false;								//是否是当天的最后一节课
classInfo* nextClassOfDay=NULL;                 //当天的下一节课
}classInfo;
*/
//当前课程存在

bool addClssses(studentInfo * stu, int weekBegin, int weekEnd,int day, int order, char* className, int* tchNum)
{
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
	if (now == NULL)//当前周次无课
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
	return now;//当前周未找到
}


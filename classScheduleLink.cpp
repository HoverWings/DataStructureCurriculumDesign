#include<classScheduleLink.h>

bool addClass(studentInfo * stu, int week, int day, int order, courseInfo * course)
{
	return false;
}

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

/*
typedef struct classInfo
{
int week;										//��ǰ�ܴ� 0-6
int day;										//��ǰ���� 1-20
int order;                                      //�Ͽ�ʱ�� 1-6
char className[20];                             //�γ�����
teacherInfo* tch=NULL;							//��ʦָ��
int stuNum[10];									//�Ͽΰ༶���
classInfo* nextClassOfSameTime=NULL;            //���ڵ�ǰ�༶ (��ǰ����γ̱䶯) ��ͬ��
classInfo* nextSameClass=NULL;                  //��һ�οε�info
bool isEnd=false;								//�Ƿ��ǵ�������һ�ڿ�
classInfo* nextClassOfDay=NULL;                 //�������һ�ڿ�
}classInfo;
*/
//��ǰ�γ̴���

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


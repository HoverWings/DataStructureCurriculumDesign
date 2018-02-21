#include "student.h"

bool addStu(studentInfo ** headStu, studentInfo * stu)
{
	studentInfo* now = (*headStu);
	if (now == NULL)
	{
		(*headStu) = stu;	
		stuNum++;
		return true;
	}
	while (now->nextStu!=NULL)
	{
		now = now->nextStu;
	}
	now->nextStu = stu;
	stuNum++;
	return true;
}

bool deleteStu(studentInfo ** headStu, char * stuName)
{
	studentInfo* now = (*headStu);
	if (strcmp(now->stuName, stuName) == 0)
	{
		(*headStu)->nextStu = now->nextStu;
		free(now);
		stuNum--;
		return true;
	}
	studentInfo* pre = findPreStu(*headStu, stuName);
	if(pre==NULL)
	{
		return false;
	}
	else
	{
		now = pre->nextStu;
		pre->nextStu = now->nextStu;
		free(now);
		stuNum--;
		return true;
	}
	return false;
}

//初始条件:headStu不为空
studentInfo * findStu(studentInfo * headStu, char * stuName)
{
	if (strcmp(headStu->stuName, stuName) == 0)
	{
		return headStu;
	}
	studentInfo* pre = findPreStu(headStu, stuName);
	if (pre == NULL)
	{
		return NULL;
	}
	else
	{
		return pre->nextStu;
	}
}

//初始条件:headStu不为空 且不为寻找
studentInfo * findPreStu(studentInfo * headStu, char * stuName)
{
	studentInfo* pre = headStu;
	studentInfo* now = pre->nextStu;
	while (now != NULL)
	{
		if (strcmp(now->stuName, stuName) == 0)
		{
			return pre;
		}
		pre = now;
		now = now->nextStu;
	}
	return NULL;
}

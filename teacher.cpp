#include "teacher.h"

tchLink tchL;

bool addTch(teacherInfo ** headTch, teacherInfo * tch)
{
	teacherInfo* now = (*headTch);
	if (now == NULL)
	{
		(*headTch) = tch;
		tchL.tchNum++;
		return true;
	}
	while (now->nextTch != NULL)
	{
		now = now->nextTch;
	}
	now->nextTch = tch;
	tchL.tchNum++;
	return true;
	return false;
}

bool deleteTch(teacherInfo ** headTch, char * tchName)
{
	teacherInfo* now = (*headTch);
	if (strcmp(now->tchName, tchName) == 0)
	{
		(*headTch)->nextTch = now->nextTch;
		free(now);
		tchL.tchNum--;
		return true;
	}
	teacherInfo* pre = findPreTch(*headTch, tchName);
	if (pre == NULL)
	{
		return false;
	}
	else
	{
		now = pre->nextTch;
		pre->nextTch = now->nextTch;
		free(now);
		tchL.tchNum--;
		return true;
	}
	return false;
}

teacherInfo * findTch(teacherInfo * headTch, char * tchName)
{
	if (strcmp(headTch->tchName, tchName) == 0)
	{
		return headTch;
	}
	teacherInfo* pre = findPreTch(headTch, tchName);
	if (pre == NULL)
	{
		return NULL;
	}
	else
	{
		return pre->nextTch;
	}
}

teacherInfo * findPreTch(teacherInfo * headTch, char * tchName)
{
	teacherInfo* pre = headTch;
	teacherInfo* now = pre->nextTch;
	while (now != NULL)
	{
		if (strcmp(now->tchName, tchName) == 0)
		{
			return pre;
		}
		pre = now;
		now = now->nextTch;
	}
	return NULL;
}

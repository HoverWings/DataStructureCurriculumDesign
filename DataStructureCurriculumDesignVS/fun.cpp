#include"fun.h"


extern stuLink stuL;

bool addStu(studentInfo ** headStu, studentInfo * stu)
{
	studentInfo* now = (*headStu);
	if (now == NULL)
	{
		(*headStu) = stu;
		stuL.stuNum++;
		stu->stuNum = stuL.stuNum;
		return true;
	}
	while (now->nextStu != NULL)
	{
		now = now->nextStu;
	}
	now->nextStu = stu;
	stuL.stuNum++;
	stu->stuNum = stuL.stuNum;
	return true;
}

bool deleteStu(studentInfo ** headStu, char * stuName)
{
	studentInfo* now = (*headStu);
	if (strcmp(now->stuName, stuName) == 0)
	{
		(*headStu)= now->nextStu;
		free(now);
		stuL.stuNum--;
		now = (*headStu);
		while (now != NULL)//ά���༶��� ��1��ʼ
		{
			now->stuNum--;
			now = now->nextStu;
		}
		return true;
	}
	studentInfo* pre = findPreStu(*headStu, stuName);
	if (pre == NULL)
	{
		return false;
	}
	else
	{
		now = pre->nextStu;
		pre->nextStu = now->nextStu;
		free(now);
		now = pre->nextStu;
		while (now != NULL)//ά���༶��� ��1��ʼ
		{
			now->stuNum--;
			now = now->nextStu;
		}
		stuL.stuNum--;
		return true;
	}
	return false;
}

//C:headStu��Ϊ��
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

//C:headStu��Ϊ�� �Ҳ�ΪѰ��
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

studentInfo* findStuByIndex(studentInfo * headStu, int stuNum)
{
	studentInfo* stu = headStu;
	if (stuNum > stuL.stuNum)
	{
		printf("index ����");
		return NULL;
	}
	int index = 1;
	while (index != stuNum)
	{
		stu = stu->nextStu;
		index++;
	}
	return stu;
}

extern tchLink tchL;

bool addTch(teacherInfo ** headTch, teacherInfo * tch)
{
	teacherInfo* now = (*headTch);
	if (now == NULL)	//ͷָ��Ϊ��
	{
		(*headTch) = tch;
		tchL.tchNum++;
		tch->tchNum = tchL.tchNum;
		return true;
	}
	while (now->nextTch != NULL)
	{
		now = now->nextTch;
	}
	now->nextTch = tch;//��ĩβ����
	tchL.tchNum++;
	tch->tchNum = tchL.tchNum;
	return true;
}

bool deleteTch(teacherInfo ** headTch, char * tchName)
{
	teacherInfo* now = (*headTch);
	if (strcmp(now->tchName, tchName) == 0)//ͷָ��ɾ��
	{
		(*headTch) = now->nextTch;
		free(now);
		tchL.tchNum--;
		now = (*headTch);
		while (now!=NULL)//ά����ʦ��� ��1��ʼ
		{
			now->tchNum--;
			now = now->nextTch;
		}
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
		now = pre->nextTch;
		while (now != NULL)
		{
			now->tchNum--;
			now = now->nextTch;
		}
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

teacherInfo* findTchByIndex(teacherInfo * headTch, int tchNum)
{
	teacherInfo* tch = headTch;
	if (tchNum > tchL.tchNum)
	{
		printf("index ����");
		return NULL;
	}
	int index = 1;
	while (index!= tchNum)
	{
		tch = tch->nextTch;
		index++;
	}
	return tch;
}



//C:��ѧ¥���޴˽���
bool addRoom(buildingInfo ** building, roomInfo * room)
{
	if ((*building)->firstRoom == NULL)
	{
		(*building)->firstRoom = room;
	}
	else
	{
		roomInfo* r = (*building)->firstRoom;
		while (r->nextRoom != NULL)
		{
			r = r->nextRoom;
		}
		r->nextRoom = room;
	}
	return false;
}

//C:��ǰ��ѧ¥���д˽��� pre=NULL��˵������ֻ��һ������
bool deleteRoomByPre(buildingInfo **building, roomInfo * pre)
{
	if (pre == NULL)
	{
		free((*building)->firstRoom);
		return true;
	}
	roomInfo* now = pre->nextRoom;
	if (now->nextRoom == NULL)	//û�к��
	{
		free(now);
		pre->nextRoom = NULL;
		return true;
	}
	else
	{
		pre->nextRoom = now->nextRoom;
		free(now);
		return true;
	}
	return false;
}

roomInfo * findPreRoom(buildingInfo * building, int roomArea, int roomNum)
{
	roomInfo* r = (building)->firstRoom;
	if (r == NULL)
	{
		return NULL;
	}
	roomInfo* pre = r;
	while (r != NULL)
	{
		if (r->roomArea == roomArea&&r->roomNum == roomNum)
		{
			return pre;
		}
		pre = r;
		r = r->nextRoom;
	}
	return NULL;
}




//D:ClassInfo�Ƚϣ���B��A�󷵻�True,���򷵻�False
bool compareClass(classInfo* A, classInfo* B)
{
	if (A->week <= B->week)
	{
		if (A->day <= B->day)
		{
			if (A->order < B->order)
			{
				return true;
			}
		}
	}
	return false;
}

bool classIsSameDay(classInfo* A, classInfo* B)
{
	if (A->week == B->week)
	{
		if (A->day == B->day)
		{
			return true;
		}
	}
	return false;
}

//D:newһ��class����course��Ϣ
classInfo* newClassByCourse(courseInfo * course,int week, int day, int order)
{
	classInfo* newClass = (classInfo*)malloc(sizeof(classInfo));
	strcpy(newClass->className, course->className);
	newClass->day = day;
	newClass->week = week;
	newClass->order = order;
	newClass->course = course;
	return newClass;
}

//D:�����ճ̱��ҵ�����λ��
//C:����γ�λ���޿γ�
//I:studentInfo * stu, int week, int day, int order
//O:�ճ̲���λ�õ�ǰһ�ڿγ�
classInfo* insertBySchedule(studentInfo * stu, classInfo* insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	weekInfo* insertWeek = &(stu->weeks[week]);
	dayInfo* insertDay = &(insertWeek->days[day - 1]);
	classInfo* pre = stu->scheduleFirstClass;
	classInfo* next = stu->scheduleLastClass;
	int begin = stu->beginWeek;
	int end = stu->endWeek;
	//Week judge
	if (compareClass(insertClass, pre))
	{
		stu->beginWeek = insertClass->week;
		insertClass->nextClassOfDay = stu->scheduleFirstClass;
		stu->scheduleFirstClass = insertClass;
		return insertClass;				//��ǰ�� ��������
	}
	if (compareClass(next, insertClass))
	{
		while (pre->nextClassOfDay != NULL)
		{
			pre = pre->nextClassOfDay;
		}
		pre->nextClassOfDay = insertClass;
		insertClass->isEnd = true;
		insertClass->nextClassOfDay = NULL;
		insertClass->nextSameClass = NULL;
		return pre;						//�������
	}
	//�ڵ�ǰ�Ѵ��ڵĽ�ѧ�����б���
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextClassOfDay))//�ҵ�����λ��
		{
			next = pre->nextClassOfDay;
			if (classIsSameDay(pre, next))
			{
				pre->nextClassOfDay = insertClass;
				insertClass->nextClassOfDay = next;
				insertClass->isEnd = false;
				return pre;
			}
			else
			{
				if (classIsSameDay(pre, insertClass))//��ǰ����ͬһ��
				{
					pre->isEnd = false;
					insertClass->isEnd = true;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				if (classIsSameDay(insertClass, next))//������ͬһ��
				{
					insertClass->isEnd = false;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				//����߾�����ͬһ��
				pre->nextClassOfDay = insertClass;
				insertClass->nextClassOfDay = next;
				pre->isEnd = true;
				return pre;
			}
		}
		pre = pre->nextClassOfDay;
	}
	return NULL;//BUG�� �����ϲ�����ִ����
}



//D:���ݿγ�course�ҵ�����λ��
//C:����γ�λ���޿γ�
//I:studentInfo * stu, int week, int day, int order
//O:�γ̲���λ��
classInfo* insertByCourse(courseInfo * course,classInfo* insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo *pre = course->firstClass;
	classInfo *next = course->lastClass;
	if (compareClass(insertClass, pre))	//��һ�ڿ�ǰ
	{
		//����course����
		course->firstClass = insertClass;
		insertClass->preSameClass = NULL;
		insertClass->nextSameClass = pre;
		pre->preSameClass = insertClass;
		return insertClass;
	}
	if (compareClass(next, insertClass))//���һ�ڿκ�
	{
		//����course����
		course->lastClass = insertClass;
		insertClass->preSameClass = next;
		insertClass->nextSameClass = NULL;
		next->nextSameClass = insertClass;
		return insertClass;
	}
	//����course�����ҵ���ǰ�γ�
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextSameClass))//�ҵ�����λ��
		{
			next = pre->nextSameClass;
			pre->nextSameClass = insertClass;
			insertClass->nextSameClass = next;
			return insertClass;
		}
	}
	return NULL;//BUG
}

bool insertByTch(teacherInfo* tch,classInfo* insertClass)
{

	return false;
}


//C:��ǰ�γ̴��� ����ÿһ��stu����Ҫ���ôκ���
bool addClass(courseInfo * course,int week, int day, int order )
{
	classInfo* insertClass = newClassByCourse(course,week, day, order);//��������ڵ�
	for (int i = 0; i < course->stuNum; i++)//�ж�stu�Ƿ��ͻ
	{
		studentInfo* stu = findStuByIndex(stuL.headStu, course->stuNums[i]);
		if (stu == NULL)
		{
			printf("�༶%dδ�ҵ�\n", course->stuNums[i]);
			return false;
		}
		if (isExistedClassByStu(stu, insertClass))//���ڳ�ͻ�����岻���룬����ʧ��
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 0; i < course->tchNum; i++)//�ж�tch�Ƿ��ͻ
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch, course->tchNums[i]);
		if (tch == NULL)
		{
			printf("��ʦ%dδ�ҵ�\n", course->tchNums[i]);
			return false;
		}
		if (isExistedClassByTch(tch, insertClass))//���ڳ�ͻ�����岻���룬����ʧ��
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 0; i < course->stuNum; i++)//����stu����
	{
		studentInfo* stu = findStuByIndex(stuL.headStu,course->stuNums[i]);
		if (stu == NULL)
		{
			printf("�༶%dδ�ҵ�\n",course->stuNums[i]);
			return false;
		}
		insertBySchedule(stu, insertClass);
	}
	insertByCourse(course, insertClass);    //�γ̲���
	for (int i = 0; i < course->tchNum; i++)//����tch����
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch,course->tchNums[i]);
		if (tch == NULL)
		{
			printf("��ʦ%dδ�ҵ�\n", course->tchNums[i]);
			return false;
		}
		insertByTch(tch, insertClass);
	}
	return true;
}

//I:�γ����� className
//O:��ǰ��ѧ�����Ŀγ̵ĵ�һ��
classInfo * findFirstSameClassBySchedule(studentInfo * stu, char * className)
{
	int begin = stu->beginWeek;
	int end = stu->endWeek;
	weekInfo* weeks = (stu->weeks);
	classInfo* classFirst = NULL;
	for (int i = begin; i <= end; i++)
	{
		classFirst= findFirstSameClassInWeek(stu, className, i);
		if (classFirst != NULL)
		{
			return classFirst;
		}
	}
	return NULL;
}


//I:�γ����� className,�ܴ�	 week
//O:��ǰ���ڵĿγ̵ĵ�һ��
classInfo * findFirstSameClassInWeek(studentInfo * stu, char * className, int week)
{
	int begin = stu->beginWeek;
	int end = stu->endWeek;
	weekInfo* nowWeek = &(stu->weeks)[week];
	dayInfo* days = nowWeek->days;
	classInfo* now = nowWeek->weekFirstClass;
	if (now == NULL)	//��ǰ�ܴ��޿�
	{
		return NULL;
	}
	while (now!=NULL&&now ->week==week)
	{
		if (strcmp(now->className, className) == 0)
		{
			return now;
		}
		now = now->nextClassOfDay;
	}
	return NULL;		//��ǰ��δ�ҵ�
}

//D:��Ե�ǰ�༶����ѯ�γ��Ƿ��ͻ
//I:stu,insertClass
//O:������ڳ�ͻ�γ̣����س�ͻ�γ�ָ�룬���򷵻�NULL
classInfo * isExistedClassByStu(studentInfo * stu, classInfo * insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	weekInfo* insertWeek = &(stu->weeks[week]);
	dayInfo* insertDay = &(insertWeek->days[day - 1]);
	classInfo* pre = insertDay->dayFirstClass;
	while (compareClass(pre,insertClass))//��֤pre�ڲ���֮ǰ
	{
		if (classIsSameDay(pre->nextClassOfDay, insertClass))//��ͬһ��
		{
			if (pre->nextClassOfDay->order == insertClass->order)//pre�ĺ�̳�ͻ
			{
				return pre->nextClassOfDay;
			}
		}
		if (compareClass(insertClass, pre->nextClassOfDay))
		{
			return NULL;
		}
	}
	return NULL;
}

//D:��Ե�ǰ��ʦ����ѯ�γ��Ƿ��ͻ
//I:tch,insertClass
//O:������ڳ�ͻ�γ̣����س�ͻ�γ�ָ�룬���򷵻�NULL
classInfo * isExistedClassByTch(teacherInfo * tch, classInfo * insertClass)
{
	//�˴���ҪЩ
	/*
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	weekInfo* insertWeek = &(stu->weeks[week]);
	dayInfo* insertDay = &(insertWeek->days[day - 1]);
	classInfo* pre = insertDay->dayFirstClass;
	while (compareClass(pre, insertClass))//��֤pre�ڲ���֮ǰ
	{
		if (classIsSameDay(pre->nextClassOfDay, insertClass))//��ͬһ��
		{
			if (pre->nextClassOfDay->order == insertClass->order)//pre�ĺ�̳�ͻ
			{
				return pre->nextClassOfDay;
			}
		}
		if (compareClass(insertClass, pre->nextClassOfDay))
		{
			return NULL;
		}
	}
	return NULL;
	*/
	return NULL;
}
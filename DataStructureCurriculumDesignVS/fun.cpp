#include"fun.h"

extern courseInfo allCourse[50];
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

bool classIsSameTime(classInfo* A, classInfo* B)
{
	if (A->week == B->week)
	{
		if (A->day == B->day)
		{
			if (A->order == B->order)
			{
				return true;
			}	
		}
	}
	return false;
}

//D:�ж�classʱ���Ƿ�Ϊ����ʱ��
bool classIsTheTime(classInfo* A,int week,int day,int order)
{
	if (A->week == week)
	{
		if (A->day == day)
		{
			if (A->order ==order)
			{
				return true;
			}
		}
	}
	return false;
}

//D:newһ��class����course��Ϣ
classInfo* newClassByCourse(courseInfo * course,int week, int day, int order)
{
	classInfo* newClass = (classInfo*)malloc(sizeof(classInfo));
	strcpy(newClass->className,course->courseName);
	newClass->day = day;
	newClass->week = week;
	newClass->order = order;
	newClass->course = course;
	return newClass;
}

//D:�����ճ̱��ҵ�����λ�� OBJ:stu
//C:����γ�λ���޿γ�
//I:studentInfo * stu, int week, int day, int order
//O:�ճ̲���λ�õ�ǰһ�ڿγ�
classInfo* insertInStu(studentInfo * stu, classInfo* insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	int begin = stu->beginWeek;
	int end = stu->endWeek;
	weekInfo* insertWeek = &(stu->weeks[week]);
	dayInfo* insertDay = &(insertWeek->days[day - 1]);
	classInfo* pre = stu->stuFirstClass;
	classInfo* next = stu->stuLastClass;
	//Week judge
	if (compareClass(insertClass, pre))
	{
		stu->beginWeek = insertClass->week;
		insertClass->nextClassOfDay = stu->stuFirstClass;
		if (!classIsSameDay(insertClass, insertClass->nextClassOfDay))
		{
			insertClass->isLast = true;
		}
		stu->stuFirstClass = insertClass;
		return insertClass;				//��ǰ�� ��������
	}
	if (compareClass(next, insertClass))
	{
		while (pre->nextClassOfDay != NULL)
		{
			pre = pre->nextClassOfDay;
		}
		pre->nextClassOfDay = insertClass;
		insertClass->isLast = true;
		insertClass->nextClassOfDay = NULL;
		insertClass->nextSameClass = NULL;
		stu->stuLastClass = insertClass;
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
				insertClass->isLast = false;
				return pre;
			}
			else
			{
				if (classIsSameDay(pre, insertClass))//��ǰ����ͬһ��
				{
					pre->isLast = false;
					insertClass->isLast = true;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				if (classIsSameDay(insertClass, next))//������ͬһ��
				{
					insertClass->isLast = false;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				//����߾�����ͬһ��
				pre->nextClassOfDay = insertClass;
				insertClass->nextClassOfDay = next;
				pre->isLast = true;
				return pre;
			}
		}
		pre = pre->nextClassOfDay;
	}
	printf("�γ���Ϣ����\n");
	return NULL;//BUG�� �����ϲ�����ִ����
}



//D:���ݿγ�course�ҵ�����λ��
//C:����γ�λ���޿γ�
//I:studentInfo * stu, int week, int day, int order
//O:�γ̲���λ��
classInfo* insertInCourse(courseInfo * course,classInfo* insertClass)
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
	return NULL;
}

//D:�����ʦ����
//C:tch�γ̲���ͻ
//I:tch , insertClass
//O:���������� 
bool insertInTch(teacherInfo* tch,classInfo* insertClass)
{
	if (isExistedClassInTch(tch, insertClass))//OC����
	{
		printf("��ʦ %d �γ̴��ڳ�ͻ����ʧ��!\n",tch->tchNum);
		return false;
	}
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo *pre = tch->firstClass;
	classInfo *next = tch->lastClass;
	if (compareClass(insertClass, pre))	//��һ�ڿ�ǰ
	{
		//����course����
		tch->firstClass = insertClass;
		insertClass->nextTchClass = pre;
		pre->preTchClass = insertClass;
		return true;
	}
	if (compareClass(next, insertClass))//���һ�ڿκ�
	{
		//����course����
		tch->lastClass = insertClass;
		insertClass->preTchClass = next;
		insertClass->nextTchClass = NULL;
		next->nextTchClass = insertClass;
		return true;
	}
	//����course�����ҵ���ǰ�γ�
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextTchClass))//�ҵ�����λ��
		{
			next = pre->nextTchClass;
			pre->nextTchClass = insertClass;
			insertClass->nextTchClass = next;
			return true;
		}
	}
	return false;
}

//D:�����������
//C:room�γ̲���ͻ
//I:room , insertClass
//O:���������� ά��Roomռ������
bool insertInRoom(roomInfo* room, classInfo* insertClass)
{
	if (isExistedClassInRoom(room, insertClass))//OC����
	{
		return false;
	}
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo *pre = room->firstClass;
	classInfo *next = room->lastClass;
	if (compareClass(insertClass, pre))	//��һ�ڿ�ǰ
	{
		//����room����
		room->firstClass = insertClass;
		insertClass->nextRoomClass = pre;
		room->isUsed[week][day][order] = true;
		return true;
	}
	if (compareClass(next, insertClass))//���һ�ڿκ�
	{
		//����room����
		room->lastClass = insertClass;
		insertClass->nextRoomClass = NULL;
		next->nextRoomClass = insertClass;
		room->isUsed[week][day][order] = true;
		return true;
	}
	//����room�����ҵ���ǰ�γ�
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextRoomClass))//�ҵ�����λ��
		{
			next = pre->nextRoomClass;
			pre->nextRoomClass = insertClass;
			insertClass->nextRoomClass = next;
			room->isUsed[week][day][order] = true;
			return true;
		}
	}
	return false;
}

//D:Ϊ��ǰ�γ��е����ж����� 
//	�Ͽ�ʱ��:week day order 
//	�Ͽεص�:room ��ӿγ� 
//OBJ:	�༶stu
//		��ʦtch
//		��ʦroom
//		�γ�course
//C:��ǰ�γ̴��� ����ÿһ���γ�������stu����Ҫ������ӿγ�
//I:course,week,day,order,room
//O:�������
classInfo* addClass(courseInfo * course,int week, int day, int order,roomInfo* room)
{
	classInfo* insertClass = newClassByCourse(course,week, day, order);//��������ڵ�
	if (isExistedClassInRoom(room, insertClass))
	{
		printf("���Ҵ��ڳ�ͻ����ʧ��!\n");
		return false;
	}
	for (int i = 1; i <= course->stuNum; i++)//�ж�stu�Ƿ��ͻ
	{
		studentInfo* stu = findStuByIndex(stuL.headStu, course->stuNums[i]);
		if (stu == NULL)
		{
			printf("�༶%dδ�ҵ�\n", course->stuNums[i]);
			return false;
		}
		if (isExistedClassInStu(stu, insertClass))//���ڳ�ͻ�����岻���룬����ʧ��
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 1; i <= course->tchNum; i++)//�ж�tch�Ƿ��ͻ
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch, course->tchNums[i]);
		if (tch == NULL)
		{
			printf("��ʦ%dδ�ҵ�\n", course->tchNums[i]);
			return false;
		}
		if (isExistedClassInTch(tch, insertClass))//���ڳ�ͻ�����岻���룬����ʧ��
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 1; i <= course->stuNum; i++)//����stu����
	{
		studentInfo* stu = findStuByIndex(stuL.headStu,course->stuNums[i]);
		if (stu == NULL)
		{
			printf("�༶%dδ�ҵ�\n",course->stuNums[i]);
			return false;
		}
		insertInStu(stu, insertClass);
	}
	insertInCourse(course, insertClass);    //course����
	for (int i = 1; i <= course->tchNum; i++)//����tch����
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch,course->tchNums[i]);
		if (tch == NULL)
		{
			printf("��ʦ%dδ�ҵ�\n", course->tchNums[i]);
			return false;
		}
		insertInTch(tch, insertClass);
	}
	insertInRoom(room, insertClass);		//room����
	return insertClass;
}

//D:�Ӱ༶stu������ɾ������free,��Ҫ��course��ÿһ���༶���ô˺���
//	��Ҫά����isLast,stuFirstClass,stuLastClass
//C:deleteClass������������
bool deleteInStu(studentInfo * stu, classInfo* deleteClass)
{
	classInfo* pre = stu->stuFirstClass;
	classInfo* next = stu->stuLastClass;
	if (pre == NULL)
	{
		printf("��ǰ�༶�γ̱�Ϊ�գ�ɾ������\n");
		return false;
	}
	if (pre == deleteClass)	//��һ�ڿ�Ϊɾ��
	{
		stu->stuFirstClass = deleteClass->nextClassOfDay;
		if (stu->stuFirstClass->nextClassOfDay == NULL)
		{
			stu->stuLastClass = stu->stuFirstClass;
		}
		return true;
	}
	pre = findPreClassInStu(stu, deleteClass);
	if (classIsSameDay(pre, deleteClass))//ά��isLast��־λ
	{
		if (deleteClass->isLast = true)
		{
			pre->isLast = true;
		}
	}
	pre->nextClassOfDay = deleteClass->nextClassOfDay;
	if (pre->nextClassOfDay == NULL)
	{
		stu->stuLastClass = pre;
	}
	return true;
}


//D:�ӽ�ʦtch������ɾ������free,��Ҫ��tchNums��ÿһ��tch���ô˺���
//	��Ҫά����firstClass lastClass pre ,next
//C:deleteClass������������
bool deleteInTch(teacherInfo * tch, classInfo* deleteClass)
{
	classInfo* pre = deleteClass->preTchClass;
	classInfo* next = deleteClass->nextTchClass;
	if (pre == NULL&&next == NULL)
	{
		printf("deleteClass In Tch ����\n");
		return false;
	}
	if (pre == NULL)//ɾ����Ϊ��λ
	{
		tch->firstClass = next;
		next->preTchClass = NULL;
		return true;
	}
	if (next == NULL)
	{
		tch->lastClass = pre;
		pre->nextTchClass = NULL;
		return true;
	}
	pre->nextTchClass = next;
	next->preTchClass = pre;
	return true;
}

//D:�ӽ�ʦroom������ɾ������free,
//	��Ҫά����firstClass lastClass ,pre ,next
//C:deleteClass������������
bool deleteInRoom(roomInfo * room, classInfo* deleteClass)
{
	classInfo* pre = room->firstClass;
	if (pre == NULL)
	{
		printf("��ǰ���ҿγ̱�Ϊ�գ�ɾ������\n");
		return false;
	}
	if (pre == deleteClass)			//��һ�ڿ�Ϊɾ��
	{
		room->firstClass = deleteClass->nextRoomClass;
		if (room->firstClass->nextRoomClass == NULL)
		{
			room->lastClass = room->firstClass;
		}
		return true;
	}
	pre = findPreClassInRoom(room, deleteClass);
	pre->nextRoomClass = deleteClass->nextRoomClass;
	if (pre->nextRoomClass == NULL)//���һ�ڿ�Ϊɾ��
	{
		room->lastClass = pre;
	}
	return true;
}


bool deleteInCourse(courseInfo * course, classInfo* deleteClass)
{
	classInfo* pre = deleteClass->preSameClass;
	classInfo* next = deleteClass->nextSameClass;
	if (pre == NULL&&next == NULL)
	{
		printf("deleteClass In Same ����\n");
		return false;
	}
	if (pre == NULL)//ɾ����Ϊ��λ
	{
		course->firstClass = next;
		next->preSameClass = NULL;
		return true;
	}
	if (next == NULL)
	{
		course->lastClass = pre;
		pre->nextSameClass = NULL;
		return true;
	}
	pre->nextSameClass = next;
	next->preSameClass = pre;
	return true;
}

//D:Ϊ��ǰ�γ��е����ж�����ɾ����classInfo��Ϣ
//OBJ:	�༶stu
//		��ʦtch
//		��ʦroom
//		�γ�course
//C:��ǰclass���� ����ÿһ���γ�������stu����Ҫ����ɾ���γ�
//I:course,week,day,order,room
//O:ɾ���������
bool deleteClass(courseInfo * course, classInfo * deleteClass)
{
	for (int i = 1; i <= course->stuNum; i++)//����stuɾ��
	{
		studentInfo* stu = findStuByIndex(stuL.headStu, course->stuNums[i]);
		if (stu == NULL)
		{
			printf("�༶%dδ�ҵ�\n", course->stuNums[i]);
			//return false;
		}
		deleteInStu(stu, deleteClass);
	}
	for (int i = 1; i <= course->tchNum; i++)//����tchɾ��
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch, course->tchNums[i]);
		if (tch == NULL)
		{
			printf("��ʦ%dδ�ҵ�\n", course->tchNums[i]);
			//return false;
		}
		deleteInTch(tch, deleteClass);
	}
	deleteInRoom(deleteClass->room, deleteClass);
	deleteInCourse(course, deleteClass);
	return true;
}

//D:Ϊ��ǰcourse������class����deleteClassɾ���γ�
//OBJ:	�༶stu
//		��ʦtch
//		��ʦroom
//		�γ�course
//C:��ǰcourse���� ����ÿһ���γ�������class����Ҫ����deleteClassɾ���γ�
//I:course
//O:ɾ���������
bool deleteCourse(courseInfo * course)
{
	classInfo * delClass = course->firstClass;
	classInfo * next = delClass->nextSameClass;
	if (deleteClass == NULL)
	{
		printf("��ǰcourse�¿γ�Ϊ��");
		return true;
	}
	while (deleteClass!=NULL)
	{
		deleteClass(course, delClass);
		delClass = next;
		next = next->nextSameClass;
	}
	free(course);
	return true;
}

//D:room�������ҵ�class��ǰ��
//C:����ǰ��������Ϊfirst�Ҵ���
//I:room,nowClass
//O:����ǰ��
classInfo * findPreClassInRoom(roomInfo * room, classInfo* nowClass)
{
	classInfo* pre = room->firstClass;
	while (pre->nextSameClass != NULL)
	{
		if (pre->nextSameClass == nowClass)
		{
			return pre;
		}
	}
	return NULL;
}

//D:course�������ҵ�class��ǰ��
//C:����ǰ��������Ϊfirst�Ҵ���
//I:course,nowClass
//O:����ǰ��
classInfo * findPreClassInCourse(courseInfo * course,classInfo* nowClass)
{
	classInfo* pre = course->firstClass;
	while (pre->nextSameClass!=NULL)
	{
		if (pre->nextSameClass == nowClass)
		{
			return pre;
		}
	}
	return NULL;
}


//D:��stu�������ҵ�class��ǰ��
//C:����ǰ��������Ϊfirst�Ҵ���
//I:stu,nowClass
//O:����ǰ��
classInfo * findPreClassInStu(studentInfo * stu,classInfo* nowClass)
{
	classInfo* pre = stu->stuFirstClass;
	if (pre == NULL)
	{
		printf("��ǰcourse��classΪ��\n");
		return NULL;
	}
	while (pre->nextClassOfDay != NULL)
	{
		if (pre->nextClassOfDay == nowClass)
		{
			return pre;
		}
		pre = pre->nextClassOfDay;
	}
	return NULL;

}

//D:ͨ������,��stu�������ҵ�class��ǰ��
//C:����ǰ��������Ϊfirst�Ҵ���
//I:course,week,day,order
//O:����ǰ��
classInfo * findPreClassInStuByTime(studentInfo * stu, int week, int day, int order)
{
	classInfo* pre = stu->stuFirstClass;
	if (pre == NULL)
	{
		printf("��ǰcourse��classΪ��\n");
		return NULL;
	}
	while (pre->nextClassOfDay!=NULL)
	{
		if (classIsTheTime(pre->nextClassOfDay, week, day, order))
		{
			return pre;
		}
		pre = pre->nextClassOfDay;
	}
	return NULL;
}

//I:�γ����� className
//O:��ǰ��ѧ�����Ŀγ̵ĵ�һ��
classInfo * findFirstSameClassInStuByName(studentInfo * stu, char * className)
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
classInfo * isExistedClassInStu(studentInfo * stu, classInfo * insertClass)
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
classInfo * isExistedClassInTch(teacherInfo * tch, classInfo * insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo* pre = tch->firstClass;
	if (pre == NULL)
	{
		printf("��ǰ�����޿γ�\n");
		return NULL;
	}
	while (compareClass(pre, insertClass))
	{
		if (classIsSameDay(pre->nextTchClass, insertClass))//��ͬһ��
		{
			if (pre->nextTchClass->order == insertClass->order)//pre�ĺ�̳�ͻ
			{
				return pre->nextTchClass;
			}
		}
		if (compareClass(insertClass, pre->nextTchClass))
		{
			return NULL;
		}
	}
	return NULL;
}

//D:��Ե�ǰ���ң���ѯ�γ��Ƿ��ͻ
//I:room,insertClass
//O:������ڳ�ͻ�γ̣����س�ͻ�γ�ָ�룬���򷵻�NULL
classInfo * isExistedClassInRoom(roomInfo * room, classInfo * insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo* now = room->firstClass;
	if ((room->isUsed)[week][day][order])//�����ռ��
	{
		while (now!=NULL)
		{
			if (now->week == week&&now->day == day&&now->order == order)
			{
				if (now->room == room)
				{
					return now;
				}
				else
				{
					printf("������Ϣ����\n");
					return NULL;
				}
			}
			now = now->nextRoomClass;
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}

//D:newһ��course
courseInfo * newCourse(int beginWeek, int endWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums)
{
	courseInfo* insertCourse = (courseInfo*)malloc(sizeof(courseInfo));
	if (insertCourse == NULL)
	{
		printf("�ڴ�������newCourse����\n");
		return NULL;
	}
	insertCourse->beginWeek = beginWeek;
	insertCourse->endWeek = endWeek;
	insertCourse->courseHour = courseHour;
	strcpy(insertCourse->courseName, courseName);
	insertCourse->tchNum = tchNum;
	for (int i = 1; i < tchNum; i++)
	{
		insertCourse->tchNums[i] = tchNums[i];
	}
	insertCourse->stuNum = stuNum;
	for (int i = 1; i < stuNum; i++)
	{
		insertCourse->stuNums[i] = stuNums[i];
	}
	insertCourse->firstClass = NULL;
	insertCourse->lastClass = NULL;
	return insertCourse;
}

//D:�жϲ���γ��Ƿ���ڣ���ͬ�γ������£�ֻҪ��һ���༶��ͬ����Ϊ��ͻ
bool isEistedCourse(char * courseName, int stuNum, int *stuNums)
{
	for (int i = 1; i <= courseNum; i++)
	{
		if (strcmp(allCourse[i].courseName, courseName) == 0)
		{

			while (*stuNums!='\0')//����İ༶����
			{
				int *iStu = allCourse[i].stuNums;
				while (*iStu!='\0')
				{
					if (*stuNums == *iStu)
					{
						return true;
					}
					iStu++;
				}
				stuNum++;
			}

		}
	}
	return false;
}

//D:������ʼ��Ϣ������course��ͬʱ����addClass���class 
//OBJ:	�༶stu
//		��ʦtch
//		��ʦroom
//		�γ�course
//C:��ǰ�γ̲����ڣ�����ÿһ���γ�������stu����Ҫ������ӿγ�
//I:course,week,day,order,room
//O:�������
courseInfo * addCourse(int beginWeek, int endWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums)
{
	courseInfo* insertCourse = newCourse(beginWeek, endWeek, courseHour, courseName, tchNum, tchNums, stuNum, stuNums);//��������ڵ�
	if (isEistedCourse(courseName, stuNum, stuNums))
	{
		printf("��ǰ�γ��Ѵ��ڻ��ͻ��\n");
		free(insertCourse);
		return NULL;
	}
	return insertCourse;
}




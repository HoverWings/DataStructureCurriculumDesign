#include"fun.h"

extern buildingInfo Buildings[50];
extern int BuildingCount;
extern courseInfo allCourse[50];
extern stuLink stuL;
extern tchLink tchL;

#pragma region StuFun

bool newStu(studentInfo** stu)
{
	(*stu) = (studentInfo *)malloc(sizeof(studentInfo));
	(*stu)->nextStu = NULL;
	(*stu)->stuFirstClass=NULL;
	(*stu)->stuLastClass=NULL;
	return true;
}

//D:���Stu��StuL��ά������ͽڵ��stuNum
bool addStu(stuLink * stuL, studentInfo * stu)
{
	studentInfo* now = stuL->headStu;
	if (now == NULL)
	{
		stuL->headStu = stu;
		stuL->stuNum++;
		stu->stuNum = stuL->stuNum;
		//now->nextStu=NULL;
		return true;
	}
	while (now->nextStu != NULL)
	{
		now = now->nextStu;
	}
	now->nextStu = stu;
	stuL->stuNum++;
	stu->stuNum = stuL->stuNum;
	return true;
}

bool deleteStu(stuLink * stuL, char * stuName)
{
	studentInfo* now = stuL->headStu;
	if (strcmp(now->stuName, stuName) == 0)
	{
		stuL->headStu= now->nextStu;
		free(now);
		stuL->stuNum--;
		now = stuL->headStu;
		while (now != NULL)//ά���༶��� ��1��ʼ
		{
			now->stuNum--;
			now = now->nextStu;
		}
		return true;
	}
	studentInfo* pre = findPreStu(stuL->headStu, stuName);
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
		stuL->stuNum--;
		return true;
	}
	return false;
}

bool showStu(stuLink * stuL)
{
	studentInfo* stu = stuL->headStu;
	if (stu == NULL)
	{
		return false;
	}
	printf("�༶����:%d\n", stuL->stuNum);
	while (stu!=NULL)
	{
		printf("�༶���:%d", stu->stuNum);
		printf("\t�༶����:%s\n", stu->stuName);
		stu = stu->nextStu;
	}
	return true;;
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

//D:���ӽ�ѧ¥
buildingInfo* addBuilding(char * buildingName,bool isZoned)
{
	BuildingCount++;
	buildingInfo* pB = &Buildings[BuildingCount];
	strcpy(pB->buildingName, buildingName);
	pB->buildingNum = BuildingCount;
	pB->firstRoom = NULL;
	pB->roomCount = 0;
	return pB;
}

//D: ɾ����ѧ¥ ����deleteRoomInBuildingɾ����ѧ¥�еĽ��� ͬʱɾ���������صĿγ�
bool deleteBuilding(int index)
{
	buildingInfo* pB = &Buildings[index];
	if(pB->firstRoom!=NULL)
	{
		roomInfo* pr = pB->firstRoom;
		for (int i = 1; i <= pB->roomCount; i++)
		{
			deleteRoomInBuilding(pB, pr->roomArea, pr->roomNum);
		}
	}
	//���к���ĺ���
	for (int i = index; i < BuildingCount; i++)
	{
		Buildings[i] = Buildings[i + 1];
		Buildings[i].buildingNum = i;
	}
	BuildingCount--;
	return true;
}

bool showBuilding()
{
	buildingInfo* pB = NULL;
	for (int i = 1; i <= BuildingCount; i++)
	{
		pB = &Buildings[i];
		showRoom(pB);
	}
	return true;
}



#pragma endregion

#pragma region TchFun

bool newTch(teacherInfo ** tch)
{
	(*tch) = (teacherInfo *)malloc(sizeof(teacherInfo));
	(*tch)->nextTch = NULL;
	(*tch)->firstClass = NULL;
	(*tch)->lastClass = NULL;
	return true;
}

bool addTch(tchLink * tchL, teacherInfo * tch)
{
	teacherInfo* now = tchL->headTch;
	if (now == NULL)	//ͷָ��Ϊ��
	{
		tchL->headTch = tch;
		tchL->tchNum++;
		tch->tchNum = tchL->tchNum;
		return true;
	}
	while (now->nextTch != NULL)
	{
		now = now->nextTch;
	}
	now->nextTch = tch;//��ĩβ����
	tchL->tchNum++;
	tch->tchNum = tchL->tchNum;
	return true;
}

//D;�ӽ�ʦ������ɾ��tch ͬʱɾ��tch�����пγ�
bool deleteTch(tchLink * tchL, char * tchName)
{
	teacherInfo* now = tchL->headTch;
	if (strcmp(now->tchName, tchName) == 0)//ͷָ��ɾ��
	{
		tchL->headTch = now->nextTch;
		deleteTchClass(now);
		free(now);
		tchL->tchNum--;
		now = tchL->headTch;
		while (now!=NULL)//ά����ʦ��� ��1��ʼ
		{
			now->tchNum--;
			now = now->nextTch;
		}
		return true;
	}
	teacherInfo* pre = findPreTch(tchL->headTch, tchName);
	if (pre == NULL)
	{
		return false;
	}
	else
	{
		now = pre->nextTch;
		pre->nextTch = now->nextTch;
		deleteTchClass(now);
		free(now);
		now = pre->nextTch;
		while (now != NULL)
		{
			now->tchNum--;
			now = now->nextTch;
		}
		tchL->tchNum--;
		return true;
	}
	return false;
}

bool deleteTchClass(teacherInfo * tch)
{
	assert(tch != NULL);
	classInfo* tchClass = tch->firstClass;
	while (tchClass!=NULL)
	{
		deleteClass(tchClass->course, tchClass);
		tchClass = tchClass->nextTchClass;
	}
	return true;
}

bool showTch(tchLink * tchL)
{
	teacherInfo* tch = tchL->headTch;
	if (tch == NULL)
	{
		return false;
	}
	printf("��ʦ����:%d\n", tchL->tchNum);
	while (tch != NULL)
	{
		printf("��ʦ���:%d", tch->tchNum);
		printf("\t��ʦ����:%s\n", tch->tchName);
		tch = tch->nextTch;
	}
	return true;;
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

#pragma endregion

#pragma region RoomFun


//D:newһ��Room
bool newRoom(roomInfo ** room)
{
	(*room) = (roomInfo *)malloc(sizeof(roomInfo));
	(*room)->firstClass = NULL;
	(*room)->lastClass = NULL;
	(*room)->nextRoom = NULL;
	return true;
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
		(*building)->roomCount++;
	}
	return false;
}

//D:��building��ɾ��room ͬʱ����deleteClassɾ��������֮��ص�class
bool deleteRoomInBuilding(buildingInfo * building, int roomArea, int roomNum)
{
	roomInfo * pre= NULL;
	roomInfo * room = NULL;
	classInfo* roomClass = NULL;
	pre=findPreRoom(building,roomArea,roomArea);
	if(pre==NULL)
	{
		if((*building).roomCount!=1)//û��ǰ���������ֻ����һ������
		{
			return false;
		}
	}
	room = pre->nextRoom;
	roomClass = room->firstClass;
	while (roomClass != NULL)
	{
		deleteClass(roomClass->course, roomClass);
		roomClass = roomClass->nextRoomClass;
	}
	return	deleteRoomByPre(&building,pre);
}

bool showRoom(buildingInfo * building)
{
	printf("��ѧ¥���:%d ��ѧ¥����:%s ��������:%d\n", building->buildingNum, building->buildingName, building->roomCount);
	if (building->roomCount != 0)
	{
		printf("��ѧ¥�µĽ�����:\n");
		roomInfo * pr = building->firstRoom;
		assert(pr != NULL);
		while (pr != NULL)
		{
			if (building->isZoned)
			{
				if (pr->roomArea == 0)
				{
					printf("N%d", pr->roomNum);
				}
				else
				{
					printf("S%d", pr->roomNum);
				}
			}
			else
			{
				printf("%d", pr->roomNum);
			}
		}
	}
	return false;
}


//C:��ǰ��ѧ¥���д˽��� pre=NULL��˵������ֻ��һ������ 
bool deleteRoomByPre(buildingInfo **building, roomInfo * pre)
{
	if (pre == NULL&&(*building)->roomCount==1)	//����ֻ��һ������
	{
		free((*building)->firstRoom);
		(*building)->firstRoom=NULL;
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


#pragma endregion


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
courseInfo * newCourse(int beginWeek, int endWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums, int courseFragmentNum,timeFragment* courseFragment)
{
	courseInfo* insertCourse = (courseInfo*)malloc(sizeof(courseInfo));
	if (insertCourse == NULL)
	{
		printf("�ڴ�������newCourse����\n");
		return NULL;
	}
	insertCourse->firstWeek = beginWeek;
	insertCourse->lastWeek = endWeek;
	insertCourse->courseHour = courseHour;
	strcpy(insertCourse->courseName, courseName);
	insertCourse->tchNum = tchNum;
	for (int i = 1; i < courseFragmentNum; i++)
	{
		insertCourse->courseFragment[i] = courseFragment[i];
	}
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
courseInfo * addCourse(int firstWeek, int lastWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums,  int courseFragmentNum, timeFragment* courseFragment)
{
	courseInfo* insertCourse = newCourse(firstWeek, lastWeek, courseHour, courseName, tchNum, tchNums, stuNum, stuNums, courseFragmentNum,courseFragment);//��������ڵ�
	if (isEistedCourse(courseName, stuNum, stuNums))
	{
		printf("��ǰ�γ��Ѵ��ڻ��ͻ��\n");
		free(insertCourse);
		return NULL;
	}
	for (int i = 1; i <= courseFragmentNum; i++)
	{
		timeFragment* tF = &(courseFragment[i]);
		for (int j = tF->beginWeek; j <= tF->endWeek; j++)
		{
			if (addClass(insertCourse, j, tF->day, tF->order, tF->room) == NULL)
			{
				printf("�������\n");
			}
		}
	}
	return insertCourse;
}

//��Ҫ�洢��
//stu����
//tch����
//course����
bool saveStuToDat()
{
	FILE *out;
	if ((out = fopen("Data\\Stu.dat", "wb")) == NULL)
		return false;
	stuLink* pstuL= &stuL;
	studentInfo* pStu = stuL.headStu;
	fwrite(pstuL, sizeof(stuLink), 1, out);
	while (pStu!=NULL)
	{
		fwrite(pStu, sizeof(studentInfo), 1, out);
		pStu = pStu->nextStu;
	}
	fclose(out);
	return true;
}

bool saveTchToDat()
{
	FILE *out;
	if ((out = fopen("Data\\Tch.dat", "wb")) == NULL)
		return false;
	tchLink* ptchL = &tchL;
	teacherInfo* pTch = tchL.headTch;
	fwrite(ptchL, sizeof(tchLink), 1, out);
	while (pTch != NULL)
	{
		fwrite(pTch, sizeof(teacherInfo), 1, out);
		pTch = pTch->nextTch;
	}
	fclose(out);
	return true;
}

bool saveRoomToDat()
{
	FILE *out;
	if ((out = fopen("Data\\Building.dat", "wb")) == NULL)
		return false;
	fwrite(&BuildingCount, sizeof(int), 1, out);
	buildingInfo* pB = Buildings;
	for (int i = 1; i <= BuildingCount; i++)
	{
		pB = &Buildings[i];
		roomInfo* pr = pB->firstRoom;
		fwrite(pB, sizeof(buildingInfo), 1, out);
		for (int j = 1; j <= pB->roomCount; j++)
		{
			fwrite(pr, sizeof(roomInfo), 1, out);
			pr = pr->nextRoom;
		}
	}
	fclose(out);
	return true;
}

bool loadStuFromDat()
{
	FILE *in;
	if ((in = fopen("Data\\Stu.dat", "wb")) == NULL)
		return false;
	stuLink* pstuL = &stuL;
	studentInfo* pStu = NULL;
	studentInfo* pre = NULL;
	fread(pstuL, sizeof(stuLink),1, in);
	for (int i = 1; i <= pstuL->stuNum; i++)
	{
		newStu(&pStu);
		fread(pStu, sizeof(studentInfo), 1, in);
		if (i == 1)
		{
			pstuL->headStu = pStu;
			pre = pStu;
		}
		else
		{
			pre->nextStu = pStu;
			pre = pStu;
		}
	}
	pStu->nextStu = NULL;
	fclose(in);
	return true;
}

bool loadTchFromDat()
{
	FILE *in;
	if ((in = fopen("Data\\Tch.dat", "wb")) == NULL)
		return false;
	tchLink* ptchL = &tchL;
	teacherInfo* pTch = NULL;
	teacherInfo* pre = NULL;
	fwrite(ptchL, sizeof(tchLink), 1, in);
	for (int i = 1; i <= ptchL->tchNum; i++)
	{
		newTch(&pTch);
		fread(pTch, sizeof(teacherInfo), 1, in);
		if (i == 1)
		{
			ptchL->headTch = pTch;
			pre = pTch;
		}
		else
		{
			pre->nextTch = pTch;
			pre = pTch;
		}
	}
	pTch->nextTch = NULL;
	fclose(in);
	return true;
}

bool loadRoomFromDat()
{
	FILE *in;
	if ((in = fopen("Data\\Tch.dat", "wb")) == NULL)
		return false;
	fread(&BuildingCount, sizeof(int), 1, in);
	buildingInfo* pB = Buildings;
	roomInfo* pr =NULL;
	roomInfo* pre = NULL;
	for (int i = 1; i <= BuildingCount; i++)
	{
		pB = &Buildings[i];	
		fread(pB, sizeof(buildingInfo), 1, in);
		for (int j = 1; j <= pB->roomCount; j++)//��һ��building�ж�ȡroom
		{
			newRoom(&pr);
			fread(pr, sizeof(roomInfo), 1, in);
			if (j == 1)
			{
				pB->firstRoom = pr;
				pre = pr;
			}
			else
			{
				pre->nextRoom = pr;
				pre = pr;
			}
		}
	}
	fclose(in);
	return true;
}



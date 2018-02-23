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
		while (now != NULL)//维护班级编号 从1开始
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
		while (now != NULL)//维护班级编号 从1开始
		{
			now->stuNum--;
			now = now->nextStu;
		}
		stuL.stuNum--;
		return true;
	}
	return false;
}

//C:headStu不为空
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

//C:headStu不为空 且不为寻找
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
		printf("index 错误");
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
	if (now == NULL)	//头指针为空
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
	now->nextTch = tch;//在末尾插入
	tchL.tchNum++;
	tch->tchNum = tchL.tchNum;
	return true;
}

bool deleteTch(teacherInfo ** headTch, char * tchName)
{
	teacherInfo* now = (*headTch);
	if (strcmp(now->tchName, tchName) == 0)//头指针删除
	{
		(*headTch) = now->nextTch;
		free(now);
		tchL.tchNum--;
		now = (*headTch);
		while (now!=NULL)//维护教师编号 从1开始
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
		printf("index 错误");
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



//C:教学楼中无此教室
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

//C:当前教学楼中有此教室 pre=NULL则说明仅仅只有一个教室
bool deleteRoomByPre(buildingInfo **building, roomInfo * pre)
{
	if (pre == NULL)
	{
		free((*building)->firstRoom);
		return true;
	}
	roomInfo* now = pre->nextRoom;
	if (now->nextRoom == NULL)	//没有后继
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




//D:ClassInfo比较，若B比A大返回True,否则返回False
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

//D:new一个class根据course信息
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

//D:根据日程表找到插入位置
//C:插入课程位置无课程
//I:studentInfo * stu, int week, int day, int order
//O:日程插入位置的前一节课程
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
		return insertClass;				//无前驱 返回自身
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
		return pre;						//处理完成
	}
	//在当前已存在的教学日历中遍历
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextClassOfDay))//找到插入位置
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
				if (classIsSameDay(pre, insertClass))//与前驱在同一天
				{
					pre->isEnd = false;
					insertClass->isEnd = true;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				if (classIsSameDay(insertClass, next))//与后继在同一天
				{
					insertClass->isEnd = false;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				//与二者均不在同一天
				pre->nextClassOfDay = insertClass;
				insertClass->nextClassOfDay = next;
				pre->isEnd = true;
				return pre;
			}
		}
		pre = pre->nextClassOfDay;
	}
	return NULL;//BUG了 理论上不会出现此情况
}



//D:根据课程course找到插入位置
//C:插入课程位置无课程
//I:studentInfo * stu, int week, int day, int order
//O:课程插入位置
classInfo* insertByCourse(courseInfo * course,classInfo* insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo *pre = course->firstClass;
	classInfo *next = course->lastClass;
	if (compareClass(insertClass, pre))	//第一节课前
	{
		//处理course链表
		course->firstClass = insertClass;
		insertClass->preSameClass = NULL;
		insertClass->nextSameClass = pre;
		pre->preSameClass = insertClass;
		return insertClass;
	}
	if (compareClass(next, insertClass))//最后一节课后
	{
		//处理course链表
		course->lastClass = insertClass;
		insertClass->preSameClass = next;
		insertClass->nextSameClass = NULL;
		next->nextSameClass = insertClass;
		return insertClass;
	}
	//遍历course链表找到当前课程
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextSameClass))//找到插入位置
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


//C:当前课程存在 对于每一个stu都需要调用次函数
bool addClass(courseInfo * course,int week, int day, int order )
{
	classInfo* insertClass = newClassByCourse(course,week, day, order);//构建插入节点
	for (int i = 0; i < course->stuNum; i++)//判断stu是否冲突
	{
		studentInfo* stu = findStuByIndex(stuL.headStu, course->stuNums[i]);
		if (stu == NULL)
		{
			printf("班级%d未找到\n", course->stuNums[i]);
			return false;
		}
		if (isExistedClassByStu(stu, insertClass))//存在冲突，整体不插入，插入失败
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 0; i < course->tchNum; i++)//判断tch是否冲突
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch, course->tchNums[i]);
		if (tch == NULL)
		{
			printf("教师%d未找到\n", course->tchNums[i]);
			return false;
		}
		if (isExistedClassByTch(tch, insertClass))//存在冲突，整体不插入，插入失败
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 0; i < course->stuNum; i++)//遍历stu插入
	{
		studentInfo* stu = findStuByIndex(stuL.headStu,course->stuNums[i]);
		if (stu == NULL)
		{
			printf("班级%d未找到\n",course->stuNums[i]);
			return false;
		}
		insertBySchedule(stu, insertClass);
	}
	insertByCourse(course, insertClass);    //课程插入
	for (int i = 0; i < course->tchNum; i++)//遍历tch插入
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch,course->tchNums[i]);
		if (tch == NULL)
		{
			printf("教师%d未找到\n", course->tchNums[i]);
			return false;
		}
		insertByTch(tch, insertClass);
	}
	return true;
}

//I:课程名称 className
//O:当前教学日历的课程的第一课
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


//I:课程名称 className,周次	 week
//O:当前星期的课程的第一课
classInfo * findFirstSameClassInWeek(studentInfo * stu, char * className, int week)
{
	int begin = stu->beginWeek;
	int end = stu->endWeek;
	weekInfo* nowWeek = &(stu->weeks)[week];
	dayInfo* days = nowWeek->days;
	classInfo* now = nowWeek->weekFirstClass;
	if (now == NULL)	//当前周次无课
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
	return NULL;		//当前周未找到
}

//D:针对当前班级，查询课程是否冲突
//I:stu,insertClass
//O:如果存在冲突课程，返回冲突课程指针，否则返回NULL
classInfo * isExistedClassByStu(studentInfo * stu, classInfo * insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	weekInfo* insertWeek = &(stu->weeks[week]);
	dayInfo* insertDay = &(insertWeek->days[day - 1]);
	classInfo* pre = insertDay->dayFirstClass;
	while (compareClass(pre,insertClass))//保证pre在插入之前
	{
		if (classIsSameDay(pre->nextClassOfDay, insertClass))//在同一天
		{
			if (pre->nextClassOfDay->order == insertClass->order)//pre的后继冲突
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

//D:针对当前教师，查询课程是否冲突
//I:tch,insertClass
//O:如果存在冲突课程，返回冲突课程指针，否则返回NULL
classInfo * isExistedClassByTch(teacherInfo * tch, classInfo * insertClass)
{
	//此处需要些
	/*
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	weekInfo* insertWeek = &(stu->weeks[week]);
	dayInfo* insertDay = &(insertWeek->days[day - 1]);
	classInfo* pre = insertDay->dayFirstClass;
	while (compareClass(pre, insertClass))//保证pre在插入之前
	{
		if (classIsSameDay(pre->nextClassOfDay, insertClass))//在同一天
		{
			if (pre->nextClassOfDay->order == insertClass->order)//pre的后继冲突
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
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

//D:判断class时间是否为所求时间
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

//D:new一个class根据course信息
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

//D:根据日程表找到插入位置 OBJ:stu
//C:插入课程位置无课程
//I:studentInfo * stu, int week, int day, int order
//O:日程插入位置的前一节课程
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
		return insertClass;				//无前驱 返回自身
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
				insertClass->isLast = false;
				return pre;
			}
			else
			{
				if (classIsSameDay(pre, insertClass))//与前驱在同一天
				{
					pre->isLast = false;
					insertClass->isLast = true;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				if (classIsSameDay(insertClass, next))//与后继在同一天
				{
					insertClass->isLast = false;
					pre->nextClassOfDay = insertClass;
					insertClass->nextClassOfDay = next;
					return pre;
				}
				//与二者均不在同一天
				pre->nextClassOfDay = insertClass;
				insertClass->nextClassOfDay = next;
				pre->isLast = true;
				return pre;
			}
		}
		pre = pre->nextClassOfDay;
	}
	printf("课程信息有误！\n");
	return NULL;//BUG了 理论上不会出现此情况
}



//D:根据课程course找到插入位置
//C:插入课程位置无课程
//I:studentInfo * stu, int week, int day, int order
//O:课程插入位置
classInfo* insertInCourse(courseInfo * course,classInfo* insertClass)
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
	return NULL;
}

//D:插入教师链表
//C:tch课程不冲突
//I:tch , insertClass
//O:插入操作结果 
bool insertInTch(teacherInfo* tch,classInfo* insertClass)
{
	if (isExistedClassInTch(tch, insertClass))//OC处理
	{
		printf("教师 %d 课程存在冲突插入失败!\n",tch->tchNum);
		return false;
	}
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo *pre = tch->firstClass;
	classInfo *next = tch->lastClass;
	if (compareClass(insertClass, pre))	//第一节课前
	{
		//处理course链表
		tch->firstClass = insertClass;
		insertClass->nextTchClass = pre;
		pre->preTchClass = insertClass;
		return true;
	}
	if (compareClass(next, insertClass))//最后一节课后
	{
		//处理course链表
		tch->lastClass = insertClass;
		insertClass->preTchClass = next;
		insertClass->nextTchClass = NULL;
		next->nextTchClass = insertClass;
		return true;
	}
	//遍历course链表找到当前课程
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextTchClass))//找到插入位置
		{
			next = pre->nextTchClass;
			pre->nextTchClass = insertClass;
			insertClass->nextTchClass = next;
			return true;
		}
	}
	return false;
}

//D:插入教室链表
//C:room课程不冲突
//I:room , insertClass
//O:插入操作结果 维护Room占用数组
bool insertInRoom(roomInfo* room, classInfo* insertClass)
{
	if (isExistedClassInRoom(room, insertClass))//OC处理
	{
		return false;
	}
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo *pre = room->firstClass;
	classInfo *next = room->lastClass;
	if (compareClass(insertClass, pre))	//第一节课前
	{
		//处理room链表
		room->firstClass = insertClass;
		insertClass->nextRoomClass = pre;
		room->isUsed[week][day][order] = true;
		return true;
	}
	if (compareClass(next, insertClass))//最后一节课后
	{
		//处理room链表
		room->lastClass = insertClass;
		insertClass->nextRoomClass = NULL;
		next->nextRoomClass = insertClass;
		room->isUsed[week][day][order] = true;
		return true;
	}
	//遍历room链表找到当前课程
	while (compareClass(pre, insertClass))
	{
		if (compareClass(insertClass, pre->nextRoomClass))//找到插入位置
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

//D:为当前课程中的所有对象在 
//	上课时间:week day order 
//	上课地点:room 添加课程 
//OBJ:	班级stu
//		教师tch
//		教师room
//		课程course
//C:当前课程存在 对于每一个课程所属的stu都需要调用添加课程
//I:course,week,day,order,room
//O:操作结果
classInfo* addClass(courseInfo * course,int week, int day, int order,roomInfo* room)
{
	classInfo* insertClass = newClassByCourse(course,week, day, order);//构建插入节点
	if (isExistedClassInRoom(room, insertClass))
	{
		printf("教室存在冲突插入失败!\n");
		return false;
	}
	for (int i = 1; i <= course->stuNum; i++)//判断stu是否冲突
	{
		studentInfo* stu = findStuByIndex(stuL.headStu, course->stuNums[i]);
		if (stu == NULL)
		{
			printf("班级%d未找到\n", course->stuNums[i]);
			return false;
		}
		if (isExistedClassInStu(stu, insertClass))//存在冲突，整体不插入，插入失败
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 1; i <= course->tchNum; i++)//判断tch是否冲突
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch, course->tchNums[i]);
		if (tch == NULL)
		{
			printf("教师%d未找到\n", course->tchNums[i]);
			return false;
		}
		if (isExistedClassInTch(tch, insertClass))//存在冲突，整体不插入，插入失败
		{
			free(insertClass);
			return false;
		}
	}
	for (int i = 1; i <= course->stuNum; i++)//遍历stu插入
	{
		studentInfo* stu = findStuByIndex(stuL.headStu,course->stuNums[i]);
		if (stu == NULL)
		{
			printf("班级%d未找到\n",course->stuNums[i]);
			return false;
		}
		insertInStu(stu, insertClass);
	}
	insertInCourse(course, insertClass);    //course插入
	for (int i = 1; i <= course->tchNum; i++)//遍历tch插入
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch,course->tchNums[i]);
		if (tch == NULL)
		{
			printf("教师%d未找到\n", course->tchNums[i]);
			return false;
		}
		insertInTch(tch, insertClass);
	}
	insertInRoom(room, insertClass);		//room插入
	return insertClass;
}

//D:从班级stu链表中删除，不free,需要对course的每一个班级调用此函数
//	需要维护：isLast,stuFirstClass,stuLastClass
//C:deleteClass存在于链表中
bool deleteInStu(studentInfo * stu, classInfo* deleteClass)
{
	classInfo* pre = stu->stuFirstClass;
	classInfo* next = stu->stuLastClass;
	if (pre == NULL)
	{
		printf("当前班级课程表为空，删除有误\n");
		return false;
	}
	if (pre == deleteClass)	//第一节课为删除
	{
		stu->stuFirstClass = deleteClass->nextClassOfDay;
		if (stu->stuFirstClass->nextClassOfDay == NULL)
		{
			stu->stuLastClass = stu->stuFirstClass;
		}
		return true;
	}
	pre = findPreClassInStu(stu, deleteClass);
	if (classIsSameDay(pre, deleteClass))//维护isLast标志位
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


//D:从教师tch链表中删除，不free,需要对tchNums的每一个tch调用此函数
//	需要维护：firstClass lastClass pre ,next
//C:deleteClass存在于链表中
bool deleteInTch(teacherInfo * tch, classInfo* deleteClass)
{
	classInfo* pre = deleteClass->preTchClass;
	classInfo* next = deleteClass->nextTchClass;
	if (pre == NULL&&next == NULL)
	{
		printf("deleteClass In Tch 错误！\n");
		return false;
	}
	if (pre == NULL)//删除的为首位
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

//D:从教师room链表中删除，不free,
//	需要维护：firstClass lastClass ,pre ,next
//C:deleteClass存在于链表中
bool deleteInRoom(roomInfo * room, classInfo* deleteClass)
{
	classInfo* pre = room->firstClass;
	if (pre == NULL)
	{
		printf("当前教室课程表为空，删除有误\n");
		return false;
	}
	if (pre == deleteClass)			//第一节课为删除
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
	if (pre->nextRoomClass == NULL)//最后一节课为删除
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
		printf("deleteClass In Same 错误！\n");
		return false;
	}
	if (pre == NULL)//删除的为首位
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

//D:为当前课程中的所有对象在删除此classInfo信息
//OBJ:	班级stu
//		教师tch
//		教师room
//		课程course
//C:当前class存在 对于每一个课程所属的stu都需要调用删除课程
//I:course,week,day,order,room
//O:删除操作结果
bool deleteClass(courseInfo * course, classInfo * deleteClass)
{
	for (int i = 1; i <= course->stuNum; i++)//遍历stu删除
	{
		studentInfo* stu = findStuByIndex(stuL.headStu, course->stuNums[i]);
		if (stu == NULL)
		{
			printf("班级%d未找到\n", course->stuNums[i]);
			//return false;
		}
		deleteInStu(stu, deleteClass);
	}
	for (int i = 1; i <= course->tchNum; i++)//遍历tch删除
	{
		teacherInfo* tch = findTchByIndex(tchL.headTch, course->tchNums[i]);
		if (tch == NULL)
		{
			printf("教师%d未找到\n", course->tchNums[i]);
			//return false;
		}
		deleteInTch(tch, deleteClass);
	}
	deleteInRoom(deleteClass->room, deleteClass);
	deleteInCourse(course, deleteClass);
	return true;
}

//D:为当前course的所有class调用deleteClass删除课程
//OBJ:	班级stu
//		教师tch
//		教师room
//		课程course
//C:当前course存在 对于每一个课程所属的class都需要调用deleteClass删除课程
//I:course
//O:删除操作结果
bool deleteCourse(courseInfo * course)
{
	classInfo * delClass = course->firstClass;
	classInfo * next = delClass->nextSameClass;
	if (deleteClass == NULL)
	{
		printf("当前course下课程为空");
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

//D:room链表中找到class的前驱
//C:存在前驱，即不为first且存在
//I:room,nowClass
//O:返回前驱
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

//D:course链表中找到class的前驱
//C:存在前驱，即不为first且存在
//I:course,nowClass
//O:返回前驱
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


//D:在stu链表中找到class的前驱
//C:存在前驱，即不为first且存在
//I:stu,nowClass
//O:返回前驱
classInfo * findPreClassInStu(studentInfo * stu,classInfo* nowClass)
{
	classInfo* pre = stu->stuFirstClass;
	if (pre == NULL)
	{
		printf("当前course中class为空\n");
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

//D:通过日期,在stu链表中找到class的前驱
//C:存在前驱，即不为first且存在
//I:course,week,day,order
//O:返回前驱
classInfo * findPreClassInStuByTime(studentInfo * stu, int week, int day, int order)
{
	classInfo* pre = stu->stuFirstClass;
	if (pre == NULL)
	{
		printf("当前course中class为空\n");
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

//I:课程名称 className
//O:当前教学日历的课程的第一课
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
classInfo * isExistedClassInStu(studentInfo * stu, classInfo * insertClass)
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
classInfo * isExistedClassInTch(teacherInfo * tch, classInfo * insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo* pre = tch->firstClass;
	if (pre == NULL)
	{
		printf("当前教室无课程\n");
		return NULL;
	}
	while (compareClass(pre, insertClass))
	{
		if (classIsSameDay(pre->nextTchClass, insertClass))//在同一天
		{
			if (pre->nextTchClass->order == insertClass->order)//pre的后继冲突
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

//D:针对当前教室，查询课程是否冲突
//I:room,insertClass
//O:如果存在冲突课程，返回冲突课程指针，否则返回NULL
classInfo * isExistedClassInRoom(roomInfo * room, classInfo * insertClass)
{
	int week = insertClass->week;
	int day = insertClass->day;
	int order = insertClass->order;
	classInfo* now = room->firstClass;
	if ((room->isUsed)[week][day][order])//如果被占用
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
					printf("房间信息有误！\n");
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

//D:new一个course
courseInfo * newCourse(int beginWeek, int endWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums)
{
	courseInfo* insertCourse = (courseInfo*)malloc(sizeof(courseInfo));
	if (insertCourse == NULL)
	{
		printf("内存已满，newCourse错误！\n");
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

//D:判断插入课程是否存在，相同课程名称下，只要有一个班级相同，即为冲突
bool isEistedCourse(char * courseName, int stuNum, int *stuNums)
{
	for (int i = 1; i <= courseNum; i++)
	{
		if (strcmp(allCourse[i].courseName, courseName) == 0)
		{

			while (*stuNums!='\0')//插入的班级数组
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

//D:给出初始信息，创建course，同时调用addClass添加class 
//OBJ:	班级stu
//		教师tch
//		教师room
//		课程course
//C:当前课程不存在，对于每一个课程所属的stu都需要调用添加课程
//I:course,week,day,order,room
//O:操作结果
courseInfo * addCourse(int beginWeek, int endWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums)
{
	courseInfo* insertCourse = newCourse(beginWeek, endWeek, courseHour, courseName, tchNum, tchNums, stuNum, stuNums);//构建插入节点
	if (isEistedCourse(courseName, stuNum, stuNums))
	{
		printf("当前课程已存在或冲突！\n");
		free(insertCourse);
		return NULL;
	}
	return insertCourse;
}




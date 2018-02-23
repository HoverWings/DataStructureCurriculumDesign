#include<stdio.h>
#include<cstring>
#include<malloc.h>

/*
注释说明：
D:Description 说明函数作用
C:Condition   函数调用前提条件
I:Input		  函数输入
O:Output	  函数输出
*/

/*
需要维护的链表
schedule 日程链表
·在stu下 每一个班级一个日程链表

course   课程链表
tch	   教师线性表
·每一个教师授课链表教师授课

room   教室链表
·每一个教室的课程链表
*/


#pragma region classSchedule
//define the ClassInfo struct saved By LINK  表示课表 对于当前班级
typedef struct classInfo
{
	int week;										//当前周次 0-6
	int day;										//当前星期 1-20
	int order;                                      //上课时间 1-6
	char className[20];                             //课程名称
	struct courseInfo* course;								//所属的course
	struct classInfo* preSameClass = NULL;                 //上一次课的info 双向链表
	struct classInfo* nextSameClass = NULL;                //下一次课的info 双向链表
	bool isEnd = false;										//是否是当天的最后一节课
	struct classInfo* nextClassOfDay = NULL;                 //当天的下一节课 如果是最后一节课指向第二天的第一节课
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
	int dayNum;						 //当前星期 0-6
	char dayName[20];				 //Mon. Tues. Wed. Tuhr. Fri. Sat. Sun.
	int dayClassNum;				 //当天课程数目
	classInfo* dayFirstClass = NULL;	 //当天第一节课
}dayInfo;

//周结构体定义
typedef struct weekInfo
{
	int week;							//当前周次
	bool isExamWeek = false;			//是否为考试周
	int weekClassNum;					//当天周次数目
	dayInfo days[7];		 			//日信息数组
	classInfo* weekFirstClass = NULL;	//当周第一节课
}weekInfo;

#pragma endregion

#pragma region student
//define the student Struct 表示班级
typedef  struct studentInfo
{
	int stuNum;                   //班级编号
	char stuName[20];             //班级名称 如IOT1601	
	int beginWeek = 0;			  //开始有课周次 1-20
	int endWeek = 0;			  //开始无课周次 1-20
	weekInfo weeks[25];			  //二十周的课表数组 1-20
	classInfo* scheduleFirstClass = NULL;
	classInfo* scheduleLastClass = NULL;
	struct studentInfo* nextStu = NULL;	  //下一个班级	
}studentInfo;

typedef struct studentInfo studentInfo;

typedef struct stuLink
{
	studentInfo* headStu = NULL;
	int stuNum = 0;
}stuLink;

static stuLink stuL;
#pragma endregion

#pragma region course
typedef struct courseInfo
{
	int beginWeek;
	int endWeek;
	int courseHour;										//学时数
	char className[20];									//课程名称
	int tchNum;
	int tchNums[10];									//教师编号
	int stuNum;
	int stuNums[10];									//上课班级编号
	classInfo* firstClass = NULL;						//第一节课
	classInfo* lastClass = NULL;						//最后一节课
}courseInfo;
#pragma endregion

#pragma region room
//define the Room Struct
typedef struct roomInfo
{
	int buildingNum;               //教学楼编号
	bool isUsed = false;           //表示当前是否被占用
	int roomArea;                  //表示区域 如0表示N/1表示S
	int roomNum;                   //教室编号
	classInfo* nextClass=NULL;     //第一节课/下一节课		   当前房间的课程链表
	roomInfo* nextRoom = NULL;     //当前教学楼的下一间房间编号 房间链表
}roomInfo;

typedef struct buildingInfo
{
	int buildingNum;               //教学楼编号
	char buildingName[20];         //教学楼名称
	roomInfo* firstRoom = NULL;
}buildingInfo;



#pragma endregion

#pragma region teacher
																		//define the teacher info Struct
typedef struct teacherInfo
{
	int tchNum;					 //教师编号
	char tchName[20];			 //教师名称
	int classNums[10];           //上课班级编号
	classInfo* nextClass=NULL;   //教师的的第一节课/下一节课
	teacherInfo* nextTch = NULL;
}teacherInfo;



typedef struct tchLink
{
	teacherInfo* headTch = NULL;
	int tchNum = 0;
}tchLink;

static tchLink tchL;
#pragma endregion

//stu函数声明
bool addStu(studentInfo** headStu, studentInfo* stu);					//增加班级
bool deleteStu(studentInfo** headStu, char* stuName);					//删除班级
studentInfo* findStu(studentInfo* headStu, char* stuName);				//找到当前班级
studentInfo* findPreStu(studentInfo* headStu, char* stuName);			//找到当前班级的前驱
studentInfo* findStuByIndex(studentInfo * headStu, int stuNum);			//根据stuNum找到stu


//room函数声明
bool addRoom(buildingInfo** building, roomInfo* room);
bool deleteRoomByPre(buildingInfo** building, roomInfo*pre);
roomInfo* findPreRoom(buildingInfo* building, int roomArea, int roomNum);	//找到当前教室的前驱

//tch函数声明
bool addTch(teacherInfo** headTch, teacherInfo* tch);					//增加教师
bool deleteTch(teacherInfo** headTch, char* tchName);					//删除教师
teacherInfo* findTch(teacherInfo* headTch, char* tchName);				//找到当前教师
teacherInfo* findPreTch(teacherInfo* headTch, char* tchName);			//找到当前教师的前驱
teacherInfo* findTchByIndex(teacherInfo * headTch, int tchNum);			//根据tchNum找到tch
		

																		
//class函数声明
//当前course存在
bool addClass(studentInfo* stu, int week, int day, int order, courseInfo* course);


//course不存在 需要维护course
bool addClssses(studentInfo* stu, int weekBegin, int weekEnd, int day, int order, char* className, int* tchNum);

classInfo* findFirstSameClassBySchedule(studentInfo* stu, char* className);//根据日程遍历找到当前班级当前课程的第一节课指针
classInfo* findFirstSameClassInWeek(studentInfo* stu, char* className,int week);//需要查找当前课程的周次
classInfo* isExistedClassByStu(studentInfo* stu,classInfo* insertClass);
classInfo* isExistedClassByTch(teacherInfo* tch,classInfo* insertClass);

bool compareClass(classInfo* A, classInfo* B);
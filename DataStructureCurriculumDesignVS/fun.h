#include<stdio.h>
#include<cstring>
#include<malloc.h>

/*
注释说明：
D:Description 说明函数作用
C:Condition   函数调用前提条件
I:Input		  函数输入
O:Output	  函数输出
OBJ:Objective 操作对象
*/

/*
需要维护的链表
·stu 日程链表
··在stu下 每一个班级一个日程链表

·course   课程链表

·tch	   教师线性表
··每一个教师授课链表教师授课

·room   教室链表
··每一个教室的课程链表
*/


#pragma region room
//define the Room Struct
typedef struct roomInfo
{
	int buildingNum;						 //教学楼编号
	bool isUsed[21][7][7] = { false };		 //表示当前是否被占用(需要考虑是否占用 缘由不那么重要)
	int roomArea;							 //表示区域 如0表示N/1表示S
	int roomNum;							 //教室编号
	struct classInfo* firstClass = NULL;     //第一节课   当前房间的课程链表
	struct classInfo* lastClass = NULL;      //第一节课   当前房间的课程链表
	roomInfo* nextRoom = NULL;				 //当前教学楼的下一间房间编号 房间链表
}roomInfo;

typedef struct buildingInfo
{
	int buildingNum;                //教学楼编号
	char buildingName[20];          //教学楼名称
	roomInfo* firstRoom = NULL;
}buildingInfo;
#pragma endregion

#pragma region classStu
//define the ClassInfo struct saved By LINK  表示课表 对于当前班级
typedef struct classInfo
{
	int week;										       //当前周次 1-20
	int day;										       //当前星期 1-7
	int order;                                             //上课时间 1-6
	char className[20];                                    //课程名称
	struct roomInfo* room = NULL;						   //所属roomInfo
	struct courseInfo* course;							   //所属的courseInfo
	struct classInfo* preTchClass = NULL;				   //上一节教师的info tch双向链表
	struct classInfo* nextTchClass = NULL;				   //下一节教师的info tch双向链表
	struct classInfo* nextRoomClass = NULL;				   //下一节教室的info room链表
	struct classInfo* preSameClass = NULL;                 //上一次相同课的info course双向链表
	struct classInfo* nextSameClass = NULL;                //下一次相同课的info course双向链表
	bool isLast = false;								   //是否是当天的最后一节课（标志位）PS:此处的第一节为相对第一节 即当天学生所上的第一节课
	struct classInfo* nextClassOfDay = NULL;               //当天的下一节课 如果是最后一节课指向周后的第一节课 用于日程遍历 
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
	int dayNum;							 //当前星期 1-7
	char dayName[20];					 //Mon. Tues. Wed. Tuhr. Fri. Sat. Sun.
	int dayClassNum;					 //当天课程数目
	classInfo* dayFirstClass = NULL;	 //当天第一节课
}dayInfo;

//周结构体定义
typedef struct weekInfo
{
	int week;							//当前周次 1-20
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
	int stuNum;									//班级编号
	char stuName[20];							//班级名称 如IOT1601	
	int beginWeek = 0;							//开始有课周次 1-20
	int endWeek = 0;							//开始无课周次 1-20
	weekInfo weeks[25];							//二十周的课表数组 1-20
	classInfo* stuFirstClass = NULL;		//日程链表 可获取开始周次
	classInfo* stuLastClass = NULL;		//日程链表 可获取结束周次
	struct studentInfo* nextStu = NULL;		    //下一个班级	
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
	//int courseNum;									//课程编号
	char courseName[20];								//课程名称
	int beginWeek;										//开始周次	统计数据输入
	int endWeek;										//结束周次
	int courseHour;										//学时数	统计数据输入
	int tchNum;											//教师数目
	int tchNums[10];									//教师编号
	int stuNum;											//班级数目
	int stuNums[10];									//上课班级编号
	classInfo* firstClass = NULL;						//第一节课		实际的开始周次
	classInfo* lastClass = NULL;						//最后一节课	实际的结束周次
}courseInfo;


static courseInfo allCourse[50];//所有course	  数组
static int	courseNum = 0;		//用于courseIndex 从1开始
#pragma endregion

#pragma region teacher
//define the teacher info Struct
typedef struct teacherInfo
{
	int tchNum;					 //教师编号
	char tchName[20];			 //教师名称
	int classNums[10];           //上课班级编号
	classInfo* firstClass=NULL;  //教师的的第一节课
	classInfo* lastClass = NULL; //教师的的最后一节课
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
		

bool compareClass(classInfo* A, classInfo* B);

//class函数声明
//当前course存在
classInfo* addClass(courseInfo * course, int week, int day, int order, roomInfo* room);
bool deleteClass(courseInfo * course, classInfo* deleteClass);




classInfo * findPreClassInStu(studentInfo * stu, classInfo* nowClass);	
classInfo * findPreClassInStuByTime(studentInfo * stu, int week, int day, int order);

classInfo* findFirstSameClassInStuByName(studentInfo* stu, char* className);		//根据日程遍历找到当前班级名称当前课程的第一节课指针


classInfo* findFirstSameClassInWeek(studentInfo* stu, char* className,int week);		//需要查找当前课程的周次
classInfo* isExistedClassInStu(studentInfo* stu,classInfo* insertClass);
classInfo* isExistedClassInTch(teacherInfo* tch,classInfo* insertClass);
classInfo* isExistedClassInRoom(roomInfo* room, classInfo* insertClass);



courseInfo* addCourse(int beginWeek, int endWeek, int courseHour, char* courseName, int tchNum, int* tchNums, int stuNum, int* stuNums);


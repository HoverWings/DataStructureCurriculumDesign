#include<stdio.h>
#include<cstring>
#include<malloc.h>

/*
ע��˵����
D:Description ˵����������
C:Condition   ��������ǰ������
I:Input		  ��������
O:Output	  �������
*/

/*
��Ҫά��������
schedule �ճ�����
����stu�� ÿһ���༶һ���ճ�����

course   �γ�����
tch	   ��ʦ���Ա�
��ÿһ����ʦ�ڿ������ʦ�ڿ�

room   ��������
��ÿһ�����ҵĿγ�����
*/


#pragma region classSchedule
//define the ClassInfo struct saved By LINK  ��ʾ�α� ���ڵ�ǰ�༶
typedef struct classInfo
{
	int week;										//��ǰ�ܴ� 0-6
	int day;										//��ǰ���� 1-20
	int order;                                      //�Ͽ�ʱ�� 1-6
	char className[20];                             //�γ�����
	struct courseInfo* course;								//������course
	struct classInfo* preSameClass = NULL;                 //��һ�οε�info ˫������
	struct classInfo* nextSameClass = NULL;                //��һ�οε�info ˫������
	bool isEnd = false;										//�Ƿ��ǵ�������һ�ڿ�
	struct classInfo* nextClassOfDay = NULL;                 //�������һ�ڿ� ��������һ�ڿ�ָ��ڶ���ĵ�һ�ڿ�
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
	int dayNum;						 //��ǰ���� 0-6
	char dayName[20];				 //Mon. Tues. Wed. Tuhr. Fri. Sat. Sun.
	int dayClassNum;				 //����γ���Ŀ
	classInfo* dayFirstClass = NULL;	 //�����һ�ڿ�
}dayInfo;

//�ܽṹ�嶨��
typedef struct weekInfo
{
	int week;							//��ǰ�ܴ�
	bool isExamWeek = false;			//�Ƿ�Ϊ������
	int weekClassNum;					//�����ܴ���Ŀ
	dayInfo days[7];		 			//����Ϣ����
	classInfo* weekFirstClass = NULL;	//���ܵ�һ�ڿ�
}weekInfo;

#pragma endregion

#pragma region student
//define the student Struct ��ʾ�༶
typedef  struct studentInfo
{
	int stuNum;                   //�༶���
	char stuName[20];             //�༶���� ��IOT1601	
	int beginWeek = 0;			  //��ʼ�п��ܴ� 1-20
	int endWeek = 0;			  //��ʼ�޿��ܴ� 1-20
	weekInfo weeks[25];			  //��ʮ�ܵĿα����� 1-20
	classInfo* scheduleFirstClass = NULL;
	classInfo* scheduleLastClass = NULL;
	struct studentInfo* nextStu = NULL;	  //��һ���༶	
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
	int courseHour;										//ѧʱ��
	char className[20];									//�γ�����
	int tchNum;
	int tchNums[10];									//��ʦ���
	int stuNum;
	int stuNums[10];									//�Ͽΰ༶���
	classInfo* firstClass = NULL;						//��һ�ڿ�
	classInfo* lastClass = NULL;						//���һ�ڿ�
}courseInfo;
#pragma endregion

#pragma region room
//define the Room Struct
typedef struct roomInfo
{
	int buildingNum;               //��ѧ¥���
	bool isUsed = false;           //��ʾ��ǰ�Ƿ�ռ��
	int roomArea;                  //��ʾ���� ��0��ʾN/1��ʾS
	int roomNum;                   //���ұ��
	classInfo* nextClass=NULL;     //��һ�ڿ�/��һ�ڿ�		   ��ǰ����Ŀγ�����
	roomInfo* nextRoom = NULL;     //��ǰ��ѧ¥����һ�䷿���� ��������
}roomInfo;

typedef struct buildingInfo
{
	int buildingNum;               //��ѧ¥���
	char buildingName[20];         //��ѧ¥����
	roomInfo* firstRoom = NULL;
}buildingInfo;



#pragma endregion

#pragma region teacher
																		//define the teacher info Struct
typedef struct teacherInfo
{
	int tchNum;					 //��ʦ���
	char tchName[20];			 //��ʦ����
	int classNums[10];           //�Ͽΰ༶���
	classInfo* nextClass=NULL;   //��ʦ�ĵĵ�һ�ڿ�/��һ�ڿ�
	teacherInfo* nextTch = NULL;
}teacherInfo;



typedef struct tchLink
{
	teacherInfo* headTch = NULL;
	int tchNum = 0;
}tchLink;

static tchLink tchL;
#pragma endregion

//stu��������
bool addStu(studentInfo** headStu, studentInfo* stu);					//���Ӱ༶
bool deleteStu(studentInfo** headStu, char* stuName);					//ɾ���༶
studentInfo* findStu(studentInfo* headStu, char* stuName);				//�ҵ���ǰ�༶
studentInfo* findPreStu(studentInfo* headStu, char* stuName);			//�ҵ���ǰ�༶��ǰ��
studentInfo* findStuByIndex(studentInfo * headStu, int stuNum);			//����stuNum�ҵ�stu


//room��������
bool addRoom(buildingInfo** building, roomInfo* room);
bool deleteRoomByPre(buildingInfo** building, roomInfo*pre);
roomInfo* findPreRoom(buildingInfo* building, int roomArea, int roomNum);	//�ҵ���ǰ���ҵ�ǰ��

//tch��������
bool addTch(teacherInfo** headTch, teacherInfo* tch);					//���ӽ�ʦ
bool deleteTch(teacherInfo** headTch, char* tchName);					//ɾ����ʦ
teacherInfo* findTch(teacherInfo* headTch, char* tchName);				//�ҵ���ǰ��ʦ
teacherInfo* findPreTch(teacherInfo* headTch, char* tchName);			//�ҵ���ǰ��ʦ��ǰ��
teacherInfo* findTchByIndex(teacherInfo * headTch, int tchNum);			//����tchNum�ҵ�tch
		

																		
//class��������
//��ǰcourse����
bool addClass(studentInfo* stu, int week, int day, int order, courseInfo* course);


//course������ ��Ҫά��course
bool addClssses(studentInfo* stu, int weekBegin, int weekEnd, int day, int order, char* className, int* tchNum);

classInfo* findFirstSameClassBySchedule(studentInfo* stu, char* className);//�����ճ̱����ҵ���ǰ�༶��ǰ�γ̵ĵ�һ�ڿ�ָ��
classInfo* findFirstSameClassInWeek(studentInfo* stu, char* className,int week);//��Ҫ���ҵ�ǰ�γ̵��ܴ�
classInfo* isExistedClassByStu(studentInfo* stu,classInfo* insertClass);
classInfo* isExistedClassByTch(teacherInfo* tch,classInfo* insertClass);

bool compareClass(classInfo* A, classInfo* B);
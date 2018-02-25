#include<stdio.h>
#include<cstring>
#include<malloc.h>
#include<assert.h>

/*
ע��˵����
D:Description ˵����������
C:Condition   ��������ǰ������
I:Input		  ��������
O:Output	  �������
OBJ:Objective ��������
*/

/*
��Ҫά��������
��stu �ճ�����
������stu�� ÿһ���༶һ���ճ�����

��course   �γ�����

��tch	   ��ʦ���Ա�
����ÿһ����ʦ�ڿ������ʦ�ڿ�

��room   ��������
����ÿһ�����ҵĿγ�����
*/


#pragma region room
//define the Room Struct
typedef struct roomInfo
{
	int buildingNum;						 //��ѧ¥��� ��1��ʼ
	bool isUsed[21][7][7] = { false };		 //��ʾ��ǰ�Ƿ�ռ��(��Ҫ�����Ƿ�ռ�� Ե�ɲ���ô��Ҫ)
	int roomArea;							 //��ʾ���� ��0��ʾN 1��ʾS
	int roomNum;							 //���ұ��
	struct classInfo* firstClass = NULL;     //��һ�ڿ�   ��ǰ����Ŀγ�����
	struct classInfo* lastClass = NULL;      //��һ�ڿ�   ��ǰ����Ŀγ�����
	roomInfo* nextRoom = NULL;				 //��ǰ��ѧ¥����һ�䷿���� ��������
}roomInfo;

typedef struct buildingInfo
{
	int buildingNum=-1;             //��ѧ¥��� Ϊindex
	char buildingName[20];          //��ѧ¥����
	int roomCount=0;				//���Ҽ���
	bool isZoned;					//�Ƿ���� �����Ƿ��NS 
	roomInfo* firstRoom = NULL;
}buildingInfo;

static buildingInfo Buildings[50];	//����building ����
static int BuildingCount = 0;
#pragma endregion

#pragma region classStu
//define the ClassInfo struct saved By LINK  ��ʾ�α� ���ڵ�ǰ�༶
typedef struct classInfo
{
	int week;										       //��ǰ�ܴ� 1-20
	int day;										       //��ǰ���� 1-7
	int order;                                             //�Ͽ�ʱ�� 1-6
	char className[20];                                    //�γ�����
	struct roomInfo* room = NULL;						   //����roomInfo
	struct courseInfo* course;							   //������courseInfo
	struct classInfo* preTchClass = NULL;				   //��һ�ڽ�ʦ��info tch˫������
	struct classInfo* nextTchClass = NULL;				   //��һ�ڽ�ʦ��info tch˫������
	struct classInfo* nextRoomClass = NULL;				   //��һ�ڽ��ҵ�info room����
	struct classInfo* preSameClass = NULL;                 //��һ����ͬ�ε�info course˫������
	struct classInfo* nextSameClass = NULL;                //��һ����ͬ�ε�info course˫������
	bool isLast = false;								   //�Ƿ��ǵ�������һ�ڿΣ���־λ��PS:�˴��ĵ�һ��Ϊ��Ե�һ�� ������ѧ�����ϵĵ�һ�ڿ�
	struct classInfo* nextClassOfDay = NULL;               //�������һ�ڿ� ��������һ�ڿ�ָ���ܺ�ĵ�һ�ڿ� �����ճ̱��� 
}classInfo;

//define the DayInfo struct saved By LINK
typedef struct dayInfo
{
	int dayNum;							 //��ǰ���� 1-7
	char dayName[20];					 //Mon. Tues. Wed. Tuhr. Fri. Sat. Sun.
	int dayClassNum;					 //����γ���Ŀ
	classInfo* dayFirstClass = NULL;	 //�����һ�ڿ�
}dayInfo;

//�ܽṹ�嶨��
typedef struct weekInfo
{
	int week;							//��ǰ�ܴ� 1-20
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
	int stuNum;									//�༶���
	char stuName[20];							//�༶���� ��IOT1601	
	int beginWeek = 0;							//��ʼ�п��ܴ� 1-20
	int endWeek = 0;							//��ʼ�޿��ܴ� 1-20
	weekInfo weeks[25];							//��ʮ�ܵĿα����� 1-20
	classInfo* stuFirstClass = NULL;			//�ճ����� �ɻ�ȡ��ʼ�ܴ�
	classInfo* stuLastClass = NULL;				//�ճ����� �ɻ�ȡ�����ܴ�
	struct studentInfo* nextStu = NULL;		    //��һ���༶	
}studentInfo;

typedef struct studentInfo studentInfo;

typedef struct stuLink
{
	studentInfo* headStu = NULL;
	int stuNum = 0;
}stuLink;

static stuLink stuL;
#pragma endregion


typedef struct timeFragment
{
	int beginWeek;				//��ʼ�ܴ�
	int endWeek;				//�����ܴ� endWeek>=beginWeek
	int day;					//����1-7
	int order;					//�Ͽ�ʱ��1-6
	struct roomInfo* room;		//�Ͽεص�ָ��
}timeFragment;



#pragma region course
typedef struct courseInfo
{
	//int courseNum;									//�γ̱��
	char courseName[20];								//�γ�����
	int firstWeek=0;									//��ʼ�ܴ�	ͳ����������
	int lastWeek=0;										//�����ܴ�
	int courseFragmentNum=0;							//ʱ�����Ŀ
	timeFragment courseFragment[5];						//�����Ͽε�ʱ��ڵ�							
	int courseHour;										//ѧʱ��	ͳ����������
	int tchNum;											//��ʦ��Ŀ
	int tchNums[10];									//��ʦ���
	int stuNum;											//�༶��Ŀ
	int stuNums[10];									//�Ͽΰ༶���
	classInfo* firstClass = NULL;						//��һ�ڿ�		ʵ�ʵĿ�ʼ�ܴ�
	classInfo* lastClass = NULL;						//���һ�ڿ�	ʵ�ʵĽ����ܴ�
}courseInfo;


static courseInfo allCourse[50];//����course	  ����
static int	courseNum = 0;		//����courseIndex ��1��ʼ
#pragma endregion

#pragma region teacher
//define the teacher info Struct
typedef struct teacherInfo
{
	int tchNum;					 //��ʦ���
	char tchName[20];			 //��ʦ����
	int classNums[10];           //�Ͽΰ༶���
	classInfo* firstClass=NULL;  //��ʦ�ĵĵ�һ�ڿ�
	classInfo* lastClass = NULL; //��ʦ�ĵ����һ�ڿ�
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
bool newStu(studentInfo** stu);
bool addStu(stuLink * stuL, studentInfo * stu);							//���Ӱ༶
bool deleteStu(stuLink * stuL, char* stuName);							//ɾ���༶
bool showStu(stuLink * stuL);											//�����༶
studentInfo* findStu(studentInfo* headStu, char* stuName);				//�ҵ���ǰ�༶
studentInfo* findPreStu(studentInfo* headStu, char* stuName);			//�ҵ���ǰ�༶��ǰ��
studentInfo* findStuByIndex(studentInfo * headStu, int stuNum);			//����stuNum�ҵ�stu 

//building��������
buildingInfo* addBuilding(char* buildingName,bool isZoned);
bool deleteBuilding(int index);
bool showBuilding();

//��room��������
bool newRoom(roomInfo** room);
bool addRoom(buildingInfo** building, roomInfo* room);
bool deleteRoomInBuilding(buildingInfo * building, int roomArea, int roomNum);		//ɾ������
bool showRoom(buildingInfo * building);
bool deleteRoomByPre(buildingInfo** building, roomInfo*pre);
roomInfo* findPreRoom(buildingInfo* building, int roomArea, int roomNum);			//�ҵ���ǰ���ҵ�ǰ��


//tch��������
bool newTch(teacherInfo** tch);
bool addTch(tchLink * tchL, teacherInfo* tch);							//���ӽ�ʦ
bool deleteTch(tchLink * tchL, char* tchName);							//ɾ����ʦ
bool deleteTchClass(teacherInfo* tch);									//ɾ��������˽�ʦ��صĿγ�
bool showTch(tchLink * tchL);											//������ʦ
teacherInfo* findTch(teacherInfo* headTch, char* tchName);				//�ҵ���ǰ��ʦ
teacherInfo* findPreTch(teacherInfo* headTch, char* tchName);			//�ҵ���ǰ��ʦ��ǰ��
teacherInfo* findTchByIndex(teacherInfo * headTch, int tchNum);			//����tchNum�ҵ�tch
		


																		//class��������
bool compareClass(classInfo* A, classInfo* B);
classInfo* addClass(courseInfo * course, int week, int day, int order, roomInfo* room);
bool deleteClass(courseInfo * course, classInfo* deleteClass);



classInfo * findPreClassInRoom(roomInfo * room, classInfo* nowClass);
classInfo * findPreClassInStu(studentInfo * stu, classInfo* nowClass);	
classInfo * findPreClassInStuByTime(studentInfo * stu, int week, int day, int order);

classInfo* findFirstSameClassInStuByName(studentInfo* stu, char* className);		//�����ճ̱����ҵ���ǰ�༶���Ƶ�ǰ�γ̵ĵ�һ�ڿ�ָ��
classInfo* findFirstSameClassInWeek(studentInfo* stu, char* className,int week);		//��Ҫ���ҵ�ǰ�γ̵��ܴ�

classInfo* isExistedClassInStu(studentInfo* stu,classInfo* insertClass);
classInfo* isExistedClassInTch(teacherInfo* tch,classInfo* insertClass);
classInfo* isExistedClassInRoom(roomInfo* room, classInfo* insertClass);


courseInfo * newCourse(int beginWeek, int endWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums, int courseFragmentNum, timeFragment* courseFragment);
courseInfo * addCourse(int firstWeek, int lastWeek, int courseHour, char * courseName, int tchNum, int * tchNums, int stuNum, int * stuNums, int courseFragmentNum, timeFragment* courseFragment);


bool saveStuToDat();
bool saveTchToDat();
bool saveRoomToDat();

bool loadStuFromDat();
bool loadTchFromDat();
bool loadRoomFromDat();



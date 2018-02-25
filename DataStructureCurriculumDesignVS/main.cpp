#include"fun.h"
#include<stdio.h>
#include<cstring>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Assert.h>

extern stuLink stuL;
extern tchLink tchL;
extern buildingInfo Buildings[50];	//所有building 数组
extern int BuildingCount;

//void init();//执行一些初始化方法

int main()
{
	//init();
	int op = 1;
	studentInfo *stu = NULL;
	teacherInfo *tch = NULL;
	int index=0;
	char* name =(char*) malloc(sizeof(char) * 20);
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. addStu			 8. PriorElem\n");
		printf("    	  2. deleteStu		 9. NextElem\n");
		printf("    	  3. showStu		 10. ListInsert\n");
		printf("    	  4. addTch			 11. ListDelete\n");
		printf("    	  5. deleteTch       12. ListTraverse\n");
		printf("    	  6. showTch         13. SaveToFile\n");
		printf("    	  7. addRoom      14. LoadFromFile\n");	//处理building 
		printf("    	  8. LocateElem      14. LoadFromFile\n");
		printf("    	  9. LocateElem      14. LoadFromFile\n");
		printf("    	  10. LocateElem      14. LoadFromFile\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			newStu(&stu);
			printf("请输入班级名称,如IOT1601\n");
			scanf("%s", stu->stuName);
			addStu(&stuL, stu);
			printf("插入班级%s成功\n", stu->stuName);
			getchar(); getchar();
			break;
		case 2:
			printf("请输入班级名称,如IOT1601\n");
			scanf("%s", name);
			deleteStu(&stuL, name);
			getchar(); getchar();
			break;
		case 3:
			if (stuL.stuNum == 0)
			{
				printf("当前班级列表为空\n");
				getchar(); getchar();
				break;
			}
			showStu(&stuL);
			getchar(); getchar();
			break;
		case 4:
			newTch(&tch);
			printf("请输入教师名称\n");
			scanf("%s", tch->tchName);
			addTch(&tchL, tch);
			printf("插入班级%s成功\n", tch->tchName);
			getchar(); getchar();
			break;
		case 5:
			printf("请输入教师名称\n");
			scanf("%s", name);
			deleteTch(&tchL, name);
			getchar(); getchar();
			break;
		case 6:
			if (tchL.tchNum == 0)
			{
				printf("当前教师列表为空\n");
				getchar(); getchar();
				break;
			}
			showTch(&tchL);
			getchar(); getchar();
			break;
		case 7://增加教学楼
			printf("请输入教学楼名称\n");
			scanf("%s", name);
			printf("请输入是否分区 1分区 0不分区\n");
			scanf("%d", index);
			addBuilding(name, (bool)index);

			printf("添加教学楼成功！\n");
			getchar(); getchar();
			break;
		case 8://删除教学楼
			printf("请输入教学楼序号\n");
			scanf("%d", index);
			deleteBuilding(index);
			printf("删除教学楼成功！\n");
			getchar(); getchar();
			break;
		case 9://遍历教学楼
			showBuilding();
			getchar(); getchar();
			break;
		case 10://增加教室
			printf("请输入教学楼序号\n");
			scanf("%d", index);
			//newRoom();
			//addRoom();
			getchar(); getchar();
			break;
		case 11://删除教室


			getchar(); getchar();
			break;
		case 12://遍历教室

			getchar(); getchar();
			break;
		case 50://保存教室，教室，班级

			getchar(); getchar();
			break;
		case 51://读取 教室，教室，班级

			getchar(); getchar();
			break;
		case 52://保存课程
			getchar(); getchar();
			break;

	
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");

	printf("hello world\n ");
} 
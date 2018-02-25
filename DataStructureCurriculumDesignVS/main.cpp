#include"fun.h"
#include<stdio.h>
#include<cstring>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Assert.h>

extern stuLink stuL;
extern tchLink tchL;
extern buildingInfo Buildings[50];	//����building ����
extern int BuildingCount;

//void init();//ִ��һЩ��ʼ������

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
		printf("    	  7. addRoom      14. LoadFromFile\n");	//����building 
		printf("    	  8. LocateElem      14. LoadFromFile\n");
		printf("    	  9. LocateElem      14. LoadFromFile\n");
		printf("    	  10. LocateElem      14. LoadFromFile\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~14]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			newStu(&stu);
			printf("������༶����,��IOT1601\n");
			scanf("%s", stu->stuName);
			addStu(&stuL, stu);
			printf("����༶%s�ɹ�\n", stu->stuName);
			getchar(); getchar();
			break;
		case 2:
			printf("������༶����,��IOT1601\n");
			scanf("%s", name);
			deleteStu(&stuL, name);
			getchar(); getchar();
			break;
		case 3:
			if (stuL.stuNum == 0)
			{
				printf("��ǰ�༶�б�Ϊ��\n");
				getchar(); getchar();
				break;
			}
			showStu(&stuL);
			getchar(); getchar();
			break;
		case 4:
			newTch(&tch);
			printf("�������ʦ����\n");
			scanf("%s", tch->tchName);
			addTch(&tchL, tch);
			printf("����༶%s�ɹ�\n", tch->tchName);
			getchar(); getchar();
			break;
		case 5:
			printf("�������ʦ����\n");
			scanf("%s", name);
			deleteTch(&tchL, name);
			getchar(); getchar();
			break;
		case 6:
			if (tchL.tchNum == 0)
			{
				printf("��ǰ��ʦ�б�Ϊ��\n");
				getchar(); getchar();
				break;
			}
			showTch(&tchL);
			getchar(); getchar();
			break;
		case 7://���ӽ�ѧ¥
			printf("�������ѧ¥����\n");
			scanf("%s", name);
			printf("�������Ƿ���� 1���� 0������\n");
			scanf("%d", index);
			addBuilding(name, (bool)index);

			printf("��ӽ�ѧ¥�ɹ���\n");
			getchar(); getchar();
			break;
		case 8://ɾ����ѧ¥
			printf("�������ѧ¥���\n");
			scanf("%d", index);
			deleteBuilding(index);
			printf("ɾ����ѧ¥�ɹ���\n");
			getchar(); getchar();
			break;
		case 9://������ѧ¥
			showBuilding();
			getchar(); getchar();
			break;
		case 10://���ӽ���
			printf("�������ѧ¥���\n");
			scanf("%d", index);
			//newRoom();
			//addRoom();
			getchar(); getchar();
			break;
		case 11://ɾ������


			getchar(); getchar();
			break;
		case 12://��������

			getchar(); getchar();
			break;
		case 50://������ң����ң��༶

			getchar(); getchar();
			break;
		case 51://��ȡ ���ң����ң��༶

			getchar(); getchar();
			break;
		case 52://����γ�
			getchar(); getchar();
			break;

	
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");

	printf("hello world\n ");
} 
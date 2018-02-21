#include "room.h"



//��ʼ��������ѧ¥���޴˽���
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

//��ʼ��������ǰ��ѧ¥���д˽��� pre=NULL��˵������ֻ��һ������
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


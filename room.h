#ifndef ROOMINFO_H
#define ROOMINFO_H

#include "classScheduleLink.h"

//define the Room Struct
typedef struct roomInfo
{
    int buildingNum;               //教学楼编号
    bool isUsed=false;             //表示当前是否被占用
    int roomArea;                  //表示区域 如0表示N/1表示S
    int roomNum;                   //教室编号
    classInfo* nextClass=NULL;     //当前周的第一节课/下一节课
    roomInfo* nextRoom=NULL;       //当前教学楼的下一间房间编号
}roomInfo;

typedef struct buildingInfo
{
    int buildingNum;               //教学楼编号
    char buildingName[20];         //教学楼名称
    roomInfo* firstRoom=NULL;
}buildingInfo;

bool addRoom(buildingInfo** building,roomInfo* room);
bool deleteRoomByPre(buildingInfo** building, roomInfo*pre);
roomInfo* findPreRoom(buildingInfo* building, int roomArea, int roomNum);	//找到当前教室的前驱

#endif  ROOMINFO_H

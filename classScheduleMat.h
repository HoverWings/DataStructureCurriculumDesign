#ifndef CLASSSCHEDULEMAT_H
#define CLASSSCHEDULEMAT_H
//仅仅读取单个课表

//define the ClassInfo struct saved By MAT
typedef struct classMat
{
    int order;              //class order 1-6 
    char className[20];     
    char teacherName[20];   
    int classNum[10];           
}classMat;



bool loadFromFile();


#endif  CLASSSCHEDULELMAT_H






#ifndef MYGROUP_H
#define MYGROUP_H
#include "myitem.h"
#include <QRect>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsObject>
#include <QKeyEvent>

class MyGroup
{
public :
    int pos_x;
    int pos_y;
    //组的位置
public:
    MyGroup();
    MyGroup(int pos_x,int pos_y,int type);
    int isColliding();
    void zhuangLeft();
    void zhuangRigth();
    void clear();

    QList<QGraphicsItem * > list;
    int Type_rotation; //设置当前的状态。
    int Type_style;
    void setPos(int x,int y);
    void moveBy(int x,int y);

};

#endif // MYGROUP_H

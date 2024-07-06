#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsRectItem>

class MyItem : public QGraphicsRectItem
{
public:
    MyItem();
    MyItem(int x);
    MyItem(int w,int h);
    MyItem(int x,int y,int w,int h);

};

#endif // MYITEM_H

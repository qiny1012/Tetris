#include "inc/myitem.h"

MyItem::MyItem()
{

}


MyItem::MyItem(int x)
{

}

//使用这个函数构造一个item的类
MyItem::MyItem(int w, int h)
{
    this->setRect(0,0,18,18);
}

//没有使用到
MyItem::MyItem(int x, int y, int w, int h)
{
    this->setRect(x,y,w,h);

}

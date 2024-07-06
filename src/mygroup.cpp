#include "inc/mygroup.h"
/******************************************
    问题，旋转之后无法正常碰撞检验
    建立旋转之后的位置坐标
*/


int type_pos_x [7][4][4] = {

  //第一种情况
  {
    {0,20,0,20},
    {0,20,0,20},
    {0,20,0,20},
    {0,20,0,20},
  },

  //第二个图形
    {

      {0,0,0,20},
      {20,0,-20,-20},
      {20,20,20,0},
      {0,20,40,40},

    },

   //第三个图形
  {
    {20,20,20,0},
    {20,0,-20,-20},
    {0,0,0,20},
    {0,20,40,40},
  },

    //第四个图形
   {
     {0,0,20,20},
     {20,0,0,-20},
     {0,0,20,20},
     {20,0,0,-20},
   },

    //第5个图形
   {
     {20,20,0,0},
     {20,0,0,-20},
     {20,20,0,0},
     {20,0,0,-20},
   },
    //第6个图形
   {
     {0,0,0,0},
     {-40,-20,0,20},
     {0,0,0,0},
     {-40,-20,0,20},
   },
    //第7个图形
   {
     {0,-20,0,20},
     {20,0,0,0},
     {0,20,0,-20},
     {-20,0,0,0},
   },
};

int type_pos_y [7][4][4] = {

  //第一种情况
  {
    {0,0,20,20},
    {0,0,20,20},
    {0,0,20,20},
    {0,0,20,20},
  },

  //第二个图形
    {

      {0,20,40,40},
      {0,0,0,20},
      {20,0,-20,-20},
      {20,20,20,0},

    },

   //第三个图形
  {
    {0,20,40,40},
    {20,20,20,0},
    {20,0,-20,-20},
    {0,0,0,20},
  },

    //第四个图形
   {
     {0,20,20,40},
     {0,0,20,20},
     {0,20,20,40},
     {0,0,20,20},
   },

    //第5个图形
   {
     {0,20,20,40},
     {20,20,0,0},
     {0,20,20,40},
     {20,20,0,0},
   },
    //第6个图形
   {
     {0,20,40,60},
     {0,0,0,0},
     {0,20,40,60},
     {0,0,0,0},
   },
    //第7个图形
   {
     {0,20,20,20},
     {0,-20,0,20},
     {20,0,0,0},
     {0,20,0,-20},
   },
};



int type_x[7][4] ={
                    {0,0,20,20}
                    ,{0,0,0,20}
                    ,{20,20,20,0}
                    ,{0,0,0,0}
                    ,{0,0,20,20}
                    ,{20,20,0,0}
                    ,{20,0,20,40}
                };
int type_y[7][4] = {
                    {0,20,0,20}
                    ,{0,20,40,40}
                    ,{0,20,40,40}
                    ,{0,20,40,60}
                    ,{0,20,20,40}
                    ,{0,20,20,40}
                    ,{0,20,20,20}
};

MyGroup::MyGroup()
{

}

MyGroup::MyGroup(int pos_x, int pos_y, int type)
{
    Type_rotation = 0;
    Type_style = type;
    /*
    MyItem * item1 = new MyItem(pos_x+type_x[type][0],pos_y+type_y[type][0],18,18);
    MyItem * item2 = new MyItem(pos_x+type_x[type][1],pos_y+type_y[type][1],18,18);
    MyItem * item3 = new MyItem(pos_x+type_x[type][2],pos_y+type_y[type][2],18,18);
    MyItem * item4 = new MyItem(pos_x+type_x[type][3],pos_y+type_y[type][3],18,18);
    */
    this->setPos(pos_x,pos_y);
    MyItem * item1 = new MyItem(18,18);
    MyItem * item2 = new MyItem(18,18);
    MyItem * item3 = new MyItem(18,18);
    MyItem * item4 = new MyItem(18,18);
    item1->setPos(pos_x+type_pos_x[type][Type_rotation][0],pos_y+type_pos_y[type][Type_rotation][0]);
    item2->setPos(pos_x+type_pos_x[type][Type_rotation][1],pos_y+type_pos_y[type][Type_rotation][1]);
    item3->setPos(pos_x+type_pos_x[type][Type_rotation][2],pos_y+type_pos_y[type][Type_rotation][2]);
    item4->setPos(pos_x+type_pos_x[type][Type_rotation][3],pos_y+type_pos_y[type][Type_rotation][3]);
    list.append(item1);
    list.append(item2);
    list.append(item3);
    list.append(item4);
}


int MyGroup::isColliding()
{
       QGraphicsItem *item;
       foreach(item, list)
       {
           if(item->collidingItems(Qt::ContainsItemBoundingRect).count()>0)//collidingItems返回与当前item碰撞的子item列表
               return 1;//代表至少有一个item发生了碰撞
       }
       return 0;
}

void MyGroup::zhuangLeft()
{

    Type_rotation++;
    if(Type_rotation == 4)
    {
        Type_rotation = 0;
    }
    qDebug() << type_pos_x[Type_style][Type_rotation][0] << type_pos_x[Type_style][Type_rotation][0] ;
    list.at(0)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][0],pos_y + type_pos_y[Type_style][Type_rotation][0]);
    list.at(1)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][1],pos_y + type_pos_y[Type_style][Type_rotation][1]);
    list.at(2)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][2],pos_y + type_pos_y[Type_style][Type_rotation][2]);
    list.at(3)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][3],pos_y + type_pos_y[Type_style][Type_rotation][3]);

    /*this->addToGroup(list.at(0));
    this->addToGroup(list.at(1));
    this->addToGroup(list.at(2));
    this->addToGroup(list.at(3));*/


    //qDebug() << list.at(0)->mapToScene(list.at(0)->scenePos());
/*
    list.at(0)->setPos(list.at(0)->scenePos().x()-280,list.at(0)->scenePos().y());
    list.at(1)->setPos(list.at(1)->scenePos().x()-280,list.at(1)->scenePos().y());
    list.at(2)->setPos(list.at(2)->scenePos().x()-280,list.at(2)->scenePos().y());
    list.at(3)->setPos(list.at(3)->scenePos().x()-280,list.at(3)->scenePos().y());
*/

     //qDebug() << this->boundingRect();
     //qDebug() <<  this->mapToScene(280,0);

     //this->setTransformOriginPoint(this->mapToScene(280,0));
     //qDebug() << this->rotation() << endl;
     //qDebug() << this->scale() << endl;

     //QList<QGraphicsItem * > list = childItems();

     /*
     qDebug() << list.at(0)->scenePos();
     qDebug() << list.at(1)->scenePos();
     qDebug() << list.at(2)->scenePos();
     qDebug() << list.at(3)->scenePos();
     */

     //foreach (QGraphicsItem * item, list) {
         //item->setTransformOriginPoint(item->boundingRect().x(),item->boundingRect().y());
         //qDebug() << item->mapToItem(item,0)<< endl;
         //qDebug() << item->pos() << endl;
         //qDebug() << item->scenePos() << endl;
         //item->setRotation(90);
    // }
     //setRotation(90);

     /*
    QTransform transform;
    transform.translate(this->mapToScene(280,0).x(),this->mapToScene(280,0).y());
    transform.rotate(90);
    transform.scale(0.5, 1.0);
    this->setTransform(transform);
    //update();
    */
}

void MyGroup::zhuangRigth()
{
    Type_rotation--;
    if(Type_rotation == -1)
    {
        Type_rotation = 3;
    }
    qDebug() << type_pos_x[Type_style][Type_rotation][0] << type_pos_x[Type_style][Type_rotation][0] ;
    list.at(0)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][0],pos_y + type_pos_y[Type_style][Type_rotation][0]);
    list.at(1)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][1],pos_y + type_pos_y[Type_style][Type_rotation][1]);
    list.at(2)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][2],pos_y + type_pos_y[Type_style][Type_rotation][2]);
    list.at(3)->setPos(pos_x + type_pos_x[Type_style][Type_rotation][3],pos_y + type_pos_y[Type_style][Type_rotation][3]);

}

void MyGroup::clear()
{
    list.clear();
}

void MyGroup::setPos(int x, int y)
{
    pos_x = x ;
    pos_y = y ;

}

void MyGroup::moveBy(int x, int y)
{
    pos_x = pos_x + x;
    pos_y = pos_y + y;
    list.at(0)->moveBy(x,y);
    list.at(1)->moveBy(x,y);
    list.at(2)->moveBy(x,y);
    list.at(3)->moveBy(x,y);
}


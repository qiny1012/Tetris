#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include "myitem.h"
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <QTime>
#include <QtGlobal>
#include "mygroup.h"
#include <QMessageBox>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QGraphicsLineItem * lineItem1;
    QGraphicsLineItem * lineItem2;
    QGraphicsLineItem * lineItem3;
    QTimer *timer;
    MyGroup * curGroup;
    MyGroup * nextGroup;
    QGraphicsItem * type_ret[20][10];
    int score;
    int testEnd;
public:
    explicit MyScene(QObject *parent = 0);
    void initScene();
    int IsColliding(); //return 1 yes return 0 no
    void keyPressEvent(QKeyEvent * keyEvent);
    void addGroup(MyGroup * group);
    void creatNewGroup();  //产生一个方块组并且放在场景中
    void setRet(); //方块放置完成记录方块。
    int testRet(int row); //如果有放置之后要检测这一行是不是已经数据完成了，如果成功放回1，否则0
    int destroyFromRet(int row); //把row行的数据删除，然后再把数据全部向下移动
    int moveDownRet(int row);
    void strat();
    void stop();
    void starNewGame();

public slots:
    int moveDownTest(); //return 1 is over;

};

#endif // MYSCENE_H

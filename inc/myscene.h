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
    QGraphicsLineItem * lineItem1;      // 边界线1
    QGraphicsLineItem * lineItem2;      // 边界线2
    QGraphicsLineItem * lineItem3;      // 边界线3
    QTimer *timer;                      // 定时器
    MyGroup * curGroup;                 // 当前元素组合，一个元素代表一个方块，一个元素组合代表4个元素
    MyGroup * nextGroup;                // 下一个元素组合
    QGraphicsItem * type_ret[20][10];   // 界面中可以放置的元素数量
    int score;                          // 得分
    int testEnd;                        // 测试
public:
    explicit MyScene(QObject *parent = 0);          // 构造函数，explicit表明无法被隐式构建

    /**
     * 初始化场景
     * 初始化3个边界线段
     * 初始化curGroup
     * 初始化nextGroup
     * 根据定时器信号出发移动函数
     * 初始化界面中的
    */
    void initScene();

    /**
     * 碰撞检测
     * 1. 判断和边界线是否有碰撞
     * 2. 判断和界面状态数组之间是否有碰撞
     *
     * @brief MyScene::IsColliding
     * @return
     */
    int IsColliding();

    /** 创建一个新的元素组，并将其放置到界面上。
     * @brief MyScene::creatNewGroup
     */
    void creatNewGroup();

    /** 将元素组放置到界面上。
     * @brief MyScene::creatNewGroup
     */
    void addGroup(MyGroup * group);

    /** 当数据元素组停止落地后，对4个元素所在的行进行检测。
     *  当行内所有位置都已经包含元素后，则清除一行数据。
     * @brief MyScene::setRet
     */
    void setRet();

    /**
     *  判断某行是否已经全部放满
     * @brief MyScene::testRet
     * @param row
     * @return
     */
    int testRet(int row);

    /**
     * （成功消除了一行数据后）将消除的哪一行的元素全部删除，并将所有的元素向下移动一格。
     * @brief MyScene::destroyFromRet
     * @param row
     * @return
     */
    int destroyFromRet(int row);

    /**
     * 将所有的元素向下移动一格，（成功消除了一行数据）
     * 容易出现问题的地方，1.如果只是改变图元的位置，并没有改变图源的坐标，
     *                  2.一个组的元素还没有全部添加到数组中，则移动操作不会该表他们。
     * @brief MyScene::moveDownRet
     * @param row
     * @return
     */
    int moveDownRet(int row);

    /**
     * 接受键盘输入，AD左右移动，S为快速下降，Q为向左旋转，E为向右选装
     * @brief MyScene::keyPressEvent
     * @param keyEvent
     */
    void keyPressEvent(QKeyEvent * keyEvent);

    /** 开始新的游戏，删除curGroup，nextGroup。清空界面状态数组
     *  初始化新的curGroup，nextGroup
     * @brief MyScene::starNewGame
     */
    void starNewGame();

    /** 启动定时器，触发间隔为0.5s
     * @brief MyScene::strat
     */
    void strat();

    /** 暂停游戏，关闭定时器
     * @brief MyScene::stop
     */
    void stop();


public slots:
    /** 槽函数，由定时器触发
     *  向下移动curgroup，同时判断是否结束游戏
     * @brief MyScene::moveDownTest
     * @return
     */
    int moveDownTest(); //return 1 is over;

};

#endif // MYSCENE_H

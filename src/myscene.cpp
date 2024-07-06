#include "inc/myscene.h"

/*
 * 构造函数，只支持显式构建
*/
MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
{
    initScene();
}

/**
 * 初始化场景
 * 初始化3个边界线段
 * 初始化curGroup
 * 初始化nextGroup
 * 根据定时器信号出发移动函数
 * 初始化界面中的
*/
void MyScene::initScene()
{
    //nextgroup的显示
    lineItem1 = new QGraphicsLineItem;
    lineItem1->setLine(198,-10,198,400);
    this->addItem(lineItem1);

    lineItem2 = new QGraphicsLineItem;
    lineItem2->setLine(401,-10,401,400);
    this->addItem(lineItem2);

    lineItem3 = new QGraphicsLineItem;
    lineItem3->setLine(201,400,399,400);
    this->addItem(lineItem3);
    this->setSceneRect(0,0,580,410);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int type = qrand();
    type = type % 7;
    this->curGroup = new MyGroup(280,0,type);
    this->addGroup(curGroup);

    type = qrand();
    type = type % 7;
    this->nextGroup = new MyGroup(450,50,type);
    this->addGroup(nextGroup);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveDownTest()));

    //设置状态，当前没有一个方块在界面中
    for(int i = 0; i< 20 ;i ++)
    {
        for(int j = 0 ;j < 10 ;j ++)
        {
            type_ret[i][j] = NULL;
        }
    }
    testEnd = 0;
}


/**
 * 碰撞检测
 * 1. 判断和边界线是否有碰撞
 * 2. 判断和界面状态数组之间是否有碰撞
 *
 * @brief MyScene::IsColliding
 * @return
 */
int MyScene::IsColliding()
{
    QList<QGraphicsItem * > list = this->collidingItems(lineItem1);
    if(list.size() != 0)
    {
        qDebug() << "line 1 "<<endl;
        return 1;
    }
    list = this->collidingItems(lineItem2);
    if(list.size() != 0)
    {
        //this->group->moveUp();
        qDebug() << "line 2 "<<endl;
        return 1;
    }
    list = this->collidingItems(lineItem3);
    if(list.size() != 0)
    {
        qDebug() << "line 3 "<<endl;
        //this->group->moveUp();
        return 1;
    }
    if(this->curGroup->isColliding())
    {
        return 1;
    };
    return 0;
}

/**
 * 接受键盘输入，AD左右移动，S为快速下降，Q为向左旋转，E为向右选装
 * @brief MyScene::keyPressEvent
 * @param keyEvent
 */
void MyScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if(!timer->isActive())
    {
        return ;
    }
    if(keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_A)
    {
        curGroup->moveBy(-20,0);
        if(this->IsColliding())
        {
            curGroup->moveBy(20,0);
            return ;
        }
    }
    else if(keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_D)
    {
        curGroup->moveBy(20,0);
        if(this->IsColliding())
        {
            curGroup->moveBy(-20,0);
            return ;
        }
    }
    else if(keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_S)
    {
        curGroup->moveBy(0,20);
        if(this->IsColliding())
        {
            curGroup->moveBy(0,-20);
            return ;
        }
    }
    else if(keyEvent->key() == Qt::Key_Q)
    {
        curGroup->zhuangLeft();
        if(this->IsColliding())
        {
            curGroup->zhuangRigth();
        }
    }
    if(keyEvent->key() == Qt::Key_Space)
    {
        this->testEnd ++ ;
        while(!this->IsColliding())
        {
            curGroup->moveBy(0,20);
        }
        curGroup->moveBy(0,-20);
    }
    if(keyEvent->key() == Qt::Key_P)
    {
        if(timer->isActive())
        {
            timer->stop();

        }
        else
        {
            timer->start(500);
        }
    }
}

//把一组图形放到scene中
void MyScene::addGroup(MyGroup *group)
{
    this->addItem(group->list.at(0));
    this->addItem(group->list.at(1));
    this->addItem(group->list.at(2));
    this->addItem(group->list.at(3));
}

void MyScene::creatNewGroup()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int type = qrand();
    type = type % 7;
    curGroup = new MyGroup(280,0,nextGroup->Type_style);
    this->removeItem(nextGroup->list.at(0));
    this->removeItem(nextGroup->list.at(1));
    this->removeItem(nextGroup->list.at(2));
    this->removeItem(nextGroup->list.at(3));
    this->nextGroup = new MyGroup(450,50,type);
    this->addGroup(nextGroup);
    this->addGroup(curGroup);
    testEnd = 0;
}


/** 当数据元素组停止落地后，对4个元素所在的行进行检测。
 *  当行内所有位置都已经包含元素后，则清除一行数据。
 * @brief MyScene::setRet
 */
void MyScene::setRet()
{
    //此处为了解决下面移动问题采用一种笨方法
    int row[4];
    int count = 0;
    QGraphicsItem * item ;
     //qDebug() << curGroup->pos_x  << curGroup->pos_y;
    foreach (item, curGroup->list) {
        int i = (item->pos().x() - 200) / 20;
        int j = item->pos().y() / 20;
        qDebug() << i << j ;
        type_ret[j][i] = item;
        row[count] = j;
        count ++ ;
    }
    //从开始遍历,仅仅遍历row中存在的，也就是刚才存放过的
    //如果消除的顺序不是cong'shang倒下就会出现下面的数据无法处理
    for(int i = 0 ; i < 20;i ++ )
    {
        if(testRet(i))
        {
            destroyFromRet(i);
        }
    }


}

/**
 *  判断某行是否已经全部放满
 * @brief MyScene::testRet
 * @param row
 * @return
 */
int MyScene::testRet(int row)
{
    for(int i = 0 ; i < 10 ; i++)
    {
        if(type_ret[row][i] == NULL)
            return 0;
    }
    return 1;
}

/**
 * （成功消除了一行数据后）将消除的哪一行的元素全部删除，并将所有的元素向下移动一格。
 * @brief MyScene::destroyFromRet
 * @param row
 * @return
 */
int MyScene::destroyFromRet(int row)
{
    int pos_x = 210;
    int pos_y = row * 20 + 10;

    //删除一行的元素
    for(int i = 0 ; i < 10 ; i++)
    {
        this->removeItem(type_ret[row][i]);
        type_ret[row][i] = NULL ;
    }
    moveDownRet(row);
    return 0;
}


/**
 * （成功消除了一行数据后）将所有的元素向下移动一格，
 * 容易出现问题的地方，1.如果只是改变图元的位置，并没有改变图源的坐标，
 *                  2.一个组的元素还没有全部添加到数组中，则移动操作不会该表他们。
 * @brief MyScene::moveDownRet
 * @param row
 * @return
 */
int MyScene::moveDownRet(int row)
{
    for(int i = row - 1 ;i >-1 ; i --)
    {
        for(int j = 0 ; j < 10 ;j ++)
        {
            if(type_ret[i][j])
            {
                type_ret[i][j]->moveBy(0,20);
                type_ret[i+1][j] = type_ret[i][j];
                type_ret[i][j] = NULL;
            }
        }
    }
    return 0;
}

/** 开始游戏，启动定时器，触发间隔为0.5s
 * @brief MyScene::strat
 */
void MyScene::strat()
{
    timer->start(500);
}

/** 暂停游戏，关闭定时器
 * @brief MyScene::stop
 */
void MyScene::stop()
{
    timer->stop();
}

/** 开始新的游戏，删除curGroup，nextGroup。清空界面状态数组
 *  初始化新的curGroup，nextGroup
 * @brief MyScene::starNewGame
 */
void MyScene::starNewGame()
{
    timer->stop();
    QGraphicsItem * item ;
    foreach(item,curGroup->list)
    {
        this->removeItem(item);
    }

    foreach(item,nextGroup->list)
    {
        this->removeItem(item);
    }

    for(int i = 0 ; i < 20; i ++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            if(type_ret[i][j])
            {
                this->removeItem(type_ret[i][j]);
                type_ret[i][j] = NULL;
            }
        }

    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int type = qrand();
    type = type % 7;
    this->curGroup = new MyGroup(280,0,type);
    this->addGroup(curGroup);

    qDebug() << "clear" <<endl;
    type = qrand();
    type = type % 7;
    this->nextGroup = new MyGroup(450,50,type);
    this->addGroup(nextGroup);
}


/** 槽函数，由定时器触发
 *  向下移动curgroup，同时判断是否结束游戏
 * @brief MyScene::moveDownTest
 * @return
 */
int MyScene::moveDownTest()
{
    if(curGroup == NULL)
    {
        return 0;
    }
    curGroup->moveBy(0,20);
    if(this->IsColliding())
    {
        if(testEnd == 0)
        {
            //比赛结束
            //QMessageBox::warning(this, tr("game over"),tr("GAME OVER\n" "start new game"),QMessageBox::Ok);
            qDebug() << "game over";
            this->starNewGame();
            return 0;
        }

        curGroup->moveBy(0,-20);
        setRet();
        curGroup->clear();
        creatNewGroup();
        return 0;
    }
    testEnd ++;
    return 1;
}





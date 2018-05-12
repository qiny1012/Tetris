#include "myscene.h"


MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
{
    initScene();


    /*
     * 测试每个图形是否可以旋转，每个转是否正常
     * 没有去检测是否符合碰撞，但是如果不符合碰撞理论可以使用scene去处理
     *
    this->addLine(0,0 ,0,100);
    this->addLine(100,100 ,300,100);
    this->addLine(100,100,100,200);
    this->addLine(200,100,200,200);
    int type = 6;
    MyGroup * group = new MyGroup(0,0,type);
    this->addItem(group);

    MyGroup * group2 = new MyGroup(100,100,type);
    this->addItem(group2);
    //group2->moveBy(0,40);
    group2->zhuangLeft();
    //this->addItem(group2);

    MyGroup * group3 = new MyGroup(200,200,type);
    this->addItem(group3);
    group3->zhuangLeft();
    group3->zhuangLeft();

    MyGroup * group4 = new MyGroup(300,300,type);
    this->addItem(group4);
    group4->zhuangLeft();
    group4->zhuangLeft();
    group4->zhuangLeft();
    */

}

//初始化
void MyScene::initScene()
{
    //nextgroup的显示
    /*
    this->addLine(420,30,420,110);
    this->addLine(420,30,500,30);
    this->addLine(500,30,500,110);
    this->addLine(500,110,420,110);
    */

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


//碰撞检测
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

    /*
    list = curGroup->collidingItems();

    if(list.size() > 4)
    {
       qDebug() << "box 1 "<<endl;
        //this->group->moveUp();
        return 1;
    }
    */

    if(this->curGroup->isColliding())
    {
        return 1;
    };
    return 0;
}

//键盘事件
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
       //qDebug() << this->curGroup->pos_x << this->curGroup->pos_y ;
       //curGroup->moveBy(0,400-this->curGroup->pos_y - 80);
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

int MyScene::testRet(int row)
{
    for(int i = 0 ; i < 10 ; i++)
    {
        if(type_ret[row][i] == NULL)
            return 0;
    }
    return 1;
}

int MyScene::destroyFromRet(int row)
{
    int pos_x = 210;
    int pos_y = row * 20 + 10;


    //删除一行的元素
    for(int i = 0 ; i < 10 ; i++)
    {
       // QTransform tra ;
       // QGraphicsItem * item = this->itemAt(pos_x,pos_y,tra);
       // QList<QGraphicsItem * > list = this->itemAt(QPointF(pos_x,pos_y),tra);
        this->removeItem(type_ret[row][i]);
        type_ret[row][i] = NULL ;
    }
    moveDownRet(row);
    return 0;
}



//容易出现问题的地方，1.如果只是改变图元的位置，并没有改变图源的坐标，
//                2.一个组的元素还没有全部添加到数组中，则移动操作不会该表他们。
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

void MyScene::strat()
{
    timer->start(500);
}

void MyScene::stop()
{
    timer->stop();
}

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


//下落的函数
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





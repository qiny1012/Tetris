#include "inc/mainwindow.h"
#include "inc/myscene.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,30,800,420);
    ui->graphicsView->setGeometry(0,0,610,420);
    scene = new MyScene ();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    scene->strat();
}

void MainWindow::on_pushButton_2_clicked()
{
    scene->stop();
}

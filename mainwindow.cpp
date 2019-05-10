#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->pushButtonReload,SIGNAL(clicked()),this,SLOT(reload()));
    reload();
}

void MainWindow::reload()
{
 hide();
 QTimer::singleShot(400,this,SLOT(delayUpdate()));
}

void MainWindow::delayUpdate()
{
    ui->widget->MakeScreenShots();
    show();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    reload();
}

MainWindow::~MainWindow()
{
    delete ui;
}

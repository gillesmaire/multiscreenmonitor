#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<this->size();
    double max=0;
    for ( auto scr: qApp->screens())

    {
        if (max < scr->size().width()/(size()*1.0).width())
            max= scr->size().width()/(size()*1.0).width();
        if (max < scr->size().height()/(size()*1.0).height() )
            max= scr->size().height()/(size()*1.0).height();
    }
    qDebug()<<max;
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QDebug>


double MainWindow::ratio()
{
    double ratio=0;
    for ( auto scr: qApp->screens())
    {
        if (ratio < scr->size().width()/(size()*1.0).width())
            ratio= scr->size().width()/(size()*1.0).width();
        if (ratio < scr->size().height()/(size()*1.0).height() )
            ratio= scr->size().height()/(size()*1.0).height();
    }
    return ratio;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    for ( auto scr: qApp->screens())
    {
        QPixmap pix=scr->grabWindow(0);
        ppix
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_ratio=ratio();
}


MainWindow::~MainWindow()
{
    delete ui;
}

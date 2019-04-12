#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TotalSize();
}

void MainWindow:: TotalSize()
{
    m_allScreensHeight=m_allScreensWith=0;
    for ( auto scr: qApp->screens())
    {
        m_allScreensWith+=  scr->size().width();
        if ( m_allScreensHeight <  scr->size().height() )m_allScreensHeight=scr->size().height() ;
    }
    this->adjustSize();
}

void MainWindow::RelativeSizes()
{
    m_lp.clear();
    int x=0;
    for ( auto scr: qApp->screens())
        {

            QPixmap pix=scr->grabWindow(0);
            double rapx=scr->size().width()*1.0/m_allScreensWith;
            double rapy=scr->size().height()*1.0/m_allScreensHeight;
            QSizeF size=QSizeF(m_widgetWidth*rapx,
                             m_widgetHeight*rapy);
            pix = pix.scaled(size.toSize(),
                 //Qt::IgnoreAspectRatio,
                             Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
            m_lp<<pix;
            qDebug()<<"rapx"<<"rapy"<<rapx<<rapy;
            m_rects<<QRectF(x,0,m_widgetWidth*rapx,m_widgetHeight*rapy);
            x+=m_widgetWidth*rapx;
        }
}


void MainWindow::paintEvent(QPaintEvent * )
{

    QPainter painter(this);
    int x=0;
    qDebug()<<"window size"<< m_widgetWidth<< m_widgetHeight;
    for ( auto pix : m_lp )
    {
        qDebug()<<"pix"<<"at"<<x<<0<<pix.width()<<pix.height();
        painter.drawPixmap(x,0,pix.width(),pix.height(),pix);
        x+=pix.width();
    }

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    m_widgetHeight=ui->centralWidget->height();
    m_widgetWidth=ui->centralWidget->width();

     QTimer::singleShot(200,this,SLOT(Draw()));

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if ( e->button()==Qt::LeftButton )
    {
        int i=0;
        for ( auto rect : m_rects)
        {
            if ( rect.contains(e->pos()))
            {
                 qDebug()<<"ecran"<<i;
                 break;

            }
            i++;
        }
    }

}



void MainWindow::Draw()
{
    hide();
     QTimer::singleShot(500,this,SLOT(MakeScreenShots()));

}

void MainWindow::MakeScreenShots()
{
    RelativeSizes();
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

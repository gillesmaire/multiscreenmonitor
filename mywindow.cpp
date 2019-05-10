#include "mywindow.h"
#include <QApplication>


MyWindow::MyWindow(QWidget *parent):QWidget(parent)
{
    TotalSize();
}


void MyWindow::TotalSize()
{
    m_allScreensHeight=m_allScreensWith=0;
    for ( auto scr: qApp->screens())
    {
        m_allScreensWith+=  scr->size().width();
        if ( m_allScreensHeight <  scr->size().height() )m_allScreensHeight=scr->size().height() ;
    }
    this->adjustSize();
}

void MyWindow::RelativeSizes()
{
    m_lp.clear();
    int x=0;
    HideMultiScreen();
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

void MyWindow::HideMultiScreen()
{
    qDebug()<<m_multiscreendisplay<<m_multiscreenwindow;
 if ( m_multiscreendisplay != nullptr)  XUnmapWindow(m_multiscreendisplay,m_multiscreenwindow);
}

QList<Window> MyWindow::listXWindowsRecursive(Display *disp, Window w)
{
        Window root;
        Window parent;
           Window *children;
           unsigned int childrenCount;

           QList<Window> windows;
           if(XQueryTree(disp, w, &root, &parent, &children, &childrenCount))
           {
               for(unsigned int i = 0; i < childrenCount; ++i)
               {
                   windows << children[i];
                   windows << listXWindowsRecursive(disp, children[i]);
               }
               XFree(children);
           }
           return windows;
}


int MyWindow::WinId(int screen, QPoint pos)
{
    Display *disp = XOpenDisplay(QString(":0.%1").arg(screen).toLocal8Bit());
    Window rootWin = XDefaultRootWindow(disp);
    QList<Window> windows = listXWindowsRecursive(disp, rootWin);
    int i=0;
    for( Window win : windows)
     {
        i++;

        XWindowAttributes attr;
        XGetWindowAttributes(disp, win,&attr );

        if ( attr.map_state == IsViewable  && ! winName(disp,win).isEmpty()&& ! IsIconified(disp,win))
        {

         QRect rect(attr.x,attr.y,attr.width,attr.height);

         if (rect.contains(pos))
         {
             QString str=winName(disp,win);

             qDebug()<<winName(disp,win)<<rect<<pos;
             //qDebug()<<win<<winName(disp,screen,win)<<winName(disp,win)<<this->winId();
         }


         }
     }
    return 0;
}


QString MyWindow::winName (Display *disp, Window win)
{
    Atom prop = XInternAtom(disp,"WM_NAME",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;

    if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                &type,&form,&len,&remain,&list) != Success) {
        return nullptr;
    }
    QString ret=QString((char*)list);
    if ( ret==QString("MultiScreenMonitor"))
    {
        m_multiscreenwindow=win;
        m_multiscreendisplay=disp;
        return QString();
    }

    if ( ret == QString("mutter guard window")) ret.clear();
    return ret;
}

bool MyWindow::IsIconified(Display *disp, Window win)
{
    Atom prop = XInternAtom(disp,"WM_STATE",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;
    if ( XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                                &type,&form,&len,&remain,&list) != Success)
        return false;
    else
        {
        if (list == nullptr ) return true;
        else if ( *list == NormalState	) return false;
        else  return true;
        }

}

void MyWindow::paintEvent(QPaintEvent * )
{

    QPainter painter(this);
    int x=0;
    for ( auto pix : m_lp )
    {
        qDebug()<<"pix"<<"at"<<x<<0<<pix.width()<<pix.height();
        painter.drawPixmap(x,0,pix.width(),pix.height(),pix);
        x+=pix.width();
    }

}

void MyWindow::resizeEvent(QResizeEvent *)
{
    m_widgetHeight=height();
    m_widgetWidth=width();
}

void MyWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint pos=e->pos();
    QPoint posOnScreen;
    if ( e->button()==Qt::LeftButton )
    {
        int i=0;
        int retenue=0;
        for ( auto rect : m_rects)
        {
            if ( i >= qApp->screens().count()) break;
            if ( rect.contains(pos))
            {
                double rapx=rect.width()*1.0/qApp->screens().at(i)->size().width();
                double rapy=rect.height()*1.0/qApp->screens().at(i)->size().height();
                int posx=pos.x()/rapx-retenue;
                int posy=pos.y()/rapy;
                posOnScreen.setX(posx);
                posOnScreen.setY(posy);
                WinId(i,QPoint(posx,posy));
                break;
            }
            retenue+=qApp->screens().at(i)->size().width();
            i++;
        }
    }

}




void MyWindow::MakeScreenShots()
{
    RelativeSizes();
}


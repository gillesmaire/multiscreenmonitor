#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QScreen>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <freetype2/ft2build.h>
#include <X11/Xft/Xft.h>


class MyWindow : public QWidget
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent);
    void TotalSize();

    int m_allScreensWith=0;
    int m_allScreensHeight=0;
    int m_widgetWidth;
    int m_widgetHeight;
    QList <QPixmap> m_lp;
    QList <QRectF> m_rects;

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void RelativeSizes();
    void HideMultiScreen();
    int WinId(int screen, QPoint pos);
    QList<Window> listXWindowsRecursive(Display *disp, Window w);
    QString winName(Display *disp, Window win);
    bool IsIconified(Display *disp, Window win);
public:
    void MakeScreenShots();
private:
    Display *m_multiscreendisplay=0;
    Window m_multiscreenwindow=-1;
signals:
    void askDraw();
};

#endif // MYWINDOW_H

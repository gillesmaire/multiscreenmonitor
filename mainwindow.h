#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
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
private slots:
    void Draw();
    void MakeScreenShots();
signals:
    void askDraw();
};

#endif // MAINWINDOW_H

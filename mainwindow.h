#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QResizeEvent>






namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void reload();
    void delayUpdate();

private:
    Ui::MainWindow *ui;
   void resizeEvent(QResizeEvent *) override;
};

#endif // MAINWINDOW_H

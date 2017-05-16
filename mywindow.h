#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "widget.h"
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

class QSlider;
class QPushButton;


class MyWindow : public QWidget
{
    Q_OBJECT
public:
    MyWindow();
    void LoadOBJ();
protected:
    void keyPressEvent(QKeyEvent *event);
    QSlider* createSlider();
    Widget *glWidget;
    QHBoxLayout *container;

private:
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *lightXSlider;

};

#endif // MYWINDOW_H

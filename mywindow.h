#ifndef MYWINDOW_H
#define MYWINDOW_H

//#include "widget.h"
#include "glwidget.h"
#include <QWidget>
#include <QSlider>
#include <QLabel>
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
    QLabel* createLabel(QString labelText);
    GLWidget *glWidget;
    //QHBoxLayout *container;
    QVBoxLayout *ctrContainer;
    QHBoxLayout *mainContainer;

    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *lightXSlider;

    QLabel *rotxLabel;
    QLabel *rotyLabel;
    QLabel *rotzLabel;
    QLabel *lightPosLabel;

};

#endif // MYWINDOW_H

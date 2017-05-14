#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "widget.h"
#include <QWidget>

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
private:


    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *lightXSlider;

};

#endif // MYWINDOW_H

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
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider* createSlider();
    Widget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;

};

#endif // MYWINDOW_H

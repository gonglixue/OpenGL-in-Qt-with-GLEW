#ifndef PROGRAMMAINWINDOW_H
#define PROGRAMMAINWINDOW_H

#include <QMainWindow>
#include "mywindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include "goochwindow.h"

class ProgramMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ProgramMainWindow(QWidget *parent = 0);
    void LoadVertexShader();
    void LoadOBJModel();
signals:

public slots:

private:
    MyWindow* centralWindow;

};

#endif // PROGRAMMAINWINDOW_H

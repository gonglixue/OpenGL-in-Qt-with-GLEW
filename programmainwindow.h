#ifndef PROGRAMMAINWINDOW_H
#define PROGRAMMAINWINDOW_H

#include <QMainWindow>
#include "mywindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>

class ProgramMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ProgramMainWindow(QWidget *parent = 0);
    void LoadVertexShader();
signals:

public slots:
};

#endif // PROGRAMMAINWINDOW_H

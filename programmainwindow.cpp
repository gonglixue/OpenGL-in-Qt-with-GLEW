#include "programmainwindow.h"

ProgramMainWindow::ProgramMainWindow(QWidget *parent) : QMainWindow(parent)
{
    QMenuBar *menuBar = new QMenuBar;

    QMenu *menuLoad = new QMenu;
    menuLoad = menuBar->addMenu(tr("&Load"));
    QAction *actionVShader = new QAction(menuLoad);
    actionVShader->setText(tr("vShader"));
    menuLoad->addAction(actionVShader);

    QAction *actionLoadOBJ = new QAction(menuLoad);
    actionLoadOBJ->setText(tr("Load OBJ Model"));
    menuLoad->addAction(actionLoadOBJ);

    connect(actionVShader, &QAction::triggered, this, &ProgramMainWindow::LoadVertexShader);
    connect(actionLoadOBJ, &QAction::triggered, this, &ProgramMainWindow::LoadOBJModel);
    setMenuBar(menuBar);

    //centralWindow = new MyWindow;
    centralWindow = new GoochWindow;
    setCentralWidget(centralWindow);
}

void ProgramMainWindow::LoadVertexShader()
{
    qDebug() << "load vertex shader";
    // TODO 更改shader
}

void ProgramMainWindow::LoadOBJModel()
{
    qDebug() << "load obj file";
    centralWindow->LoadOBJ();
}


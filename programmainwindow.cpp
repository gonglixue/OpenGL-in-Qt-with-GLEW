#include "programmainwindow.h"

ProgramMainWindow::ProgramMainWindow(QWidget *parent) : QMainWindow(parent)
{
    QMenuBar *menuBar = new QMenuBar;

    QMenu *menuLoadVShader = menuBar->addMenu(tr("&Load"));
    QAction *actionVShader = new QAction(menuLoadVShader);
    actionVShader->setText(tr("vShader"));
    menuLoadVShader->addAction(actionVShader);

    connect(actionVShader, &QAction::triggered, this, &ProgramMainWindow::LoadVertexShader);
    setMenuBar(menuBar);

    setCentralWidget(new MyWindow);
}

void ProgramMainWindow::LoadVertexShader()
{
    qDebug() << "load vertex shader";
}


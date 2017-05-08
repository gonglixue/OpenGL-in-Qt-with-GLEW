#include "mywindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

MyWindow::MyWindow()
{
    glWidget = new Widget;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    lightXSlider = new QSlider(Qt::Vertical);
    lightXSlider->setRange(-30, 30);


    connect(xSlider, &QSlider::valueChanged, glWidget, &Widget::setXRotation);
    connect(ySlider, &QSlider::valueChanged, glWidget, &Widget::setYRotation);
    connect(zSlider, &QSlider::valueChanged, glWidget, &Widget::setZRotation);
    connect(lightXSlider, &QSlider::valueChanged, glWidget, &Widget::setLightX);

    connect(glWidget, &Widget::xRotationChanged, xSlider, &QSlider::setValue);
    connect(glWidget, &Widget::yRotationChanged, ySlider, &QSlider::setValue);
    connect(glWidget, &Widget::zRotationChanged, zSlider, &QSlider::setValue);

    //QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);
    container->addWidget(xSlider);
    container->addWidget(ySlider);
    container->addWidget(zSlider);
    container->addWidget(lightXSlider);

    setLayout(container);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);
    lightXSlider->setValue(0);

    setWindowTitle(tr("GLEW Rendering"));
}

QSlider *MyWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360*16);
    slider->setSingleStep(16);
    slider->setPageStep(15*16);
    slider->setTickInterval(15*16);
    slider->setTickPosition(QSlider::TicksRight);

    return slider;
}


void MyWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "window" << event->key();
    switch(event->key())
    {
    case 87: glWidget->camera.ProcessKeyboard(FORWARD, 0.01); break;
    case 83: glWidget->camera.ProcessKeyboard(BACKWARD, 0.01); break;
    case 65: glWidget->camera.ProcessKeyboard(LEFT, 0.01); break;
    case 68: glWidget->camera.ProcessKeyboard(RIGHT, 0.01); break;
    }

    update();
}

#include "mywindow.h"


MyWindow::MyWindow()
{
    //glWidget = new Widget;
    glWidget = new GLWidget;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    lightXSlider = new QSlider(Qt::Horizontal);
    lightXSlider->setRange(-30, 30);

    rotxLabel = createLabel("X Rotation");
    rotyLabel = createLabel("Y Rotation");
    rotzLabel = createLabel("Z Rotation");
    lightPosLabel = createLabel("Light Position");


//    connect(xSlider, &QSlider::valueChanged, glWidget, &Widget::setXRotation);
//    connect(ySlider, &QSlider::valueChanged, glWidget, &Widget::setYRotation);
//    connect(zSlider, &QSlider::valueChanged, glWidget, &Widget::setZRotation);
//    connect(lightXSlider, &QSlider::valueChanged, glWidget, &Widget::setLightX);
    connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
    connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
    connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
    connect(lightXSlider, &QSlider::valueChanged, glWidget, &GLWidget::setLightX);

    connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
    connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
    connect(glWidget, &GLWidget::yRotationChanged, zSlider, &QSlider::setValue);

    //QVBoxLayout *mainLayout = new QVBoxLayout;
    //this->container = new QHBoxLayout;
    ctrContainer = new QVBoxLayout;
    mainContainer = new QHBoxLayout;
    ctrContainer->addWidget(rotxLabel);
    ctrContainer->addWidget(xSlider);
    ctrContainer->addWidget(rotyLabel);
    ctrContainer->addWidget(ySlider);
    ctrContainer->addWidget(rotzLabel);
    ctrContainer->addWidget(zSlider);
    ctrContainer->addWidget(lightPosLabel);
    ctrContainer->addWidget(lightXSlider);

    //setLayout(container);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);
    lightXSlider->setValue(0);

    setWindowTitle(tr("GLEW Rendering"));
}

QSlider *MyWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360*16);
    slider->setSingleStep(16);
    slider->setPageStep(15*16);
    //slider->setTickInterval(15*16);
    //slider->setTickPosition(QSlider::TicksRight);

    return slider;
}

QLabel *MyWindow::createLabel(QString labelText)
{
    QLabel *label = new QLabel();
    label->setText(labelText);

    return label;
}

void MyWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "window" << event->key();
    switch(event->key())
    {
    case 87: glWidget->camera.ProcessKeyboard(FORWARD, 0.01); break;
    case 83: glWidget->camera.ProcessKeyboard(BACKWARD, 0.01); break;
    case 65: glWidget->camera.ProcessKeyboard(LEFT, 0.01); break;
    case 68: glWidget->camera.ProcessKeyboard(RIGHT, 0.01); break;
    }

    update();
}

void MyWindow::LoadOBJ()
{
    //glWidget->ReLoadOBJ();
}

#include "glwidget.h"
#include <QDebug>
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent),
    xRotAngle(0),
    yRotAngle(0),
    zRotAngle(0),
    program(0),
    camera(QVector3D(0, 0, 3.0f))
{
    screenHeight = 500;
    screenWidth = 500;

    vShaderFile = QDir::currentPath() + "/basiclambert.vert";
    fShaderFile = QDir::currentPath() + "/basiclambert.frag";

    lightPos = QVector3D(1.2f, 1.0f, 2.0f);
    objectColor = QVector3D(0.9f, 0.9f, 0.9f);
    lightColor = QVector3D(1.0f, 1.0f, 1.0f);
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::cleanup()
{

}

void GLWidget::loadOBJ()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open An Obj File"),
                QString(),
                tr("OBJ Files(*.obj)")
                );
    if(!fileName.isEmpty()){
        qDebug() << "OBJ file name: " << fileName;
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("Could not open this obj file"));
            return;
        }
        else{
            QTextStream in (&file);
            vector<QVector3D> vertices_coords;
            vector<QVector3D> vertices_normal;
            vector<QVector3D> vertices_texcoords;
            vector<Vertex> vertices;

            QString line = in.readLine();
            while(true)
            {
                if(line.isEmpty())
                {
                    line = in.readLine();
                    continue;
                }
                if(line[0] == '#'){
                    qDebug() << line;  //注释
                }
            }
        }
    }
}


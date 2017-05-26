#include "glwidget.h"
#include <QDebug>
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent),
    xRotAngle(0),
    yRotAngle(0),
    zRotAngle(0),
    program(0)
{
    camera = QCamera(QVector3D(0, 0, 3.0f));
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
    makeCurrent();
    //mesh.VBO.destroy();
    mesh.deleteBuffer();
    delete this->program;
    this->program = 0;
    doneCurrent();

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
                else if(line.left(2) == "v ")
                {
                    line.remove(0,1); // remove"v "
                    QStringList vertex_coords = line.split(' ', QString::SkipEmptyParts);
                    float x = vertex_coords[0].toFloat();
                    float y = vertex_coords[1].toFloat();
                    float z = vertex_coords[2].toFloat();

                    vertices_coords.push_back(QVector3D(x,y,z));
                }
                else if(line.left(2) == "vn")
                {
                    line.remove(0,2);  // remove "vn "
                    QStringList vertex_normal = line.split(' ', QString::SkipEmptyParts);
                    float x = vertex_normal[0].toFloat();
                    float y = vertex_normal[1].toFloat();
                    float z = vertex_normal[2].toFloat();

                    vertices_normal.push_back(QVector3D(x,y,z));;
                }
                else if(line.left(2) == "vt")
                {
                    line.remove(0,2);
                    QStringList vertex_texcoords = line.split(' ', QString::SkipEmptyParts);
                    float x = vertex_texcoords[0].toFloat();
                    float y = vertex_texcoords[1].toFloat();

                    vertices_texcoords.push_back(QVector2D(x,y));
                }
                else if(line.left(2) == "f")
                {
                    line.remove(0, 1);
                    QStringList face_index = line.split(' ', QString::SkipEmptyParts);

                    for(int i=0; i<3; i++)
                    {
                        QString aVert = face_index[i];
                        QStringList aVert_index = aVert.split('/');
                        int v_index = aVert_index[0].toInt();
                        // int t_index = aVert_index[1].toInt();
                        int n_index = aVert_index[2].toInt();

                        Vertex vert;
                        vert.Position = vertices_coords[v_index-1];
                        vert.Normal = vertices_normal[n_index-1];

                        vertices.push_back(vert);
                    }
                }

                if(in.atEnd())
                    break;
                line = in.readLine();
            }

            file.close();
            mesh = QMesh(vertices);
        }
    }
    update();
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle2(angle);
    if(angle != this->xRotAngle)
    {
        this->xRotAngle = angle;
        emit xRotationChanged(angle);
        update();
    }
}
void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle2(angle);
    if(angle != this->yRotAngle)
    {
        this->yRotAngle = angle;
        emit yRotationChanged(angle);
        update();
    }
}
void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle2(angle);
    if(angle != zRotAngle)
    {
        zRotAngle = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::setLightX(GLfloat light_x)
{
    this->lightPos.setX(light_x);
    update();
}
void GLWidget::setLightY(GLfloat light_y)
{
    this->lightPos.setY(light_y);
    update();
}
void GLWidget::setLightZ(GLfloat light_z)
{
    this->lightPos.setZ(light_z);
    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    this->mouseLastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouseLastPos.x();
    int dy = event->y() - mouseLastPos.y();
    if(event->button() & Qt::LeftButton)
    {
        setXRotation(xRotAngle + 8*dy);
        setYRotation(yRotAngle + 8*dx);
    }
    else if(event->button() & Qt::RightButton){
        setXRotation(xRotAngle + 8*dy);
        setZRotation(zRotAngle + 8*dx);
    }

    mouseLastPos = event->pos();
}

void GLWidget::resizeGL(int w, int h)
{
    screenHeight = h;
    screenWidth = w;
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(camera.Zoom, GLfloat(w)/h, 0.01f, 100.0f);
}

QSize GLWidget::sizeHint() const
{
    return QSize(screenWidth, screenHeight);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case 87: camera.ProcessKeyboard(FORWARD, 0.01); break;
    case 83: camera.ProcessKeyboard(BACKWARD, 0.01); break;
    case 65: camera.ProcessKeyboard(LEFT, 0.01); break;
    case 68: camera.ProcessKeyboard(RIGHT, 0.01); break;
    }

    update();
}

void qNormalizeAngle2(int &angle){
    while(angle < 0)
        angle += 360 * 16;
    while(angle > 360*16)
        angle -= 360 * 16;
}

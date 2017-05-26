#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      camera(glm::vec3(0, 0, 3.0f))
{
    screenHeight = 500;
    screenWidth = 500;
    xRotAngle = yRotAngle = zRotAngle = 0;
    shaderType = 1;

    if(shaderType == 1)
    {
        vShaderFile = QDir::currentPath() + "/basiclambert.vert";
        fShaderFile = QDir::currentPath() + "/basiclambert.frag";
    }
    else if(shaderType == 2)
    {
        vShaderFile = QDir::currentPath() + "/gooch.vert";
        fShaderFile = QDir::currentPath() + "/gooch.frag";
    }

    lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    objectColor = glm::vec3(0.9f, 0.9f, 0.9f);
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);


}

Widget::~Widget()
{
    cleanup();
}

void Widget::cleanup()
{

}

void Widget::ReLoadOBJ()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open An Obj File"),
                QString(),
                tr("OBJ Files(*.obj)")
                );
    if(!fileName.isEmpty()){
        qDebug() << "OBJ file name:" << fileName;
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("could not open this obj file"));
            return;
        }
        else{
            QTextStream in (&file);

            vector<glm::vec3> vertices_coords;
            vector<glm::vec3> vertices_normal;
            vector<glm::vec2> vertices_texcoords;
            vector<Vertex> vertices;

            int ftest = 0;
            QString line = in.readLine();
            while(true)
            {
                if(line.isEmpty())
                {
                    qDebug() << "space"   ;
                    line = in.readLine();
                    continue;

                }

                if(line[0] == '#')
                {
                    qDebug() << line;
                }
                else if(line.left(2) == "v ")  //顶点坐标
                {
                    line.remove(0, 1);  // remove "# "
                    QStringList vertex_coords = line.split(' ', QString::SkipEmptyParts);
                    GLfloat x = vertex_coords[0].toFloat();
                    GLfloat y = vertex_coords[1].toFloat();
                    GLfloat z = vertex_coords[2].toFloat();

                    //qDebug() << "v " << x << " " << y << " " << z;
                    vertices_coords.push_back(glm::vec3(x, y, z));
                }
                else if(line.left(2) == "vn")
                {
                    line.remove(0, 2);  //remove "vn "
                    QStringList vertex_normal = line.split(' ', QString::SkipEmptyParts);
                    GLfloat x = vertex_normal[0].toFloat();
                    GLfloat y = vertex_normal[1].toFloat();
                    GLfloat z = vertex_normal[2].toFloat();

                    //qDebug() << "vn " << x << " " << y << " " << z;
                    vertices_normal.push_back(glm::vec3(x, y, z));
                }
                else if(line.left(2) == "vt")
                {
                    line.remove(0,2);
                    QStringList vertex_texcoords = line.split(' ',QString::SkipEmptyParts);
                    GLfloat x = vertex_texcoords[0].toFloat();
                    GLfloat y = vertex_texcoords[1].toFloat();

                    vertices_texcoords.push_back(glm::vec2(x,y));
                }
                else if(line.left(2) == "f ")
                {
                    line.remove(0, 1);  // remove "f "
                    QStringList face_index = line.split(' ',QString::SkipEmptyParts);
                    int v_testIndex[3];
                    int n_testIndex[3];

                    for(int i=0; i<3; i++)
                    {
                        QString aVert = face_index[i];
                        QStringList  aVert_index = aVert.split('/');
                        int v_index = aVert_index[0].toInt();
                        //int t_index = aVert_index[1].toInt();
                        int n_index = aVert_index[2].toInt();

                        v_testIndex[i] = v_index;
                        n_testIndex[i] = n_index;

                        Vertex vert;
                        vert.Position = vertices_coords[v_index-1];
                        vert.Normal = vertices_normal[n_index-1];
                        //vert.TexCoords =

                        vertices.push_back(vert);
                    }

                    ftest++;
                }
                if(in.atEnd())
                    break;

                line = in.readLine();
            }

            file.close();
            mesh.ReloadVertices(vertices);

        }
    }

    update();
}

void Widget::LoadOBJ()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open An Obj File"),
                QString(),
                tr("OBJ Files(*.obj)")
                );
    if(!fileName.isEmpty()){
        qDebug() << "OBJ file name:" << fileName;
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("could not open this obj file"));
            return;
        }
        else{
            QTextStream in (&file);

            vector<glm::vec3> vertices_coords;
            vector<glm::vec3> vertices_normal;
            vector<glm::vec2> vertices_texcoords;
            vector<Vertex> vertices;


            int ftest = 0;
            QString line = in.readLine();
            while(true)
            {
                if(line.isEmpty())
                {
                    qDebug() << "space"   ;
                    line = in.readLine();
                    continue;

                }

                if(line[0] == '#')
                {
                    qDebug() << line;
                }
                else if(line.left(2) == "v ")  //顶点坐标
                {
                    line.remove(0, 1);  // remove "# "
                    QStringList vertex_coords = line.split(' ', QString::SkipEmptyParts);
                    GLfloat x = vertex_coords[0].toFloat();
                    GLfloat y = vertex_coords[1].toFloat();
                    GLfloat z = vertex_coords[2].toFloat();

                    //qDebug() << "v " << x << " " << y << " " << z;
                    vertices_coords.push_back(glm::vec3(x, y, z));
                }
                else if(line.left(2) == "vn")
                {
                    line.remove(0, 2);  //remove "vn "
                    QStringList vertex_normal = line.split(' ', QString::SkipEmptyParts);
                    GLfloat x = vertex_normal[0].toFloat();
                    GLfloat y = vertex_normal[1].toFloat();
                    GLfloat z = vertex_normal[2].toFloat();

                    //qDebug() << "vn " << x << " " << y << " " << z;
                    vertices_normal.push_back(glm::vec3(x, y, z));
                }
                else if(line.left(2) == "vt")
                {
                    line.remove(0,2);
                    QStringList vertex_texcoords = line.split(' ',QString::SkipEmptyParts);
                    GLfloat x = vertex_texcoords[0].toFloat();
                    GLfloat y = vertex_texcoords[1].toFloat();

                    //qDebug() << "vt " << x << " " << y;
                    vertices_texcoords.push_back(glm::vec2(x,y));
                }
                else if(line.left(2) == "f ")
                {
                    line.remove(0, 1);  // remove "f "
                    QStringList face_index = line.split(' ',QString::SkipEmptyParts);
                    int v_testIndex[3];
                    int n_testIndex[3];

                    for(int i=0; i<3; i++)
                    {
                        QString aVert = face_index[i];
                        QStringList  aVert_index = aVert.split('/');
                        int v_index = aVert_index[0].toInt();
                        //int t_index = aVert_index[1].toInt();
                        int n_index = aVert_index[2].toInt();

                        if(v_index != n_index){
                            qDebug() << "v_index != n_index";
                        }

                        v_testIndex[i] = v_index;
                        n_testIndex[i] = n_index;

                        Vertex vert;
                        vert.Position = vertices_coords[v_index-1];
                        vert.Normal = vertices_normal[n_index-1];
                        //vert.TexCoords =

                        vertices.push_back(vert);
                    }

//                    qDebug() << v_testIndex[0] <<"/"<<n_testIndex[0] << " "
//                                              << v_testIndex[1] << "/" << n_testIndex[1] << " "
//                                              << v_testIndex[2] << "/" << n_testIndex[2];

                    ftest++;
                }
                if(in.atEnd())
                    break;

                line = in.readLine();
//                if(line==NULL)
//                {
//                    qDebug() << "null";
//                    break;
//                }
            }

            file.close();
            mesh = Mesh(vertices);

        }
    }

    update();
}

void Widget::LoadOBJ2()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open An Obj File"),
                QString(),
                tr("OBJ Files(*.obj)")
                );
    if(!fileName.isEmpty()){
        qDebug() << "OBJ file name:" << fileName;
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("could not open this obj file"));
            return;
        }
        else{
            QTextStream in (&file);

            vector<glm::vec3> vertices_coords;
            vector<glm::vec3> vertices_normal;
            vector<glm::vec2> vertices_texcoords;
            vector<Vertex> vertices;

            vector<GLuint> indices;
            int vCount=0;
            int vnCount=0;

            int ftest = 0;
            QString line = in.readLine();
            while(true)
            {
                if(line.isEmpty())
                {
                    qDebug() << "space"   ;
                    line = in.readLine();
                    continue;

                }

                if(line[0] == '#')
                {
                    qDebug() << line;
                }
                else if(line.left(2) == "v ")  //顶点坐标
                {
                    line.remove(0, 1);  // remove "# "
                    QStringList vertex_coords = line.split(' ', QString::SkipEmptyParts);
                    GLfloat x = vertex_coords[0].toFloat();
                    GLfloat y = vertex_coords[1].toFloat();
                    GLfloat z = vertex_coords[2].toFloat();

                    //qDebug() << "v " << x << " " << y << " " << z;
                    //vertices_coords.push_back(glm::vec3(x, y, z));

                    Vertex vert;
                    vert.Position = glm::vec3(x,y,z);
                    vertices.push_back(vert);
                    vCount++;
                }
                else if(line.left(2) == "vn")
                {
                    line.remove(0, 2);  //remove "vn "
                    QStringList vertex_normal = line.split(' ', QString::SkipEmptyParts);
                    GLfloat x = vertex_normal[0].toFloat();
                    GLfloat y = vertex_normal[1].toFloat();
                    GLfloat z = vertex_normal[2].toFloat();

                    //qDebug() << "vn " << x << " " << y << " " << z;
                    //vertices_normal.push_back(glm::vec3(x, y, z));
                    vertices[vnCount].Normal = glm::vec3(x,y,z);
                    vnCount++;
                }
                else if(line.left(2) == "vt")
                {
                    line.remove(0,2);
                    QStringList vertex_texcoords = line.split(' ',QString::SkipEmptyParts);
                    GLfloat x = vertex_texcoords[0].toFloat();
                    GLfloat y = vertex_texcoords[1].toFloat();

                    //qDebug() << "vt " << x << " " << y;
                    vertices_texcoords.push_back(glm::vec2(x,y));
                }
                else if(line.left(2) == "f ")
                {
                    line.remove(0, 1);  // remove "f "
                    QStringList face_index = line.split(' ',QString::SkipEmptyParts);
                    int v_testIndex[3];
                    int n_testIndex[3];

                    for(int i=0; i<3; i++)
                    {
                        QString aVert = face_index[i];
                        QStringList  aVert_index = aVert.split('/');
                        GLuint v_index = aVert_index[0].toInt() - 1;
                        //int t_index = aVert_index[1].toInt();
                        GLuint n_index = aVert_index[2].toInt() - 1;

                        if(v_index != n_index){
                            qDebug() << "v_index != n_index";
                        }
                        else{
                            indices.push_back(n_index);
                        }

                        v_testIndex[i] = v_index;
                        //n_testIndex[i] = n_index;
                    }

//                    qDebug() << v_testIndex[0] <<"/"<<n_testIndex[0] << " "
//                                              << v_testIndex[1] << "/" << n_testIndex[1] << " "
//                                              << v_testIndex[2] << "/" << n_testIndex[2];
                    //qDebug() << "indices:" << v_testIndex[0] <<"/" << v_testIndex[1] << "/" << v_testIndex[2];
                    ftest++;
                }
                if(in.atEnd())
                    break;

                line = in.readLine();
//                if(line==NULL)
//                {
//                    qDebug() << "null";
//                    break;
//                }
            }
            qDebug() << "count " << vCount << "," << vnCount;
            file.close();
            mesh = Mesh(vertices, indices);

        }
    }

    update();
}

void qNormalizeAngle(int &angle)
{
    while(angle < 0)
        angle += 360 * 16;
    while(angle > 360 * 16)
        angle -= 360 * 16;
}

void Widget::setXRotation(int angle)
{

    qNormalizeAngle(angle);
    //qDebug() << "set x rotation:" << angle;
    //if(angle != xRotAngle)
    if(true)
    {
        xRotAngle = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void Widget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != yRotAngle)
    {
        yRotAngle = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void Widget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != zRotAngle)
    {
        zRotAngle = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void Widget::setLightX(GLfloat light_x)
{
    lightPos.x = light_x/10.0;
    update();
}

void Widget::setLightY(GLfloat light_y)
{
    lightPos.y = light_y/10.0;
    update();
}

void Widget::setLightZ(GLfloat light_z)
{
    lightPos.z = light_z/10.0;
    update();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mouseLastPos = event->pos();
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouseLastPos.x();
    int dy = event->y() - mouseLastPos.y();
    if(event->buttons() & Qt::LeftButton){
        setXRotation(xRotAngle + 8*dy);
        setYRotation(yRotAngle + 8*dx);
    }
    else if(event->buttons() & Qt::RightButton){
        setXRotation(xRotAngle + 8*dy);
        setZRotation(zRotAngle + 8*dx);
    }

    mouseLastPos = event->pos();
}
/*
void Widget::initializeGL()
{

    makeCurrent();

    // To properly initialize all available OpenGL function pointers
    // and stops from segfaulting
    glewExperimental=true;
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        std::cerr << glewGetErrorString(err);
    }

    std::cerr << "using OpenGL " << format().majorVersion() << "." << format().minorVersion() << "\n";

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    LoadOBJ();

    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vShaderFile))
        std::cerr <<"unable to compile vertx shader\n";

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fShaderFile))
        std::cerr <<"unable to compile fragmet shader\n";

    if (!program.link())
        std::cerr <<"unable to link shader program\n";

    program.bind();

}*/


void Widget::resizeGL(int w, int h)
{
    this->screenHeight = h;
    this->screenWidth = w;
    glViewport(0, 0, w, h);
}

QSize Widget::sizeHint() const
{
    return QSize(screenWidth, screenHeight);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();

    switch(event->key())
    {
    case 87: camera.ProcessKeyboard(FORWARD, 0.01); break;
    case 83: camera.ProcessKeyboard(BACKWARD, 0.01); break;
    case 65: camera.ProcessKeyboard(LEFT, 0.01); break;
    case 68: camera.ProcessKeyboard(RIGHT, 0.01); break;
    }

    update();
}


void Widget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.programId());

    //glBindVertexArray(VAO);
    glBindVertexArray(mesh.VAO);
    //qDebug() << "vao" << mesh.VAO;

    if(shaderType == 0)
    {
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.1f,0,0));
        model = glm::rotate(model, glm::radians((GLfloat)xRotAngle), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians((GLfloat)yRotAngle), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians((GLfloat)zRotAngle), glm::vec3(0, 0, 1));
        GLuint modelLoc = glGetUniformLocation(program.programId(),"model" );
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        GLuint viewLoc = glGetUniformLocation(program.programId(),"view" );
        GLuint projLoc = glGetUniformLocation(program.programId(),"projection" );
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(projection));
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices total -> 1 triangle

    }

    else if(shaderType == 1)
    {
        GLuint objectColorLoc = glGetUniformLocation(program.programId(), "objectColor");
        GLuint lightColorLoc = glGetUniformLocation(program.programId(), "lightColor");
        GLuint lightPosLoc = glGetUniformLocation(program.programId(), "lightPos");
        GLuint viewPosLoc = glGetUniformLocation(program.programId(), "viewPos");

        glUniform3f(objectColorLoc, objectColor.x, objectColor.y, objectColor.z);
        glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

        glm::mat4 model;
        model = glm::rotate(model, glm::radians((GLfloat)xRotAngle), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians((GLfloat)yRotAngle), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians((GLfloat)zRotAngle), glm::vec3(0, 0, 1));
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        GLuint modelLoc = glGetUniformLocation(program.programId(), "model");
        GLuint viewLoc = glGetUniformLocation(program.programId(), "view");
        GLuint projLoc = glGetUniformLocation(program.programId(), "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

         glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());
    }

    glBindVertexArray(0);

}

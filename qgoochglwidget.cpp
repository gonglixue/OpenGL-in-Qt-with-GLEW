#include "qgoochglwidget.h"

QGoochGLWidget::QGoochGLWidget() : GLWidget(),
    VBO(QOpenGLBuffer::VertexBuffer),
    EBO(QOpenGLBuffer::IndexBuffer)
{
    vShaderFile = QDir::currentPath() + "/gooch.vert";
    fShaderFile = QDir::currentPath() + "/gooch.frag";
    qDebug() << "shader path:" << vShaderFile;
    gooch_alpha = 0.5;
    gooch_beta = 0.5;

    coolColor = QVector3D(0, 0, 1);
    warmColor = QVector3D(1, 0, 0);
    edgeColor = QVector3D(0, 1, 0);

    silhVShaderFile = QDir::currentPath() + "/silh.vert";
    silhFShaderFile = QDir::currentPath() + "/silh.frag";
    silhGShaderFile = QDir::currentPath() + "/silh.geom";

}

void QGoochGLWidget::setAlpha(float alpha)
{
    this->gooch_alpha = alpha / 10.0f;
    update();
}

void QGoochGLWidget::setBeta(float beta)
{
    this->gooch_beta = beta / 10.0f;
    update();
}

void QGoochGLWidget::setXRotation(int angle)
{
    qNormalizeAngle2(angle);
    if(angle != this->xRotAngle)
    {
        xRotAngle = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void QGoochGLWidget::setYRotation(int angle)
{
    qNormalizeAngle2(angle);
    //qDebug() << "set x rotation in child" << angle;
    if(angle != yRotAngle)
    {
        yRotAngle = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void QGoochGLWidget::setZRotation(int angle)
{
    qNormalizeAngle2(angle);
    //qDebug() << "set x rotation in child" << angle;
    if(angle != zRotAngle)
    {
        zRotAngle = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void QGoochGLWidget::setLightX(GLfloat light_x)
{
    //lightPos.x() = light_x/10.0;
    lightPos.setX(light_x/10.0);
    update();
}

void QGoochGLWidget::setLightY(GLfloat light_y)
{
    //lightPos.y = light_y/10.0;
    lightPos.setY(light_y/10.0);
    update();
}

void QGoochGLWidget::setLightZ(GLfloat light_z)
{
    //lightPos.z = light_z/10.0;
    lightPos.setZ(light_z/10.0);
    update();
}

void QGoochGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case 87: camera.ProcessKeyboard(FORWARD, 0.01); break;
    case 83: camera.ProcessKeyboard(BACKWARD, 0.01); break;
    case 65: camera.ProcessKeyboard(LEFT, 0.01); break;
    case 68: camera.ProcessKeyboard(RIGHT, 0.01); break;
    }
    qDebug() << event->key() << "pressed";

    update();
}

void QGoochGLWidget::initializeGL()
{
    //connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, )
    qDebug() << "QGooghGLWidget Initialize";
    makeCurrent();
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(0,0,0.4f,1);

    //this->loadOBJ();
    this->loadOBJ2();
    setupVertexAttribs();

    this->program = new QOpenGLShaderProgram;
    if(!program->addShaderFromSourceFile(QOpenGLShader::Vertex, vShaderFile))
    {
        std::cerr <<"unable to compile vertx shader: " ;
        std::cerr << vShaderFile.toStdString() << std::endl;
    }

    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, fShaderFile))
        std::cerr <<"unable to compile fragmet shader: " << fShaderFile.toStdString() << endl;

    if (!program->link())
        std::cerr <<"unable to link shader program\n";

    this->silhProgram = new QOpenGLShaderProgram;
    if(!silhProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, silhVShaderFile))
    {
        std::cerr << "unable to compile vertex shader: ";
        std::cerr << silhVShaderFile.toStdString() << std::endl;
    }
    if(!silhProgram->addShaderFromSourceFile(QOpenGLShader::Geometry, silhGShaderFile))
    {
        std::cerr << "unable to compile geometry shader: ";
        std::cerr << silhGShaderFile.toStdString() << std::endl;
    }
    if(!silhProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, silhFShaderFile))
    {
        std::cerr << "unable to compile fragment shader: ";
        std::cerr << silhFShaderFile.toStdString() << std::endl;
    }
    if(!silhProgram->link())
        std::cerr << "unable to link silhouette shaders.\n";

    program->bind();

}

void QGoochGLWidget::setupVertexAttribs()
{
    this->VAO.create();
    QOpenGLVertexArrayObject::Binder VAOBinder(&this->VAO);
    this->VBO.create();
    this->EBO.create();

    //VAO.bind();
    VBO.bind();
    VBO.allocate(&this->mesh.vertices[0], this->mesh.vertices.size()*sizeof(Vertex));
    EBO.bind();
    EBO.allocate(&this->mesh.indices[0], this->mesh.indices.size()*sizeof(GLuint));

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    // POSITION
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));
    // NORMALS
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));
    // TEXCOORDS
    //f->glEnableVertexAttribArray(2);
    //f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, TexCoords)));

    //this->VBO.release();  // unbind
    //this->VAO.release();
}

void QGoochGLWidget::paintGL()
{
    //qDebug() << "paintGL";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QOpenGLVertexArrayObject::Binder vaoBinder(&this->VAO);
    QMatrix4x4 model;
    model.setToIdentity();
    model.rotate(xRotAngle, QVector3D(1, 0, 0));
    model.rotate(yRotAngle, QVector3D(0, 1, 0));
    model.rotate(zRotAngle, QVector3D(0, 0, 1));

    this->program->bind();
    //qDebug() << "program bind ok";
    //this->VAO.bind();
    GLuint objectColorLoc = program->uniformLocation("u_objectColor");
    GLuint coolColorLoc = program->uniformLocation("u_coolColor");
    GLuint warmColorLoc = program->uniformLocation("u_warmColor");
    GLuint lightColorLoc = program->uniformLocation("u_lightColor");
    GLuint lightPosLoc = program->uniformLocation("u_lightPos");
    GLuint viewPosLoc = program->uniformLocation("u_viewPos");
    GLuint alphaLoc = program->uniformLocation("u_alpha");
    GLuint betaLoc = program->uniformLocation("u_beta");
    GLuint modelLoc = program->uniformLocation("u_model_mat");
    GLuint viewLoc = program->uniformLocation("u_view_mat");
    GLuint projLoc = program->uniformLocation("u_projection_mat");

    program->setUniformValue(objectColorLoc, this->objectColor);
    program->setUniformValue(coolColorLoc, this->coolColor);
    program->setUniformValue(warmColorLoc, this->warmColor);
    program->setUniformValue(alphaLoc, this->gooch_alpha);
    program->setUniformValue(betaLoc, this->gooch_beta);
    program->setUniformValue(lightColorLoc, this->lightColor);
    program->setUniformValue(lightPosLoc, this->lightPos);
    program->setUniformValue(viewPosLoc, this->camera.Position );


    program->setUniformValue(modelLoc, model);
    program->setUniformValue(viewLoc, this->camera.GetViewMatrix());
    program->setUniformValue(projLoc, this->projection);
    //qDebug() << "set uniform ok";
    //glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());
    //glDrawElements(GL_TRIANGLES, this->mesh.indices.size(), GL_UNSIGNED_INT, 0);
    //qDebug() << "draw ok";
    program->release();
    //qDebug() << "release ok";

    // 2nd pass: silhouettes
    this->silhProgram->bind();
    objectColorLoc = silhProgram->uniformLocation("u_objectColor");
    modelLoc = silhProgram->uniformLocation("u_model_mat") ;
    viewLoc = silhProgram->uniformLocation("u_view_mat");
    projLoc = silhProgram->uniformLocation("u_projection_mat");
    glLineWidth(2.0f);
    silhProgram->setUniformValue(objectColorLoc, this->edgeColor);
    silhProgram->setUniformValue(modelLoc, model);
    silhProgram->setUniformValue(viewLoc, this->camera.GetViewMatrix());
    silhProgram->setUniformValue(projLoc, this->projection);
    //geom test
    GLuint model_geo = silhProgram->uniformLocation("u_model_geo");
    GLuint view_geo = silhProgram->uniformLocation("u_view_geo");
    silhProgram->setUniformValue(model_geo, model);
    silhProgram->setUniformValue(view_geo, this->camera.GetViewMatrix());

    glDrawElements(GL_TRIANGLES_ADJACENCY, this->mesh.indices.size(), GL_UNSIGNED_INT, 0);
    silhProgram->release();
}

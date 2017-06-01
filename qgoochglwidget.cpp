#include "qgoochglwidget.h"

QGoochGLWidget::QGoochGLWidget() : GLWidget(),
    VBO(QOpenGLBuffer::VertexBuffer),
    EBO(QOpenGLBuffer::IndexBuffer)
{
    vShaderFile = QDir::currentPath() + "/gooch.vert";
    fShaderFile = QDir::currentPath() + "/gooch.frag";

    gooch_alpha = 0.5;
    gooch_beta = 0.5;

    coolColor = QVector3D(0, 0, 1);
    warmColor = QVector3D(1, 0, 0);

    //VBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
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

void QGoochGLWidget::initializeGL()
{
    //connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, )
    qDebug() << "QGooghGLWidget Initialize";
    makeCurrent();
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
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
    qDebug() << "paintGL";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QOpenGLVertexArrayObject::Binder vaoBinder(&this->VAO);
    this->program->bind();
    qDebug() << "program bind ok";
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

    QMatrix4x4 model;
    model.setToIdentity();
    model.rotate(xRotAngle, QVector3D(1, 0, 0));
    model.rotate(yRotAngle, QVector3D(0, 1, 0));
    model.rotate(zRotAngle, QVector3D(0, 0, 1));
    program->setUniformValue(modelLoc, model);
    program->setUniformValue(viewLoc, this->camera.GetViewMatrix());
    program->setUniformValue(projLoc, this->projection);
    qDebug() << "set uniform ok";
    //glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());
    glDrawElements(GL_TRIANGLES, this->mesh.indices.size(), GL_UNSIGNED_INT, 0);
    qDebug() << "draw ok";
    program->release();
    qDebug() << "release ok";
}

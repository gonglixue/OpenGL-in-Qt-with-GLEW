#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      camera(glm::vec3(0, 0, 3.0f))
{
    screenHeight = 500;
    screenWidth = 500;
    xRotAngle = yRotAngle = zRotAngle = 0;
    vShaderFile = QDir::currentPath() + "/basiclambert.vert";
    fShaderFile = QDir::currentPath() + "/basiclambert.frag";
    lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    shaderType = 1;
}

Widget::~Widget()
{
    cleanup();
}

void Widget::cleanup()
{

}

static void qNormalizeAngle(int &angle)
{
    while(angle < 0)
        angle += 360 * 16;
    while(angle > 360 * 16)
        angle -= 360 * 16;
}

static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

static const GLfloat g_vertex_buffer_data_normal[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

void Widget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != xRotAngle)
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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_normal), g_vertex_buffer_data_normal, GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vShaderFile))
        std::cerr <<"unable to compile vertx shader\n";

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fShaderFile))
        std::cerr <<"unable to compile fragmet shader\n";

    if (!program.link())
        std::cerr <<"unable to link shader program\n";

    program.bind();

}

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
    qDebug() << event->key();

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

    glBindVertexArray(VAO);

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

         glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

}

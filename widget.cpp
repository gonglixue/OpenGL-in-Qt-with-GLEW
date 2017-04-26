#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      camera(glm::vec3(0, 0, 3.0f))
{
    screenHeight = 500;
    screenWidth = 500;
    xRotAngle = yRotAngle = zRotAngle = 0;
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


static QString vertex_shader =
        "#version 400 core\r\n"
        "layout(location = 0) in vec3 position;"
        "uniform mat4 model;"
        "uniform mat4 view;"
        "uniform mat4 projection;"
        "void main(){"
        "gl_Position = projection * view * model * vec4(position, 1);"
        "}";

static QString fragment_shader =
        "#version 400 core\r\n"
        "out vec3 color;"
        "void main(){"
        "color = vec3(1,0,0);"
        "}";

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

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       5*sizeof(GLfloat),                  // stride
       (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader))
        std::cerr <<"unable to compile vertx shader\n";

    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader))
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
    if(event->key() == 87)
    {
        camera.ProcessKeyboard(FORWARD, 0.01);
    }

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

    glBindVertexArray(0);

}

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      camera(glm::vec3(0, 0, 3.0f))
{
    //camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    screenHeight = 500;
    screenWidth = 500;
}

Widget::~Widget()
{

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

GLuint vertexbuffer;
GLuint VertexArrayID;

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


    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
    if(event->key() == 87)
    {
        camera.ProcessKeyboard(FORWARD, 0.01);
    }
    update();
}


void Widget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.programId());

    glBindVertexArray(VertexArrayID);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.1f,0,0));
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
    //glDisableVertexAttribArray(0);
    glBindVertexArray(0);

}

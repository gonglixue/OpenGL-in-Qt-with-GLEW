#include "goochglwidget.h"

GoochGLWidget::GoochGLWidget():Widget()
{
    qDebug() << "constructor of GoochGLWidget" ;
    vShaderFile = QDir::currentPath() + "/gooch.vert";
    fShaderFile = QDir::currentPath() + "/gooch.frag";

    gooch_alpha = 0.5;
    gooch_beta = 0.5;

    coolColor = glm::vec3(0,0,1);
    warmColor = glm::vec3(1,0,0);
}

void GoochGLWidget::setAlpha(float alpha)
{
    gooch_alpha = alpha/10.0f;
    update();
}

void GoochGLWidget::setBeta(float beta)
{
    gooch_beta = beta/10.0f;
    update();
}

void GoochGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    //qDebug() << "set x rotation in child" << angle;
    if(angle != xRotAngle)
    {
        xRotAngle = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GoochGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    //qDebug() << "set x rotation in child" << angle;
    if(angle != yRotAngle)
    {
        yRotAngle = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GoochGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    //qDebug() << "set x rotation in child" << angle;
    if(angle != zRotAngle)
    {
        zRotAngle = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GoochGLWidget::setLightX(GLfloat light_x)
{
    lightPos.x = light_x/10.0;
    update();
}

void GoochGLWidget::setLightY(GLfloat light_y)
{
    lightPos.y = light_y/10.0;
    update();
}

void GoochGLWidget::setLightZ(GLfloat light_z)
{
    lightPos.z = light_z/10.0;
    update();
}

void GoochGLWidget::initializeGL()
{
    qDebug() << "GoochGLWidget\n";
    makeCurrent();
    glewExperimental = true;
    GLenum err = glewInit();
    if(err != GLEW_OK){
        std::cerr << "Fialed to initialize GLEW\n";
        std::cerr << glewGetErrorString(err);
    }

    //std::cerr << "using OpenGL" << format().majorVersion() << "." << format.minorVersion() << "\n";

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
}

void GoochGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program.programId());
    glBindVertexArray(mesh.VAO);

    GLuint objectColorLoc = glGetUniformLocation(program.programId(), "u_objectColor");
    GLuint coolColorLoc = glGetUniformLocation(program.programId(), "u_coolColor");
    GLuint warmColorLoc = glGetUniformLocation(program.programId(), "u_warmColor");
    GLuint lightColorLoc = glGetUniformLocation(program.programId(), "u_lightColor");

    //GLuint lightColorLoc = glGetUniformLocation(program.programId(), "lightColor");
    GLuint lightPosLoc = glGetUniformLocation(program.programId(), "u_lightPos");
    GLuint viewPosLoc = glGetUniformLocation(program.programId(), "u_viewPos");

    GLuint alphaLoc = glGetUniformLocation(program.programId(), "u_alpha");
    GLuint betaLoc = glGetUniformLocation(program.programId(), "u_beta");

    glUniform3f(objectColorLoc, objectColor.r, objectColor.g, objectColor.b);
    glUniform3f(coolColorLoc, coolColor.r, coolColor.g, coolColor.b);
    glUniform3f(warmColorLoc, warmColor.r, warmColor.g, warmColor.b);
    glUniform1f(alphaLoc, this->gooch_alpha);
    glUniform1f(betaLoc, this->gooch_beta);
    glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);

    //glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

    glm::mat4 model;
    model = glm::rotate(model, glm::radians((GLfloat)xRotAngle), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians((GLfloat)yRotAngle), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians((GLfloat)zRotAngle), glm::vec3(0, 0, 1));
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

    GLuint modelLoc = glGetUniformLocation(program.programId(), "u_model_mat");
    GLuint viewLoc = glGetUniformLocation(program.programId(), "u_view_mat");
    GLuint projLoc = glGetUniformLocation(program.programId(), "u_projection_mat");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());

    glBindVertexArray(0);
}

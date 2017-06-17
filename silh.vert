#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_model_mat;
uniform mat4 u_view_mat;

void main()
{
    gl_Position = u_view_mat * u_model_mat * vec4(position, 1.0f);
}

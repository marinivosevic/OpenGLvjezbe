#version 330 core
layout(location = 0) in vec4 position;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    // gl_Position = position;
    //gl_Position = transform*position;
    gl_Position = projection*view*transform*position;
}

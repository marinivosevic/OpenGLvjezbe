#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 u_color;
void main()
{
    //color = vec4(0.2, 0.3, 0.8, 1.);
    color = u_color;
}

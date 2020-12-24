#version 130

in vec4 position;
uniform float horizoff;

//layout(location = 0) in vec4 position;
//layout(location = 0)in vec4 vert;

//uniform mat4 projection;
//uniform mat4 view;
//uniform mat4 model;

uniform mat4 mat;

void main()
{
//    gl_Position = projection * view * model * vert;
    gl_Position = position + vec4(horizoff, 0.0, 0.0, 0.0);
//  gl_Position = mat * position;
}

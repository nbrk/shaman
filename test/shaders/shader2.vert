#version 130

in vec3 a_position;
uniform float horizoff;

void main()
{
    gl_Position = vec4(a_position, 1.0) + vec4(horizoff, 0.0, 0.0, 1.0);
}

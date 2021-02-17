#version 330

in vec3 v_normal;
in vec4 v_color;
in vec2 v_texcoord;

void main()
{
  gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0) + v_color;
}

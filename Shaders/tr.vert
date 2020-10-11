#version 330

layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec3 a_color;

uniform vec2 u_projection;

out vec3 v_color;

void main()
{
  gl_Position = vec4(a_pos * u_projection, 0.0, 1.0);
  v_color = a_color;
}

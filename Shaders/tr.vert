#version 330

layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec3 a_color;
//layout (location = 2) in ves2 t_pos;

out vec3 v_color;

uniform vec2 u_projection;
uniform vec2 u_position;
uniform float u_size;
uniform float u_angle;


void main()
{
  v_color = a_color;
  float cs = cos(u_angle);
  float sn = sin(u_angle);
  vec2 pos = vec2(a_pos.x * cs - a_pos.y * sn, a_pos.x * sn + a_pos.y * cs);
  gl_Position = vec4((pos * u_size + u_position) * u_projection, 0.0, 1.0);
}

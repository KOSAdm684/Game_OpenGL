#version 330

layout (location = 0) in vec2 a_pos;

uniform vec2 u_projection;
uniform vec2 u_position;
uniform float u_size;
uniform float u_angle;


void main()
{
  float cs = cos(u_angle);
  float sn = sin(u_angle);
  vec2 pos  = vec2(a_pos.x * cs - a_pos.y * sn, a_pos.x * sn + a_pos.y * cs);
  gl_Position = vec4((pos * u_size + u_position) * u_projection, 0.0, 1.0);
}

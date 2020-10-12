#version 330

layout (location = 0) in vec2 a_pos;

uniform vec2 u_projection;
uniform vec2 u_position;
uniform float u_size;

void main()
{
  gl_Position = vec4((a_pos * u_size + u_position) * u_projection, 0.0, 1.0);
}

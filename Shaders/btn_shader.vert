#version 330

layout (location = 0) in vec2 a_pos;

uniform float u_offset;

void main()
{
  gl_Position = vec4(a_pos + vec2(0.0, u_offset), 0.0, 1.0);
}

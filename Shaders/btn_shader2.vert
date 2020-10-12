#version 330

layout (location = 0) in vec2 a_pos;

out vec4 v_color;

void main()
{
  gl_Position = vec4(a_pos, 0.0, 1.0);
  v_color = vec4(0.0, 1.0, 0.0, 1.0);
}

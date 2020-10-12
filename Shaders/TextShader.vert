#version 330 core

layout (location = 0) in vec4 a_position; // <vec2 pos, vec2 tex>

uniform vec2 u_screen;
uniform float u_width;
uniform float u_height;
uniform float u_center;
uniform float u_offset;

out vec2 v_texCoords;

void main()
{
  vec2 alignment = vec2(u_width / 2.0, u_height / 3.0) * u_center;
  vec2 pos = a_position.xy - alignment;

  gl_Position = vec4(pos / u_screen + vec2(0.0, u_offset), 0.0, 1.0);
  v_texCoords = a_position.zw;
}

#version 330 core

in vec2 v_texCoords;

uniform sampler2D u_texture;
uniform vec3 u_color;

void main()
{
  gl_FragColor = vec4(u_color, texture(u_texture, v_texCoords).r);
}

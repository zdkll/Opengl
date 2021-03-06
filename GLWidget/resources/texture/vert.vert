﻿attribute vec3 Vertex;
attribute vec3 Color;
attribute vec2 Texc;

out vec2       TexCoord;
varying vec3 VColor;

uniform mat4  transform;

void main(void)
{
    gl_Position = transform*vec4(Vertex,1.0f);

    VColor = Color;
    TexCoord = Texc;
}

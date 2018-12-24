﻿attribute vec3 Vertex;
attribute vec3 Color;
attribute vec2 Texc;

out vec2 TexCoord;
varying vec3 FragColor;

void main(void)
{
    gl_Position = vec4(Vertex,1.0f);

    FragColor = Color;

    TexCoord = Texc;
}
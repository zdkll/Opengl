#version 430

layout(location = 0) in vec2 vetex;

void main(void)
{
    gl_Position = vec4(vetex,0,1);
}

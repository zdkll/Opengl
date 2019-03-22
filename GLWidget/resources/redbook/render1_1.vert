#version 430

layout(location = 0) in vec2 vetex;
in vec3 color;

out vec3 varyingColor;

void main(void)
{
    gl_Position = vec4(vetex,0,1);
    varyingColor = color;
}

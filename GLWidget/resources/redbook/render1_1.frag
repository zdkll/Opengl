#version 430

in  vec3 varyingColor;

void main(void)
{
    gl_FragColor = vec4(varyingColor,1);
}

uniform sampler2D Texture;

in vec2 TexCoord;
varying vec3 FragColor;

void main(void)
{
    gl_FragColor = texture2D(Texture, TexCoord.st);//vec4(FragColor,1.0);
}

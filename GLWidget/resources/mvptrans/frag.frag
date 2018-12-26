uniform sampler2D Texture1;
uniform sampler2D Texture2;

uniform  float   MixFactor;

in vec2 TexCoord;
varying vec3 VColor;

void main(void)
{
    gl_FragColor = mix(texture2D(Texture1, TexCoord.st),texture2D(Texture2,TexCoord),MixFactor);//vec4(VColor,1.0);
}

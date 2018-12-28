#version 330
uniform  vec3 objectColor;
uniform  vec3 lightColor;

uniform vec3 lightPos;

in vec3 fragPos;
in vec3 Normal;

void main(void)
{
    float ambientIntensity = 0.1f;
    vec3 ambientColor = ambientIntensity*lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir= normalize(lightPos-fragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuseColor = lightColor*diff;

    gl_FragColor =  vec4(objectColor*(ambientColor+diffuseColor),1.0);
}

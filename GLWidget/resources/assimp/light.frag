#version 330
uniform  vec3 objectColor;
uniform  vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 Normal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main(void)
{
    //环境光
    vec3 ambientColor = material.ambient*lightColor;

    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir= normalize(lightPos-fragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuseColor = lightColor*(diff*material.diffuse);

    //镜面反射
    float specularIntensity = 0.5f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir= reflect(-lightDir,norm);
    float  specularFactor = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specularColor = (specularFactor*material.specular)*lightColor;

    gl_FragColor =  vec4(objectColor*(ambientColor+diffuseColor+specularColor),1.0);
}

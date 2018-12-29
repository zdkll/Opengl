attribute vec3 Vertex;
attribute vec3 aNormal;

uniform mat4  model;
uniform mat4  view;
uniform mat4  projection;

uniform mat4  normModel;

out vec3 fragPos;
out vec3 Normal;

void main(void)
{
    gl_Position = projection*view*model*vec4(Vertex,1.0f);

    fragPos = vec3(model*vec4(Vertex,1.0f));
    Normal  = mat3(normModel)*aNormal;
}

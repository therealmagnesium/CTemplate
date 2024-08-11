#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec2 fragTexCoords;

struct Material
{
    sampler2D diffuseMap;
};

uniform vec4 tint;
uniform Material material;

void main()
{
    vec3 texel = texture(material.diffuseMap, fragTexCoords).xyz;
    vec3 result = texel * tint.xyz;
    finalColor = vec4(result, 1.f);
}

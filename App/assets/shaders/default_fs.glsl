#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec2 fragTexCoords;

uniform vec4 tint;
uniform sampler2D texture0;

void main()
{
    vec4 texel = texture(texture0, fragTexCoords);
    finalColor = texel;
}

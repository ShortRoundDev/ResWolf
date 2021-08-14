#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 view;
uniform mat4 projection;

uniform vec3 scale;
uniform vec3 offset;

void main() {
    vec3 translatedPos = (aPos * scale) + offset;
    gl_Position = projection * view * vec4(translatedPos, 1.0f);
    
    FragPos = translatedPos;

    TexCoord = vec2(aTex.x, aTex.y);
    Normal = aNormal;
}
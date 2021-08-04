#version 330 core
layout (location = 0) in vec3 aPos; // aPos is a unit square
layout (location = 1) in vec2 aTex; // aTex -> UV map to 1/255th of the font file

out vec2 TexCoord;

uniform float character;

uniform vec2 pos;                   // position of character
uniform vec2 size;                  // size of character

void main() {
    gl_Position = vec4((aPos.xy * size.xy) + pos, 1.0, 1.0);
    float charOffset = character/254.0;
    TexCoord = vec2(aTex.x + charOffset, aTex.y);
}
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;

void main(){
    vec4 t = texture(tex, TexCoord);
    FragColor = t;
}
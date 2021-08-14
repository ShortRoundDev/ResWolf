#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;
uniform vec3 playerPos;
uniform vec2 scale;

void main(){
    vec4 newPosition = vec4(aPos.xy * scale, aPos.z, 1.0);
    vec3 cameraRight = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 cameraUp = vec3(0.0, 1.0, 0.0);
    
    
    newPosition = vec4(
        offset
            + cameraRight   * newPosition.x
            + cameraUp      * newPosition.y,
        1.0
    );
    
    FragPos = newPosition.xyz;

    gl_Position = projection * view * newPosition;
    TexCoord = vec2(aTex.x, aTex.y);
    Normal = vec3(-view[2][0], 0, view[2][2]);
}
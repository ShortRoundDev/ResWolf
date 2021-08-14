#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D tex;

/*uniform float angle;
uniform float maxAngles;

uniform float frame;
uniform float maxFrame;*/

uniform vec3 lightPos;

void main(){

 /*  // ----- Animation -----
        vec4 t = texture(tex);, vec2(
            (TexCoord.x/maxFrame) + (frame/maxFrame),
            (TexCoord.y/maxAngles) + (angle/maxAngles)
        ));
        // ---------------------
    */

    vec4 t = texture(tex, TexCoord);
    if(t.a == 0.0)
        discard;
   
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.8, 0.8, 0.8);

    FragColor = vec4(diffuse * t.xyz, 1.0);
}
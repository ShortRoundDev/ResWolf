#version 330 core

out vec4 FragColor;

/* ----- Textures ----- */

/* UV map
in vec2 texCoord;

/* texture */
uniform sampler2D tex;

/* ----- Light ----- */

/* Distance of frag from player's point */
in vec3 dist;

/* tint override. Used for debugging usually */
uniform vec4 tint;

/* the lowest level of brightness applied to a fragment */
uniform float minBright;

/* the highest level of brightness applied to a fragment */
uniform float maxBright;

void main(){
    /* Initial tex mapping */
    vec4 t = texture(tex, TexCoord);
    
    /* Ignore transparency */
    if(t.a == 0.0)
        discard;
    
    /* Calculate light.
     * Iterate Light dropoff in chunks by 1/10.
     */
    float z = min(maxBright,
        max(
            minBright,
            round(10.0/(length(dist.xz)) - 1)/10.0
        )
    );

    /* Tint is a color multiplier, so (0.5, 1, 1) means "reduce red by 50%, everything else normal".
     * This is used for debugging, not regular light calculations
     * 
     * Multiply blue by 1.2 (with a ceil of 1.0) to give everything a blue tint. Maybe this SHOULD be
     * handled by `tint`...
     */
    FragColor = t * vec4(z, z, min(1.0, z * 1.2), 1.0) * tint;
}
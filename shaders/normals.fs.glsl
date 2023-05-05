#version 330

in vec3 vPosition_vs; // Position du sommet transformée dans l'espace View (vs)
in vec3 vNormal_vs; // Normale du sommet transformée dans l'espace View (vs)
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;

// uniform vec3 uLightDir_vs;
// uniform vec3 uLightIntensity;


out vec4 fFragColor;

uniform float uOpacity;
uniform sampler2D uTexture;

vec3 blinnPhong() {
    return (uDiffuse * dot(normalize(vec3(-2,-1,0)), vNormal_vs) + uSpecular * pow(dot((normalize(-vPosition_vs) + normalize(vec3(-2,-1,0)))/2, vNormal_vs), uShininess));
    // return uLightIntensity * (uDiffuse * dot(normalize(uLightDir_vs), vNormal_vs) + uSpecular * pow(dot((normalize(-vPosition_vs) + normalize(uLightDir_vs))/2, vNormal_vs), uShininess));
}


void main() {
    //   fFragColor = vec4(normalize(vNormal_vs),uOpacity);
    fFragColor = texture(uTexture, vTexCoords) * uOpacity;
}
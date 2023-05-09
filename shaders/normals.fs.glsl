#version 330

in vec3 vPosition_vs; // Position du sommet transformée dans l'espace View (vs)
in vec3 vNormal_vs; // Normale du sommet transformée dans l'espace View (vs)
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;

uniform vec3 uLight1Position;
uniform vec3 uLight1Intensity;
uniform vec3 uLight2Direction;
uniform vec3 uLight2Intensity;


out vec4 fFragColor;

uniform float uOpacity;
uniform sampler2D uTexture;

vec3 blinnPhongPointLight() {
    vec3 Wo =  (normalize(-vPosition_vs));
    vec3 Wi = (normalize(uLight1Position - vPosition_vs));

    vec3 Li = (uLight1Intensity / pow(length(vPosition_vs - uLight1Position), 1));
    vec3 halfVector = (Wo+Wi)/2;

    return 5*Li*(uDiffuse*(dot(Wi, vNormal_vs)))+uSpecular*(pow(dot(halfVector,vNormal_vs), uShininess));
}

vec3 blinnPhongDirectionalLight() {

    vec3 Wo = (normalize(-vPosition_vs));
    vec3 Wi = normalize(uLight2Direction);

    vec3 halfVector = (Wo+Wi)/2;

    return uLight2Intensity*(uDiffuse*(dot(Wi, vNormal_vs)))+uSpecular*(pow(dot(halfVector,vNormal_vs), uShininess));
}

vec3 ambiantLight()
{
    vec3 color = vec3(0,0.2,0.7);
    float ambientIntensity = 0.5;
    return color*ambientIntensity;
}


void main() {
    fFragColor = texture(uTexture, vTexCoords) * uOpacity;
    fFragColor = vec4(blinnPhongPointLight(),1) + fFragColor;
    fFragColor = vec4(blinnPhongDirectionalLight(),1)*fFragColor;
    fFragColor =  vec4(ambiantLight(),1)+fFragColor;
}
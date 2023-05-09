#version 330

in vec3 vPosition_vs; // Position du sommet transformée dans l'espace View (vs)
in vec3 vNormal_vs; // Normale du sommet transformée dans l'espace View (vs)
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;

uniform vec3 uLight1Position;
uniform vec3 uLight1Intensity;

out vec4 fFragColor;

uniform float uOpacity;
uniform sampler2D uTexture;

vec3 blinnPhong(vec3 lightIntensity, vec3 lightPosition) {
    // return (uDiffuse * dot(normalize(vec3(-2,-1,0)), vNormal_vs) + uSpecular * pow(dot((normalize(-vPosition_vs) + normalize(vec3(-2,-1,0)))/2, vNormal_vs), uShininess));
    // MARCHE PAS PAS BON
    // return uLight1Intensity * (uDiffuse * dot(normalize(uLight1Position), vNormal_vs) + uSpecular * pow(dot((normalize(-vPosition_vs) + normalize(uLight1Position))/2, vNormal_vs), uShininess));
    // VERSION ER
    vec3 Wo =  (normalize(-vPosition_vs));
    vec3 Wi = (normalize(uLight1Position - vPosition_vs));

    vec3 Li = (uLight1Intensity / pow(distance(vPosition_vs, uLight1Position), 2));
    vec3 halfVector = (Wo+Wi)/2;

    // return 10*Li*(uDiffuse*(dot(Wi, vNormal_vs))); //MARCHE TROP BIEN ???
    // return vec3(uShininess);
    // return vec3(uSpecular);
        return 10*Li*(uDiffuse*(dot(Wi, vNormal_vs)))+uSpecular*(pow(dot(halfVector,vNormal_vs), uShininess));
   }

vec3 Blinn_Phong() //W ET T
{
    vec3 light_dir = normalize(uLight1Position - vPosition_vs); // actual w_i

    vec3 w_o = normalize(-vPosition_vs);

    vec3 halfVector = normalize((w_o + light_dir) / 2.);

    vec3 diffuse = uDiffuse * max(dot(light_dir, vNormal_vs), 0.);
    vec3 glossy  = uSpecular * (pow(max(dot(halfVector, vNormal_vs), 0.),uShininess));

    float light_distance_i = distance(uLight1Position, vPosition_vs);

    vec3 light_factor = uLight1Intensity / (light_distance_i * light_distance_i);

    // return glossy;
    return light_factor * (diffuse + glossy);
}




void main() {
    fFragColor = vec4(blinnPhong(uLight1Intensity, uLight1Position),1)   *     (texture(uTexture, vTexCoords) * uOpacity);
}
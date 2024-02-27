#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition; // Recevoir la position du fragment

out vec4 fragColor;

uniform float alpha; // Paramètre alpha de l'atténuation
uniform float beta; // Paramètre beta de l'atténuation


void main() {
    // Calculer la distance du fragment au centre du triangle
    float distance = length(vFragPosition);

    // Calculer l'atténuation en fonction de la distance
    float attenuation = alpha * exp(-beta * distance * distance);

    // Appliquer l'atténuation à la couleur finale
    fragColor = vec4(vFragColor * attenuation, 1.0);
}

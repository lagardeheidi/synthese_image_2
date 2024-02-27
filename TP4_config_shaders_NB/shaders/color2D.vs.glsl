#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

// Fonction pour créer une matrice de translation
mat3 translate(float tx, float ty) {
    return mat3(
        vec3(1.0, 0.0, 0.0),
        vec3(0.0, 1.0, 0.0),
        vec3(tx, ty, 1.0)
    );
}

// Fonction pour créer une matrice de rotation d'angle alpha (en degrés)
mat3 rotate(float a) {
    float alpha = radians(a); // Convertir l'angle en radians
    float c = cos(alpha);
    float s = sin(alpha);
    return mat3(
        vec3(c, s, 0.0),
        vec3(-s, c, 0.0),
        vec3(0.0, 0.0, 1.0)
    );
}

// Fonction pour créer une matrice de mise à l'échelle
mat3 scale(float sx, float sy) {
    return mat3(
        vec3(sx, 0.0, 0.0),
        vec3(0.0, sy, 0.0),
        vec3(0.0, 0.0, 1.0)
    );
}

void main() {
    // Translation du triangle
    mat3 translationMatrix = translate(0.5, 0.5);

    // Rotation du triangle de 45 degrés autour de l'origine 
    mat3 rotationMatrix = rotate(45.0);

    // Réduction du triangle
    mat3 scaleMatrix = scale(0.5, 0.5); 

    // multiplication des matrices dans l'ordre inverse (rotation, puis mise à l'échelle, puis translation)
    mat3 finalTransformation = translationMatrix * scaleMatrix * rotationMatrix;

    // Transformation de la position du sommet avec la matrice finale
    vec2 transformedPosition = (finalTransformation * vec3(aVertexPosition, 1.0)).xy;
    
    // Assignation de la position transformée
    gl_Position = vec4(transformedPosition, 0.0, 1.0);

    // Passage de la couleur du sommet au fragment shader
    vFragColor = aVertexColor;
}

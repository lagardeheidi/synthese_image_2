#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragPosition;
out vec3 vFragColor;
out vec2 vVertexPosition; // Ajout de la sortie pour la position du vertex

// Fonction qui renvoie la matrice de translation tx et ty
mat3 translate(float tx, float ty) {
  mat3 M = mat3(
    vec3(1, 0, 0), // Première colonne de la matrice
    vec3(0, 1, 0), // Deuxième colonne de la matrice
    vec3(tx, ty, 1) // Troisième colone de la matrice
  );
  return M;
}
// Fonction qui renvoie la matrice de scale sx et sy
mat3 scale(float sx, float sy) {
  mat3 M = mat3(
    vec3(sx, 0, 0), // Première colonne de la matrice
    vec3(0, sy, 0), // Deuxième colonne de la matrice
    vec3(0, 0, 1) // Troisième colone de la matrice
  );
  return M;
}

// Fonction qui renvoie la matrice de rotation d'angle a
mat3 rotate(float a) {
  a = radians(a);
  mat3 M = mat3(
    vec3(cos(a), sin(a), 0), // Première colonne de la matrice
    vec3(-sin(a), cos(a), 0), // Deuxième colonne de la matrice
    vec3(0, 0, 1) // Troisième colone de la matrice
  );
  return M;
}

void main() {
  vFragPosition = vec3(aVertexPosition, 0.0); 
  vVertexPosition = aVertexPosition;
  vFragColor = aVertexColor;

  gl_Position = vec4(((rotate(0)*translate(.0, .0)*scale(1.5, 1.5)) * vec3(aVertexPosition, 1.)).xy, 0.0, 1.0);
}
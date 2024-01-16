#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // Création d'un seul vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // À partir de ce point, la variable vbo contient l'identifiant d'un VBO

    // binding d'un VBO sur la cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On peut à prénset modifier le VBO en passant par la cible GL_ARRAY_BUFFER
    // creer un tableau de GLfloat contenant toutes les coordonnées à la suite
    GLfloat vertices[] = {
        -0.5f, -0.5f, // Premier sommet
        0.5f, -0.5,   // Deuxieme sommet
        0.0f, 0.5f    // Troisieme sommet
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Debinder VBO

    // creation d'un vao
    GLuint vao;

    // on la remplit
    glGenVertexArrays(1, &vao);

    // on le bind
    glBindVertexArray(vao);

    // on utilise un attribut donné (position)
    static constexpr GLuint vertex_attr_position = 0;
    glEnableVertexAttribArray(vertex_attr_position);

    // on re bind le vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // specification des attributs de vertex
    glVertexAttribPointer(vertex_attr_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

    // Debinder VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Debinder VAO
    glBindVertexArray(0);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // nettoyer la fenetre
        glClear(GL_COLOR_BUFFER_BIT);

        // Bindez le vao
        glBindVertexArray(vao);

        // Dessiner en utilisant le VAO
        //(le type de primitive, l'indice du premier sommet, le nb de sommets)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // debindez le vao
        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // liberer les ressources allouees sur GPU
    // desallouer le vbo et vao
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
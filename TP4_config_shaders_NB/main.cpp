#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP4 EX1"}};
    ctx.maximize_window();
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    const p6::Shader shader = p6::load_shader(
        "shaders/color2D.vs.glsl",
        "shaders/grey2d.fs.glsl"
    );
    // Création d'un seul vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // À partir de ce point, la variable vbo contient l'identifiant d'un VBO

    // binding d'un VBO sur la cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On peut à prénset modifier le VBO en passant par la cible GL_ARRAY_BUFFER
    // creer un tableau de GLfloat contenant toutes les coordonnées à la suite
    GLfloat vertices[] = {
        -0.5f, -0.5f, 1.f, 0.f, 0.7f, // Premier sommet
        0.5f, -0.5f, 0.f, 0.8f, 0.5f, // Deuxième sommet
        0.0f, 0.5f, 0.2f, 0.f, 0.9f   // Troisième sommet
    };

    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
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

    // on utilise un attribut donné (position)
    static constexpr GLuint vertex_attr_color = 1;
    glEnableVertexAttribArray(vertex_attr_color);

    // on re bind le vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // specification des attributs de vertex
    glVertexAttribPointer(vertex_attr_position, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glVertexAttribPointer(vertex_attr_color, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid*)(2 * sizeof(GLfloat)));

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
        // indique a opengl d'utiliser ce shader
        shader.use();

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
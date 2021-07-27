#include <cube.h>

float vertices[] = {
    // position             // texture
    0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
    0.5f,  -0.5f,  0.5f,    1.0f, 0.0f,
    -0.5f,  -0.5f,  0.5f,   0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
    -0.5f,  -0.5f,  0.5f,   0.0f, 0.0f,     // front
    0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f,  -0.5f,   0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
    -0.5f,  0.5f,  -0.5f,   0.0f, 1.0f,     // top
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f,  -0.5f,   0.0f, 1.0f,
    -0.5f,  -0.5f,  -0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
    -0.5f,  -0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  -0.5f,  -0.5f,  0.0f, 0.0f,     // left
    0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
    0.5f,  0.5f,  -0.5f,    1.0f, 1.0f,
    0.5f,  -0.5f,  -0.5f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
    0.5f,  -0.5f,  0.5f,    0.0f, 0.0f,
    0.5f,  -0.5f,  -0.5f,   1.0f, 0.0f,     // right
    -0.5,  -0.5f,  -0.5f,   0.0f, 0.0f,
    -0.5f,  -0.5f,  0.5f,   0.0f, 1.0f,
    0.5f,  -0.5f,  0.5f,    1.0f, 1.0f,
    -0.5,  -0.5f,  -0.5f,   0.0f, 0.0f,
    0.5f,  -0.5f,  -0.5f,   1.0f, 0.0f,
    0.5f,  -0.5f,  0.5f,    1.0f, 1.0f,     // bottom
    -0.5f,  -0.5f,  -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  -0.5f,   1.0f, 1.0f,
    0.5,  0.5f,  -0.5f,     0.0f, 1.0f,
    -0.5f,  -0.5f,  -0.5f,  1.0f, 0.0f,
    0.5f,  -0.5f,  -0.5f,   0.0f, 0.0f,
    0.5f,  0.5f,  -0.5f,    0.0f, 1.0f      // back
};

/*std::vector<Vertex> vertices = {
    Vertex { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) }, // front-right-top
    Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) }, // front-left-top
    Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
    Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
    Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f) }, // back-left-bottom
};*/

Cube::Cube()
{
    VAO; VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(2);
}

Cube::~Cube()
{
}

void Cube::Draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::Draw(Part_Section section)
{
    glDrawArrays(GL_TRIANGLES, section * 6, section *6 + 6);
}
#ifndef BLOCKK_H
#define BLOCKK_H

#include <glx.h>
#include <util.h>

#include <mesh.h>

enum Part_Section {
    FRONT = 0,
    TOP = 1,
    LEFT = 2,
    RIGHT = 3,
    BOTTOM = 4,
    BACK = 5
};

class Cube
{
private:
    unsigned int VAO;
    unsigned int VBO;
public:
    Mesh *mesh;
    Cube();
    ~Cube();
    void Draw();
    void Draw(Part_Section section);
};

#endif
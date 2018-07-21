// Tetromino header file
#include "Angel.h"
#include <vector>
#include <utility>
#include "TetrisGrid.h"
enum class Shape  {O,I,S,Z,L,J,T};

class Tetromino
{
public:
    Tetromino(Shape type);
    void initPoints();
    void initBlockO();
    void initBlockI();
    void initBlockS();
    void initBlockZ();
    void initBlockL();
    void initBlockJ();
    void initBlockT();
    void initVaosBuffersShaders();
    void draw();
    void rotateCCW(TetrisGrid& staticGrid);
    GLuint getVao();
    int getNumPoints();
    vec2* getPoints();
    vec3* getColors();
    vec3 getColor();
    int getShape();
    GLuint* getProgram();
    std::pair<int, int> coordinates[4];
    void moveLeft(int squares);
    void moveRight(int squares);
    void printShape();
private:
    void updatePointsFromCoordinates();
    //void updatePivotPosition();
    void rotateCoordinatesCCW(TetrisGrid& staticGrid);
    void randomPositionRotation();
    GLuint vao; // Vertex Array Object
    static const int numPoints = 24; // Number of vertexes
    vec3 color;
    vec2 points[24]; // 4 squares per tetromino, 2 triangles each, 3 points per triangle
    vec3 colors[24]; // Color array
    Shape shape;
    GLuint program;
    GLuint buffer;
    int rotation; // 0 - 3 states
};

// Extra: Fast Drop
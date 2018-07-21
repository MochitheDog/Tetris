// Header file for TetrisGrid.cpp
#pragma once
#include "globals.h"
#include "Angel.h"
#include <vector>
class TetrisGrid
{

public:
    TetrisGrid();

    //bool grid[10][20];
    int grid[10][20];
    // 0 = empty
    // 1 = O
    // 2 = I
    // 3 = S
    // 4 = Z
    // 5 = L
    // 6 = J
    // 7 = T
    // determines colour of static block
    void draw();
    void clearLine(int y);
    bool checkLineFilled(int y);
    void increaseLandedCounter(int num);
    void decreaseLandedCounter(int num);
    void generatePoints();
    void colorEntireGrid(vec3 color);
    void resetGrid();
    //void printGrid();
private:
    int landedCounter = 0;
    
    GLuint vao;
    GLuint buffer;
    GLuint program;
    std::vector<vec2> points;
    std::vector<vec3> colors;
    const vec2 templatePoints[6] = {
        vec2(-0.5,1.0), // top left
        vec2(-0.5,0.9), // bottom left
        vec2(-0.4,1.0), // top right
        vec2(-0.4,1.0), // top right
        vec2(-0.5,0.9), // bottom left
        vec2(-0.4,0.9) // bottom right
    };
};
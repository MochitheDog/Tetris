#include "Tetromino.h"
#include "globals.h"
#include <iostream>

Tetromino::Tetromino(Shape type)
{
    switch(type) {
        case Shape::O:  initBlockO();
                        break;
        case Shape::I:  initBlockI();
                        break;
        case Shape::S:  initBlockS();
                        break;
        case Shape::Z:  initBlockZ();
                        break;
        case Shape::L:  initBlockL();
                        break;
        case Shape::J:  initBlockJ();
                        break;
        case Shape::T:  initBlockT();
                        break;
    }
    rotation = 0; // fixes the rotation bug
}


void Tetromino::moveRight(int squares)
{
    for (int i = 0; i < 4; i++)
    {
        coordinates[i].first += squares;
    }
    updatePointsFromCoordinates();
}

void Tetromino::moveLeft(int squares)
{
    for (int i = 0; i < 4; i++)
    {
        coordinates[i].first -= squares;
    }
    updatePointsFromCoordinates();
}

void Tetromino::initPoints()
{
    // Init all squares at 0,0
    points[0] = vec2(-0.5,1.0); // top left
    points[1] = vec2(-0.5,0.9); // bottom left
    points[2] = vec2(-0.4,1.0); // top right
    points[3] = vec2(-0.4,1.0); // top right
    points[4] = vec2(-0.5,0.9); // bottom left
    points[5] = vec2(-0.4,0.9); // bottom right

    points[6] = vec2(-0.5,1.0); // top left
    points[7] = vec2(-0.5,0.9); // bottom left
    points[8] = vec2(-0.4,1.0); // top right
    points[9] = vec2(-0.4,1.0); // top right
    points[10] = vec2(-0.5,0.9); // bottom left
    points[11] = vec2(-0.4,0.9); // bottom right

    points[12] = vec2(-0.5,1.0); // top left
    points[13] = vec2(-0.5,0.9); // bottom left
    points[14] = vec2(-0.4,1.0); // top right
    points[15] = vec2(-0.4,1.0); // top right
    points[16] = vec2(-0.5,0.9); // bottom left
    points[17] = vec2(-0.4,0.9); // bottom right

    points[18] = vec2(-0.5,1.0); // top left
    points[19] = vec2(-0.5,0.9); // bottom left
    points[20] = vec2(-0.4,1.0); // top right
    points[21] = vec2(-0.4,1.0); // top right
    points[22] = vec2(-0.5,0.9); // bottom left
    points[23] = vec2(-0.4,0.9); // bottom right
}

// Make a new O block (square)
void Tetromino::initBlockO()
{
    shape = Shape::O;
    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(0,0); // Top left
    coordinates[1] = std::make_pair(1,0); // Top right // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(1,1); // Bottom right
    coordinates[3] = std::make_pair(0,1); // Bottom left
    updatePointsFromCoordinates();

    // Init colors
    color = vec3( 1.0, 1.0, 0.0); // Yellow
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color;
    }
    
    initVaosBuffersShaders();
}

void Tetromino::initBlockI()
{
    shape = Shape::I;

    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(1,0); // Top
    coordinates[1] = std::make_pair(1,1); // Second // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(1,2); // Third
    coordinates[3] = std::make_pair(1,3); // Fourth
    updatePointsFromCoordinates(); // Sets the squares in the correct position

    // Init colors
    color = vec3( 0.0, 1.0, 1.0); // Cyan
    //colors.resize(numPoints);
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color;
    }
    
    initVaosBuffersShaders();
}

void Tetromino::initBlockS()
{
    shape = Shape::S;
    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(1,2); // First
    coordinates[1] = std::make_pair(1,1); // Second // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(2,1); // Third
    coordinates[3] = std::make_pair(2,0); // Fourth

    // Init colors
    color = vec3( 0.0, 1.0, 0.0); // Green
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color;
    }
    initVaosBuffersShaders();

}

void Tetromino::initBlockZ()
{
    shape = Shape::Z;
    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(0,0); // First
    coordinates[1] = std::make_pair(1,0); // Second // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(1,1); // Third
    coordinates[3] = std::make_pair(2,1); // Fourth

    // Init colors
    color = vec3( 1.0, 0.0, 0.0); // Red
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color;
    }
    initVaosBuffersShaders();

}

void Tetromino::initBlockL()
{
    shape = Shape::L;
    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(2,1); // First
    coordinates[1] = std::make_pair(1,1); // Second // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(0,1); // Third  // 3 2 1
    coordinates[3] = std::make_pair(0,2); // Fourth // 4

    // Init colors
    color = vec3( 1.0, 0.6, 0.2); // Orange
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color;
    }
    initVaosBuffersShaders();
}

void Tetromino::initBlockJ()
{
    shape = Shape::J;
    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(0,1); // First
    coordinates[1] = std::make_pair(1,1); // Second // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(2,1); // Third
    coordinates[3] = std::make_pair(2,2); // Fourth
    // on its side pointing down

    // Init colors
    color = vec3( 0.0, 0.4, 1.0); // Dark blue
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color;
    }
    initVaosBuffersShaders();
}

void Tetromino::initBlockT()
{
    shape = Shape::T;
    initPoints();
    // Coordinates on the game grid (10x20), coordinates start at 0, 0,0 is top left corner
    coordinates[0] = std::make_pair(0,1); // First
    coordinates[1] = std::make_pair(1,1); // Second // "SECOND" block / rotation axis block
    coordinates[2] = std::make_pair(2,1); // Third
    coordinates[3] = std::make_pair(1,2); // Fourth
    // 1 2 3
    //   4

    // Init colors
    color = vec3( 0.78, 0.2, 1.0); // Purple
    for (int i = 0; i < numPoints; i++)
    {
        colors[i] = color; // Purple
    }
    initVaosBuffersShaders();
}

void Tetromino::initVaosBuffersShaders()
{
    // Set up vertex array object for block
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), points, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(points.data()) + sizeof(colors.data()), points.data(), GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors.data()), colors.data());
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

    // Initialize the vertex position attribute from the vertex shader
    // Keep in mind that the second parameter is associated with the length of the array sent to opengl (1D,2D,3D or 4D).
    // The last parameter is the offset where the data is stored on the buffer.
    program = InitShader( "vshader.glsl", "fshader.glsl" );

    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );
}

void Tetromino::updatePointsFromCoordinates()
{
    // all squares start at 0,0 and translate to desired points
    points[0] = vec2(-0.5,1.0); // top left
    points[1] = vec2(-0.5,0.9); // bottom left
    points[2] = vec2(-0.4,1.0); // top right
    points[3] = vec2(-0.4,1.0); // top right
    points[4] = vec2(-0.5,0.9); // bottom left
    points[5] = vec2(-0.4,0.9); // bottom right

    points[6] = vec2(-0.5,1.0); // top left
    points[7] = vec2(-0.5,0.9); // bottom left
    points[8] = vec2(-0.4,1.0); // top right
    points[9] = vec2(-0.4,1.0); // top right
    points[10] = vec2(-0.5,0.9); // bottom left
    points[11] = vec2(-0.4,0.9); // bottom right

    points[12] = vec2(-0.5,1.0); // top left
    points[13] = vec2(-0.5,0.9); // bottom left
    points[14] = vec2(-0.4,1.0); // top right
    points[15] = vec2(-0.4,1.0); // top right
    points[16] = vec2(-0.5,0.9); // bottom left
    points[17] = vec2(-0.4,0.9); // bottom right

    points[18] = vec2(-0.5,1.0); // top left
    points[19] = vec2(-0.5,0.9); // bottom left
    points[20] = vec2(-0.4,1.0); // top right
    points[21] = vec2(-0.4,1.0); // top right
    points[22] = vec2(-0.5,0.9); // bottom left
    points[23] = vec2(-0.4,0.9); // bottom right

    for (int coord = 0; coord < 4; coord++)
    {
        for (int i = coord*6; i < (coord+1)*6; i++)
        {
            // Have to translate 6 points for each coordinate
            points[i] = points[i] + (vec2(coordinates[coord].first*0.1, coordinates[coord].second*-0.1));
        }
    }
}


int Tetromino::getShape()
{
    return (int)shape;
}

void Tetromino::draw()
{
    updatePointsFromCoordinates();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), points, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(points.data()) + sizeof(colors.data()), points.data(), GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors.data()), colors.data());
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    glBindVertexArray(vao);
    glDrawArrays( GL_TRIANGLES, 0, numPoints );
}

void Tetromino::rotateCCW(TetrisGrid& staticGrid)
{
    // update coordinates
    // 
    rotateCoordinatesCCW(staticGrid);
    
    updatePointsFromCoordinates();

    //Always remember to update your canvas
    glutPostRedisplay();
}

void Tetromino::rotateCoordinatesCCW(TetrisGrid& staticGrid)
{
    
    int blockCheckX = coordinates[1].first; // #2 is always pivot
    int blockCheckY = coordinates[1].second;
    switch (shape) {
        case Shape::O:
            // no rotation necessary
            break;
        case Shape::I:
            switch (rotation) {
                case 0: // upright 
                    // #1
                    // #2
                    // #3
                    // #4
                    // Collision detection: If there is horizontal space around block to rotate, do so
                    // check horizontal from square #2
                    // check out of bounds
                    if (blockCheckX <= 0) // left edge of grid
                    {
                        blockCheckX = 1; // move reference 1 to the right
                    }
                    else if (blockCheckX == GRID_WIDTH-1 || blockCheckX == GRID_WIDTH-2) // right edge of grid
                    {
                        blockCheckX = GRID_WIDTH-3; // give clearance by moving to left
                    }
                    // Check static grid if have block on left side
                    else if (staticGrid.grid[blockCheckX-1][blockCheckY] >= 0)
                    {
                        // move reference to right
                        blockCheckX++;
                    }
                    else if (staticGrid.grid[blockCheckX+1][blockCheckY] >= 0)
                    {
                        // move referene to left
                        blockCheckX-=2;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+2][blockCheckY] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX-1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX+1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX+2; coordinates[3].second = blockCheckY;
                        rotation = 1;
                    }
                    // Else: Collision: Do nothing
                    
                    break;
                case 1: // 1 CCW from upright - rotate to upside down upright
                    // #1 #2 #3 #4
                    // Collision detection
                    // Will not rotate if not enough room above
                    // Check vertical clearance
                    if (staticGrid.grid[blockCheckX][blockCheckY-2] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0)
                    {
                        // Vertical
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY+1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX; coordinates[3].second = blockCheckY-2;
                        rotation = 2;
                    }
                    break;
                case 2: // (upside down upright) 
                    // #4
                    // #3
                    // #2 
                    // #1
                    // rotate to #4 #3 #2 #1
                    if (blockCheckX == GRID_WIDTH-1) // right edge of grid
                    {
                        blockCheckX = GRID_WIDTH-2; // move reference 1 to the left
                    }
                    else if (blockCheckX == 0 || blockCheckX == 1) // left edge of grid
                    {
                        blockCheckX = 2; // move to right to give clearance
                    }
                    // Check static grid if have block on left side
                    else if (staticGrid.grid[blockCheckX-1][blockCheckY] >= 0)
                    {
                        // move reference to right
                        blockCheckX+=2;
                    }
                    else if (staticGrid.grid[blockCheckX+1][blockCheckY] >= 0)
                    {
                        // move reference to left
                        blockCheckX--;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-2][blockCheckY] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX-1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX-2; coordinates[3].second = blockCheckY;
                        rotation = 3;
                    }

                    break;
                case 3: // #4 #3 #2 #1
                    // rotate to upright 1 2 3 4
                    // do not rotate if not enough room
                    if (staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+2] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0 )
                    {
                        // Vertical
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY-1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY+1;
                        coordinates[3].first = blockCheckX; coordinates[3].second = blockCheckY+2;
                        rotation = 0;
                    }
                    break;
            }
            break;
        case Shape::S:
            switch (rotation) {
                case 0:
                    //              #1
                    //    #2 #1 --> #2#3
                    // #4 #3          #4
                    // Don't rotate if no room            
                    if (staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY+1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY-1;
                        coordinates[2].first = blockCheckX+1; coordinates[2].second = blockCheckY;
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY+1;
                        rotation = 1;
                    }
                    break;
                case 1:
                    // 1         3 4
                    // 2 3 ->  1 2
                    //   4
                    if (staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY-1] < 0)
                    {
                        coordinates[0].first = blockCheckX-1; coordinates[0].second = blockCheckY;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY-1;
                        rotation = 2;
                    }
                    break;
                case 2:
                    //  3 4    4
                    //1 2  --> 3 2
                    //           1
                    if (staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY-1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY+1;
                        coordinates[2].first = blockCheckX-1; coordinates[2].second = blockCheckY;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY-1;
                        rotation = 3;
                    }
                    break;
                case 3:
                    // 4
                    // 3 2 ->  2 1
                    //   1   4 3
                    if (staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY+1] < 0 )
                    {
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY+1;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY+1;
                        rotation = 0;
                    }
                    break;
            }
            break;
        case Shape::Z:
            switch (rotation) {
                case 0:
                    // Don't rotate if no room            
                    if (staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY-1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY+1;
                        coordinates[2].first = blockCheckX+1; coordinates[2].second = blockCheckY;
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY-1;
                        rotation = 1;
                    }
                    break;
                case 1:
                    if (staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY-1] < 0)
                    {
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY-1;
                        rotation = 2;
                    }
                    break;
                case 2:
                    //     1    
                    //-> 3 2 
                    //   4
                    if (staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY+1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY-1;
                        coordinates[2].first = blockCheckX-1; coordinates[2].second = blockCheckY;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY+1;
                        rotation = 3;
                    }
                    break;
                case 3:
                    // -> 1 2
                    //      3 4
                    if (staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY+1] < 0)
                    {
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY-1;
                        rotation = 0;
                    }
                    break;
            }
            break;
        case Shape::L:
            switch (rotation) {
                // Shift like I block
                case 0: // on its side pointing down
                    if (staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY+1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY-1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY+1;
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY+1;
                        rotation = 1;
                    }
                    break;
                case 1: // upright L
                    
                    if (blockCheckX <= 0) // left edge of grid
                    {
                        blockCheckX = 1; // move reference 1 to the right
                    }
                    // Check static grid if have block on left side
                    else if (staticGrid.grid[blockCheckX-1][blockCheckY] >= 0)
                    {
                        // move reference to right
                        blockCheckX++;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY-1] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX-1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX+1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY-1;
                        rotation = 2;
                    }
                    break;
                case 2: // on its side pointing up to upright upside down
                    if (staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY-1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY+1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY-1;
                        rotation = 3;
                    }

                    break;
                case 3:
                    if (blockCheckX == GRID_WIDTH-1) // right edge of grid
                    {
                        blockCheckX = GRID_WIDTH-2; // move reference 1 to the left
                    }
                    else if (staticGrid.grid[blockCheckX+1][blockCheckY] >= 0)
                    {
                        // move reference to left
                        blockCheckX--;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY+1] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX-1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY+1;
                        rotation = 0;
                    }
                    break;
            }
            break;
        case Shape::J:
            switch (rotation) {
                case 0:
                    // on side pointing down
                    if (staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY-1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY+1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY-1;
                        rotation = 1;
                    }
                    break;
                case 1:
                    // upright pointing right
                    if (blockCheckX <= 0) // left edge of grid
                    {
                        blockCheckX = 1; // move reference 1 to the right
                    }
                    // Check static grid if have block on left side
                    else if (staticGrid.grid[blockCheckX-1][blockCheckY] >= 0)
                    {
                        // move reference to right
                        blockCheckX++;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY-1] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX-1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY-1;
                        rotation = 2;
                    }
                    break;
                case 2:
                    // on its side pointing up
                    if (staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY+1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY-1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY+1;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY+1;
                        rotation = 3;
                    }
                    break;
                case 3:
                    // upright pointing left
                    if (blockCheckX == GRID_WIDTH-1) // right edge of grid
                    {
                        blockCheckX = GRID_WIDTH-2; // move reference 1 to the left
                    }
                    else if (staticGrid.grid[blockCheckX+1][blockCheckY] >= 0)
                    {
                        // move reference to left
                        blockCheckX--;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY+1] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX-1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX+1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY+1;
                        rotation = 0;
                    }
                    break;
            }
            break;
        case Shape::T:
            switch (rotation) {
                case 0:
                    // 1 2 3 --> 3
                    //   4       2 4
                    //           1
                    if (staticGrid.grid[blockCheckX][blockCheckY+1] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY+1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY-1;
                        coordinates[3].first = blockCheckX+1; coordinates[3].second = blockCheckY;
                        rotation = 1;
                    }
                    break;
                case 1:
                    // 3         4
                    // 2 4 --> 3 2 1
                    // 1
                    // shifting like I/L/J on left side
                    if (blockCheckX <= 0) // left edge of grid
                    {
                        blockCheckX = 1; // move reference 1 to the right
                    }
                    // Check static grid if have block on left side
                    else if (staticGrid.grid[blockCheckX-1][blockCheckY] >= 0)
                    {
                        // move reference to right
                        blockCheckX++;
                    }
                    if (staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY-1] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX+1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX-1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX; coordinates[3].second = blockCheckY-1;
                        rotation = 2;
                    }
                    break;
                case 2:
                    // --> 1
                    //   4 2
                    //     3
                    if (staticGrid.grid[blockCheckX][blockCheckY-1] < 0 &&
                        staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0)
                    {
                        coordinates[0].first = blockCheckX; coordinates[0].second = blockCheckY-1;
                        coordinates[2].first = blockCheckX; coordinates[2].second = blockCheckY+1;
                        coordinates[3].first = blockCheckX-1; coordinates[3].second = blockCheckY;
                        rotation = 3;
                    }
                    break;
                case 3:
                    // -->1 2 3 
                    //      4    
                    if (blockCheckX == GRID_WIDTH-1) // right edge of grid
                    {
                        blockCheckX = GRID_WIDTH-2; // move reference 1 to the left
                    }
                    else if (staticGrid.grid[blockCheckX+1][blockCheckY] >= 0)
                    {
                        // move reference to left
                        blockCheckX--;
                    }
                    // Check horizontal clearance of 4 squares
                    if (staticGrid.grid[blockCheckX-1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX+1][blockCheckY] < 0 &&
                        staticGrid.grid[blockCheckX][blockCheckY+1] < 0)
                    {
                        // No collision: Enough clearance to rotate (remember down is ++ on the grid)
                        // Horizontal
                        coordinates[0].first = blockCheckX-1; coordinates[0].second = blockCheckY;
                        coordinates[1].first = blockCheckX; coordinates[1].second = blockCheckY;
                        coordinates[2].first = blockCheckX+1; coordinates[2].second = blockCheckY; 
                        coordinates[3].first = blockCheckX; coordinates[3].second = blockCheckY+1;
                        rotation = 0;
                    }
                    break;
            }
            break;
    }

}


GLuint Tetromino::getVao()
{
    return vao;
}

int Tetromino::getNumPoints()
{
    return numPoints;
}

vec2* Tetromino::getPoints()
{
    return points;
}


vec3* Tetromino::getColors()
{
    return colors;
}

vec3 Tetromino::getColor()
{
    return color;
}


GLuint* Tetromino::getProgram()
{
    return &program;
}
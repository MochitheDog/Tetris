#include <iostream>
#include "TetrisGrid.h"
// Class to represent the tetris grid, which cells are occupied
// Cells with num >= 0 are occupied, -1 is empty

// Constructor: Initialize grid as all empty (-1)
TetrisGrid::TetrisGrid()
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            grid[i][j] = -1;
        }
    }
    points.reserve(GRID_WIDTH*GRID_HEIGHT*6);
    colors.reserve(GRID_WIDTH*GRID_HEIGHT*6);
    landedCounter = 0; // save a couple of draw calls?
    
}

// Called whenever a Tetromino lands => +4 static squares
void TetrisGrid::increaseLandedCounter(int num)
{
    landedCounter += num;
}

void TetrisGrid::decreaseLandedCounter(int num)
{
    landedCounter -= num;
}

// For debugging
// void TetrisGrid::printGrid()
// {
//     for (int i = 0; i < GRID_HEIGHT; i++)
//     {
//         for (int j = 0; j < GRID_WIDTH; j++)
//         {
//             if (grid[j][i] >= 0)
//             {
//                 std::cout << " ";
//             }
//             std::cout << grid[j][i] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

void TetrisGrid::colorEntireGrid(vec3 color)
{
   for (int i = 0; i < colors.size(); i++)
   {
        colors[i] = color;
   }
   draw();
}

void TetrisGrid::resetGrid()
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            grid[i][j] = -1;
        }
    }
    points.clear();
    colors.clear();
    draw();
    landedCounter = 0;

}

// Generate vertices from static grid
// Called whenever a new block lands or a line is cleared
void TetrisGrid::generatePoints()
{
    // Reset vectors
    // These don't change capacity of vector, making push_backs fast
    points.clear();
    colors.clear();
    // Go backwards cuz blocks are at the bottom
    for (int j = GRID_HEIGHT-1; j >= 0; j--)
    {
        for (int i = GRID_WIDTH-1; i >= 0; i--)
        {
            if (grid[i][j] >= 0)
            {
                vec3 newColor = base_colors[grid[i][j]]; // color palette corresponds to shapes in Tetromino
                for (int p = 0; p < 6; p++)
                {
                    vec2 newPoint = templatePoints[p];
                    // Have to translate 6 points to proper positions
                    newPoint = newPoint + (vec2(i*0.1, j*-0.1));
                    points.push_back(newPoint);
                    colors.push_back(newColor);
                    
                }
            }  
        }
    }
}

// Return true if line is filled (clear-ready)
bool TetrisGrid::checkLineFilled(int y)
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        if (grid[i][y] < 0)
        {
            return false;
        }
    }
    return true;
}

// Shift grid down to clear line Y
void TetrisGrid::clearLine(int lineY)
{
    if (lineY < 0 || lineY >= GRID_HEIGHT) return;

    // Replacing lines at lineY and above by shifting the grid down
    for (int y = lineY; y >= 0; y--)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            // y == 0 == top of the grid, set to -1
            if (y == 0)
            {
                grid[x][y] = -1;
            }
            else
            {
                grid[x][y] = grid[x][y-1];
            }
            
        }
    }
}

void TetrisGrid::draw()
{
    if (landedCounter <= 0)
    {
        return;
    }

    // Create and bind a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and bind a buffer object
    
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
    size_t sizeofPoints = sizeof(vec2)*points.size(); // NOT sizeof(points)*points.size()
    size_t sizeofColors = sizeof(vec3)*colors.size();
    glBufferData( GL_ARRAY_BUFFER, sizeofPoints + sizeofColors, points.data(), GL_STATIC_DRAW );


    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeofPoints, points.data() );
    glBufferSubData( GL_ARRAY_BUFFER, sizeofPoints, sizeofColors, colors.data() );
    

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    // Keep in mind that the second parameter is associated with the length of the array sent to opengl (1D,2D,3D or 4D).
    // The last parameter is the offset where the data is stored on the buffer.
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
                           BUFFER_OFFSET(sizeofPoints) );

    //Draw triangles
    //Here we are binding back the first vertex array object. Now we can acess all the buffers associated to it and render accordingly
    glBindVertexArray( vao );
    glDrawArrays( GL_TRIANGLES, 0, points.size() );

    //Causes all issued commands to be executed as quickly as they are accepted by the actual rendering engine
    glFlush();
}
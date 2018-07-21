// Tetris thing

#include "Angel.h"
#include <iostream>
#include "TetrisGrid.h"
#include <vector>
#include <utility> // for Pair
#include "globals.h"
#include "Tetromino.h"
#include <random>

//It is nice to define and use a color pallete on your software. You can put this information on another utility file.
const vec3 base_colors[] = {
    vec3( 1.0, 1.0, 0.0 ), // yellow 0
    vec3( 0.0, 1.0, 1.0 ), // Cyan 1
    vec3( 0.0, 1.0, 0.0 ), // Green 2
    vec3( 1.0, 0.0, 0.0 ), // red 3
    vec3( 1.0, 0.6, 0.2 ), // Orange 4
    vec3( 0.0, 0.4, 1.0 ), // Dark blue 5
    vec3( 0.78, 0.2, 1.0), // Purple 6
    vec3( 0.0, 0.0, 0.0 ), // black 7
    vec3( 1.0, 1.0, 1.0 ),  // white 8
    vec3( 0.65, 0.65, 0.65) // gameover grey 9
};


const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20; // 23?
const int EXTENDED_GRID_HEIGHT = 23;

//2 triangles (black rectangle)
const int NumBlackRectPoints = 6;

//lines for grid
const int NumGridPointsV = 22;
const int NumGridPointsH = 40;
const int NumGridPoints = NumGridPointsH + NumGridPointsV;

//vertex array for the black bg and for the grid lines, respectively
GLuint vaoBlackBG, vaoGridLines, vaoTestBlock;

// black rectangle points and colors arrays
vec2 blackrectPoints[NumBlackRectPoints];
vec3 blackrectColors[NumBlackRectPoints];

//lines points and colors arrays
vec2 gridpoints[NumGridPoints];
vec3 gridcolors[NumGridPoints];

//
static const vec2 downStep = vec2( 0.0, -0.1 );
static const vec2 rightStep = vec2( 0.1, 0.0 );
static const vec2 leftStep = vec2( -0.1, 0.0 );

GLuint currentTetrominoVao; // VAO for current (moving, controllable) tetromino
Tetromino* currentTetromino;

std::vector<GLuint> vaosVec;
std::vector<int> pointsVec;
//GLuint program;

// Static grid for collision
TetrisGrid tetrisGrid;
//std::vector<std::vector<StaticSquare* > > staticTetrominos(GRID_HEIGHT,std::vector<StaticSquare*>(GRID_WIDTH,nullptr));

// Number of squares each Tetromino is made up of
const int blockSize = 4;

bool gameIsRunning;
bool isGameOver = false;

std::uniform_int_distribution<int> rando; // random generator
std::mt19937 rng;
std::uniform_int_distribution<int> randPos; // random positions for tetrominos
std::uniform_int_distribution<int> randRot; // rand rotation for tetrominos

int gameSpeed = 1; // default SLOW speed
const int gameSpeedMax = 8;
//----------------------------------------------------------------------------

// Spawn a new block
Tetromino* spawnNewTetromino()
{
    int randomInt = rando(rng); // between 0 and 6 inclusive
    Tetromino* newBlock;
    switch (randomInt) {
        case 0: newBlock = new Tetromino(Shape::O);
                break;
        case 1: newBlock = new Tetromino(Shape::I);
                break;
        case 2: newBlock = new Tetromino(Shape::S);
                break;
        case 3: newBlock = new Tetromino(Shape::Z);
                break;
        case 4: newBlock = new Tetromino(Shape::L);
                break;
        case 5: newBlock = new Tetromino(Shape::J);
                break;
        case 6: newBlock = new Tetromino(Shape::T);
                break;
    }
    
    // Random starting rotation
    int randrot = randRot(rng);
    for (int i = 0; i < randrot; i++)
    {
        newBlock->rotateCCW(tetrisGrid);
    }
    // Random starting position
    int randpos = randPos(rng);
    newBlock->moveRight(randpos);
    for (int i = 0; i < 4; i++)
    {
        if (newBlock->coordinates[i].first >= GRID_WIDTH)
        {
            newBlock->moveLeft(1);
            i--;
        }
    }
    

    currentTetromino = newBlock;
    return newBlock;
    
}

void init( void )
{
    // Hard code the grid
    // Background rectangle (black)
    blackrectPoints[0] = vec2(-0.51,1.0); // Top left
    blackrectPoints[1] = vec2(0.51, 1.0); // Top right
    blackrectPoints[2] = vec2(-0.51,-1.0); // Bottom left
    blackrectPoints[3] = vec2(0.51, 1.0); // Top right
    blackrectPoints[4] = vec2(-0.51,-1.0); // Bottom left
    blackrectPoints[5] = vec2(0.51, -1.0); // Bottom right

    //color stuff for each vertex of each of the triangles
    blackrectColors[0] = base_colors[7];
    blackrectColors[1] = base_colors[7];
    blackrectColors[2] = base_colors[7];

    blackrectColors[3] = base_colors[7];
    blackrectColors[4] = base_colors[7];
    blackrectColors[5] = base_colors[7]; // Black

    //***************************

    
    //line starting points and ending points. The first two positions represent one line segment,
    //while the last two positions represent another line segment.
    // Make a 20x10 grid in the black rectangle
    int i = 0;
    float x = -0.5;
    while (i < NumGridPointsV)
    {
        // 11 vertical lines from -0.5 to 0.5, spaced 0.1 apart
        gridpoints[i++] = vec2(x, -1.0);
        gridpoints[i++] = vec2(x, 1.0);
        x += 0.1;
    }
    // Make horizontal lines
    float y = -1.0;
    while (i < NumGridPoints)
    {
        // 20 horizontal lines 
        gridpoints[i++] = vec2(-0.5,y);
        gridpoints[i++] = vec2(0.5, y);
        y += 0.1;
    }
    // Make grid lines white
    for (int i = 0; i < NumGridPoints; i++)
    {
        gridcolors[i] = base_colors[8]; // white
    }

    glGenVertexArrays( 1, &vaoBlackBG);
    glBindVertexArray( vaoBlackBG);
     // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(blackrectPoints) + sizeof(blackrectColors), blackrectPoints, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(blackrectPoints), sizeof(blackrectColors), blackrectColors);

    // Load shaders and use the resulting shader program
    GLuint program1 = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program1 );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc1 = glGetAttribLocation( program1, "vPosition" );
    glEnableVertexAttribArray( loc1 );
    glVertexAttribPointer( loc1, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor1 = glGetAttribLocation( program1, "vColor" );
    glEnableVertexAttribArray( vColor1 );
    glVertexAttribPointer( vColor1, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(blackrectPoints)) );

    //Here we create another vertexArrayObject to render some lines. This is intended to be your grid, so since the
    //grid positions never change, you can leave this vertex array object on the initialization.
    // Create and bind a vertex array object
    glGenVertexArrays( 1, &vaoGridLines );
    glBindVertexArray( vaoGridLines );

    // Create and initialize a buffer object
    GLuint buffer2;
    glGenBuffers( 1, &buffer2 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
    
    //glBufferData( GL_ARRAY_BUFFER, sizeof(gridpoints), gridpoints, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(gridpoints) + sizeof(gridcolors), gridpoints, GL_STATIC_DRAW );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(gridpoints), gridpoints );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(gridpoints), sizeof(gridcolors), gridcolors);



    // Load shaders and use the resulting shader program
    GLuint program2 = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program2 );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc2 = glGetAttribLocation( program2, "vPosition" );
    glEnableVertexAttribArray( loc2 );
    glVertexAttribPointer( loc2, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor2 = glGetAttribLocation( program2, "vColor" );
    glEnableVertexAttribArray( vColor2 );
    glVertexAttribPointer( vColor2, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(gridpoints)) );

    
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
    spawnNewTetromino();
}

//----------------------------------------------------------------------------



// Check the collision of the current block with the bottom of the grid
// return TRUE if collides with floor
bool checkCollideFloor()
{
    // For each of 4 component squares
    for (int i = 0; i < blockSize; i++)
    {
        if (currentTetromino->coordinates[i].second >= 19)
        {
            return true;
        }
    }
    return false;
}

// CHeck the collision of the current block with the grid of static blocks
// direction can be D, L, or R (for down/left/right check)
bool checkCollisionStaticGrid(char direction)
{
    switch (direction) {
        case 'D':  
            for (int i = 0; i < blockSize; i++)
            {
                int x = currentTetromino->coordinates[i].first;
                int y = currentTetromino->coordinates[i].second;
                // Check out-of-bounds
                if (y+1 >= GRID_HEIGHT)
                {
                    return true;
                }
                // Check collision against other blocks
                if (tetrisGrid.grid[x][y+1] >= 0)
                {
                    return true;
                }
            }
            return false;
            break;
        case 'L':
            for (int i = 0; i < blockSize; i++)
            {
                int x = currentTetromino->coordinates[i].first;
                int y = currentTetromino->coordinates[i].second;
                if (x-1 < 0) return true;
                if (tetrisGrid.grid[x-1][y] >= 0)
                {
                    return true;
                }
            }
            return false;
            break;
        case 'R':
            for (int i = 0; i < blockSize; i++)
            {
                int x = currentTetromino->coordinates[i].first;
                int y = currentTetromino->coordinates[i].second;
                if (x+1 >= GRID_WIDTH) return true;   
                if (tetrisGrid.grid[x+1][y] >= 0)
                {
                    return true;
                }
            }
            return false;
            break;
        default:
            return false;
    }
}

// Adds the landed current block to the static grid
void addBlockToGrid()
{
    //std::cout << "shape = " << currentTetromino->getShape() << std::endl;
    for (int i = 0; i < blockSize; i++)
    {
        int x = currentTetromino->coordinates[i].first;
        int y = currentTetromino->coordinates[i].second;
        vec3 color = currentTetromino->getColor();

        tetrisGrid.grid[x][y] = currentTetromino->getShape(); // Color palette is set to correspond to shapes in Tetromino
        
    }
    tetrisGrid.increaseLandedCounter(4);
    tetrisGrid.generatePoints(); // re-generate static blocks
    
}

void display( void )
{
    if (currentTetromino == nullptr)
    {
        std::cout << "tetromino nullptr" << std::endl; // ????
    }

    // TODO: Check for game over

    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    
    //Draw lines using the second vertex array object. On your tetris code, you probabily want to draw the lines first, then the triangles.
    //If you want to change the thickness of the lines, this is how:  glLineWidth(5.0);    
    glBindVertexArray( vaoBlackBG );
    glDrawArrays( GL_TRIANGLES, 0, NumBlackRectPoints );

    currentTetromino->draw();

    // Draw static blocks
    tetrisGrid.draw();

    glBindVertexArray( vaoGridLines );
    glDrawArrays( GL_LINES, 0, NumGridPoints );
    
    //Causes all issued commands to be executed as quickly as they are accepted by the actual rendering engine
    glFlush(); // Render RIGHT NOW
}

// Do clear lines operations
void checkClearLines()
{
    for (int i = GRID_HEIGHT-1; i >= 0; i--)
    {
        if (tetrisGrid.checkLineFilled(i))
        {
            tetrisGrid.clearLine(i);
            i++;
        }

    }
    tetrisGrid.generatePoints();
}


// GameOver if Tetromino spawns inside of another piece
bool checkGameOver()
{

    for (int i = 0; i < blockSize; i++)
    {
        int x = currentTetromino->coordinates[i].first;
        int y = currentTetromino->coordinates[i].second;
        std::cout << x << " " << y << std::endl;
        if (tetrisGrid.grid[x][y] >= 0)
        {

            return true;
        }
        
    }    
    return false;
}

void gameOver()
{
    tetrisGrid.colorEntireGrid(base_colors[9]);
    isGameOver = true;
}

void restartGame()
{
    tetrisGrid.resetGrid();
    isGameOver = false;
    gameIsRunning = true;
    gameSpeed = 1;
    spawnNewTetromino();
    glutPostRedisplay();
}

// move block one cell down every second
void moveDownDelay(int)
{
    if (gameIsRunning && !isGameOver)
    {
        // Check colllision/Bottom of screen
        if (checkCollideFloor() || checkCollisionStaticGrid('D'))
        {
            // Collision detected: Don't move
            addBlockToGrid();

            // Clear lines if necessary
            checkClearLines();

            spawnNewTetromino();

            if (checkCollisionStaticGrid('D'))
            {
                if (checkGameOver)
                {
                    gameOver();
                }
            }
            

        }
        else
        {
            // Update coordinates, move block down 1
            for (int i = 0; i < blockSize; i++)
            {
                currentTetromino->coordinates[i].second += 1;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000.0/gameSpeed, moveDownDelay, 0);
}


//If you want to use arrows, take a look at this function
//It works similarly, but you have no acess to the ASCII keys using it. Please see the link below for details.
//https://www.opengl.org/resources/libraries/glut/spec3/node54.html
void keyboardSpecial( int key, int x, int y )
{
    if (!isGameOver)
    {
        if (gameIsRunning)
        {
            switch ( key ) {
            //similar to the stuff inside the keyboard class, but applying the translaton only to the third triangle.
            case  GLUT_KEY_DOWN:
                if (!(checkCollideFloor() || checkCollisionStaticGrid('D')) ) // if no collision detected
                {
                    // Update coordinates shift Y down
                    for (int i = 0; i < blockSize; i++)
                    {
                        currentTetromino->coordinates[i].second += 1;
                    }
                }
                
                //Always remember to call glutpostRedisplay after changes. It will just call the "display" method again. 
                glutPostRedisplay();
                break;
            case GLUT_KEY_RIGHT:
                if (!checkCollisionStaticGrid('R'))
                {
                    // Update coordinates shift X right
                    for (int i = 0; i < blockSize; i++)
                    {
                        currentTetromino->coordinates[i].first += 1;
                    }
                }
                glutPostRedisplay();
                break;
            case GLUT_KEY_LEFT:
                if (!checkCollisionStaticGrid('L'))
                {
                    // Update coordinates shift X right
                    for (int i = 0; i < blockSize; i++)
                    {
                        currentTetromino->coordinates[i].first -= 1;
                    }
                }
                glutPostRedisplay();
                break;
            case GLUT_KEY_UP:
                currentTetromino->rotateCCW(tetrisGrid); // update coordinates too

                break;
            case 033:
                exit( EXIT_SUCCESS );
                break;
            case GLUT_KEY_PAGE_UP:
                if (gameSpeed < gameSpeedMax)
                {
                    std::cout << "Game speed increased" << std::endl;
                    gameSpeed++;
                }
                break;
            case GLUT_KEY_PAGE_DOWN:
                if (gameSpeed > 1)
                {
                    std::cout << "Game speed decreased" << std::endl;
                    gameSpeed--;
                }
                break;
            }
        }
    }
    else
    {
        if (key == 033)
        {
            exit( EXIT_SUCCESS );
            return;
        }
    }
    
}

//bind most keys on your keyboard to this function
void
keyboard( unsigned char key, int x, int y )
{
    
    switch ( key ) {
    
    case 'q':
        exit( EXIT_SUCCESS );
        break;

    case 'r':
        restartGame();
        break;
    case 'p':
        gameIsRunning = !gameIsRunning;
        break;
    // case 't':
    //     tetrisGrid.printGrid(); // For debugging
    //     break;
    //Esc pressed!
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    // Init random generator https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device random;  // seed engine
    rng = std::mt19937(random()); // Mersenne-Twister random number generator
    rando = std::uniform_int_distribution<int>(0,6); // Random numbers for spawning Tetrominos
    randPos = std::uniform_int_distribution<int>(0,7); // Random numbers for choosing Tetromino start position, rotation
    randRot = std::uniform_int_distribution<int>(0,3); // " " rotation
    
    glutInit( &argc, argv );
    //We explicitly tell OpenGL that we are using the RGBA mode. When we start working with 3D resources there will be changes here.
    glutInitDisplayMode( GLUT_RGBA );

    //Change the size of the screen here. Keep in mind that the coordinates will also change accordingly
    //so, if you want to keep your points on the rendering canvas undisturbed you need a square screen.
    glutInitWindowSize( 600, 600 );

    // If you are using freeglut, the next two lines will check if 
    // the code is truly 3.2. Otherwise, comment them out
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    //Title of your screen, change accordingly
    glutCreateWindow( "Tetris" );

    // Iff you get a segmentation error at line 34, please uncomment the line below
    glewExperimental = GL_TRUE; 
    glewInit();
    
    //this is the initialization function for your data.
    init();

    gameIsRunning = true;

    //Here we bind the function "display" to the OpenGL handler that will render your data
    glutDisplayFunc( display );

    //Similarly, we can also bind a function that will be executed 1000 miliseconds later. We bind this to the function rotateDelay.
    // We then bind this to the function "rotateDelay". The 0 in the end is the input of the rotateDelay class, it can only be an integer.
    
    glutTimerFunc(1000.0, moveDownDelay, 0);

    //Finally, we bind the keyboard events inside the class "keyboard" using the line below
    glutKeyboardFunc( keyboard );

    //If you really want to use F1 ~ F9 keys, or the arrow keys, then use the line of code below.
    glutSpecialFunc( keyboardSpecial );

    glutMainLoop();
    return 0;
}

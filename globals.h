// common globals
#include <random>
#include "Angel.h"
//extern GLuint program;

extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

extern std::uniform_int_distribution<int> rando; // random generator
extern std::mt19937 rng;

extern std::uniform_int_distribution<int> randPos; // random positions for tetrominos
extern std::uniform_int_distribution<int> randRot; // random rotation states for tetrominos

extern const vec3 base_colors[]; // defined in Tetris.cpp
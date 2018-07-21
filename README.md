# Tetris game in OpenGL for a graphics class assignment

## Dependencies:
- OpenGL 3
- freeglut
- GLEW

## Setup:
- use 'make tetris' to build
- type ./tetris in terminal to play

## How to Play:
- Use LEFT and RIGHT arrow keys to move the Tetromino.
- Press UP arrow to rotate the Tetromino counter-clockwise.
- Press DOWN arrow to make the Tetromino move down faster.
- Press ESC or Q to quit the game.
- Press R to restart the game.
- Press PAGE UP and PAGE DOWN to increase and decrease the game speed
	(make the Tetrominos fall faster)

- Starting position and orientation of new Tetris pieces are randomized

- The game is over when a new Tetromino spawns inside an existing tile
(because the position and orientation is random, luck plays a factor here-
	the game does not try to spawn in an empty space)


## Extra features:
- Press P to pause
- Instead of terminating the program upon Game Over, the game turns grey and stops.
	Press R to restart the game or ESC/Q to quit.

- When an I, L, or J piece is at the edge of the grid such that rotating it would put it out of bounds,
	the piece will shift over to allow the piece to rotate as long as there is sufficient space to do so.

![screenshot](https://raw.githubusercontent.com/MochitheDog/Tetris/master/tetrispic.png)

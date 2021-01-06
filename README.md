# Tetris Game
A Tetris Console game that was the main project of the Object-Oriented Programming in C++ course.
The game was done in the first year of my BSc Computer Science degree.

## Credits
This game project was made by Liat Matzov ([liat92](https://github.com/liat92)) and Linoy Mizrahi ([](link)) .

## More Gameplay Information
This Tetris is a game that has random block shapes falling during the game and the player needs to fit every block to another so there are no empty spaces.
The kind of blocks: "Square", "Stick", “L-shape”, “Z-shape”, “Plus”, "Joker" and the "Bomb".
Rotation options: 0° / 90°/ 180°/ 270°.

### How is it work? 
Every line that is full will be automatically removed and the others above it will get down number of steps as the number of lines that were full(and were removed).
BE CAREFUL! Once you've got to the upper limit of the board and there is no space for the other coming 
block you will L-O-S-E. The score is calculated by a few certain terms (will be clarified next).

### Special blocks

#### Bomb
You have the bomb "in your side" that when it hits a square it will explode all the blocks that in its territory (3X3 in this game),
BUT remember... it will reduce your score.

#### Joker
The joker is another block that will help you - it can move through blocks and stay where you want by pressing 'e' and in this way it will fill the empty square in the zone,
it stops automatically ONLY when getting to the bottom of the board.

##### Note:
We decided to allow the joker to fall down and to the bomb either,
even when there is an obstacle for them in the upper limit ,
In order to let the user the opportunity to be saved.

### Goal
The GOAL of the game is to get the highest score by getting rid of most of the blocks in the game.

### Operating the block:
* Moving: Right, left and hard drop.
* Rotating:  Generally all blocks get rotated from one root, but since just the shapes: Square, Joker and Bomb can't be seen after rotation then they won't be rotated. 
 The rotation method is from the mentioned root and can be 0° / 90° / 180° / 270° from the basic shape.
* Joker's freezing: Only the joker can be freezed in the user requested place.

### Operating the game:
* Start: Choose to start a new game at any minute. 
* Speed up and down : Control the game speed- speed it up or slow it down.
* Pause/Continue : Pause the game at any moment and continue it from the point you stopped with the same key.
* Exit: Exit the game at any moment.

### Game Keys:
Key | Definition
----|-------------
1 | Start\Restart
2 | Pause/Continue
3 | Speed UP
4 | Slow Down
5 | Save
6 | Load
9 | Exit
r | Rotate
e | Stop move (joker only)
f | Hard drop down
a | Left
d | Right
                                    
### Score calculation:

* Hard Drop:              2 * Distance
* Lines cleared:          100 + (number of lines cleared - 1) * 200
* Bomb Explosion         (-50) * (number of block parts exploded)
* Joker Line Cleared      50

Note: The category of joker’s clear means that if the joker is the block shape that will make the line full than clear the line and update the score.

## Screenshots
### Game Menu
![Game Menu](/Screenshots/Game_Menu.PNG)

### Game Gameplay
![Game Gameplay](/Screenshots/Game_Gameplay.PNG)

### Game Over Screen
![Game Over Screen](/Screenshots/Game_Over_Screen.PNG)

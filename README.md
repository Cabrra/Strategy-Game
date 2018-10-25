Strategy Game
=============

![Strategy Game Chart](/Images/flowchart.jpg)

This is a very simple two-player turn-based strategy game. Each player controls a three-character team on a 6x6 playfield. Each team consists of an Archer, Sorcerer, and Warrior. 

## Gameplay

One round of the game involves all of the characters that are still alive (initially 6) to be allowed a turn. The order of the turns during a round is set randomly. 

A turn has 2 stages: 
+ Move phase
+ Attack phase

The move phase occurs first. During the move phase, the user is asked if he/she would like to move the character.  
If the user says yes, then the user picks a space to move to. A character can only move 1 space during a turn. They can only move left, right, up, or down (no diagonals). 
They can only move to an empty space. If a player is unable to move (is trapped), the character is not allowed to move.

The attack phase allows the user to pick a character on the screen to attack. The characters which can be attacked are those within the range of attack. This is determined by comparing the 
location of the attacking character with the locations of the other characters in the game. The distance between two characters is determined by the following formula:

> distance = abs (x2 – x1) + abs (y2 – y1)

Finally, attack is based on the following numbers:
> A Warrior (W or w) has an attack range of 1. Attack range is 7 to 14.
> A Sorcerer (S or s) has an attack range of 2. Attack range is 1 to 10.
> An Archer (A or a) has an attack range of 4. Attack range is 2 to 7.

A character which has 0 hit points is represented as a ‘D’ or ‘d’ on the battlefield (depending on which team they are on).
The game ends when a team has no players left alive to continue fighting.

+ The turn order and each character’s remaining/max hit points are displayed at all times during the game
+ The character whose turn it is currently is highlighted in the turn-order

Sample screen:
AW****		Turn Order
S*****		a   <-
******		W
******		s
*****s		w
****wa		A
 			S

P1: A: 20/20, W 20/20, S 20/20
P2: a: 20/20, w 20/20, s 20/20

+ "*" represents an empty space on the play field.  A, W, and S are for Player 1’s Archer, Warrior, and Sorcerer. a, w, and s are for Player 2’s team.
+ Moving and Attacking are optional.
+ Dead characters do not get a turn
+ The corpse stays on the field until the game is over
+ Attacking a dead player is not allowed (this is pointless and more than a little psycho)

## Prerequisites

This project is based on some custom data structures implemented on one of my [repos](https://github.com/Cabrra/Data-Structures).

## Built With

* [Visual Studio](https://visualstudio.microsoft.com/)	- C++ development
* Run with Windows CMD

## Contributing

Please read [CONTRIBUTING.md](https://github.com/Cabrra/Contributing-template/blob/master/Contributing-template.md) for details on the code of conduct, and the process for submitting pull requests to me.

## Authors

* **Jagoba "Jake" Marcos** - [Cabrra](https://github.com/Cabrra)

## License

This project is licensed under the MIT license - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Full Sail University - Game Development Department
* Rodney Stoeffler

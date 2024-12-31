# Battleship Game

This repository contains the implementation of the classic **Battleship game** in **C++**, developed with a focus on **Object-Oriented Programming (OOP)** principles.

## Features
- **Game Type**: Two-player interactive game on a 10x10 board.
- Players take turns placing ships and attacking the opponent's board until one player sinks all of the opponent's ships.

## Code Structure
### Classes
1. **`Barco` (Ship)**:
   - Represents ships with attributes like type, length, coordinates, and orientation.
   - Handles ship placement, registering hits, and checking if a ship is sunk.

2. **`Tablero` (Board)**:
   - Manages the game board, ship placement, and attack processing.
   - Includes methods for validating ship positions and displaying the board.

3. **`Jugador` (Player)**:
   - Represents each player with their own board.
   - Allows players to attack the opponent's board.

4. **`Referi` (Referee)**:
   - Verifies if a player has won by checking if all opponent ships are sunk.

5. **`Juego` (Game)**:
   - Controls the main game flow, including ship placement and turn alternation.

### Rules
- Players place ships (Battleship, Submarine, Patrol Boat) on valid positions without overlaps or going out of bounds.
- Attacks are performed in turns, resulting in "miss," "hit," or "ship sunk."
- The winner is the first player to sink all of their opponent's ships.


## Technical Highlights
- Utilizes modern C++ structures like `std::vector` for dynamic data handling.
- Includes robust input validation for user interactions.
- Modular design ensures clarity, maintainability, and extensibility.

## Example Usage
1. Players are prompted to place their ships on a 10x10 board.
2. Each player takes turns attacking the opponent's board by entering coordinates.
3. The game announces the winner once all ships of one player are sunk.




# Chess++

A GUI- and terminal-based chess application built using **C++** according to OOP principles.

## Usage

Download and open the `Code` folder on a Unix system. Then run `make` to compile. Finally, run `./chess` to start the program.

## Features

- Full support for chess rules, including en passent, castling, pawn promotions, etc.
- Four levels of CPU players with increasing difficulty
- Setup mode to create custom starting setups and puzzles
- GUI to display chess board and highlight moves
- Terminal text-based display and command entry
- Cumulative scoring over multiple games
- Move undo support

## Design

- Adheres to OOP principles to reduce coupling and increase cohesion, facilitating future changes
- Utilizes smart pointers to avoid manual memory management and memory leaks
- Leverages design patterns such as MVC and the observer pattern to modularize components
- A full [UML](https://github.com/smchase/Chess/blob/main/uml.pdf) showing the design of the program

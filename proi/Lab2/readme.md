##Lab 2 - Check possibility to fill rectangle area with some kind of polyomino

### Task

Design the interface for classes representing a figure: domino, tromino, tetramino etc.

Interface should implement a class that store specific figures.

Using this interface implement the algorithm covering the board of size an n×m with figures of such type. Algorithm can be, for example, with backtracking (you can propose a different algorithm). The algorithm must use only interface methods of figures.
The result should be information, whether the setting is possible to set parameters and, if so, one of the solutions.

The interface should be designed to allow the creation of figures any number of unit squares.

### Requirements

- program should be correctly and logically separated into modules (header file, class implementation, testing file)
- clear code layout, concise and clear comments
- using appropriate naming of variables, functions, classes
- dynamic memory allocation, user-defined constructors & destructors, appropriate assignment operators
- public and private parts in classes
- testing program must have at least 5 different non-trivial test cases to show pros and cons of implemented interface
- testing program must provide posibility to provide testing date from keyboard
- compilation using Makefile

### Additional information

Domino is a figure obtained by gluing unit squares, tromino this figure was created by gluing three squares unit along some sides (there are two types of tromin: simple and shaped L), tetromino is of four squares (tetromino present in the game Tetris).

>_From Wikipedia, the free encyclopedia -  [More info here](https://en.wikipedia.org/wiki/Polyomino "Wikipedia")_
>
>**A polyomino** is a plane geometric figure formed by joining one or more equal squares edge to edge. It is a polyform whose cells are squares. It may be regarded as a finite subset of the regular square tiling with a connected interior.
>
>Polyominoes are classified according to how many cells they have:
>
>| Number of cells | Name |
>|  :---: | :---: |
>|    1 |	  monomino    |
>|    2 |	  domino      |
>|    3 |	  tromino     |
>|    4 |	  tetromino   |
>|    5 |	  pentomino   |
>|    6 |	  hexomino    |
>|    7 |	  heptomino   |
>|    8 |	  octomino    |
>|    9 |	  nonomino    |
>|    10 |	decomino    |
>|    11 |	undecomino  |
>|    12 |	dodecomino  |
>
>**Example** (_The 18 one-sided pentominoes, including 6 mirrored pairs_)
>![pentominoes](https://upload.wikimedia.org/wikipedia/commons/a/aa/All_18_Pentominoes.svg "The 18 one-sided pentominoes, including 6 mirrored pairs")
>

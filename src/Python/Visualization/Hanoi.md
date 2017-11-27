### Description

This is three-dimensional implementation of the Towers of Hanoi.

Here we visualize the operation of the recursive Towers of Hanoi puzzle. In this puzzle there are three pegs. In the initial position there are one or more disks(or pucks) of varying diameter on the pegs. The disks are sorted according to disk diameter, so that
the largest disk is on the bottom, followed by the next largest, and so on. The goal of the puzzle is to move the disks from one peg to another, moving the disks one at a time, and never placing a larger disk on top of a smaller disk.

Here we first set up the scene with the table, pegs and pucks. Then we use a function called `Hanoi()` to begin the recursion. A second function `MovePuck()` moves the puck from one peg to another.

To give a pleasing visual effect we move the disk in small, user-specified increments, flipping the disc over as it moves
from one peg to the next. Option `-s` controls the user-defined increments. The option `-c 2` freezes a disk in mid air moving from one peg to another.

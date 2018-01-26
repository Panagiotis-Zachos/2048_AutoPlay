# 2048_AutoPlay
A small programm that tries to solve the 2048 game via statistical analysis.

The function that selects the best possible move works as follows:

For each possible (legal) action (move), it copies the original matrix int a temporary matrix (temp) and
moves the matrix to that direction as the initial move.

After making the initial move, 1000 games are simulated with the same initial move, until each one of them is lost. The moves
after the initial one are selected at random. In the end the final scores of each game is added.

The best move is selected as the one that procured the highest total score.

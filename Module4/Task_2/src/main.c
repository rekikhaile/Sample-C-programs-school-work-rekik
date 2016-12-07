#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"

int main(void)
{
    /* Feel free to modify this function to test different things */
    
    Field *f = createField(10,10);
    if (!f)
        return EXIT_FAILURE;
    
    /* Let's lay some mines! */
    deployMines(f, 10);
    
    /* Let's play the game: ask coordinates from user repeatedly.
     * Then check the location and print the current state of the field
     * (You can modify this loop to exit when user hits a mine) */
    while (1) {
        int x, y;
        scanf("%d %d", &x, &y);
        checkPlace(f, x, y);
        printField(f);        
    }
}

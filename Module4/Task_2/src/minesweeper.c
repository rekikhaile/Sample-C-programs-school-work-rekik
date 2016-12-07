#include <stdlib.h>
#include "minesweeper.h"

/* Print the current state of the field */
void printField(const Field *f)
{
    unsigned int i, j, n;
    for (i = 0; i < f->ysize; i++) {
        for (j = 0; j < f->xsize; j++) {
            char c = '.';
            switch (f->places[i][j]) {
                case UNKNOWN_FREE:
                case UNKNOWN_MINE:
                    c = '?';
                    break;
                    
                case KNOWN_MINE:
                    c = '*'; break;
                    
                case KNOWN_FREE:
                    c = '.';
                    break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}


/* Deploy mines to random locations in the given field
 * 
 * Parameters:
 * f: Minefield that has been created earlier
 * mines: number of mines to be deployed */
void deployMines(Field *f, unsigned int mines)
{
    unsigned int i;
    for (i = 0; i < mines; i++) {
        int x, y;
        do {
            x = rand() % f->xsize;
            y = rand() % f->ysize;
        } while(f->places[y][x] != UNKNOWN_FREE);
        
        f->places[y][x] = UNKNOWN_MINE;
    }
}


/* Create new field with given dimensions
 * 
 * Parameters:
 * xsize: horizontal size of the field
 * ysize: vertical size of the field
 * 
 * Returns:
 * Pointer to the newly allocated minefield */
Field *createField(unsigned int xsize, unsigned int ysize)
{
return NULL;   // replace this
}

/* Checks the status of given location. At the same time, change the
 * status from UNKNOWN_MINE to KNOWN_MINE, or UNKNOWN_FREE to KNOWN_FREE
 * 
 * Parameters:
 * f: Minefield that has been allocated earlier
 * x, y: the coordinates of the place to be checked
 * 
 * Returns:
 * 1 if there was a mine; 0 if the location was free; -1 if given
 * coordinates are out of bounds */
int checkPlace(const Field *f, unsigned int x, unsigned int y)
{
}

/* Count how many of the neighboring locations have mines.
 * 
 * Parameters:
 * f: pointer to the field allocated earlier
 * x, y: coordinates of the place to be checked
 * 
 * Returns:
 * Number of mines in the neighborhood. At maximum there are 8 neighboring
 * locations. */
int countNeighbours(const Field *f, unsigned int x, unsigned int y)
{
}

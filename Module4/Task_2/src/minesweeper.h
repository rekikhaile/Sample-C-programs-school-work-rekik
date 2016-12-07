#ifndef AALTO_MINESWEEPER_H
#define	AALTO_MINESWEEPER_H

typedef enum {
    UNKNOWN_FREE,
    UNKNOWN_MINE,
    KNOWN_FREE,
    KNOWN_MINE
} State;

typedef struct {
    unsigned int xsize, ysize;
    State **places;
} Field;

Field *createField(unsigned int xsize, unsigned int ysize);

void printField(const Field *f);

void deployMines(Field *f, unsigned int mines);

int checkPlace(const Field *f, unsigned int x, unsigned int y);

int countNeighbours(const Field *f, unsigned int x, unsigned int y);

#endif	/* AALTO_MINESWEEPER_H */

#include <stdlib.h>
#include <stdint.h>
#include "piece.h"
#include "logger.h"


Piece piece_get(Shape shape, int y, int x) {
    switch (shape) {
        case I: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 5,
                .l = 4,
                .r = 0,
                .M = {
                    {
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}
                    },
                    {
                        {0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0}
                    },
                    {
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}
                    },
                    {
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0}
                    }
                }
            };
            return piece;
        }
        case J: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 3,
                .l = 3,
                .r = 0,
                .M = {
                    {
                        {1, 0, 0},
                        {1, 1, 1},
                        {0, 0, 0}
                    },
                    {
                        {0, 1, 1},
                        {0, 1, 0},
                        {0, 1, 0}
                    },
                    {
                        {0, 0, 0},
                        {1, 1, 1},
                        {0, 0, 1}
                    },
                    {
                        {0, 1, 0},
                        {0, 1, 0},
                        {1, 1, 0}
                    }
                }
            };
            return piece;
        }
        case L: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 3,
                .l = 3,
                .r = 0,
                .M = {
                    {
                        {0, 0, 1},
                        {1, 1, 1},
                        {0, 0, 0}
                    },
                    {
                        {0, 1, 0},
                        {0, 1, 0},
                        {0, 1, 1}
                    },
                    {
                        {0, 0, 0},
                        {1, 1, 1},
                        {1, 0, 0}
                    },
                    {
                        {1, 1, 0},
                        {0, 1, 0},
                        {0, 1, 0}
                    }
                }
            };
            return piece;
        }
        case O: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 2,
                .l = 2,
                .r = 0,
                .M = {
                    {
                        {1, 1},
                        {1, 1}
                    },
                    {
                        {1, 1},
                        {1, 1}
                    },
                    {
                        {1, 1},
                        {1, 1}
                    },
                    {
                        {1, 1},
                        {1, 1}
                    },
                }
            };
            return piece;
        }
        case S: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 3,
                .l = 3,
                .r = 0,
                .M = {
                    {
                        {0, 1, 1},
                        {1, 1, 0},
                        {0, 0, 0}
                    },
                    {
                        {0, 1, 0},
                        {0, 1, 1},
                        {0, 0, 1}
                    },
                    {
                        {0, 0, 0},
                        {0, 1, 1},
                        {1, 1, 0}
                    },
                    {
                        {1, 0, 0},
                        {1, 1, 0},
                        {0, 1, 0}
                    }
                }
            };
            return piece;
        }
        case T: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 3,
                .l = 3,
                .r = 0,
                .M = {
                    {
                        {0, 1, 0},
                        {1, 1, 1},
                        {0, 0, 0}
                    },
                    {
                        {0, 1, 0},
                        {0, 1, 1},
                        {0, 1, 0}
                    },
                    {
                        {0, 0, 0},
                        {1, 1, 1},
                        {0, 1, 0}
                    },
                    {
                        {0, 1, 0},
                        {1, 1, 0},
                        {0, 1, 0}
                    }
                }
            };
            return piece;
        }
        case Z: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 3,
                .l = 3,
                .r = 0,
                .M = {
                    {
                        {1, 1, 0},
                        {0, 1, 1},
                        {0, 0, 0}
                    },
                    {
                        {0, 0, 1},
                        {0, 1, 1},
                        {0, 1, 0}
                    },
                    {
                        {0, 0, 0},
                        {1, 1, 0},
                        {0, 1, 1}
                    },
                    {
                        {0, 1, 0},
                        {1, 1, 0},
                        {1, 0, 0}
                    }
                }
            };
            return piece;
        }
    }
    return (Piece){ 0 };
}

Piece* piece_init(Shape shape, int y, int x) {
    Piece* piece = malloc(sizeof(Piece));
    *piece = piece_get(shape, y, x);
    return piece;
}

void piece_destroy(Piece* piece) {
    if (piece) {
        *piece = (Piece){ 0 };
        free(piece);
        piece = NULL;
    }
}

void piece_debug_print(Piece* piece) {
    if (piece) {
        fprintf(
            debug_log,
            "%p = {shape = %c, y = %i, x = %i, n = %lu, l = %lu, r = %lu, M = ...}\n",
            piece,
            shape_to_char(piece->shape),
            piece->y,
            piece->x,
            piece->n,
            piece->l,
            piece->r
        );
    } else {
        fprintf(debug_log, "NULL\n");
    }
}

void piece_move(Piece* piece, int y, int x) {
    if (piece) {
        piece->x = x;
        piece->y = y;
    }
}

void piece_rotate_right(Piece* piece) {
    if (piece) {
        piece->r = (piece->r + 1) % R_MAX;
    }
}

void piece_rotate_left(Piece* piece) {
    if (piece) {
        piece->r = (piece->r > 0) ? piece->r - 1 : R_MAX - 1;    
    }
}

char shape_to_char(Shape shape) {
    switch (shape) {
        case I:
            return 'I';
        case J:
            return 'J';
        case L:
            return 'L';
        case O:
            return 'O';
        case S:
            return 'S';
        case T:
            return 'T';
        case Z:
            return 'Z';
    }
    return 0;
}

#include <stdlib.h>
#include <stdint.h>
#include "piece.h"
#include "logger.h"


Piece piece_get(Shape shape, uint8_t y, uint8_t x) {
    switch (shape) {
        case I: {
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 5,
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
                .n = 3,
                .r = 0,
                .M = {
                    {
                        {0, 1, 1},
                        {0, 1, 1},
                        {0, 0, 0}
                    },
                    {
                        {0, 0, 0},
                        {0, 1, 1},
                        {0, 1, 1}
                    },
                    {
                        {0, 0, 0},
                        {1, 1, 0},
                        {1, 1, 0}
                    },
                    {
                        {1, 1, 0},
                        {1, 1, 0},
                        {0, 0, 0}
                    }
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
        default:
            Piece piece = {
                .shape = shape,
                .y = y,
                .x = x,
                .n = 3,
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

Piece* piece_init(Shape shape, uint8_t y, uint8_t x) {
    Piece* piece = malloc(sizeof(Piece));
    *piece = piece_get(shape, y, x);
    return piece;
}

void piece_destroy(Piece* piece) {
    if (piece) {
        *piece = (Piece){ 0 };
        free(piece);
    }
}

void piece_debug_print(Piece* piece) {
    if (piece) {
        fprintf(
            debug_log,
            "%p = {shape = %i, y = %u, x = %u, n = %u, r = %u, M = ...}\n",
            piece,
            piece->shape,
            piece->y,
            piece->x,
            piece->n,
            piece->r
        );
    }
}

void piece_move(Piece* piece, uint8_t y, uint8_t x) {
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

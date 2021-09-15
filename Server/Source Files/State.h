//
// Created by kendall on 15/9/21.
//

#ifndef PROYECTO_1_CRAZY_BREAK_OUT_STATE_H
#define PROYECTO_1_CRAZY_BREAK_OUT_STATE_H

#include <allegro5/allegro_font.h>

// Estructura principal de una escena (state)
struct State
{  const char *name;

    int (*On_Load)(void *param);
    void (*On_Unload)(void);

    void (*On_Enter)(void *param);
    void (*On_Exit)(void);

    void (*On_Event)(ALLEGRO_EVENT*);
    void (*On_Update)(int *key, int mouse_x, int mouse_y);
    void (*On_Draw)(ALLEGRO_FONT*, int fps);

    // Esta variable es privada y se usa unicamente en Game.c
    // Indica si la escena ya se inicializó con On_Load().
    int loaded;
};

#endif //PROYECTO_1_CRAZY_BREAK_OUT_STATE_H

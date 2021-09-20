
#ifndef PROYECTO_1_CRAZY_BREAK_OUT_BALL_H
#define PROYECTO_1_CRAZY_BREAK_OUT_BALL_H
#include <allegro5/allegro.h>

int ball_init(ALLEGRO_BITMAP *sprite, float x, float y);
void ball_restart(int update_speed);
int ball_update(void);
int ball_check_collision(float x, float y, int w, int h, int is_paddle);
void ball_draw(void);


#endif // BALL_H_INCLUDED

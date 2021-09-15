//
// Created by kendall on 15/9/21.
//

#include "Ball.h"

#include <math.h>
#include "Ball.h"
#include "Game.h"



static struct
{  ALLEGRO_BITMAP *sprite;
    float x, y;
    float xprev, yprev;
    float dx, dy;
    float speed;
    int w, h;
} ball;



static void set_new_dir(int dir)
{
    ball.dx = cos(dir * 3.141592 / 180) * ball.speed;
    ball.dy = sin(dir * 3.141592 / 180) * ball.speed;
}



int ball_init(ALLEGRO_BITMAP *sprite, float x, float y)
{
    ball.sprite = sprite;

    int w = al_get_bitmap_width(ball.sprite);
    int h = al_get_bitmap_height(ball.sprite);

    ball.w = w;
    ball.h = h;

    ball.x = x;
    ball.y = y;

    ball.dx = 0;
    ball.dy = 0;

    return 1;
}



void ball_restart(int update_speed)
{
    // Velocidad inicial
    static float speed = 8.0f;

    int dir, dir_select = rand() % 2;

    // Se elige una dirección "random" al iniciar
    if (dir_select == 0)
    {  dir = 230 + rand() % 30;
    }
    else
    {  dir = 310 - rand() % 30;
    }

    if (update_speed)
    {  speed += 1.0f;
    }

    ball.speed = speed;

    set_new_dir(dir);
}



int ball_update(void)
{
    // Actualizar las coordenadas
    ball.xprev = ball.x;
    ball.yprev = ball.y;

    ball.x += ball.dx;
    ball.y += ball.dy;

    if (ball.x < 0 || ball.x > 640 - ball.w)
    {  ball.x = ball.xprev;
        ball.dx *= -1;
    }

    if (ball.y < 0)
    {  ball.y = ball.yprev;
        ball.dy *= -1;
    }

    if (ball.y > GAME_H)
    {  return 0; // Devolver 0 si la pelota ha caído
    }

    return 1;
}



int ball_check_collision(float x, float y, int w, int h, int is_paddle)
{  // Checar una colisión por los lados de un bloque
    if (check_bb_collision(ball.x + ball.dx, ball.y, ball.w, ball.h, x, y, w, h))
    {  ball.dx *= -1;
        return TRUE;
    }

    // Checar una colisión por la parte de arriba o abajo de un bloque
    if (check_bb_collision(ball.x, ball.y + ball.dy, ball.w, ball.h, x, y, w, h))
    {  ball.dy *= -1;

        // Si tocó el paddle, hacer que la pelota rebote hacia un ángulo diferente
        if (is_paddle)
        {  int w = al_get_bitmap_width(ball.sprite);

            // Obtener el centro "x" de la pelota
            int ball_center_x = ball.x + w / 2;

            // Rebotar hacia la izquierda
            if (ball_center_x < x + 50)
            {  if (ball_center_x < x + 22)
                {  set_new_dir(210);
                }
                else
                {  set_new_dir(250);
                }
            }
                // Rebotar hacia la derecha
            else
            {  if (ball_center_x > x + 82)
                {  set_new_dir(330);
                }
                else
                {  set_new_dir(290);
                }
            }
        }

        return TRUE;
    }

    return FALSE;
}



void ball_draw(void)
{
    al_draw_bitmap(ball.sprite, ball.x, ball.y, 0);
}

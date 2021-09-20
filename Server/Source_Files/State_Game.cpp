#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro_primitives.h>

#include "State_Game.h"
#include "Game.h"
#include "Ball.h"


// Estructura de un bloque
struct Block
{  float x, y;
    int destroyed;
};

// Estructura con los datos y variables de la escena
static struct
{
    // Recursos
    ALLEGRO_BITMAP *spr_ball;
    ALLEGRO_BITMAP *spr_paddle;
    ALLEGRO_BITMAP *spr_block[5];
    ALLEGRO_FONT *font_def;

    // Bloques
    struct Block blocks[50];

    // Variables del "HUD" (puntos, fase y vidas)
    int score, phase, lives;

    float paddle_x, paddle_y;
    int blocks_destroyed;
    int is_paused;
    int show_info;
    int is_new_phase;
    int can_restart;

} game;



// Función para reposicionar la pelota en el lugar de inicio
static void Reposition_Ball(void)
{
    ball_init(game.spr_ball, 310, 500);
    game.can_restart = TRUE;
}


// On_Load(): Cargar los recursos de la escena.
static int On_Load(void *param)
{
    game.spr_ball = al_load_bitmap("data/ball.png");
    game.spr_paddle = al_load_bitmap("data/paddle.png");

    game.spr_block[0] = al_load_bitmap("data/block purple.png");
    game.spr_block[1] = al_load_bitmap("data/block green.png");
    game.spr_block[2] = al_load_bitmap("data/block blue.png");
    game.spr_block[3] = al_load_bitmap("data/block yellow.png");
    game.spr_block[4] = al_load_bitmap("data/block red.png");

    game.font_def = al_load_font("data/font1.ttf", 20, 0);

    // Posición inicial del paddle
    game.paddle_x = 300.0f;
    game.paddle_y = 530.0f;

    game.phase = 1;
    game.lives = 3;

    // Devolver 1 para continuar
    return 1;
}


// On_Unload(): Liberar la memoria de los recursos.
static void On_Unload(void)
{
    al_destroy_bitmap(game.spr_ball);
    al_destroy_bitmap(game.spr_paddle);

    al_destroy_bitmap(game.spr_block[0]);
    al_destroy_bitmap(game.spr_block[1]);
    al_destroy_bitmap(game.spr_block[2]);
    al_destroy_bitmap(game.spr_block[3]);
    al_destroy_bitmap(game.spr_block[4]);

    al_destroy_font(game.font_def);
}


// On_Enter(): Entrada normal.
static void On_Enter(void *param)
{
    Set_BG_Color(al_map_rgb(192, 192, 255));

    Reposition_Ball();

    // Creación de los bloques
    {  int x = 0, y = 0;
        for (struct Block *b = game.blocks; b != game.blocks + 50; ++b)
        {  b->destroyed = FALSE;

            b->x = x;
            b->y = y;

            x += 64;

            if (x >= 640)
            {  y += 32;
                x = 0;
            }
        }
    }

    game.blocks_destroyed = 0;
}


// On_Exit(): Salida normal.
static void On_Exit(void)
{
}


// On_Events(): Recibir los eventos de Allegro.
static void On_Event(ALLEGRO_EVENT *ev)
{
    if ((*ev).type == ALLEGRO_EVENT_KEY_DOWN)
    {  if ((*ev).keyboard.keycode == ALLEGRO_KEY_P)
        {  game.is_paused = 1 - game.is_paused;
        }
            // La tecla "F" mostrará los FPS
        else if ((*ev).keyboard.keycode == ALLEGRO_KEY_F)
        {  game.show_info = 1 - game.show_info;
        }
            // Con la tecla "Espacio" hacemos que la pelota empieze a moverse tras
            // haber pasado una fase o después de perder una vida.
        else if ((*ev).keyboard.keycode == ALLEGRO_KEY_SPACE && !game.is_paused)
        {  if (game.is_new_phase && game.can_restart)
            {  ball_restart(TRUE); // Se aumenta la velocidad de la pelota (TRUE)
                game.is_new_phase = FALSE;
                game.can_restart = FALSE;
            }
            else if (game.can_restart)
            {  ball_restart(FALSE);
                game.can_restart = FALSE;
            }
        }
    }
}


// On_Update(): Actualizar la escena.
static void On_Update(int *key, int mouse_x, int mouse_y)
{
    // Dejar de actualizar si el juego está pausado
    if (game.is_paused)
    {  return;
    }

    // El paddle seguirá el mouse horizontalmente
    game.paddle_x = mouse_x;

    // Hacer que el paddle no sobrepase la región del juego
    int paddle_w = al_get_bitmap_width(game.spr_paddle);
    while (game.paddle_x > 639 - paddle_w)
    {  --game.paddle_x;
    }

    // Actualizar la pelota
    // La función "ball_update" devuelve 0 si la pelota ha caído
    if (!ball_update())
    {  // Quitar una vida si la pelota se salió de la pantalla
        --game.lives;

        if (game.lives < 0)
        {  char final_score[100];

            sprintf(final_score, "Tu puntuacion final fue: %i", game.score);

            // Al no tener vidas, se mostrará un cuadro de diálogo simple con la
            // puntuación final.
            Show_Message("Gracias por jugar!", final_score);

            Game_Over();
            return;
        }

        Reposition_Ball();
    }

    // Checar si la pelota tocó el paddle
    ball_check_collision(game.paddle_x, game.paddle_y + 2, paddle_w, 8, TRUE);

    // Checar si la pelota ha tocado un bloque
    for (struct Block *b = game.blocks; b != game.blocks + 50; ++b)
    {  if (!b->destroyed && ball_check_collision(b->x, b->y, 64, 32, FALSE))
        {  // Destruir el bloque y aumentar el score
            b->destroyed = TRUE;
            game.score += 5;

            ++game.blocks_destroyed;

            if (game.blocks_destroyed == 50)
            {  ++game.phase;

                game.is_new_phase = TRUE;

                // Se reinicia la escena tras haber destruido todos los bloques (50)
                Change_State(STATE_GAME, NULL);
            }
        }
    }
}


// On_Draw(): Dibujar la escena.
static void On_Draw(ALLEGRO_FONT *font, int fps)
{
    // Fondo del "HUD"
    al_draw_filled_rectangle(640, 0, GAME_W, GAME_H, al_map_rgb(80, 80, 80));

    // Dibujar todos los bloques
    for (struct Block *b = game.blocks; b != game.blocks + 50; ++b)
    {  if (!b->destroyed)
        {  al_draw_bitmap(game.spr_block[(int) b->y / 32], b->x, b->y, 0);
        }
    }

    if (!game.is_paused)
    {  // Pelota
        ball_draw();

        // Paddle
        al_draw_bitmap(game.spr_paddle, game.paddle_x, game.paddle_y, 0);

        // Texto de inicio
        if (game.can_restart)
        {  al_draw_text(game.font_def, C_BLACK, 320, 280, ALLEGRO_ALIGN_CENTER
                    , "Mueve el paddle con el mouse");

            al_draw_text(game.font_def, C_BLACK, 320, 300, ALLEGRO_ALIGN_CENTER
                    , "Pulsa Espacio para iniciar");
        }
    }
    else
    {  al_draw_text(game.font_def, C_BLACK, 320, 300, ALLEGRO_ALIGN_CENTER
                , "PAUSA");

        al_draw_text(game.font_def, C_BLACK, 320, 330, ALLEGRO_ALIGN_CENTER
                , "Pulsa P para reanudar");
    }

    // Info adicional (se habilita con "F")
    if (game.show_info)
    {  al_draw_textf(font, C_BLACK, 320, 400, ALLEGRO_ALIGN_CENTER
                , "FPS: %i", fps);
    }

    // HUD
    al_draw_text(game.font_def, C_WHITE, 720, 20, ALLEGRO_ALIGN_CENTER
            , "Score");

    al_draw_textf(game.font_def, C_WHITE, 720, 40, ALLEGRO_ALIGN_CENTER
            , "%06i", game.score);

    al_draw_text(game.font_def, C_WHITE, 720, 100, ALLEGRO_ALIGN_CENTER
            , "Fase");

    al_draw_textf(game.font_def, C_WHITE, 720, 120, ALLEGRO_ALIGN_CENTER
            , "%i", game.phase);

    al_draw_text(game.font_def, C_WHITE, 720, 200, ALLEGRO_ALIGN_CENTER
            , "Restantes");

    for (int i = 0; i < game.lives; ++i)
    {  al_draw_bitmap(game.spr_ball, 680 + (i * 30), 220, 0);
    }
}



// Funcion de obtención de la escena
struct State *State_Game(void)
{
    static struct State state =
            {  // Nombre
                    "Juego (State_Game)",

                    // Funciones
                    On_Load,
                    On_Unload,
                    On_Enter,
                    On_Exit,
                    On_Event,
                    On_Update,
                    On_Draw
            };

    return &state;
}

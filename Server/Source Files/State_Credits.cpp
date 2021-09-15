#include "State_Credits.h"
#include "State_Menu.h"
#include "Game.h"


// Fuentes usadas para los créditos
static ALLEGRO_FONT *font_big;


// On_Load(): Cargar los recursos de la escena.
static int On_Load(void *param)
{
    font_big = al_load_font("data/font1.ttf", 36, 0);

    return 1;
}


// On_Unload(): Liberar la memoria de los recursos.
static void On_Unload(void)
{
    al_destroy_font(font_big);
}


// On_Enter(): Entrada normal.
static void On_Enter(void *param)
{
    Set_BG_Color(C_BLACK);
}


// On_Exit(): Salida normal.
static void On_Exit(void)
{
}


static void On_Event(ALLEGRO_EVENT *ev)
{
    if ((*ev).type == ALLEGRO_EVENT_KEY_DOWN
        && (*ev).keyboard.keycode == ALLEGRO_KEY_ESCAPE)
    {  // Regresar al menú tras haber pulsado <Esc>
        Change_State(STATE_MENU, NULL);
    }
}


// On_Update(): Actualizar la escena.
static void On_Update(int *key, int mouse_x, int mouse_y)
{

}


// On_Draw(): Dibujar la escena.
static void On_Draw(ALLEGRO_FONT *font, int fps)
{
    al_draw_text(font_big, al_map_rgb(255, 255, 0), GAME_W / 2, 50
            , ALLEGRO_ALIGN_CENTER, "Creditos");

    al_draw_text(font_big, C_WHITE, 50, 200, 0
            , "Programacion por \"Kendall Martinez C.\" (kendallmc@estudiantec.cr)");

    al_draw_text(font_big, C_WHITE, 50, 250, 0
            , "Programacion por \"Daniel Ureña L.\" (dlurena@estudiantec.cr)");

    al_draw_text(font_big, C_WHITE, 50, 300, 0
            , "Sprites de \"Breakout\" por Kendall Martinez C");

    al_draw_text(font, C_WHITE, GAME_W / 2, GAME_H - 50, ALLEGRO_ALIGN_CENTER
            , "Pulse <Esc> para ir al menu");
}



// Funcion de obtención de la escena
struct State *State_Credits(void)
{
    static struct State state =
            {  // Nombre
                    "Creditos (State_Credits)",

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
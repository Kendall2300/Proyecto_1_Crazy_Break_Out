#include <string.h>

#include <allegro5/allegro_primitives.h>

#include "State_Menu.h"
#include "State_Game.h"
#include "State_Credits.h"
#include "Game.h"


// Opciones del menú
// Nota: Hay que poner "0" al final para indicar el final de la lista
static const char *menu_strings[] =
        {  "Jugar",
           "Creditos",
           "Salir",
           0
        };

// Cantidad de opciones (se detecta automaticamente)
static int menu_options;

// Opción seleccionada del menú
static int menu_sel;

// Logo del menu
static ALLEGRO_BITMAP *logo;

// Fuente grande
static ALLEGRO_FONT *font_big;



// On_Load(): Cargar los recursos de la escena.
static int On_Load(void *param)
{
    //logo = data[SPR_LOGO].dat;
    //font_big = data[FONT_BIG].dat;

    logo = al_load_bitmap("data/logo.png");
    font_big = al_load_font("data/font1.ttf", 40, 0);

    // Auto-detectar la cantidad de opciones que tiene el menú
    while (menu_strings[++menu_options]);

    return 1;
}


// On_Unload(): Liberar la memoria de los recursos.
static void On_Unload(void)
{
    al_destroy_bitmap(logo);
    al_destroy_font(font_big);
}


// On_Enter(): Entrada normal.
static void On_Enter(void *param)
{
    Set_BG_Color(al_map_rgb(192, 192, 255));
}


// On_Exit(): Salida normal.
static void On_Exit(void)
{

}


// On_Event(): Recibir los eventos de Allegro.
static void On_Event(ALLEGRO_EVENT *ev)
{
    if ((*ev).type == ALLEGRO_EVENT_KEY_DOWN)
    {  // Cambiar la opción del menú si se pulsó la flecha de arriba/abajo
        if ((*ev).keyboard.keycode == ALLEGRO_KEY_UP && menu_sel != 0)
        {  --menu_sel;
        }
        else if ((*ev).keyboard.keycode == ALLEGRO_KEY_DOWN
                 && menu_sel != menu_options - 1)
        {  ++menu_sel;
        }

        // Al pulsar Enter, se checa la opción que está seleccionada del menú
        if ((*ev).keyboard.keycode == ALLEGRO_KEY_ENTER)
        {  if (strcmp(menu_strings[menu_sel], "Jugar") == 0)
            {  // Ir al juego al seleccionar la opcion
                Change_State(STATE_GAME, NULL);
            }
            else if (strcmp(menu_strings[menu_sel], "Creditos") == 0)
            {  // Ir a la pantalla de Créditos al seleccionar la opcion
                Change_State(STATE_CREDITS, NULL);
            }
            else if (strcmp(menu_strings[menu_sel], "Salir") == 0)
            {  // Cerrar el juego al seleccionar la opcion
                Game_Over();
            }
        }
    }
}


// On_Update(): Actualizar la escena.
static void On_Update(int *key, int mouse_x, int mouse_y)
{

}


// On_Draw(): Dibujar la escena.
static void On_Draw(ALLEGRO_FONT *font, int fps)
{
    al_draw_filled_rectangle(0, 90, GAME_W, 200, C_WHITE);

    al_draw_bitmap(logo, GAME_W / 2 - 222, 100, 0);

    al_draw_textf(font, C_BLACK, GAME_W / 2, 180, ALLEGRO_ALIGN_CENTER
            , "Creado con Allegro %s", ALLEGRO_VERSION_STR);

    // Dibujar el menú
    for (int i = 0; i < menu_options; ++i)
    {  if (i == menu_sel)
        {  al_draw_textf(font_big, al_map_rgb(255, 255, 128), GAME_W / 2
                    , 280 + (i * 50), ALLEGRO_ALIGN_CENTER, "> %s <"
                    , menu_strings[i]);
        }
        else
        {  al_draw_text(font_big, al_map_rgb(0, 0, 0), GAME_W / 2
                    , 280 + (i * 50), ALLEGRO_ALIGN_CENTER, menu_strings[i]);
        }
    }

    al_draw_text(font, C_BLACK, 0, GAME_H - 8, 0
            , "Pulsa F4 para ir a pantalla completa o ventana");

    al_draw_text(font, C_BLACK, GAME_W, GAME_H - 8, ALLEGRO_ALIGN_RIGHT
            , GAME_VER);
}



// Funcion de obtención de la escena
struct State *State_Menu(void)
{
    static struct State state =
            {  // Nombre
                    "Menu (State_Menu)",

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

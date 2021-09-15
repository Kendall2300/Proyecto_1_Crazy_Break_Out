#include "stdlib.h"
#include "time.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#include "Game.h"
#include "State.h"

struct Game_conf *mainconf;

static void Fix_Game_Screen(ALLEGRO_DISPLAY *display){
    int window_w = al_get_display_width(display);
    int window_h = al_get_display_height(display);

    float sw = (float) window_w / GAME_W;
    float sh = (float) window_h / GAME_H;
    float scale =  (sw < sh ? sw : sh);

    float scale_w = (float) GAME_W *scale;
    float scale_h = (float) GAME_H *scale;
    int scale_x_pos = (window_w - scale_w) / 2;
    int scale_y_pos = (window_h -scale_h) / 2;

    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_build_transform(&trans,scale_x_pos,scale_y_pos,scale,scale,0);
    al_use_transform(&trans);
}

static void Change_Video_Mode(ALLEGRO_DISPLAY *display){
    int flags = al_get_display_flags(display);

    if (flags & ALLEGRO_FULLSCREEN_WINDOW){
        al_toggle_display_flag(display,ALLEGRO_FULLSCREEN_WINDOW,0);
    } else{
        al_toggle_display_flag(display,ALLEGRO_FULLSCREEN_WINDOW,1);
    }
    Fix_Game_Screen(display);
}


static struct{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *buffer;
    ALLEGRO_TIMER *timer, *fps_timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR bg_color;
    int initialized;
    int is_running;
    int can_change_state;
    int frame_count;
    struct State *state;
    struct State **loaded_states;
    int loaded_count;
} core;

int Game_Init(struct Game_Conf *conf)
{
    if (core.initialized)
    {  return 1;
    }

    al_init();

    if (!al_install_keyboard())
    {  puts("Game_Init:\n"
            "Error al inicializar el teclado\n");
        return 0;
    }

    if (!al_install_mouse())
    {  puts("Game_Init:\n"
            "No se pudo inicializar el mouse...\n");
    }

    // Add-ons
    if (!al_init_image_addon())
    {  puts("Game_Init:\n"
            "Error al inicializar el image_addon\n");
        return 0;
    }

    if (!al_init_font_addon())
    {  puts("Game_Init:\n"
            "Error al inicializar el font_addon\n");
        return 0;
    }

    if (!al_init_primitives_addon())
    {  puts("Game_Init:\n"
            "Error al inicializar el primitives_addon\n");
        return 0;
    }

    if (!al_init_ttf_addon())
    {  puts("Game_Init:\n"
            "Error al inicializar el ttf_addon\n");
        return 0;
    }

    if (conf->fullscreen)
    {  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    }



    // Habilita la siguiente línea para usar OpenGL en Windows.
    //al_set_new_display_flags(ALLEGRO_OPENGL);

    core.display = al_create_display(conf->width, conf->height);

    if (!core.display)
    {  puts("Game_Init:\n"
            "Imposible crear una ventana para el juego\n");
        return 0;
    }

    al_set_window_title(core.display, conf->title);

    mainconf = conf;
    Fix_Game_Screen(core.display);

    al_add_new_bitmap_flag(ALLEGRO_MAG_LINEAR);

    if (conf->buffer)
    {  core.buffer = al_create_bitmap(conf->width, conf->height);
        al_set_new_bitmap_flags(0);
    }

    core.font = al_create_builtin_font();
    core.timer = al_create_timer(1.0 / conf->framerate);
    core.fps_timer = al_create_timer(1.0);
    core.event_queue = al_create_event_queue();

    Set_BG_Color(al_map_rgb(192, 192, 192));

    srand(time(NULL));

    core.initialized = TRUE;
    core.can_change_state = TRUE;

    return 1;
}



// Función con el ciclo principal
void Game_Run(struct State *s)
{
    int mouse_x = 0, mouse_y = 0;
    int redraw = FALSE;
    int fps = 0;

    if (core.is_running)
    {  return;
    }

    if (!Change_State(s, NULL))
    {  return;
    }


    int window_w = al_get_display_width(core.display);
    int window_h = al_get_display_height(core.display);

    // Array para los botones del teclado
    int *key = calloc(ALLEGRO_KEY_MAX, sizeof *key);


    // Generar eventos de la ventana (display)
    al_register_event_source(core.event_queue
            , al_get_display_event_source(core.display));


    // Timer
    al_register_event_source(core.event_queue
            , al_get_timer_event_source(core.timer));

    al_register_event_source(core.event_queue
            , al_get_timer_event_source(core.fps_timer));


    // Teclado
    al_register_event_source(core.event_queue
            , al_get_keyboard_event_source());


    // Mouse
    al_register_event_source(core.event_queue
            , al_get_mouse_event_source());


    al_start_timer(core.timer);
    al_start_timer(core.fps_timer);

    core.is_running = TRUE;

    // Ciclo principal
    while (core.is_running)
    {  ALLEGRO_EVENT event;
        al_wait_for_event(core.event_queue, &event);

        core.state->On_Event(&event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {  core.is_running = FALSE;
            break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {  key[event.keyboard.keycode] = TRUE;

            // La tecla de F4 alternará entre modo ventana y pantalla completa
            if (key[ALLEGRO_KEY_F4])
            {  al_stop_timer(core.timer);
                Change_Video_Mode(core.display);
                al_start_timer(core.timer);

                window_w = al_get_display_width(core.display);
                window_h = al_get_display_height(core.display);
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {  key[event.keyboard.keycode] = FALSE;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {  mouse_x = event.mouse.x / ((float) window_w / GAME_W);
            mouse_y = event.mouse.y / ((float) window_h / GAME_H);
        }
        else if (event.type == ALLEGRO_EVENT_TIMER)
        {  if (event.timer.source == core.timer)
            {  core.state->On_Update(key, mouse_x, mouse_y);
                redraw = TRUE;
            }
            else if (event.timer.source == core.fps_timer)
            {  fps = core.frame_count;
                core.frame_count = 0;
            }
        }

        if (redraw && core.is_running
            && al_is_event_queue_empty(core.event_queue))
        {  redraw = FALSE;

            if (mainconf->buffer)
            {  al_set_target_bitmap(core.buffer);
            }
            else
            {  al_set_target_backbuffer(core.display);
            }

            al_clear_to_color(core.bg_color);

            core.state->On_Draw(core.font, fps);

            if (mainconf->buffer)
            {  al_set_target_backbuffer(core.display);
                al_clear_to_color(C_BLACK);
                al_draw_bitmap(core.buffer, 0, 0, 0);
            }

            al_flip_display();
            ++core.frame_count;
        }
    }

    core.can_change_state = FALSE;

    // Liberar la memoria
    while (core.loaded_count)
    {  core.loaded_states[--core.loaded_count]->On_Unload();
    }

    free(core.loaded_states);

    al_destroy_display(core.display);
    al_destroy_timer(core.timer);
    al_destroy_timer(core.fps_timer);
    al_destroy_event_queue(core.event_queue);
    al_destroy_font(core.font);

    if (mainconf->buffer)
    {  al_destroy_bitmap(core.buffer);
    }

    free(key);
}



int Change_State(struct State *s, void *param)
{
    if (!core.can_change_state)
    {  puts("Change_State:\n"
            "Esta funcion solo se puede llamar adentro de On_Events(), "
            "On_Update() y On_Draw() en una escena.");
        return TRUE;
    }

    core.can_change_state = FALSE;

    if (!s->loaded)
    {  void *ptr = realloc(core.loaded_states
                , sizeof *core.loaded_states * (core.loaded_count + 1));

        if (ptr != NULL)
        {  if (!s->On_Load(param))
            {  printf("Change_State:\n"
                      "La escena \"%s\" devolvio 0.\n", s->name);
                core.can_change_state = TRUE;
                return FALSE;
            }

            s->loaded = TRUE;
            core.loaded_states = ptr;
            core.loaded_states[core.loaded_count++] = s;
        }
        else
        {  puts("Change_State:\n"
                "Error en realloc() - No hay memoria suficiente?");
            core.can_change_state = TRUE;
            return FALSE;
        }
    }

    s->On_Enter(param);

    if (core.state != NULL)
    {  core.state->On_Exit();
    }

    core.state = s;
    core.can_change_state = TRUE;

    al_flush_event_queue(core.event_queue);

    return TRUE;
}



void Game_Over(void)
{
    core.is_running = FALSE;
}



void Set_BG_Color(ALLEGRO_COLOR c)
{
    core.bg_color = c;
}



void Show_Message(const char *heading, const char *msg)
{
    al_show_native_message_box(core.display, "Breakout", heading, msg, NULL, 0);
}
#include <iostream>
#include <string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <math.h>
#include <thread>

using namespace std;


int jugar();
int menu();
int ancho = 1400;
int alto = 800;
int contSalto = 0;
int altSalto = 72;
bool caer = false;
bool salto = false;


ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* hillshort;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_TIMER* fps;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_KEYBOARD_STATE wait_key_State;


int main() {

	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();



	ventana = al_create_display(ancho, alto);
	hillshort = al_load_font("fuentes/Hillshort.otf", 70, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);

	al_set_window_title(ventana, "Donkey Kong");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	//al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

	//eventos timer
	segundoTimer = al_create_timer(1.0);
	fps = al_create_timer(1.0 / 30);

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(fps);
	al_start_timer(segundoTimer);

	menu();


	return 0;
}


int jugar()
{
	{

		// allegro_init();

		al_init();

		al_init_image_addon();
		

		al_install_keyboard();


	
		// BITMAP* prota = load_bmp("personaje.bmp", NULL);

		

		ALLEGRO_BITMAP* prota = al_load_bitmap("IMAGENES/mario_quieto.png");
		ALLEGRO_BITMAP* mapaUno = al_load_bitmap("IMAGENES/mapa_Uno.png");
		ALLEGRO_BITMAP* floor = al_load_bitmap("IMAGENES/Floor.png");
		ALLEGRO_BITMAP* escalera = al_load_bitmap("IMAGENES/escalera.png");
		ALLEGRO_SAMPLE* songNivel1 = al_load_sample("sonidos/songNivelUno.mp3");


		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(songNivel1);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());


		al_play_sample_instance(song_instance);



		// defino lista de eventos

		ALLEGRO_EVENT_QUEUE* Mis_eventos;

		ALLEGRO_EVENT evento;


		// creo lista de eventos

		Mis_eventos = al_create_event_queue();


		// asigno eventos a la lista de eventos

		al_register_event_source(Mis_eventos, al_get_keyboard_event_source());

		al_register_event_source(Mis_eventos, al_get_display_event_source(ventana));


		ALLEGRO_KEYBOARD_STATE teclado;

		int plataformaUno[16][28] = {
			{0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2.0},
		};
		bool salir;

		int x, y;

		int desplaza;

		int paso;

		int dir;


		// inicializar variables

		x = 50;

		y = 700;


		desplaza = 4;


		paso = 0;

		dir = 0;


		salir = false;





		while (!salir)

		{
			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 

			// clear_to_color(buffer, 0x785a5a);
			
			al_clear_to_color(al_map_rgb(0, 0, 0));
			for (int xmap = 15; xmap >= 0; xmap--) {
				for (int ymap = 27; ymap >=0; ymap--) {
					if (plataformaUno[xmap][ymap] == 2) {
						al_draw_bitmap(floor, (ymap*50), (xmap*50), 0);

					}
					if (plataformaUno[xmap][ymap] == 3) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
				}

			}


			// masked_blit(prota, buffer, paso*32, dir*32, x, y, 32,32);

			al_draw_bitmap_region(prota, paso *48, dir *48, 48, 48, x , y , 0);

			//colision plataforma caida
			if (plataformaUno[lround(((y)*16) / 800)+1][lround(((x+24)*28)/1400)]==0 && !salto ) {
				caer = true;
				cout << y << endl;

			}
			else {
				caer = false;
				
				
			}


			if (caer) {
				y+=6;
			}
			if (salto && contSalto <= altSalto) {
				contSalto += 12;
				y-=12;
			}
			else {
				salto = false;
				
				contSalto = 0;
			}			
			
			// mostramos la pantalla

			// blit(buffer, screen, 0, 0, 0, 0, 800, 600);

			al_flip_display();


			al_wait_for_event(Mis_eventos, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&teclado);


			if (al_key_down(&teclado, ALLEGRO_KEY_UP))

			{

				if (plataformaUno[lround(((y+48) * 16) / 800) ][lround(((x + 24) * 28) / 1400)] == 3) {

					y -= 5;

					dir = 3;

					paso++;
				}

			}
			
			if (al_key_down(&teclado, ALLEGRO_KEY_DOWN))

			{
				if (plataformaUno[lround(((y) * 16) / 800)+1][lround(((x + 24) * 28) / 1400) ] == 3){

					y+=5;

					dir = 0;

					paso++;
				}
			}

			if (al_key_down(&teclado, ALLEGRO_KEY_LEFT))

			{

				
				if (plataformaUno[lround(((y+24) * 16) / 800) ][lround(((x+48) * 28) / 1400)-1] != 2) {
					
					x -= 5;

					

					
				}
				paso++;
				dir = 1;
			}

			if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT))

			{
				if (plataformaUno[lround(((y+24) * 16) / 800)][lround(((x) * 28) / 1400) + 1] != 2) {
					x += 5;

					

					

				}
				paso++;
				dir = 2;
				

			}

			if (!caer && !salto && !al_key_down(&wait_key_State, ALLEGRO_KEY_SPACE) && al_key_down(&teclado, ALLEGRO_KEY_SPACE)) {
				
				salto = true;	
					
				

			}
			cout << salto  << endl;

			
			// limitadores


			if (x < 0) x = 0;

			if (x > 1400 - 48) x = 1400 - 48;

			if (y < 0) y = 0;

			if (y > 800 - 48) y = 800 - 48;


			if (paso > 2) paso = 0;


			if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE)) {
				al_destroy_sample(songNivel1);
				salir = true;
				menu();

			}


		}



		// destroy_bitmap(prota);

		al_destroy_bitmap(prota);


		// destroy_display(pantalla);

		al_destroy_display(ventana);


		return 0;

	}

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_filled_circle(200, 200, 100, al_map_rgb(255, 255, 255));
		al_flip_display();
	}
	return 1;
}

//menu
int menu() {
	
	al_install_audio();
	al_init_acodec_addon();

	int segundos = 0;
	int x = -1, y = -1;
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR azar = al_map_rgb(255, 50, 65);

	ALLEGRO_BITMAP* menu_null = al_load_bitmap("IMAGENES/menuInicial.png");
	ALLEGRO_BITMAP* menu_jugar = al_load_bitmap("IMAGENES/menu_play.png");
	ALLEGRO_BITMAP* menu_opciones = al_load_bitmap("IMAGENES/menu_opciones.png");
	ALLEGRO_BITMAP* menu_salir = al_load_bitmap("IMAGENES/menu_salir.png");

	ALLEGRO_SAMPLE* efectoMenu = al_load_sample("sonidos/caminar.wav");
	ALLEGRO_SAMPLE* menuSong = al_load_sample("sonidos/menuSong.mp3");

	al_reserve_samples(1);

	ALLEGRO_SAMPLE_INSTANCE * song_instance = al_create_sample_instance(menuSong);
	al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());


	al_play_sample_instance(song_instance);
	//menu
	int botones[] = { 0 };
	
	
	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);

		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			if (Evento.timer.source == segundoTimer) {
				segundos++;
			}

		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (botones[0] == 0)
			al_draw_bitmap(menu_null, 0, 0, 0);
		else if (botones[0] == 1)
			al_draw_bitmap(menu_jugar, 0, 0, 0);
			
		
			
		else if (botones[0] == 2) 
			al_draw_bitmap(menu_opciones, 0, 0, 0);
			
		
			
		else

			al_draw_bitmap(menu_salir, 0, 0, 0);
		    
	

		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			x = Evento.mouse.x;
			y = Evento.mouse.y;

			if (x >= 175 && x <=392 && y >= 288 && y <= 343) {
				botones[0] = 1;
				al_play_sample(efectoMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				
				if (Evento.mouse.button & 1) {
					al_destroy_sample(menuSong);
					jugar();

					
				}
					
			}
			else {
				if (x >= 492 && x <= 822 && y >= 435 && y <= 486) {
					botones[0] = 2;
					al_play_sample(efectoMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					
					if (Evento.mouse.button & 1) {
						cout << "menu opcones" << endl;;
						

					}
						
				}
				else if (x >= 172 && x <= 368 && y >= 646 && y <= 701) {
					botones[0] = 3;
					al_play_sample(efectoMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				
					if (Evento.mouse.button & 1){
						return 1;
					}
						
						
				}
				else {
					botones[0] = 0;
				}

			}


		}

		al_flip_display();
	}
}
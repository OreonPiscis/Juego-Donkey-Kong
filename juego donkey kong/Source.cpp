
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
#include <stdlib.h>
#include <time.h>

using namespace std;

int vida = 5;
int jugar();
int menu();
int ancho = 1400;
int alto = 800;
int contSalto = 0;
int altSalto = 130;
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

//novel 3
//game over
int gameOver()
{
	{

		const float FPS = 60.0;
		// allegro_init();

		al_init();

		al_init_image_addon();


		al_install_keyboard();


		int x1 = -1, y1 = -1;
		int segundos = 0;

		// BITMAP* prota = load_bmp("personaje.bmp", NULL);



		ALLEGRO_BITMAP* gameOver = al_load_bitmap("IMAGENES/gameOver.png");
		ALLEGRO_BITMAP* gameOver2 = al_load_bitmap("IMAGENES/gameOver.png");



		ALLEGRO_SAMPLE* endSong = al_load_sample("sonidos/overSong.mp3");

		al_reserve_samples(1);

		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(endSong);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());







		al_play_sample_instance(song_instance);



		// defino lista de eventos



		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
		ALLEGRO_KEYBOARD_STATE keyState;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));

		int botones2[] = { 0 };



		al_start_timer(timer);


		al_init();

		al_init_image_addon();


		al_install_keyboard();

		bool salir;




		srand(time(0));



		// inicializar variables

		salir = false;



		ALLEGRO_KEYBOARD_STATE keyState1;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos


		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));





		al_start_timer(timer);


		while (!salir)

		{
			ALLEGRO_EVENT evento;

			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 




			// clear_to_color(buffer, 0x785a5a);

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(gameOver, 0, 0, 0);



			// mostramos la pantalla

			// blit(buffer, screen, 0, 0, 0, 0, 800, 600);

			al_flip_display();


			al_wait_for_event(event_queue, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&keyState);


			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
				al_destroy_sample(endSong);
				salir = true;
				menu();

			}


		}






	}











	// destroy_display(pantalla);

	al_destroy_display(ventana);






	return 1;
}

//WIN GAME
int winGame()
{
	{

		const float FPS = 60.0;
		// allegro_init();

		al_init();

		al_init_image_addon();


		al_install_keyboard();


		int x1 = -1, y1 = -1;
		int segundos = 0;

		// BITMAP* prota = load_bmp("personaje.bmp", NULL);



		ALLEGRO_BITMAP* winGame = al_load_bitmap("IMAGENES/win_null.png");
		ALLEGRO_BITMAP* gameOver2 = al_load_bitmap("IMAGENES/win_null.png");



		ALLEGRO_SAMPLE* winSong = al_load_sample("sonidos/winSong.mp3");

		al_reserve_samples(1);

		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(winSong);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());







		al_play_sample_instance(song_instance);



		// defino lista de eventos



		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
		ALLEGRO_KEYBOARD_STATE keyState;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));

		int botones2[] = { 0 };



		al_start_timer(timer);


		al_init();

		al_init_image_addon();


		al_install_keyboard();

		bool salir;




		srand(time(0));



		// inicializar variables

		salir = false;



		ALLEGRO_KEYBOARD_STATE keyState1;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos


		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));





		al_start_timer(timer);


		while (!salir)

		{
			ALLEGRO_EVENT evento;

			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 




			// clear_to_color(buffer, 0x785a5a);

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(winGame, 0, 0, 0);



			// mostramos la pantalla

			// blit(buffer, screen, 0, 0, 0, 0, 800, 600);

			al_flip_display();


			al_wait_for_event(event_queue, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&keyState);


			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
				al_destroy_sample(winSong);
				salir = true;
				menu();

			}


		}






	}











	// destroy_display(pantalla);

	al_destroy_display(ventana);






	return 1;
}
int plataformaTres()
{
	{

		const float FPS = 60.0;
		// allegro_init();

		al_init();

		al_init_image_addon();


		al_install_keyboard();





		// BITMAP* prota = load_bmp("personaje.bmp", NULL);



		ALLEGRO_BITMAP* prota = al_load_bitmap("IMAGENES/mario_quieto.png");
		ALLEGRO_BITMAP* mapaUno = al_load_bitmap("IMAGENES/mapa_Uno.png");
		ALLEGRO_BITMAP* floor = al_load_bitmap("IMAGENES/floorTres.png");
		ALLEGRO_BITMAP* escalera = al_load_bitmap("IMAGENES/escaleraTres.png");
		ALLEGRO_SAMPLE* songNivel3 = al_load_sample("sonidos/songNivelTres.mp3");
		ALLEGRO_BITMAP* barril = al_load_bitmap("IMAGENES/barrilTres.png");

		ALLEGRO_BITMAP* star = al_load_bitmap("IMAGENES/star.png");
		ALLEGRO_BITMAP* protaStar = al_load_bitmap("IMAGENES/mario_estrella.png");
		ALLEGRO_BITMAP* life = al_load_bitmap("IMAGENES/vidas.png");

		//Donkey Kong
		ALLEGRO_BITMAP* jefe1 = al_load_bitmap("IMAGENES/don1.png");
		ALLEGRO_BITMAP* jefe2 = al_load_bitmap("IMAGENES/don2.png");
		ALLEGRO_BITMAP* jefe3 = al_load_bitmap("IMAGENES/don3.png");
		ALLEGRO_BITMAP* jefe4 = al_load_bitmap("IMAGENES/don4.png");

		//lavayos
		ALLEGRO_BITMAP* lacayo = al_load_bitmap("IMAGENES/lacayo1.png");
		ALLEGRO_BITMAP* lacayo2 = al_load_bitmap("IMAGENES/lacayo2.png");

		//princesa
		ALLEGRO_BITMAP* princes1 = al_load_bitmap("IMAGENES/peach1.png");
		ALLEGRO_BITMAP* princes2 = al_load_bitmap("IMAGENES/peach2.png");




		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(songNivel3);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());


		al_play_sample_instance(song_instance);



		// defino lista de eventos



		int plataformaUno[16][28] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,11,12,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,14,13,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,4,4,4,4,4,0,0,2,2,4,4,4,4,4,4,4,4,4,0,4,4,5,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,2,2,2,4,4,4,4,5,0,5,2,0,2,3,2,2,2,2,2,2,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,3,0,0,0,0,0,0,0,0},
			{0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,3,0,0,0,9,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,3,0,0,0,0,0,0,0,0},
			{0,2,0,6,2,2,0,2,2,0,2,2,2,2,2,4,0,0,4,4,4,0,4,4,5,4,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{7,2,4,4,4,4,4,7,7,2,2,7,2,2,0,2,2,4,4,4,4,4,4,4,4,4,4,7},
		};
		bool salir;


		//mario 
		float x, y, moveSpeed = 5;
		float velx, vely;
		int desplaza;

		int paso;

		int dir;
		// barriles spawn 1
		int barrily1[3] = { 100,100,100 };
		int barrilx1[3] = { 350,350,350 };
		int cantBarriles = 100;
		int barDir[3] = { 1,1,1 };

		// barriles spawn 2
		int barrily2[3] = { 100,100,100 };
		int barrilx2[3] = { 550,550,550 };
		int cantBarriles2 = 100;
		int barDir2[3] = { 1,1,1 };

		// barriles spawn 3
		int barrily3[3] = { 100,100,100 };
		int barrilx3[3] = { 750,750,750 };
		int cantBarriles3 = 100;
		int barDir3[3] = { 1,1,1 };

		// estrella

		bool marioStar = false;
		int timeStar = 500;
		int contStar = 0;

		srand(time(0));





		// inicializar variables

		x = 50;

		y = 700;

		velx = vely = 0;

		moveSpeed = 4;


		paso = 0;

		dir = 0;


		salir = false;

		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
		ALLEGRO_KEYBOARD_STATE keyState;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));





		al_start_timer(timer);


		while (!salir)

		{
			ALLEGRO_EVENT evento;

			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 




			// clear_to_color(buffer, 0x785a5a);

			al_clear_to_color(al_map_rgb(0, 0, 0));

			//vidas

			for (int contLife = 0; contLife < vida; contLife++) {
				al_draw_bitmap(life, contLife * 50, 0, 0);
			}


			for (int xmap = 15; xmap >= 0; xmap--) {
				for (int ymap = 27; ymap >= 0; ymap--) {
					if (plataformaUno[xmap][ymap] == 2) {
						al_draw_bitmap(floor, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 4) {
						al_draw_bitmap(floor, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 3) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 5) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 6) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 8) {
						al_draw_bitmap(princes2, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 9) {
						al_draw_bitmap(star, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 11) {
						al_draw_bitmap(jefe1, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 12) {
						al_draw_bitmap(jefe2, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 13) {
						al_draw_bitmap(jefe3, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 14) {
						al_draw_bitmap(jefe4, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 16) {
						al_draw_bitmap(princes1, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 17) {
						al_draw_bitmap(lacayo2, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 18) {
						al_draw_bitmap(lacayo, (ymap * 50), (xmap * 50), 0);
					}
				}

			}
			//print set Barril 1

			for (int posBar = 0; posBar < cantBarriles / 80; posBar++) {
				al_draw_bitmap(barril, barrilx1[posBar], barrily1[posBar], 0);



			}

			//movimiento barriles
			for (int posBar = 0; posBar < cantBarriles / 100; posBar++) {
				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 4) {
					barrilx1[posBar] += 3;
				}

				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 5) {
					barrilx1[posBar] += 3;
				}

				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 2) {
					barrilx1[posBar] -= 3;
				}

				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 6) {
					barrilx1[posBar] -= 3;
				}


				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 0) {
					barrily1[posBar] += 2;

				}
				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 7) {

					barrily1[posBar] = 100;
					barrilx1[posBar] = 350;
				}






			}



			if (cantBarriles / 100 < 3) {
				cantBarriles++;
			}
			for (int posBar = 0; posBar < 3; posBar++) {
				if (barrily1[posBar] > 700 || barrilx1[posBar] > 1350) {
					barrily1[posBar] = 100;
					barrilx1[posBar] = 350;
				}
			}

			//Colision Barriles Set 1.
			for (int posBar = 0; posBar < 6; posBar++) {
				if (barrily1[posBar] >= y - 10 && barrily1[posBar] + 50 <= y + 60 && barrilx1[posBar] >= x - 10 && barrilx1[posBar] + 50 <= x + 60 && marioStar) {
					barrily1[posBar] = 100;
					barrilx1[posBar] = 350;

				}
				else if (barrily1[posBar] >= y - 10 && barrily1[posBar] + 50 <= y + 60 && barrilx1[posBar] >= x - 10 && barrilx1[posBar] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}

			}
			//Print Barriles set 2


			for (int posBar2 = 0; posBar2 < cantBarriles2 / 80; posBar2++) {
				al_draw_bitmap(barril, barrilx2[posBar2], barrily2[posBar2], 0);



			}

			//movimiento barriles
			for (int posBar2 = 0; posBar2 < cantBarriles2 / 100; posBar2++) {
				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 4) {
					barrilx2[posBar2] += 3;
				}

				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 5) {
					barrilx2[posBar2] += 3;
				}

				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 2) {
					barrilx2[posBar2] -= 3;
				}

				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 6) {
					barrilx2[posBar2] -= 3;
				}


				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 0) {
					barrily2[posBar2] += 2;

				}
				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 7) {

					barrily2[posBar2] = 100;
					barrilx2[posBar2] = 550;
				}






			}



			if (cantBarriles2 / 100 < 3) {
				cantBarriles2++;
			}
			for (int posBar2 = 0; posBar2 < 3; posBar2++) {
				if (barrily2[posBar2] > 700 || barrilx2[posBar2] > 1350) {
					barrily2[posBar2] = 100;
					barrilx2[posBar2] = 550;
				}
			}

			//Colision Barriles Set 2.
			for (int posBar2 = 0; posBar2 < 6; posBar2++) {
				if (barrily2[posBar2] >= y - 10 && barrily2[posBar2] + 50 <= y + 60 && barrilx2[posBar2] >= x - 10 && barrilx2[posBar2] + 50 <= x + 60 && marioStar) {
					barrily2[posBar2] = 100;
					barrilx2[posBar2] = 550;

				}
				else if (barrily2[posBar2] >= y - 10 && barrily2[posBar2] + 50 <= y + 60 && barrilx2[posBar2] >= x - 10 && barrilx2[posBar2] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}

			}
			//Print Barriles set 3


			for (int posBar3 = 0; posBar3 < cantBarriles3 / 80; posBar3++) {
				al_draw_bitmap(barril, barrilx3[posBar3], barrily3[posBar3], 0);



			}

			//movimiento barriles
			for (int posBar3 = 0; posBar3 < cantBarriles3 / 100; posBar3++) {
				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 4) {
					barrilx3[posBar3] += 3;
				}

				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 5) {
					barrilx3[posBar3] += 3;
				}

				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 2) {
					barrilx3[posBar3] -= 3;
				}

				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 6) {
					barrilx3[posBar3] -= 3;
				}


				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 0) {
					barrily3[posBar3] += 2;

				}
				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 7) {

					barrily3[posBar3] = 100;
					barrilx3[posBar3] = 750;
				}






			}



			if (cantBarriles3 / 100 < 3) {
				cantBarriles3++;
			}
			for (int posBar3 = 0; posBar3 < 3; posBar3++) {
				if (barrily3[posBar3] > 700 || barrilx3[posBar3] > 1350) {
					barrily3[posBar3] = 100;
					barrilx3[posBar3] = 750;
				}
			}
			//Colision Barriles.
			for (int posBar3 = 0; posBar3 < 6; posBar3++) {
				if (barrily3[posBar3] >= y - 10 && barrily3[posBar3] + 50 <= y + 60 && barrilx3[posBar3] >= x - 10 && barrilx3[posBar3] + 50 <= x + 60 && marioStar) {
					cout << vida << endl;
					barrily3[posBar3] = 100;
					barrilx3[posBar3] = 750;
				}
				else if (barrily3[posBar3] >= y - 10 && barrily3[posBar3] + 50 <= y + 60 && barrilx3[posBar3] >= x - 10 && barrilx3[posBar3] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}
			}


			// masked_blit(prota, buffer, paso*32, dir*32, x, y, 32,32);

			if (marioStar) {

				al_draw_bitmap_region(protaStar, paso * 48, dir * 48, 48, 48, x, y, 0);
				contStar++;
				if (contStar > timeStar) {
					marioStar = false;
					contStar = 0;
				}
			}
			else {
				al_draw_bitmap_region(prota, paso * 48, dir * 48, 48, 48, x, y, 0);
			}

			// colision estrella
			if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 24) * 28) / 1400)] == 9) {
				plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 24) * 28) / 1400)] = 0;
				marioStar = true;

			}

			//colision plataforma caida
			if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 0 || plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 7 && !salto) {
				caer = true;
				cout << y << endl;

			}
			else {
				caer = false;


			}
			if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 7) {

				vida--;
				x = 50;
				y = 700;
				

			}

			if (caer) {

				y += 3;


			}
			if (salto && contSalto <= altSalto) {
				contSalto += 12;
				y -= 12;
			}
			else {
				salto = false;

				contSalto = 0;
			}

			// mostramos la pantalla

			// blit(buffer, screen, 0, 0, 0, 0, 800, 600);

			al_flip_display();


			al_wait_for_event(event_queue, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&keyState);

			// mario movimiento
			if (al_key_down(&keyState, ALLEGRO_KEY_UP))

			{

				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 3) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 6) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 5) {
					
					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 8) {
					al_destroy_sample(songNivel3);
					winGame();
					y -= 5;

					dir = 3;

					paso++;
				}

			}

			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))

			{
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 3) {

					y += 3;

					dir = 0;

					paso++;
				}
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 5) {

					y += 3;

					dir = 0;

					paso++;
				}
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 6) {

					y += 3;

					dir = 0;

					paso++;
				}
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))

			{


				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 48) * 28) / 1400) - 1] != 2) {

					x -= 3;




				}
				paso++;
				dir = 1;
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))

			{
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x) * 28) / 1400) + 1] != 2) {
					x += 3;





				}
				paso++;
				dir = 2;


			}

			if (!caer && !salto && !al_key_down(&wait_key_State, ALLEGRO_KEY_SPACE) && al_key_down(&keyState, ALLEGRO_KEY_SPACE) && plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] != 3) {

				salto = true;



			}
			cout << salto << endl;


			// limitadores


			if (x < 0) x = 0;

			if (x > 1400 - 48) x = 1400 - 48;

			if (y < 0) y = 0;

			if (y > 800 - 48) y = 800 - 48;


			if (paso > 2) paso = 0;


			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
				al_destroy_sample(songNivel3);
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



int plataformaDos()
{
	{

		const float FPS = 60.0;
		// allegro_init();

		al_init();

		al_init_image_addon();


		al_install_keyboard();





		// BITMAP* prota = load_bmp("personaje.bmp", NULL);



		ALLEGRO_BITMAP* prota = al_load_bitmap("IMAGENES/mario_quieto.png");
		ALLEGRO_BITMAP* mapaUno = al_load_bitmap("IMAGENES/mapa_Uno.png");
		ALLEGRO_BITMAP* floor = al_load_bitmap("IMAGENES/floorDos.png");
		ALLEGRO_BITMAP* escalera = al_load_bitmap("IMAGENES/escaleraDOs.png");
		ALLEGRO_SAMPLE* songNivel2 = al_load_sample("sonidos/songNivelDos.mp3");
		ALLEGRO_BITMAP* barril = al_load_bitmap("IMAGENES/barrilDos.png");

		ALLEGRO_BITMAP* star = al_load_bitmap("IMAGENES/star.png");
		ALLEGRO_BITMAP* protaStar = al_load_bitmap("IMAGENES/mario_estrella.png");
		ALLEGRO_BITMAP* life = al_load_bitmap("IMAGENES/vidas.png");

		//lavayos
		ALLEGRO_BITMAP* lacayo = al_load_bitmap("IMAGENES/lacayo1.png");
		ALLEGRO_BITMAP* lacayo2 = al_load_bitmap("IMAGENES/lacayo2.png");


		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(songNivel2);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());


		al_play_sample_instance(song_instance);



		// defino lista de eventos



		int plataformaUno[16][28] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,10,0,0,0,0,0,11,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,4,4,4,4,4,0,0,2,2,4,4,4,4,4,4,4,4,4,0,4,4,5,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,2,2,2,4,4,4,4,4,5,4,0,2,2,2,0,2,2,2,2,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,9,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,4,4,5,4,4,4,0,0,4,4,4,4,4,3,4,0,0,4,4,4,0,4,4,5,4,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{7,2,2,2,2,2,2,7,7,2,2,2,2,2,7,7,7,2,2,2,2,7,2,2,2,2,2,7},
		};
		bool salir;


		//mario 
		float x, y, moveSpeed = 5;
		float velx, vely;
		int desplaza;

		int paso;

		int dir;
		// barriles spawn 1
		int barrily1[3] = { 100,100,100 };
		int barrilx1[3] = { 350,350,350 };
		int cantBarriles = 100;
		int barDir[3] = { 1,1,1 };

		// barriles spawn 2
		int barrily2[3] = { 100,100,100 };
		int barrilx2[3] = { 550,550,550 };
		int cantBarriles2 = 100;
		int barDir2[3] = { 1,1,1 };

		// barriles spawn 3
		int barrily3[3] = { 100,100,100 };
		int barrilx3[3] = { 750,750,750 };
		int cantBarriles3 = 100;
		int barDir3[3] = { 1,1,1 };

		// estrella

		bool marioStar = false;
		int timeStar = 500;
		int contStar = 0;

		srand(time(0));


		


		// inicializar variables

		x = 50;

		y = 700;

		velx = vely = 0;

		moveSpeed = 4;


		paso = 0;

		dir = 0;


		salir = false;

		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
		ALLEGRO_KEYBOARD_STATE keyState;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));





		al_start_timer(timer);


		while (!salir)

		{
			ALLEGRO_EVENT evento;

			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 




			// clear_to_color(buffer, 0x785a5a);

			al_clear_to_color(al_map_rgb(0, 0, 0));

			//vidas

			for (int contLife = 0; contLife < vida; contLife++) {
				al_draw_bitmap(life, contLife * 50, 0, 0);
			}


			for (int xmap = 15; xmap >= 0; xmap--) {
				for (int ymap = 27; ymap >= 0; ymap--) {
					if (plataformaUno[xmap][ymap] == 2) {
						al_draw_bitmap(floor, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 4) {
						al_draw_bitmap(floor, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 3) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 5) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 6) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 8) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 9) {
						al_draw_bitmap(star, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 10) {
						al_draw_bitmap(lacayo, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 11) {
						al_draw_bitmap(lacayo2, (ymap * 50), (xmap * 50), 0);
					}
				}

			}

			//print set Barril 1

			for (int posBar = 0; posBar < cantBarriles / 80; posBar++) {
				al_draw_bitmap(barril, barrilx1[posBar], barrily1[posBar], 0);



			}

			//movimiento barriles
			for (int posBar = 0; posBar < cantBarriles / 100; posBar++) {
				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 4) {
					barrilx1[posBar] += 3;
				}

				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 5) {
					barrilx1[posBar] += 3;
				}

				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 2) {
					barrilx1[posBar] -= 3;
				}

				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 6) {
					barrilx1[posBar] -= 3;
				}


				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 0) {
					barrily1[posBar] += 2;

				}
				if (plataformaUno[lround(((barrily1[posBar]) * 16) / 800) + 1][lround(((barrilx1[posBar] + 24) * 28) / 1400)] == 7) {

					barrily1[posBar] = 100;
					barrilx1[posBar] = 350;
				}






			}



			if (cantBarriles / 100 < 3) {
				cantBarriles++;
			}
			for (int posBar = 0; posBar < 3; posBar++) {
				if (barrily1[posBar] > 700 || barrilx1[posBar] > 1350) {
					barrily1[posBar] = 100;
					barrilx1[posBar] = 350;
				}
			}
		
			//Colision Barriles Set 1.
			for (int posBar = 0; posBar < 6; posBar++) {
				if (barrily1[posBar] >= y - 10 && barrily1[posBar] + 50 <= y + 60 && barrilx1[posBar] >= x - 10 && barrilx1[posBar] + 50 <= x + 60 && marioStar) {
					barrily1[posBar] = 100;
					barrilx1[posBar] = 350;

				}
				else if (barrily1[posBar] >= y - 10 && barrily1[posBar] + 50 <= y + 60 && barrilx1[posBar] >= x - 10 && barrilx1[posBar] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}

			}
			//Print Barriles set 2


			for (int posBar2 = 0; posBar2 < cantBarriles2 / 80; posBar2++) {
				al_draw_bitmap(barril, barrilx2[posBar2], barrily2[posBar2], 0);



			}

			//movimiento barriles
			for (int posBar2 = 0; posBar2 < cantBarriles2 / 100; posBar2++) {
				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 4) {
					barrilx2[posBar2] += 3;
				}

				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 5) {
					barrilx2[posBar2] += 3;
				}

				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 2) {
					barrilx2[posBar2] -= 3;
				}

				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 6) {
					barrilx2[posBar2] -= 3;
				}


				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 0) {
					barrily2[posBar2] += 2;

				}
				if (plataformaUno[lround(((barrily2[posBar2]) * 16) / 800) + 1][lround(((barrilx2[posBar2] + 24) * 28) / 1400)] == 7) {

					barrily2[posBar2] = 100;
					barrilx2[posBar2] = 550;
				}






			}



			if (cantBarriles2 / 100 < 3) {
				cantBarriles2++;
			}
			for (int posBar2 = 0; posBar2 < 3; posBar2++) {
				if (barrily2[posBar2] > 700 || barrilx2[posBar2] > 1350) {
					barrily2[posBar2] = 100;
					barrilx2[posBar2] = 550;
				}
			}
			
			//Colision Barriles Set 2.
			for (int posBar2 = 0; posBar2 < 6; posBar2++) {
				if (barrily2[posBar2] >= y - 10 && barrily2[posBar2] + 50 <= y + 60 && barrilx2[posBar2] >= x - 10 && barrilx2[posBar2] + 50 <= x + 60 && marioStar) {
					barrily2[posBar2] = 100;
					barrilx2[posBar2] = 550;

				}
				else if (barrily2[posBar2] >= y - 10 && barrily2[posBar2] + 50 <= y + 60 && barrilx2[posBar2] >= x - 10 && barrilx2[posBar2] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}

			}
			//Print Barriles set 3


			for (int posBar3 = 0; posBar3 < cantBarriles3 / 80; posBar3++) {
				al_draw_bitmap(barril, barrilx3[posBar3], barrily3[posBar3], 0);



			}

			//movimiento barriles
			for (int posBar3 = 0; posBar3 < cantBarriles3 / 100; posBar3++) {
				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 4) {
					barrilx3[posBar3] += 3;
				}

				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 5) {
					barrilx3[posBar3] += 3;
				}

				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 2) {
					barrilx3[posBar3] -= 3;
				}

				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 6) {
					barrilx3[posBar3] -= 3;
				}


				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 0) {
					barrily3[posBar3] += 2;

				}
				if (plataformaUno[lround(((barrily3[posBar3]) * 16) / 800) + 1][lround(((barrilx3[posBar3] + 24) * 28) / 1400)] == 7) {

					barrily3[posBar3] = 100;
					barrilx3[posBar3] = 750;
				}






			}



			if (cantBarriles3 / 100 < 3) {
				cantBarriles3++;
			}
			for (int posBar3 = 0; posBar3 < 3; posBar3++) {
				if (barrily3[posBar3] > 700 || barrilx3[posBar3] > 1350) {
					barrily3[posBar3] = 100;
					barrilx3[posBar3] = 750;
				}
			}
			//Colision Barriles.
			for (int posBar3 = 0; posBar3 < 6; posBar3++) {
				if (barrily3[posBar3] >= y - 10 && barrily3[posBar3] + 50 <= y + 60 && barrilx3[posBar3] >= x - 10 && barrilx3[posBar3] + 50 <= x + 60 && marioStar) {
					cout << vida << endl;
					barrily3[posBar3] = 100;
					barrilx3[posBar3] = 550;
				}
				else if (barrily3[posBar3] >= y - 10 && barrily3[posBar3] + 50 <= y + 60 && barrilx3[posBar3] >= x - 10 && barrilx3[posBar3] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}
			}

			
			
			// masked_blit(prota, buffer, paso*32, dir*32, x, y, 32,32);

			// masked_blit(prota, buffer, paso*32, dir*32, x, y, 32,32);
			if (marioStar) {

				al_draw_bitmap_region(protaStar, paso * 48, dir * 48, 48, 48, x, y, 0);
				contStar++;
				if (contStar > timeStar) {
					marioStar = false;
					contStar = 0;
				}
			}
			else {
				al_draw_bitmap_region(prota, paso * 48, dir * 48, 48, 48, x, y, 0);
			}

			// colision estrella
			if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 24) * 28) / 1400)] == 9) {
				plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 24) * 28) / 1400)] = 0;
				marioStar = true;

			}

			//colision plataforma caida
			if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 0 || plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 7 && !salto) {
				caer = true;
				cout << y << endl;

			}
			else {
				caer = false;


			}
			if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 7) {

				vida--;
				x = 50;
				y = 700;


			}

			if (caer) {

				y += 3;


			}
			if (salto && contSalto <= altSalto) {
				contSalto += 12;
				y -= 12;
			}
			else {
				salto = false;

				contSalto = 0;
			}

			// mostramos la pantalla

			// blit(buffer, screen, 0, 0, 0, 0, 800, 600);

			al_flip_display();


			al_wait_for_event(event_queue, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&keyState);

			// mario movimiento
			if (al_key_down(&keyState, ALLEGRO_KEY_UP))

			{

				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 3) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 6) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 5) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 8) {
					al_destroy_sample(songNivel2);
					plataformaTres();
					y -= 5;

					dir = 3;

					paso++;
				}

			}

			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))

			{
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 3) {

					y += 3;

					dir = 0;

					paso++;
				}
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 5) {

					y += 3;

					dir = 0;

					paso++;
				}
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 6) {

					y += 3;

					dir = 0;

					paso++;
				}
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))

			{


				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 48) * 28) / 1400) - 1] != 2) {

					x -= 3;




				}
				paso++;
				dir = 1;
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))

			{
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x) * 28) / 1400) + 1] != 2) {
					x += 3;





				}
				paso++;
				dir = 2;


			}

			if (!caer && !salto && !al_key_down(&wait_key_State, ALLEGRO_KEY_SPACE) && al_key_down(&keyState, ALLEGRO_KEY_SPACE) && plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] != 3) {

				salto = true;



			}
			cout << salto << endl;


			// limitadores


			if (x < 0) x = 0;

			if (x > 1400 - 48) x = 1400 - 48;

			if (y < 0) y = 0;

			if (y > 800 - 48) y = 800 - 48;


			if (paso > 2) paso = 0;


			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE) || vida <= 0) {

				if (vida <= 0) {
					al_destroy_sample(songNivel2);
					salir = true;
					gameOver();
					// game over
				}
				else {
					al_destroy_sample(songNivel2);
					salir = true;
					menu();
					// menu();
				}

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

int nivelUno()
{
	{
		
		const float FPS = 60.0;
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
		ALLEGRO_BITMAP* barril = al_load_bitmap("IMAGENES/barril.png");
		ALLEGRO_BITMAP* star = al_load_bitmap("IMAGENES/star.png");
		ALLEGRO_BITMAP* protaStar = al_load_bitmap("IMAGENES/mario_estrella.png");
		ALLEGRO_BITMAP* life = al_load_bitmap("IMAGENES/vidas.png");

		//lavayos
		ALLEGRO_BITMAP* lacayo = al_load_bitmap("IMAGENES/lacayo1.png");


		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(songNivel1);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());


		al_play_sample_instance(song_instance);



		// defino lista de eventos

	

		int plataformaUno[16][28] = {
			{0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,10,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,2,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0},
			{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
			{7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7},
		};
		bool salir;

		

		int desplaza;

		int paso;

		int dir;
		// barriles
		int barrily[6 ] = {100,100,100,100,100,100};
		int barrilx[6] = {350,350,350,350,350,350};
		int cantBarriles = 100;
		int barDir[6]={1,1,1,1,1,1};

		// estrella
		
		bool marioStar = false;
		int timeStar = 500;
		int contStar = 0;


		
	
		srand(time(0));


		float x, y, moveSpeed = 5;
		float velx, vely;


		// inicializar variables

		x = 50;

		y = 700;
		
		velx = vely = 0;

		moveSpeed = 4;


		paso = 0;

		dir = 0;


		salir = false;

		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
		ALLEGRO_KEYBOARD_STATE keyState;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));


		


		al_start_timer(timer);

		
		while (!salir)

		{
			ALLEGRO_EVENT evento;

			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 

			

			// clear_to_color(buffer, 0x785a5a);
			
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//vidas
			
			for (int contLife = 0; contLife < vida; contLife++) {
				al_draw_bitmap(life, contLife*50, 0, 0);
			}


			// print mapa

			for (int xmap = 15; xmap >= 0; xmap--) {
				for (int ymap = 27; ymap >=0; ymap--) {
					if (plataformaUno[xmap][ymap] == 2) {
						al_draw_bitmap(floor, (ymap*50), (xmap*50), 0);

					}
					if (plataformaUno[xmap][ymap] == 4) {
						al_draw_bitmap(floor, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 3) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 5) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 6) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);

					}
					if (plataformaUno[xmap][ymap] == 8) {
						al_draw_bitmap(escalera, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 9) {
						al_draw_bitmap(star, (ymap * 50), (xmap * 50), 0);
					}
					if (plataformaUno[xmap][ymap] == 10) {
						al_draw_bitmap(lacayo, (ymap * 50), (xmap * 50), 0);
					}
				}

			}

			//print Barril
			
			for (int posBar = 0; posBar < cantBarriles/100; posBar++) {
				al_draw_bitmap(barril, barrilx[posBar], barrily[posBar], 0);
				
				

			}

			//movimiento barriles
			for (int posBar = 0; posBar < cantBarriles / 100; posBar++) {
				if (plataformaUno[lround(((barrily[posBar]) * 16) / 800) + 1][lround(((barrilx[posBar] + 24) * 28) / 1400)] == 4) {
					barrilx[posBar] += 5;
				}

				if (plataformaUno[lround(((barrily[posBar]) * 16) / 800) + 1][lround(((barrilx[posBar] + 24) * 28) / 1400)] == 5) {
					barrilx[posBar] += 5;
				}
			
				if (plataformaUno[lround(((barrily[posBar]) * 16) / 800) + 1][lround(((barrilx[posBar] + 24) * 28) / 1400)] == 2) {
					barrilx[posBar] -= 5;
				}
					
				if (plataformaUno[lround(((barrily[posBar]) * 16) / 800) + 1][lround(((barrilx[posBar] + 24) * 28) / 1400)] == 6) {
					barrilx[posBar] -= 5;
				}
					
					
				if (plataformaUno[lround(((barrily[posBar]) * 16) / 800) + 1][lround(((barrilx[posBar] + 24) * 28) / 1400)] == 0) {
					barrily[posBar] += 5;

				}
				if (plataformaUno[lround(((barrily[posBar]) * 16) / 800) + 1][lround(((barrilx[posBar] + 24) * 28) / 1400)] == 7) {
					
					barrily[posBar] = 100;
					barrilx[posBar] = 350;
				}
				
				

				
				
				
			}
			


			if (cantBarriles / 100 < 6) {
				cantBarriles++;
			}
			for (int posBar = 0; posBar < 6; posBar++) {
				if (barrily[posBar] > 700 || barrilx[posBar] >1350) {
					barrily[posBar] = 100;
					barrilx[posBar] = 350;
				}
			}

			//Colision Barriles.
			for (int posBar = 0; posBar < 6; posBar++) {
				if (barrily[posBar] >= y - 10 && barrily[posBar] + 50 <= y + 60 && barrilx[posBar] >= x - 10 && barrilx[posBar] + 50 <= x + 60 && marioStar) {
					barrily[posBar] = 100;
					barrilx[posBar] = 350;

				}
				else if (barrily[posBar] >= y-10 && barrily[posBar] + 50 <= y + 60 && barrilx[posBar] >= x-10 && barrilx[posBar] + 50 <= x + 60) {
					cout << vida << endl;
					x = 50;
					y = 700;
					vida--;
				}
				 
			}

			// masked_blit(prota, buffer, paso*32, dir*32, x, y, 32,32);
			if (marioStar) {
				
				al_draw_bitmap_region(protaStar, paso * 48, dir * 48, 48, 48, x, y, 0);
				contStar++;
				if (contStar > timeStar) {
					marioStar = false;
					contStar = 0;
				}
			}
			else {
				al_draw_bitmap_region(prota, paso * 48, dir * 48, 48, 48, x, y, 0);
			}
			
			// colision estrella
			if (plataformaUno[lround(((y + 24) * 16) / 800) ][lround(((x + 24) * 28) / 1400)] == 9) {
				plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x + 24) * 28) / 1400)] = 0;
				marioStar = true;

			}

			//colision plataforma caida
			if (plataformaUno[lround(((y-24)*16) / 800)+1][lround(((x+48)*28)/1400)]==0 || plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 48) * 28) / 1400)] == 7 && !salto ) {
				caer = true;
				cout << y << endl;

			}
			else {
				caer = false;
				
				
			}
			if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x + 24) * 28) / 1400)] == 7) {

				vida--;
				x = 50;
				y = 700;


			}

			if (caer) {
				
					y += 3;
				
				
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


			al_wait_for_event(event_queue, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&keyState);

			// mario movimiento
			if (al_key_down(&keyState, ALLEGRO_KEY_UP))

			{

				if (plataformaUno[lround(((y+24) * 16) / 800) ][lround(((x - 24) * 28) / 1400)] == 3) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 6) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 5) {

					y -= 5;

					dir = 3;

					paso++;
				}
				if (plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] == 8) {
					al_destroy_sample(songNivel1);
					plataformaDos();
					y -= 5;

					dir = 3;

					paso++;
				}

			}
			
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))

			{
				if (plataformaUno[lround(((y-24) * 16) / 800)+1][lround(((x - 24) * 28) / 1400) ] == 3 ){

					y+=3;

					dir = 0;

					paso++;
				}
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 5  ) {

					y += 3;

					dir = 0;

					paso++;
				}
				if (plataformaUno[lround(((y - 24) * 16) / 800) + 1][lround(((x - 24) * 28) / 1400)] == 6  ) {

					y += 3;

					dir = 0;

					paso++;
				}
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))

			{

				
				if (plataformaUno[lround(((y+24) * 16) / 800) ][lround(((x+48) * 28) / 1400)-1] != 2 ) {
					
					x -= 3;

					

					
				}
				paso++;
				dir = 1;
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))

			{
				if (plataformaUno[lround(((y+24) * 16) / 800)][lround(((x) * 28) / 1400) + 1] != 2) {
					x += 3;

					

					

				}
				paso++;
				dir = 2;
				

			}

			if (!caer && !salto && !al_key_down(&wait_key_State, ALLEGRO_KEY_SPACE) && al_key_down(&keyState, ALLEGRO_KEY_SPACE) && plataformaUno[lround(((y + 24) * 16) / 800)][lround(((x - 24) * 28) / 1400)] != 3) {
				
				salto = true;	
					
				

			}
			cout << salto  << endl;

			
			// limitadores


			if (x < 0) x = 0;

			if (x > 1400 - 48) x = 1400 - 48;

			if (y < 0) y = 0;

			if (y > 800 - 48) y = 800 - 48;


			if (paso > 2) paso = 0;


			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)|| vida <= 0) {
				
				if (vida <= 0) {
					al_destroy_sample(songNivel1);
					salir = true;
					gameOver();
					// game over
				}
				else {
					al_destroy_sample(songNivel1);
					salir = true;
					menu();
					// menu();
				}

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


//creditos


int creditos()
{
	{

		const float FPS = 60.0;
		// allegro_init();

		al_init();

		al_init_image_addon();


		al_install_keyboard();


		int x1 = -1, y1 = -1;
		int segundos = 0;

		// BITMAP* prota = load_bmp("personaje.bmp", NULL);



		ALLEGRO_BITMAP* creditos_null = al_load_bitmap("IMAGENES/creditMenu.png");
		ALLEGRO_BITMAP* creditos_regresar = al_load_bitmap("IMAGENES/creditSalir.png");



		ALLEGRO_SAMPLE* creditSong = al_load_sample("sonidos/creditSong.mp3");

		al_reserve_samples(1);

		ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(creditSong);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());


		


		

		al_play_sample_instance(song_instance);



		// defino lista de eventos



		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
		ALLEGRO_KEYBOARD_STATE keyState;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));

		int botones2[] = { 0 };



		al_start_timer(timer);


		al_init();

		al_init_image_addon();


		al_install_keyboard();

		bool salir;




		srand(time(0));



		// inicializar variables

		salir = false;

		
		
		ALLEGRO_KEYBOARD_STATE keyState1;




		// creo lista de eventos

		event_queue = al_create_event_queue();


		// asigno eventos a la lista de eventos


		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_register_event_source(event_queue, al_get_display_event_source(ventana));





		al_start_timer(timer);


		while (!salir)

		{
			ALLEGRO_EVENT evento;

			al_get_keyboard_state(&wait_key_State);
			// pinta el fondo de un color 




			// clear_to_color(buffer, 0x785a5a);

			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			al_draw_bitmap(creditos_null, 0, 0, 0);
			

			
			// mostramos la pantalla

			// blit(buffer, screen, 0, 0, 0, 0, 800, 600);

			al_flip_display();


			al_wait_for_event(event_queue, &evento);



			// se ha cerrado la ventana

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

			{

				salir = true;

			}


			al_get_keyboard_state(&keyState);


			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
				al_destroy_sample(creditSong);
				salir = true;
				menu();

			}


		}


			

			
		
	}

			


	



		


		// destroy_display(pantalla);

		al_destroy_display(ventana);


		
	

	
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
					vida = 5;
					al_destroy_sample(menuSong);
					nivelUno();

					
				}
					
			}
			else {
				if (x >= 492 && x <= 822 && y >= 435 && y <= 486) {
					botones[0] = 2;
					al_play_sample(efectoMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					
					if (Evento.mouse.button & 1) {
						al_destroy_sample(menuSong);
						creditos();
						

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

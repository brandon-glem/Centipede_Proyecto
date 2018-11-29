#include <allegro.h>

#include <stdlib.h>
#include <time.h>

#include "diseno.h"
#include "mapa.h"
#include "jugador.h"
#include "disparos.h"
#include "cucaracha.h"
#include "escorpion.h"
#include "centipedo.h"

//PANTALLA
#define ANCHO 680
#define ALTO 748

void init();
void deinit();

void explocion_nave(int x, int y, BITMAP *img_explosion, BITMAP *buffer, BITMAP *fondo){
     BITMAP *parche = create_bitmap(48,24);
     clear_to_color(buffer,0x000000);
     for(int i = 0; i < 9; i++){
             blit(parche, buffer, 0, 0, x, y, 48, 24);
             masked_blit(img_explosion, buffer, i*48, 0, x, y, 48, 24);
             imprimir_fondo(fondo, buffer);
             blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
             rest(125);
             }
     }

int num, tick1=0, tick2=0, mov=0; //fluidez de imagenes

int ale(int &num){
    srand(time(NULL));

    num = 1 + rand() % (6 - 1);

    return num;
}

bool temporizador(int n,int &tick){
     tick++;
     if(tick == n){
             tick = 0;
             return true;
             }
     return false;
     }

void elimina_bala_hongo(nave &n, struct mapa HO[], struct Balas B[]){
     if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                for(int i = 0; i < 64; i++){
                      if(colicion(HO[i].x, HO[i].y, 24, 24, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala) && HO[i].dan < 4){
                                           eliminar(B, n.n_disp, cont);
                                           HO[i].dan += 1;
                                           }
                      }
                }
            }
     }

void elimina_bala_cucaracha(nave &n, cucaracha &c, struct Balas B[]){
     if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                for(int i = 0; i < 64; i++){
                      if(colicion(c.x, c.y, c.ancho_cucaracha, c.alto_cucaracha, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala)){
                                           eliminar(B, n.n_disp, cont);
                                           c.cambio_pos();
                                           }
                      }
                 }
            }
     }

void elimina_nave_cucaracha(nave &n, cucaracha &c, BITMAP *buffer, BITMAP *fondo, BITMAP *explosion_nave){
     if(colicion(n.x,n.y,n.ancho_nave,n.alto_nave,c.x,c.y,c.ancho_cucaracha,c.alto_cucaracha) && n.vidas > 0){
                                                                                               n.vidas -= 1;
                                                                                               explocion_nave(n.x, n.y, explosion_nave, buffer, fondo);
                                                                                               n.cambio();
                                                                                               c.cambio_pos();
                                                                                               //rest(5);
            }
     }

void elimina_bala_escorpion(nave &n, escorpion &s, struct Balas B[]){
     if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                for(int i = 0; i < 64; i++){
                      if(colicion(s.x, s.y, s.ancho_escorpion, s.alto_escorpion, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala)){
                                           eliminar(B, n.n_disp, cont);
                                           s.cambio_pos();
                                           }
                      }
                 }
            }
     }

void elimina_nave_escorpion(nave &n, escorpion &s, BITMAP *buffer, BITMAP *fondo, BITMAP *explosion_nave){
     if(colicion(n.x, n.y, n.ancho_nave, n.alto_nave, s.x, s.y, s.ancho_escorpion, s.alto_escorpion) && n.vidas > 0){
                                                                                               n.vidas -= 1;
                                                                                               explocion_nave(n.x, n.y, explosion_nave, buffer, fondo);
                                                                                               n.cambio();
                                                                                               s.cambio_pos();
                                                                                               //rest(5);
            }
     }

void cambio_hongo(escorpion s,struct mapa HO[]){
    for(int i = 0; i < 64; i++){
        if(colicion(HO[i].x, HO[i].y, 24-1, 24-1, s.x, s.y, 0, 0)){
           HO[i].tipo = 1;
        }
    }
}

int main(){
	init();

	//IMAGENES
	BITMAP *buffer = create_bitmap(ANCHO,ALTO); //PANTALLA NEGRA
    BITMAP *portada = load_bitmap("imagenes/Recursos/portada.bmp", NULL);
    BITMAP *fin = load_bitmap("imagenes/Recursos/fin.bmp",NULL);
    BITMAP *fondo = load_bitmap("imagenes/Recursos/fondo.bmp", NULL);
    BITMAP *hongo = load_bitmap("imagenes/level_1/hongo.bmp",NULL);
    BITMAP *explosion_nave = load_bitmap("imagenes/level_1/explocion-nave.bmp",NULL);
    BITMAP *cabeza = load_bitmap("imagenes/level_1/cabeza.bmp",NULL);
    BITMAP *cuerpo = load_bitmap("imagenes/level_1/cuerpo.bmp",NULL);

    PORTADA(portada,384);

    nave n("imagenes/level_1/nave-1.bmp","imagenes/level_1/disparo.bmp", 21, 24, 6, 20, ANCHO/2, ALTO-90);
    cucaracha c("imagenes/level_1/pulga.bmp","imagenes/level_1/hongo.bmp",27,24,24,24);
    escorpion s("imagenes/level_1/escorpion.bmp","imagenes/level_1/hongo.bmp",48,24,24,24);
    centipedo head("imagenes/level_1/cabeza.bmp",21,24);

    Balas disparos[n.max_disp]; //LISTA DE DISPAROS

    mapa HO[65];
    iniciar_mapa(HO);

	while(!key[KEY_ESC]) {

          clear_to_color(buffer,0x000000); //COLOR

          pinta_mapa(HO, hongo, buffer);

          n.pinta_nave(buffer);
          n.movimiento();

          head.pintar_centipedo(buffer, mov);
          head.movimiento(buffer);

          if(num == 2){
                         c.pintar_cucaracha(buffer,mov);
                         c.movimiento(buffer);
                         elimina_bala_cucaracha(n,c,disparos);
                         }

          if(num == 3){
                         s.pintar_escorpion(buffer,mov);
                         s.movimiento(buffer);
                         cambio_hongo(s,HO);
                         elimina_bala_escorpion(n,s,disparos);
                         }


          n.dispara(disparos, buffer);

          elimina_bala_hongo(n,HO,disparos);

          elimina_nave_cucaracha(n,c, buffer, fondo, explosion_nave);
	      elimina_nave_escorpion(n,s, buffer, fondo, explosion_nave);

	      imprimir_fondo(fondo, buffer);

	      if(temporizador(65,tick1)){
                             ale(num);
                             }

          if(temporizador(3,tick2)){ //velocidad, tiempo
                                    if((++mov) == 4){ //recorre cada imagen
                                            mov = 0;
                                            }
                                    }

	      if(n.vidas == 0){
                     PORTADA(fin, 100);
                     break;
                     }

	      blit(buffer,screen, 0, 0, 0, 0, ANCHO, ALTO); //PANTALLA NEGRA

          rest(20);
	}

	deinit();
	return 0;
}

END_OF_MAIN()

void init(){
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO, ALTO, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit(){
	clear_keybuf();
	/* add other deinitializations here */
}

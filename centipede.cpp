#include <allegro.h>

#include <enemigo.h>
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

////////////////////////////////////////////////////////CENTIPEDO
void acomoda_centipedo(centipedo CE[]){
    for(int i = 1; i<16; i++){
        CE[i].x += 21*i;
    }
}

//////////////////////////////////////////////////////////////////EXPLOCIONES
void explocion_nave(int x, int y, BITMAP *img_explosion, BITMAP *buffer, BITMAP *fondo, struct mapa HO[], BITMAP *hongo){
     BITMAP *parche = create_bitmap(48,24);
     clear_to_color(buffer,0x000000);
     for(int i = 0; i < 9; i++){
             blit(parche, buffer, 0, 0, x, y, 48, 24);
             masked_blit(img_explosion, buffer, i*48, 0, x, y, 48, 24);
             pinta_mapa(HO, hongo, buffer);
             imprimir_fondo(fondo, buffer);
             blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
             rest(125);
             }
     }

void explocion_enemigo(int x, int y, BITMAP *img_explosion, BITMAP *buffer, BITMAP *fondo, struct mapa HO[], BITMAP *hongo){
     BITMAP *parche = create_bitmap(24,24);
     clear_to_color(buffer,0x000000);
     for(int i = 0; i < 7; i++){
             blit(parche, buffer, 0, 0, x, y, 24, 24);
             masked_blit(img_explosion, buffer, i*24, 0, x, y, 24, 24);
             pinta_mapa(HO, hongo, buffer);
             imprimir_fondo(fondo, buffer);
             blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
             rest(20);
             }
     }

/////////////////////////////////////////////////////////Variables globales
int num, tick1=0, tick2=0, mov=0, crear; //fluidez de imagenes

int ale(int &num,int rang){
    srand(time(NULL));

    num = 1 + rand() % (rang - 1);

    return num;
}

void crear_hongo(cucaracha c, struct mapa HO[]){
    for(int i = 0; i < 61 ; i++){
            if(((ale(crear,5) == 3) && HO[i].dan == 4) && (c.y >= 178 && (c.x > 47 || c.x < 599 ))){
                        HO[i].x = c.x;
                        HO[i].y = c.y;
                        HO[i].dan = 0;
                        HO[i].tipo = 0;
            }
    }
}

bool temporizador(int n,int &tick){
     tick++;
     if(tick == n){
             tick = 0;
             return true;
             }
     return false;
     }

void cambiar_score(int &x, int &y){
    if(x >= 120){
        while(x > 120){
            x -= 120;
            y += 12;
        }
        if(x == 120){
            x=0;
            y+=12;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////COLISION BALAS - ENEMIGOS
void elimina_bala_hongo(nave &n, struct mapa HO[], struct Balas B[], int pos_x[], int puntajes[]){
     if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                for(int i = 0; i < 61; i++){
                      if(colicion(HO[i].x, HO[i].y, 24, 24, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala) && HO[i].dan < 4){
                                           eliminar(B, n.n_disp, cont);
                                           HO[i].dan += 1;
                                           if(HO[i].tipo == 0)
                                                pos_x[7] += (12 * puntajes[0]);
                                           else
                                                pos_x[7] += (12 * puntajes[1]);
                                           cambiar_score(pos_x[7],pos_x[6]);
                                           cambiar_score(pos_x[6],pos_x[5]);
                                           cambiar_score(pos_x[5],pos_x[4]);
                                           cambiar_score(pos_x[4],pos_x[3]);
                                           cambiar_score(pos_x[3],pos_x[2]);
                                           cambiar_score(pos_x[2],pos_x[1]);
                                           cambiar_score(pos_x[1],pos_x[0]);
                                           }
                      }
                }
            }
     }

void elimina_bala_cucaracha(nave &n, cucaracha &c, struct Balas B[], BITMAP *explosion_enemigo, BITMAP *buffer, BITMAP *fondo, struct mapa HO[], BITMAP *hongo,
                            int pos_x[], int puntajes[]){
     if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                for(int i = 0; i < 64; i++){
                      if(colicion(c.x, c.y, c.ancho_cucaracha, c.alto_cucaracha, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala)){
                                           explocion_enemigo(c.x,c.y,explosion_enemigo,buffer,fondo,HO,hongo);
                                           eliminar(B, n.n_disp, cont);
                                           c.cambio_pos();
                                           pos_x[7] += (12 * puntajes[2]);
                                           cambiar_score(pos_x[7],pos_x[6]);
                                           cambiar_score(pos_x[6],pos_x[5]);
                                           cambiar_score(pos_x[5],pos_x[4]);
                                           cambiar_score(pos_x[4],pos_x[3]);
                                           cambiar_score(pos_x[3],pos_x[2]);
                                           cambiar_score(pos_x[2],pos_x[1]);
                                           cambiar_score(pos_x[1],pos_x[0]);
                                           }
                      }
                 }
            }
     }

void elimina_bala_escorpion(nave &n, escorpion &s, struct Balas B[], BITMAP *explosion_enemigo, BITMAP *buffer, BITMAP *fondo, struct mapa HO[], BITMAP *hongo,
                            int pos_x[], int puntajes[]){
     if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                for(int i = 0; i < 64; i++){
                      if(colicion(s.x, s.y, s.ancho_escorpion, s.alto_escorpion, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala)){
                                           explocion_enemigo(s.x, s.y, explosion_enemigo, buffer, fondo,HO,hongo);
                                           eliminar(B, n.n_disp, cont);
                                           s.cambio_pos();
                                           pos_x[7] += (12 * puntajes[2]);
                                           cambiar_score(pos_x[7],pos_x[6]);
                                           cambiar_score(pos_x[6],pos_x[5]);
                                           cambiar_score(pos_x[5],pos_x[4]);
                                           cambiar_score(pos_x[4],pos_x[3]);
                                           cambiar_score(pos_x[3],pos_x[2]);
                                           cambiar_score(pos_x[2],pos_x[1]);
                                           cambiar_score(pos_x[1],pos_x[0]);
                                           }
                      }
                 }
            }
     }

void elimina_bala_centipedo(nave &n, centipedo CE[], int &tam_centipedo, struct Balas B[], BITMAP *explosion_enemigo, BITMAP *buffer, BITMAP *fondo, struct mapa HO[],
                            BITMAP *hongo,float &velocidad, int pos_x[], int puntajes[]){
    if ( n.n_disp > 0 && n.n_disp < n.max_disp){
            for ( int cont = 1; cont <= n.n_disp; cont++){
                      if(colicion(CE[0].x, CE[0].y, CE[0].ancho_centipedo, CE[0].alto_centipedo, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala)){
                                           tam_centipedo -= 1;
                                           //velocidad +=0.1;
                                           explocion_enemigo(CE[0].x, CE[0].y, explosion_enemigo, buffer, fondo,HO,hongo);
                                           eliminar(B, n.n_disp, cont);
                                           pos_x[7] += (12 * puntajes[4]);
                                           cambiar_score(pos_x[7],pos_x[6]);
                                           cambiar_score(pos_x[6],pos_x[5]);
                                           cambiar_score(pos_x[5],pos_x[4]);
                                           cambiar_score(pos_x[4],pos_x[3]);
                                           cambiar_score(pos_x[3],pos_x[2]);
                                           cambiar_score(pos_x[2],pos_x[1]);
                                           cambiar_score(pos_x[1],pos_x[0]);
                                           }
                      else if(colicion(CE[tam_centipedo-1].x, CE[tam_centipedo-1].y, CE[tam_centipedo-1].ancho_centipedo, CE[tam_centipedo-1].alto_centipedo, B[cont].x, B[cont].y, n.ancho_bala, n.alto_bala)){
                                           tam_centipedo -= 1;
                                           //velocidad +=0.1;
                                           explocion_enemigo(CE[tam_centipedo-1].x, CE[tam_centipedo-1].y, explosion_enemigo, buffer, fondo,HO,hongo);
                                           eliminar(B, n.n_disp, cont);
                                           pos_x[7] += (12 * puntajes[3]);
                                           cambiar_score(pos_x[7],pos_x[6]);
                                           cambiar_score(pos_x[6],pos_x[5]);
                                           cambiar_score(pos_x[5],pos_x[4]);
                                           cambiar_score(pos_x[4],pos_x[3]);
                                           cambiar_score(pos_x[3],pos_x[2]);
                                           cambiar_score(pos_x[2],pos_x[1]);
                                           cambiar_score(pos_x[1],pos_x[0]);
                                           }
                }
        }
}

/////////////////////////////////////////////////////////////////////////////////////////COLISION ENEMIGOS - NAVE
void elimina_nave_cucaracha(nave &n, cucaracha &c, BITMAP *buffer, BITMAP *fondo, BITMAP *explosion_nave,centipedo CE[], struct mapa HO[], BITMAP *hongo, int &tam_centipedo,bool &cambio){
     if(colicion(n.x,n.y,n.ancho_nave,n.alto_nave,c.x,c.y,c.ancho_cucaracha,c.alto_cucaracha) && n.vidas > 0){
                                                                                               n.vidas -= 1;
                                                                                               explocion_nave(n.x, n.y, explosion_nave, buffer, fondo,HO,hongo);
                                                                                               for(int i = 0;i<16;i++){
                                                                                                    CE[i].restitucion(tam_centipedo);
                                                                                               }
                                                                                               acomoda_centipedo(CE);
                                                                                               reconst_hongo(HO);
                                                                                               n.cambio();
                                                                                               c.cambio_pos();
                                                                                               cambio = false;
                                                                                               //rest(5);
            }
     }

void elimina_nave_escorpion(nave &n, escorpion &s, BITMAP *buffer, BITMAP *fondo, BITMAP *explosion_nave,centipedo CE[], struct mapa HO[], BITMAP *hongo,int &tam_centipedo,bool &cambio){
     if(colicion(n.x, n.y, n.ancho_nave, n.alto_nave, s.x, s.y, s.ancho_escorpion, s.alto_escorpion) && n.vidas > 0){
                                                                                               n.vidas -= 1;
                                                                                               explocion_nave(n.x, n.y, explosion_nave, buffer, fondo,HO,hongo);
                                                                                               for(int i = 0;i<16;i++){
                                                                                                    CE[i].restitucion(tam_centipedo);
                                                                                               }
                                                                                               acomoda_centipedo(CE);
                                                                                               reconst_hongo(HO);
                                                                                               n.cambio();
                                                                                               s.cambio_pos();
                                                                                               cambio = false;
                                                                                               //rest(5);
            }
     }

void elimina_nave_centipedo(nave &n, centipedo CE[], BITMAP *buffer, BITMAP *fondo, BITMAP *explosion_nave, struct mapa HO[], BITMAP *hongo,int &tam_centipedo, bool &cambio){
     for(int j = 0; j < tam_centipedo; j++){
            if(colicion(n.x, n.y, n.ancho_nave, n.alto_nave, CE[j].x, CE[j].y, CE[j].ancho_centipedo, CE[j].alto_centipedo) && n.vidas > 0){
                                                                                               n.vidas -= 1;
                                                                                               explocion_nave(n.x, n.y, explosion_nave, buffer, fondo,HO,hongo);
                                                                                               for(int i = 0;i<16;i++){
                                                                                                    CE[i].restitucion(tam_centipedo);
                                                                                               }
                                                                                               acomoda_centipedo(CE);
                                                                                               reconst_hongo(HO);
                                                                                               n.cambio();
                                                                                               cambio = false;
                                                                                               //rest(5);
            }
     }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cambio_hongo(escorpion s,struct mapa HO[]){
    for(int i = 0; i < 61; i++){
        if(colicion(HO[i].x, HO[i].y, 23, 23, s.x, s.y, 1, 1)){
           HO[i].tipo = 1;
        }
    }
}

void nuevo_nivel(char *ruta_n, char *ruta_d, char *ruta_c, char *ruta_s, char *ruta_cabeza, char *ruta_body, nave &n,
             cucaracha &c, escorpion &s, centipedo CE[], struct mapa HO[],int &tam_centipedo){

    n.cambiar_imagen(ruta_n,ruta_d);
    c.cambiar_imagen(ruta_c);
    s.cambiar_imagen(ruta_s);

    for(int i = 0;i<16;i++){
        CE[i].restitucion(tam_centipedo);
        if(i == 0)
            CE[i].cambiar_imagen(ruta_cabeza);
        else
            CE[i].cambiar_imagen(ruta_body);
   }
   acomoda_centipedo(CE);
   reconst_hongo(HO);
   n.cambio();
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
    BITMAP *explosion_enemigo = load_bitmap("imagenes/level_1/explocion-centipede.bmp",NULL);
    BITMAP *score = load_bitmap("imagenes/level_1/score.bmp",NULL);
    BITMAP *level = load_bitmap("imagenes/level_1/level.bmp",NULL);
    BITMAP *lives = load_bitmap("imagenes/level_1/lives.bmp",NULL);
    BITMAP *v_nave = load_bitmap("imagenes/level_1/nave-0.bmp",NULL);

    BITMAP *n1 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n2 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n3 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n4 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n5 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n6 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n7 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *n8 = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    BITMAP *nro_level = load_bitmap("imagenes/level_1/numeros.bmp",NULL);
    int nro = 12;
    int puntajes[] = {4,8,15,20,30};  // hongo, hongo_e, enemigos, cola, cabeza
    int pos_x[] = {0,0,0,0,0,0,0,0}; // marcasor o score, cambialo por cada 12 pixeles


    int nivel = 1;
    PORTADA(portada,384);

    nave n("imagenes/level_1/nave-1.bmp","imagenes/level_1/disparo.bmp", 21, 24, 6, 20, ANCHO/2, ALTO-90);
    cucaracha c("imagenes/level_1/pulga.bmp","imagenes/level_1/hongo.bmp",27,24,24,24);
    escorpion s("imagenes/level_1/escorpion.bmp",48,24);
    centipedo head("imagenes/level_1/cabeza.bmp");
    centipedo body("imagenes/level_1/cuerpo.bmp");
    centipedo extra("imagenes/level_1/cuerpo.bmp");

    centipedo CE[] = {head,body,body,body,body,body,body,body,body,body,body,body,body,body,body};   ////////// 15 CUERPOS
    int tam_centipedo = 15;
    float velocidad = 7;
    bool cambio = false;
    acomoda_centipedo(CE);

    Balas disparos[n.max_disp]; //LISTA DE DISPAROS

    mapa HO[65];
    iniciar_mapa(HO);

	while(!key[KEY_ESC]) {

          if(nivel == 2){
               nuevo_nivel("imagenes/level_2/nave-1.bmp","imagenes/level_2/disparo.bmp","imagenes/level_2/pulga.bmp","imagenes/level_2/escorpion.bmp",
                           "imagenes/level_2/cabeza.bmp","imagenes/level_2/cuerpo.bmp",n,c,s,CE,HO,tam_centipedo);

               hongo = load_bitmap("imagenes/level_2/hongo.bmp",NULL);
               explosion_nave = load_bitmap("imagenes/level_2/explocion-nave.bmp",NULL);
               explosion_enemigo = load_bitmap("imagenes/level_2/explocion-centipede.bmp",NULL);
               score = load_bitmap("imagenes/level_2/score.bmp",NULL);
               level = load_bitmap("imagenes/level_2/level.bmp",NULL);
               lives = load_bitmap("imagenes/level_2/lives.bmp",NULL);
               v_nave = load_bitmap("imagenes/level_2/nave-0.bmp",NULL);
               nro_level = load_bitmap("imagenes/level_2/numeros.bmp",NULL);

               n1 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n2 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n3 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n4 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n5 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n6 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n7 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);
               n8 = load_bitmap("imagenes/level_2/numeros.bmp",NULL);

               nivel=0;
          }
          if(nivel == 3){
                nuevo_nivel("imagenes/level_3/nave-1.bmp","imagenes/level_3/disparo.bmp","imagenes/level_3/pulga.bmp","imagenes/level_3/escorpion.bmp",
                           "imagenes/level_3/cabeza.bmp","imagenes/level_3/cuerpo.bmp",n,c,s,CE,HO,tam_centipedo);

                hongo = load_bitmap("imagenes/level_3/hongo.bmp",NULL);
                explosion_nave = load_bitmap("imagenes/level_3/explocion-nave.bmp",NULL);
                explosion_enemigo = load_bitmap("imagenes/level_3/explocion-centipede.bmp",NULL);
                score = load_bitmap("imagenes/level_3/score.bmp",NULL);
                level = load_bitmap("imagenes/level_3/level.bmp",NULL);
                lives = load_bitmap("imagenes/level_3/lives.bmp",NULL);
                v_nave = load_bitmap("imagenes/level_3/nave-0.bmp",NULL);
                nro_level = load_bitmap("imagenes/level_3/numeros.bmp",NULL);

                n1 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n2 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n3 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n4 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n5 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n6 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n7 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);
                n8 = load_bitmap("imagenes/level_3/numeros.bmp",NULL);

                nivel=4;
          }

          if(cambio == false)
                velocidad = 7;


          clear_to_color(buffer,0x000000); //COLOR

          pinta_mapa(HO, hongo, buffer);
          masked_blit(score,buffer,0,0,60,135,66,11);
          masked_blit(n1,buffer,pos_x[0],0,126,135,12,11);
          masked_blit(n2,buffer,pos_x[1],0,138,135,12,11);
          masked_blit(n3,buffer,pos_x[2],0,150,135,12,11);
          masked_blit(n4,buffer,pos_x[3],0,162,135,12,11);
          masked_blit(n5,buffer,pos_x[4],0,174,135,12,11);
          masked_blit(n6,buffer,pos_x[5],0,186,135,12,11);
          masked_blit(n7,buffer,pos_x[6],0,198,135,12,11);
          masked_blit(n8,buffer,pos_x[7],0,210,135,12,11);

          masked_blit(level,buffer,0,0,315,135,66,11);
          masked_blit(nro_level,buffer,nro,0,383,135,12,11);

          masked_blit(lives,buffer,0,0,510,135,66,11);

          n.pinta_nave(buffer);
          n.imprimir_vidas(buffer,v_nave);
          n.movimiento();

          for(int i = 0; i < tam_centipedo; i++){
                CE[i].pintar_centipedo(buffer,mov);
                CE[i].movimiento(velocidad);
                CE[i].choque_hongo(HO);
          }

          elimina_bala_centipedo(n,CE,tam_centipedo,disparos,explosion_enemigo,buffer,fondo,HO,hongo,velocidad,pos_x,puntajes);

          if(num == 2){
                         c.pintar_cucaracha(buffer,mov);
                         c.movimiento();
                         for(int i=0;i<61;i++){
                            if(colicion(c.x,c.y,c.ancho_cucaracha,c.alto_cucaracha,HO[i].x,HO[i].y,24,24))
                                crear_hongo(c,HO);
                         }
                         elimina_bala_cucaracha(n,c,disparos,explosion_enemigo, buffer, fondo,HO,hongo,pos_x,puntajes);
                         }

          if(num == 3){
                         s.pintar_escorpion(buffer,mov);
                         s.movimiento();
                         cambio_hongo(s,HO);
                         elimina_bala_escorpion(n,s,disparos,explosion_enemigo, buffer, fondo,HO,hongo,pos_x,puntajes);
                         }


          n.dispara(disparos, buffer);

          elimina_bala_hongo(n,HO,disparos,pos_x,puntajes);

          elimina_nave_cucaracha(n,c, buffer, fondo, explosion_nave, CE,HO,hongo,tam_centipedo,cambio);
	      elimina_nave_escorpion(n,s, buffer, fondo, explosion_nave, CE,HO,hongo,tam_centipedo,cambio);
	      elimina_nave_centipedo(n, CE, buffer, fondo, explosion_nave,HO,hongo,tam_centipedo,cambio);

	      imprimir_fondo(fondo, buffer);

	      if(temporizador(65,tick1)){
                             ale(num,6);
                             }

          if(temporizador(3,tick2)){ //velocidad, tiempo
                                    if((++mov) == 4){ //recorre cada imagen
                                            mov = 0;
                                            }
                                    }

          if(tam_centipedo == 1 && cambio == false){
                velocidad *= 2;
                cambio = true;
          }

	      if(n.vidas == 0){
                     clear_to_color(buffer,0x000000);
                     imprimir_fondo(fondo, buffer);
                     blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
                     PORTADA(fin, 100);
                     break;
                     }

          if((tam_centipedo == 0) && (nivel == 1)){
            nivel = 2;
            nro += 12;
            cambio = false;

          }

          if((tam_centipedo == 0) && (nivel == 0)){
            nivel = 3;
            nro += 12;
            cambio = false;
          }

	      blit(buffer,screen, 0, 0, 0, 0, ANCHO, ALTO); //PANTALLA NEGRA

          rest(20);
	}

	destroy_bitmap(buffer);                         destroy_bitmap(portada);
	destroy_bitmap(fin);                            destroy_bitmap(fondo);
	destroy_bitmap(hongo);                          destroy_bitmap(explosion_nave);
	destroy_bitmap(explosion_enemigo);              destroy_bitmap(score);
	destroy_bitmap(level);                          destroy_bitmap(lives);
	destroy_bitmap(v_nave);                         destroy_bitmap(nro_level);
	destroy_bitmap(n1);                             destroy_bitmap(n2);
	destroy_bitmap(n3);                             destroy_bitmap(n4);
	destroy_bitmap(n5);                             destroy_bitmap(n6);
	destroy_bitmap(n7);                             destroy_bitmap(n8);

	return 0;
	deinit();

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

#include <allegro.h>
#ifndef JUGADOR_H
#define JUGADOR_H

#include "disparos.h"

#define ANCHO 680
#define ALTO 748

class nave
{
      public:
              BITMAP *img_nave;
              BITMAP *img_disp;

              int x, y;
              int n_disp;
              int max_disp;
              int tick;

              int alto_nave;
              int ancho_nave;

              int ancho_bala;
              int alto_bala;

              int vidas;

              nave(char *ruta_nave, char *ruta_disparo,int ancho_n, int alto_n, int ancho_b, int alto_b, int _x, int _y);

              void pinta_nave(BITMAP *buffer);

              void movimiento();

              bool temporizador();

              void dispara(struct Balas disparos[], BITMAP *buffer);

              void cambio();

              void explocion_nave(BITMAP *img_explocion, BITMAP *buffer, BITMAP *fondo);
};



#endif // JUGADOR_H

void nave::cambio(){
                    x=ANCHO/2;
                    y=ALTO-90;
     }

nave::nave(char *ruta_nave, char *ruta_disparo,int ancho_n, int alto_n, int ancho_b, int alto_b, int _x, int _y){
                //COORDENADAS DE LA NAVE
                x = _x;
                y = _y;
                //CANTIDAD DE DISPAROS
                max_disp = 5;
                n_disp = 0; //DISPAROS REALIZADOS

                img_nave = load_bitmap(ruta_nave,NULL);
                img_disp = load_bitmap(ruta_disparo,NULL);

                tick = 0;

                ancho_nave = ancho_n;
                alto_nave = alto_n;

                ancho_bala = ancho_b;
                alto_bala = alto_b;
                vidas = 3;
                }

void nave::pinta_nave(BITMAP *buffer){
     if(vidas > 0)
              masked_blit(img_nave,buffer,0,0,x,y,ancho_nave,alto_nave);  //LUGAR DE MOVIMIENTO, TAMAÑO DE LA NAVE
     }

void nave::movimiento(){
     if(key[KEY_LEFT]){
                       if(x<=40)
                                x=40;
                       else
                           x -= 8;
                       }
     if(key[KEY_RIGHT]){
                        if(x>=610)
                                  x=610;
                        else
                            x += 8;
                        }
     if(key[KEY_UP]){
                     if(y<=125)
                               y=125;
                     else
                         y -= 8;
                     }
     if(key[KEY_DOWN]){
                       if(y>=670)
                                 y=670;
                       else
                           y += 8;
                       }
     }

bool nave::temporizador(){
     tick++;
     if(tick == 5){
             tick = 0;
             return true;
             }
     return false;
     }

void nave::dispara(struct Balas disparos[], BITMAP *buffer){
     if(key[KEY_D] && temporizador())
                   crear_bala(n_disp, max_disp, disparos, x, y, -40);//X E Y POSICION NAVE, VELOCIDAD

     pintar_bala(n_disp, max_disp, disparos, buffer, img_disp, ancho_bala, alto_bala);
     elimina_bala(n_disp, max_disp, disparos, ANCHO, ALTO);
     }

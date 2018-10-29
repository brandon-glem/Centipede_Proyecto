#include <allegro.h>
#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include "disparos.h"

#define ANCHO 672
#define ALTO 672

class nave
{
      public:
              BITMAP *img_nave;
              BITMAP *img_disp;
              
              int x, y;
              int n_disp;
              int max_disp;
              int tick;
              
              int ancho_bala;
              int alto_bala;
              
              //int vidas=3;
            
              nave(char *ruta_nave, char *ruta_disparo, int ancho_b, int alto_b);
             
              void pinta_nave(BITMAP *buffer);
              
              void movimiento();
              
              bool temporizador();
              
              void dispara(struct Balas disparos[], BITMAP *buffer);
};

#endif // NAVE_H

nave::nave(char *ruta_nave, char *ruta_disparo, int ancho_b, int alto_b){
                //COORDENADAS DE LA NAVE
                x = ANCHO/2;
                y = ALTO-40;
                //CANTIDAD DE DISPAROS
                max_disp = 5;
                n_disp = 0; //DISPAROS REALIZADOS
                
                img_nave = load_bitmap(ruta_nave,NULL);
                img_disp = load_bitmap(ruta_disparo,NULL);
                
                tick = 0;
                
                ancho_bala = ancho_b;
                alto_bala = alto_b;
                }
                
void nave::pinta_nave(BITMAP *buffer){
     masked_blit(img_nave,buffer,0,0,x,y,28,40);  //LUGAR DE MOVIMIENTO, TAMAÑO DE LA NAVE
     }

void nave::movimiento(){
     if(key[KEY_LEFT])
                      x -= 8;
     if(key[KEY_RIGHT])
                       x += 8;
     if(key[KEY_UP])
                    y -= 8;
     if(key[KEY_DOWN])
                      y += 8;
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

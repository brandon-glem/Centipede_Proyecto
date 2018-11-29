#include <allegro.h>
#include "disparos.h"
#include "mapa.h"

#ifndef ESCORPION_H_INCLUDED
#define ESCORPION_H_INCLUDED

#define ANCHO 680
#define ALTO 748

class escorpion
{
      public:
             BITMAP *img_escorpion;
             BITMAP *img_obj;

             int x, y;

             int alto_escorpion, ancho_escorpion;
             int ancho_obj,alto_obj;

             int direc;

             escorpion(char *esco, char *hongo, int ancho_e, int alto_e, int ancho_h, int alto_h);
             void pintar_escorpion(BITMAP *buffer, int mov);
             void movimiento(BITMAP *buffer);
             void cambio_pos();
             int aleatorio();
};

#endif // CUCARACHA_H_INCLUDED

int escorpion::aleatorio(){
               int num;
               srand(time(NULL));

               num = 1 + rand() % (20 - 1);

               return num;
               }

escorpion::escorpion(char *esco, char *hongo, int ancho_e, int alto_e, int ancho_h, int alto_h){
                                                    img_escorpion = load_bitmap(esco,NULL);

                                                    ancho_escorpion = ancho_e;
                                                    alto_escorpion = alto_e;

                                                    y=154;

                                                    x = 30;

                                                    mov=0;

                                                    direc = 1;
                                                    }

void escorpion::pintar_escorpion(BITMAP *buffer, int mov){
     masked_blit(img_escorpion, buffer, 48*mov, 0, x, y, ancho_escorpion, alto_escorpion);
     }

void escorpion::cambio_pos(){
     if(x == 650 || x < ANCHO/2){
          x = 650;
          y = 20*aleatorio();
          direc = 0;
          rest(10);
          }

     else if(x == 30 || x > ANCHO/2 ){
          x = 30;
          y = 20*aleatorio();
          direc = 1;
          rest(10);
          }
     }

void escorpion::movimiento(BITMAP *buffer){
     if(x < 650 && direc == 1){
               x += 10;
               }

     else if(x > 30 && direc == 0){
               x -= 10;
               }

     else{
          cambio_pos();
          rest(10);
          }
     }

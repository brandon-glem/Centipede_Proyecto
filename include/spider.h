#include <allegro.h>
#include "disparos.h"

#ifndef SPIDER_H_INCLUDED
#define SPIDER_H_INCLUDED

#define ANCHO 680
#define ALTO 748

class spider:public enemigo
{
      public:
             BITMAP *img_spider;

             int x, y;

             int mov;

             int alto_spider, ancho_spider;

             spider(char *spidi, int ancho_s, int alto_s);
             void pintar_escorpion(BITMAP *buffer, int mov);
             void movimiento(BITMAP *buffer);
             void cambio_pos();
             int aleatorio();
};

#endif // SPIDER_H_INCLUDED

int spider::aleatorio(){
               int num;
               srand(time(NULL));

               num = 1 + rand() % (20 - 1);

               return num;
               }

spider::spider(char *spidi, int ancho_s, int alto_s){
                                                    img_escorpion = load_bitmap(spidi,NULL);

                                                    ancho_spider = ancho_s;
                                                    alto_spider = alto_s;

                                                    y=154;

                                                    x = 30;

                                                    mov=0;
                                                    }

void spider::pintar_spider(BITMAP *buffer, int mov){
     masked_blit(img_spider, buffer, 48*mov, 0, x, y, ancho_spider, alto_spider);
     }

void spider::cambio_pos(){
     x = 30;
     y = 20*aleatorio();
     rest(10);
     }

void spider::movimiento(BITMAP *buffer){
     if(x <= 650){
               x += 10;
               }

     else{
          cambio_pos();
          rest(10);
          }
}

#include <enemigo.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#ifndef CUCARACHA_H_INCLUDED
#define CUCARACHA_H_INCLUDED

#define ANCHO 680
#define ALTO 748

class cucaracha:public enemigo{
      public:
             BITMAP *img_cucaracha;
             BITMAP *img_obj;

             int x, y;
             int xh, yh;

             int alto_cucaracha,ancho_cucaracha;

             int ancho_obj,alto_obj;

             bool toca;

             int dan;

             cucaracha(char *cuca, char *hongo, int ancho_c, int alto_c, int ancho_h, int alto_h);
             void pintar_cucaracha(BITMAP *buffer,int mov);
             void cambio_pos();
             void movimiento();
             int aleatorio();
             void cambiar_imagen(char *cuca);
};

#endif // CUCARACHA_H_INCLUDED

int cucaracha::aleatorio(){
               int num;
               srand(time(NULL));

               num = 1 + rand() % (24);

               return num;
               }

cucaracha::cucaracha(char *cuca, char *hongo, int ancho_c, int alto_c, int ancho_h, int alto_h){
                                                    img_cucaracha = load_bitmap(cuca,NULL);
                                                    img_obj = load_bitmap(hongo,NULL);

                                                    ancho_cucaracha = ancho_c;
                                                    alto_cucaracha = alto_c;

                                                    ancho_obj = ancho_h;
                                                    alto_obj = alto_h;

                                                    y=100;

                                                    x = 47;

                                                    toca = false;

                                                    dan = 0;
                                                    }

void cucaracha::pintar_cucaracha(BITMAP *buffer,int mov){
     masked_blit(img_cucaracha, buffer, 27*mov, 0, x, y, ancho_cucaracha, alto_cucaracha);
     }

void cucaracha::cambio_pos(){
     x = 47+(24*aleatorio());
     y = 100;
     rest(10);
     }

void cucaracha::movimiento(){
     if(y <= 720 && dan == 0){
               y += 10;
               }

     else{
          cambio_pos();
          dan = 0;
          rest(10);
          }
     }
void cucaracha::cambiar_imagen(char *cuca){
    img_cucaracha = load_bitmap(cuca,NULL);
}

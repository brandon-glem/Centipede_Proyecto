#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#ifndef CUCARACHA_H_INCLUDED
#define CUCARACHA_H_INCLUDED

#define ANCHO 680
#define ALTO 748

class cucaracha
{
      private:
             BITMAP *img_cucaracha;
             BITMAP *img_obj;
             
             int x, y;
             int xh, yh;
             
             int alto_cucaracha,ancho_cucaracha;
              
             int ancho_obj,alto_obj;
             
             bool toca;
      
      public:
             cucaracha(char *cuca, char *hongo, int ancho_c, int alto_c, int ancho_h, int alto_h);
             void crear_obj(BITMAP *buffer);
             void pintar_cucaracha(BITMAP *buffer);
             void movimiento(BITMAP *buffer);   
             int aleatorio();
};

#endif // CUCARACHA_H

cucaracha::cucaracha(char *cuca, char *hongo, int ancho_c, int alto_c, int ancho_h, int alto_h){
                                                    img_cucaracha = load_bitmap(cuca,NULL);
                                                    img_obj = load_bitmap(hongo,NULL);
                                                    
                                                    ancho_cucaracha = ancho_c;
                                                    alto_cucaracha = alto_c;
                                                    
                                                    ancho_obj = ancho_h;
                                                    alto_obj = alto_h;
                                                    
                                                    y=100;
                                                    
                                                    x = 80;
                                                    
                                                    toca = false;
                                                    }

int cucaracha::aleatorio(){
               int num;
               srand(time(NULL));

               num = 1 + rand() % (4 - 1);
               
               return num;
               }
                                                    
void cucaracha::crear_obj(BITMAP *buffer){
     masked_blit(img_obj, buffer, 0, 0, xh, yh, ancho_obj, alto_obj);
     }

void cucaracha::pintar_cucaracha(BITMAP *buffer){
     masked_blit(img_cucaracha, buffer, 0, 0, x, y, ancho_cucaracha, alto_cucaracha);
     }

void cucaracha::movimiento(BITMAP *buffer){
     if(y<=710){
               y += 10;
               }
     else{
          x += 170;
          y = 100;
          }
     if(x == 760)
               x = 80;
     }
     

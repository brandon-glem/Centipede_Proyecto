<<<<<<< HEAD
#include <allegro.h>
#include "disparos.h"

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
             
             int mov;
             
             int alto_escorpion, ancho_escorpion;
             int ancho_obj,alto_obj;
      
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
                                                    }
                                                  
void escorpion::pintar_escorpion(BITMAP *buffer, int mov){
     masked_blit(img_escorpion, buffer, 48*mov, 0, x, y, ancho_escorpion, alto_escorpion);
     }

void escorpion::cambio_pos(){
     x = 30;
     y = 20*aleatorio();
     rest(10);
     }

void escorpion::movimiento(BITMAP *buffer){
     if(x <= 650){
               x += 10;
               }
     
     else{
          cambio_pos();
          rest(10);
          }
}
=======
#include <allegro.h>
#include "disparos.h"

#ifndef ESCORPION_H_INCLUDED
#define ESCORPION_H_INCLUDED

#define ANCHO 680
#define ALTO 748

class escorpion
{
      public:
             BITMAP *img_escorpion;
             
             int x, y;
             
             int alto_escorpion, ancho_escorpion;
      
             escorpion(char *esco, char *hongo, int ancho_e, int alto_e);
             void pintar_escorpion(BITMAP *buffer);
             void movimiento(BITMAP *buffer);   
};

#endif // CUCARACHA_H_INCLUDED

escorpion::escorpion(char *esco, char *hongo, int ancho_e, int alto_e, int ancho_h, int alto_h){
                                                    img_escorpion = load_bitmap(esco,NULL);
                                                    
                                                    ancho_escorpion = ancho_e;
                                                    alto_escorpion = alto_e;
                                                    
                                                    y=100;
                                                    
                                                    x = 80;
                                                    }
                                                  
void escorpion::pintar_escorpion(BITMAP *buffer){
     masked_blit(img_escorpion, buffer, 0, 0, x, y, ancho_escorpion, alto_escorpion);
     }

void escorpion::movimiento(BITMAP *buffer){
     x += 10;
}
>>>>>>> 32d2ed087c3666cf330b47a92075e3f2c82ae8e3

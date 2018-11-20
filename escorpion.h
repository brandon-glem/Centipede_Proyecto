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

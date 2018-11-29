#include <allegro.h>
#include <mapa.h>

#ifndef CENTIPEDO_H
#define CENTIPEDO_H

#define ANCHO 680
#define ALTO 748

class centipedo
{
    public:
        BITMAP *img_cabeza;

        int x, y;

        int alto_centipedo, ancho_centipedo;
        int ancho_obj,alto_obj;

        int direc;

        centipedo(char *head, int ancho_c, int alto_c);
        void pintar_centipedo(BITMAP *buffer, int mov);
        void movimiento(BITMAP *buffer);
};

#endif // CENTIPEDO_H

centipedo::centipedo(char *head, int ancho_c, int alto_c){
    img_cabeza = load_bitmap(head,NULL);

    x = ANCHO/2;
    y = 154;

    alto_centipedo = alto_c;
    ancho_centipedo = ancho_c;

    mov = 0;
    direc = 0;
}

void centipedo::pintar_centipedo(BITMAP *buffer, int mov){
     masked_blit(img_cabeza, buffer, 21*mov, 0, x, y, ancho_centipedo, alto_centipedo);
     }

void centipedo::movimiento(BITMAP *buffer){
     if(x < 650 && direc == 1){
               x += 10;
               }

     else if(x > 30 && direc == 0){
               x -= 10;
               }

}

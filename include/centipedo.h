#include <allegro.h>
#include <mapa.h>
#include <disparos.h>

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

        int direc;

        int dan;

        centipedo(char *head);
        void pintar_centipedo(BITMAP *buffer, int mov);
        void movimiento(float &velocidad);
        void choque_hongo(struct mapa HO[]);
        void restitucion(int &tam_centipedo);
        void cambiar_imagen(char *head);
};

#endif // CENTIPEDO_H

centipedo::centipedo(char *head){
    img_cabeza = load_bitmap(head,NULL);

    x = ANCHO/2;
    y = 154;

    alto_centipedo = 24;
    ancho_centipedo = 21;

    direc = 0;

    dan = 0;
}

void centipedo::pintar_centipedo(BITMAP *buffer, int mov){
     masked_blit(img_cabeza, buffer, mov*21, 0, x, y, ancho_centipedo, alto_centipedo);
     }

void centipedo::movimiento(float &velocidad){
     if(x < 627 && direc == 1){
               x += velocidad;
               }

     else if(x > 39 && direc == 0){
               x -= velocidad;
               }

     else if(x >= 627 || x <= 39){
        if(y == 706){
            for(int i = 0; i<4; i++){
                y -= 24;
            }
        }
        else
            y += 24;
        if(direc == 0){
            direc = 1;
        }
        else
            direc = 0;
     }
}

void centipedo::choque_hongo(struct mapa HO[]){
    for(int i = 0; i < 61; i++){
            if(colicion(HO[i].x, HO[i].y, 24, 24, x, y, ancho_centipedo, alto_centipedo)&&(HO[i].dan < 4)){
                y += 24;
                if(direc == 0)
                        direc = 1;
                else
                    direc = 0;
            }
        }
}

void centipedo::restitucion(int &tam_centipedo){
    img_cabeza = img_cabeza;
    x = ANCHO/2;
    y = 154;
    direc = 0;
    dan = 0;
    tam_centipedo = 15;
}

void centipedo::cambiar_imagen(char *head){
    img_cabeza = load_bitmap(head,NULL);
}

#include <allegro.h>
#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

struct mapa{
    int x , y;
    int dan;
    int tipo;
};

void iniciar_mapa(struct mapa hongo[]){
     char pos_hongo[20][25]={ //20x24
            "H H    H        H   H  H",        //24
            "   H  H       H   H   H ",
            "        H   H        H  ",
            "  H    H         H      ",
            "H        H         H  H ",
            "    H          H  H     ",
            "      H   H             ",
            " H      H         H   H ",
            "H     H                H",
            "       H             H  ",
            "     H     H      H   H ",
            "      H          H  H   ",
            " H       H             H",
            "H      H        H       ",
            "   H      H       H     ",
            "H       H       H      H",
            "      H  H           H  ",
            "H          H    H       ",
            "  H  H               H  ",
     //19
          };

     int r = 0;
     for(int i = 0; i < 24; i++){
             for (int j = 0; j < 19; j++){
                 if(pos_hongo[j][i] != ' '){
                                    hongo[r].x = 47 + i*24;
                                    hongo[r].y = 154 + j*24;
                                    hongo[r].dan = 0;
                                    hongo[r].tipo = 0;

                                    r++;
                                    }
                 }
             }

     }

void pinta_mapa(struct mapa HO[], BITMAP *img_hon, BITMAP *buffer){
     for(int i = 0; i < 64; i++){
             if(HO[i].dan != 4){
                          masked_blit(img_hon, buffer,HO[i].dan*24, HO[i].tipo*24, HO[i].x, HO[i].y, 24, 24);
                          }
             }
     }

#endif // MAPA_H_INCLUDED

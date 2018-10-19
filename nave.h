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
              
              int vidas=3;
            
              nave(char *ruta_nave, char *ruta_disparo){
                       x=ANCHO/2;
                       y=ALTO-40;
                       n_disp=0;
                       max_disp=10;
                       img_nave = load_bitmap(ruta_nave,NULL);
                       img_disp = load_bitmap(ruta bala,NULL);
                       }
             
              void pinta_nave(BITMAP buffer,){
                               
                  }
              void movimiento();
};

#endif // NAVE_H

#include <allegro.h>
#ifndef SPIDER_H_INCLUDED
#define SPIDER_H_INCLUDED

#define ANCHO 672
#define ALTO 672

class spider
{
      public:
              BITMAP *img_spider;
              
              int x, y;
              
              int alto_spider;
              int ancho_spider;
            
              spider(char *ruta_spider, int ancho_s, int alto_s);
             
              void pinta_spider(BITMAP *buffer);
              
              void movimiento();

};
#endif // SPIDER_H

spider::spider(char *ruta_spider, int ancho_s, int alto_s){
                x = 100;
                y = 50;
                                
                img_spider = load_bitmap(ruta_spider,NULL);
                                
                ancho_spider = ancho_s;
                alto_spider = alto_s;
                
                }
                
void spider::pinta_spider(BITMAP *buffer){
     masked_blit(img_spider,buffer,0,0,x,y,ancho_spider,alto_spider);
     }

void spider::movimiento(){
     x+=10;
}

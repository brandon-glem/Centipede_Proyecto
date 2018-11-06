#include <allegro.h>
#ifndef DISENO_H_INCLUDED
#define DISENO_H_INCLUDED

void PORTADA(BITMAP *p);
void imprimir_fondo(BITMAP* fondo , BITMAP* buffer);

#endif // DISENO_H_INCLUDED

void PORTADA(BITMAP *p){
     int parpadeo = 0;
     int y = 0;
     int cont = 0;
     bool salida = false;
     bool carga = false;
     
     while(!salida){
            if (parpadeo < 25)
                         blit(p,screen, 0, y, 50, 150, 576, 384);
            else
                 blit(p,screen, 576, y, 50, 150, 576, 384);
            
            if (key[KEY_ENTER]){
                   y = 384;
                   carga = true;
            }          
            
            if(carga)
                     (cont++);
            if(cont > 384)
                    salida = true;
                    
            rest(5);
            if((++parpadeo) == 50)
                          parpadeo = 0;
            
            }
            
     clear_to_color(screen, 0x000000);
}

void imprimir_fondo(BITMAP *fondo, BITMAP *buffer){
     masked_blit(fondo, buffer, 0, 0, 0, 0, 680, 748); 
}   

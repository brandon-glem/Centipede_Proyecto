#include <allegro.h>
//#include "nave.h"
#include "disparos.h"

//PANTALLA
#define ANCHO 672
#define ALTO 672

const int maxdisp = 4; 
int ndisp = 0;

void init();
void deinit();

int main() {
	init();
	//IMAGENES
	BITMAP *buffer = create_bitmap(ANCHO,ALTO); //PANTALLA NEGRA
	BITMAP *nave = load_bitmap("level_1/nave-0.bmp",NULL);
	BITMAP *disparo = load_bitmap("level_1/disparo.bmp",NULL);
	//COORDENADAS DE LA NAVE
	int X = ANCHO/2;
	int Y = ALTO - 50;
	//CANTIDAD DE DISPAROS
	const int maxdisparos = 2;
    int ndisparos = 0;	//DISPAROS REALIZADOS
    
    Balas disparos[maxdisparos]; //LISTA DE DISPAROS
    
    int dws=0, contt = 0;  //TEMPORIZADOR
  
	while(!key[KEY_ESC]) {
          
          clear_to_color(buffer,0x000000); //COLOR
          masked_blit(nave,buffer,0,0,X,Y,28,40);  //LUGAR DE MOVIMIENTO, TAMAÑO DE LA NAVE
          
          if(key[KEY_D]){
                             crear_bala(ndisparos, maxdisparos, disparos, X, Y, -40);//X E Y POSICION NAVE, VELOCIDAD
                             dws=1;
                             }
          if(contt++ > 6){ //OJOOOO
                     dws = 0;
                     contt = 0; 
                     }
                     
          pintar_bala(ndisparos, maxdisparos, disparos, buffer, disparo);
          elimina_bala(ndisparos, maxdisparos, disparos, ANCHO, ALTO);
	      
	      if(key[KEY_LEFT])
                           X -= 8;
	      if(key[KEY_RIGHT])
                            X += 8;
	      if(key[KEY_UP])
	                        Y -= 8;
          if(key[KEY_DOWN])
                            Y += 8;
	      
	      
	      blit(buffer,screen, 0, 0, 0, 0, ANCHO, ALTO); //PANTALLA NEGRA 
	      rest(20);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 672, 672, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

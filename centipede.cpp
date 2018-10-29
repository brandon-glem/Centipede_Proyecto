#include <allegro.h>
#include "nave.h"
#include "disparos.h"

//PANTALLA
#define ANCHO 672
#define ALTO 672

void init();
void deinit();

int main() {
	init();
	//IMAGENES
	BITMAP *buffer = create_bitmap(ANCHO,ALTO); //PANTALLA NEGRA
    
    nave n("level_1/nave-0.bmp","level_1/disparo.bmp", 6, 20);
    
    Balas disparos[n.max_disp]; //LISTA DE DISPAROS
  
	while(!key[KEY_ESC]) {
          
          clear_to_color(buffer,0x000000); //COLOR
          
          n.pinta_nave(buffer);
          n.movimiento();
          
          n.dispara(disparos, buffer); 
	      
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

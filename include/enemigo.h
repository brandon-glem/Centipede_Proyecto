#include <allegro.h>
#ifndef ENEMIGO_H
#define ENEMIGO_H

class enemigo
{
    public:
        virtual void movimiento() =0;
        virtual void cambio_pos() =0;
        virtual int aleatorio() =0;
};

#endif // ENEMIGO_H

/**
*   brick.h
*/

#ifndef BRICK_H
#define BRICK_H

#include "entity.h"


class Brick : public Entity
{

	int life;           // in hits
    
  public:
    
    Brick(int life, float w, float h, Color *c);

    void setLife(int life);
    int getLife();
    void decLife();

};


#endif

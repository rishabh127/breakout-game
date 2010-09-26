/**
*   color.h
*/

#ifndef COLOR_H
#define COLOR_H


class Color {

  float r;
  float g;
  float b;
  
  public:
    
    Color();
    Color(float r, float g, float b);
    
    void setR(int r);
    float getR();
    void setG(int g);
    float getG();
    void setB(int b);
    float getB();
  
};


#endif

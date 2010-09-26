/**
*   color.cpp
*/

#include "color.h"


Color::Color() {
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setR(int r) {
    this->r = r;
}

float Color::getR() {
  return this->r;
}

void Color::setG(int g) {
    this->g = g;
}

float Color::getG() {
  return this->g;
}

void Color::setB(int b) {
    this->b = b;
}

float Color::getB() {
  return this->b;
}
  



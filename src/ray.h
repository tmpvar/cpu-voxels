#ifndef __RAY__
#define __RAY__

#include <3d.h>

/******************************************************************************

  This source code accompanies the Journal of Graphics Tools paper:

  "Fast Ray-Axis-Aligned Bounding Box Overlap Tests using Ray Slopes"
  by Martin Eisemann and Marcus Magnor
  Computer Graphics Lab, TU Braunschweig, Germany

  Parts of this code are taken from
  "Fast Ray-Axis Aligned Bounding Box Overlap Tests With Pluecker Coordinates"
  by Jeffrey Mahovsky and Brian Wyvill
  Department of Computer Science, University of Calgary

  This source code is public domain, but please mention us if you use it.

******************************************************************************/

enum CLASSIFICATION {
  MMM = 63, // b00111111
  MMP = 61, // b00111101
  MPM = 55, // b00110111
  MPP = 53, // b00110101
  PMM = 31, // b00011111
  PMP = 29, // b00011101
  PPM = 23, // b00010111
  PPP = 21, // b00010101
  POO = 16, // b00010000
  MOO = 48, // b00110000
  OPO =  4, // b00000100
  OMO = 12, // b00001100
  OOP =  1, // b00000001
  OOM =  3, // b00000011
  OMM = 15, // b00001111
  OMP = 13, // b00001101
  OPM =  7, // b00000111
  OPP =  5, // b00000101
  MOM = 51, // b00110011
  MOP = 49, // b00110001
  POM = 19, // b00010011
  POP = 17, // b00010001
  MMO = 60, // b00111100
  MPO = 52, // b00110100
  PMO = 28, // b00011100
  PPO = 20, // b00010100
};

typedef struct ray_t
{
  //common variables
  double x, y, z;    // ray origin
  double i, j, k;    // ray direction
  double ii, ij, ik; // inverses of direction components

  // ray slope
  int classification;
  double ibyj, jbyi, kbyj, jbyk, ibyk, kbyi; //slope
  double c_xy, c_xz, c_yx, c_yz, c_zx, c_zy;
} ray3;

static inline void ray_classify(ray3 *r, vec3 rd) {
  // sign
  int i = (rd[0] > 0) - (rd[0] < 0);
  int j = (rd[1] > 0) - (rd[1] < 0);
  int k = (rd[2] > 0) - (rd[2] < 0);

  // b00110100 === MPO
  //    ||||||_ k non-zero (false)
  //    |||||_ k negative (false)
  //    ||||_ j non-zero (true)
  //    |||_ j negative (false)
  //    ||_ i non-zero (true)
  //    |_ i negative (true)
  r->classification = (i<0) << 5 |
                      (i&1) << 4 |
                      (j<0) << 3 |
                      (j&1) << 2 |
                      (k<0) << 1 |
                      (k&1);
}

static inline void ray_update(ray3 *r, vec3 ro, vec3 rd)
{
  r->ii = 1.0f/rd[0];
  r->ij = 1.0f/rd[1];
  r->ik = 1.0f/rd[2];

  ray_classify(r, rd);
}

#endif

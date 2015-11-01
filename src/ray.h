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

enum CLASSIFICATION
{ MMM, MMP, MPM, MPP, PMM, PMP, PPM, PPP, POO, MOO, OPO, OMO, OOP, OOM,
  OMM,OMP,OPM,OPP,MOM,MOP,POM,POP,MMO,MPO,PMO,PPO};

typedef struct ray_t
{
  //common variables
  float x, y, z;    // ray origin
  float i, j, k;    // ray direction
  float ii, ij, ik; // inverses of direction components

  // ray slope
  int classification;
  float ibyj, jbyi, kbyj, jbyk, ibyk, kbyi; //slope
  float c_xy, c_xz, c_yx, c_yz, c_zx, c_zy;
} ray3;

void ray_update(ray3 *r, vec3 ro, vec3 rd)
{
  //common variables
  r->x = ro[0];
  r->y = rd[1];
  r->z = ro[2];
  r->i = rd[0];
  r->j = rd[1];
  r->k = rd[2];

  r->ii = 1.0f/r->i;
  r->ij = 1.0f/r->j;
  r->ik = 1.0f/r->k;

  //ray slope
  r->ibyj = r->i * r->ij;
  r->jbyi = r->j * r->ii;
  r->jbyk = r->j * r->ik;
  r->kbyj = r->k * r->ij;
  r->ibyk = r->i * r->ik;
  r->kbyi = r->k * r->ii;
  r->c_xy = r->y - r->jbyi * r->x;
  r->c_xz = r->z - r->kbyi * r->x;
  r->c_yx = r->x - r->ibyj * r->y;
  r->c_yz = r->z - r->kbyj * r->y;
  r->c_zx = r->x - r->ibyk * r->z;
  r->c_zy = r->y - r->jbyk * r->z;

  //ray slope classification
  if(r->i < 0)
  {
    if(r->j < 0)
    {
      if(r->k < 0)
      {
        r->classification = MMM;
      }
      else if(r->k > 0){
        r->classification = MMP;
      }
      else//(k >= 0)
      {
        r->classification = MMO;
      }
    }
    else//(j >= 0)
    {
      if(r->k < 0)
      {
        r->classification = MPM;
        if(r->j==0)
          r->classification = MOM;
      }
      else//(k >= 0)
      {
        if((r->j==0) && (r->k==0))
          r->classification = MOO;
        else if(r->k==0)
          r->classification = MPO;
        else if(r->j==0)
          r->classification = MOP;
        else
          r->classification = MPP;
      }
    }
  }
  else//(i >= 0)
  {
    if(r->j < 0)
    {
      if(r->k < 0)
      {
        r->classification = PMM;
        if(r->i==0)
          r->classification = OMM;
      }
      else//(k >= 0)
      {
        if((r->i==0) && (r->k==0))
          r->classification = OMO;
        else if(r->k==0)
          r->classification = PMO;
        else if(r->i==0)
          r->classification = OMP;
        else
          r->classification = PMP;
      }
    }
    else//(j >= 0)
    {
      if(r->k < 0)
      {
        if((r->i==0) && (r->j==0))
          r->classification = OOM;
        else if(r->i==0)
          r->classification = OPM;
        else if(r->j==0)
          r->classification = POM;
        else
          r->classification = PPM;
      }
      else//(k > 0)
      {
        if(r->i==0)
        {
          if(r->j==0)
            r->classification = OOP;
          else if(r->k==0)
            r->classification = OPO;
          else
            r->classification = OPP;
        }
        else
        {
          if((r->j==0) && (r->k==0))
            r->classification = POO;
          else if(r->j==0)
            r->classification = POP;
          else if(r->k==0)
            r->classification = PPO;
          else
            r->classification = PPP;
        }
      }
    }
  }
}

#endif

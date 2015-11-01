/******************************************************************************

  This source code accompanies the Journal of Graphics Tools paper:

  "Fast Ray-Axis-Aligned Bounding Box Overlap Tests using Ray Slopes"
  by Martin Eisemann and Marcus Magnor
  Computer Graphics Lab, TU Braunschweig, Germany

  This source code is public domain, but please mention us if you use it.

******************************************************************************/
#ifndef __RAY_AABB__
#define __RAY_AABB__

#include "ray.h"
#include "aabb.h"
#include <3d.h>

uint8_t ray_aabb(ray3 *r, aabb b, float *t){

  switch (r->classification)
  {
  case MMM:
    {
    if ((r->x < b[0][0]) || (r->y < b[0][1]) || (r->z < b[0][2])
      || (r->jbyi * b[0][0] - b[1][1] + r->c_xy > 0)
      || (r->ibyj * b[0][1] - b[1][0] + r->c_yx > 0)
      || (r->jbyk * b[0][2] - b[1][1] + r->c_zy > 0)
      || (r->kbyj * b[0][1] - b[1][2] + r->c_yz > 0)
      || (r->kbyi * b[0][0] - b[1][2] + r->c_xz > 0)
      || (r->ibyk * b[0][2] - b[1][0] + r->c_zx > 0)
      )
      return 0;

    // compute the intersection distance

      *t = (b[1][0] - r->x) * r->ii;
      float t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[1][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }


  case MMP:
    {
    if ((r->x < b[0][0]) || (r->y < b[0][1]) || (r->z > b[1][2])
      || (r->jbyi * b[0][0] - b[1][1] + r->c_xy > 0)
      || (r->ibyj * b[0][1] - b[1][0] + r->c_yx > 0)
      || (r->jbyk * b[1][2] - b[1][1] + r->c_zy > 0)
      || (r->kbyj * b[0][1] - b[0][2] + r->c_yz < 0)
      || (r->kbyi * b[0][0] - b[0][2] + r->c_xz < 0)
      || (r->ibyk * b[1][2] - b[1][0] + r->c_zx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
      float t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case MPM:
    {
    if ((r->x < b[0][0]) || (r->y > b[1][1]) || (r->z < b[0][2])
      || (r->jbyi * b[0][0] - b[0][1] + r->c_xy < 0)
      || (r->ibyj * b[1][1] - b[1][0] + r->c_yx > 0)
      || (r->jbyk * b[0][2] - b[0][1] + r->c_zy < 0)
      || (r->kbyj * b[1][1] - b[1][2] + r->c_yz > 0)
      || (r->kbyi * b[0][0] - b[1][2] + r->c_xz > 0)
      || (r->ibyk * b[0][2] - b[1][0] + r->c_zx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
    float t1 = (b[0][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;
    float t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case MPP:
    {
    if ((r->x < b[0][0]) || (r->y > b[1][1]) || (r->z > b[1][2])
      || (r->jbyi * b[0][0] - b[0][1] + r->c_xy < 0)
      || (r->ibyj * b[1][1] - b[1][0] + r->c_yx > 0)
      || (r->jbyk * b[1][2] - b[0][1] + r->c_zy < 0)
      || (r->kbyj * b[1][1] - b[0][2] + r->c_yz < 0)
      || (r->kbyi * b[0][0] - b[0][2] + r->c_xz < 0)
      || (r->ibyk * b[1][2] - b[1][0] + r->c_zx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
      float t1 = (b[0][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case PMM:
    {
    if ((r->x > b[1][0]) || (r->y < b[0][1]) || (r->z < b[0][2])
      || (r->jbyi * b[1][0] - b[1][1] + r->c_xy > 0)
      || (r->ibyj * b[0][1] - b[0][0] + r->c_yx < 0)
      || (r->jbyk * b[0][2] - b[1][1] + r->c_zy > 0)
      || (r->kbyj * b[0][1] - b[1][2] + r->c_yz > 0)
      || (r->kbyi * b[1][0] - b[1][2] + r->c_xz > 0)
      || (r->ibyk * b[0][2] - b[0][0] + r->c_zx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
      float t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[1][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }


  case PMP:
    {
    if ((r->x > b[1][0]) || (r->y < b[0][1]) || (r->z > b[1][2])
      || (r->jbyi * b[1][0] - b[1][1] + r->c_xy > 0)
      || (r->ibyj * b[0][1] - b[0][0] + r->c_yx < 0)
      || (r->jbyk * b[1][2] - b[1][1] + r->c_zy > 0)
      || (r->kbyj * b[0][1] - b[0][2] + r->c_yz < 0)
      || (r->kbyi * b[1][0] - b[0][2] + r->c_xz < 0)
      || (r->ibyk * b[1][2] - b[0][0] + r->c_zx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
      float t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case PPM:
    {
    if ((r->x > b[1][0]) || (r->y > b[1][1]) || (r->z < b[0][2])
      || (r->jbyi * b[1][0] - b[0][1] + r->c_xy < 0)
      || (r->ibyj * b[1][1] - b[0][0] + r->c_yx < 0)
      || (r->jbyk * b[0][2] - b[0][1] + r->c_zy < 0)
      || (r->kbyj * b[1][1] - b[1][2] + r->c_yz > 0)
      || (r->kbyi * b[1][0] - b[1][2] + r->c_xz > 0)
      || (r->ibyk * b[0][2] - b[0][0] + r->c_zx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
      float t1 = (b[0][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[1][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case PPP:
    {
    if ((r->x > b[1][0]) || (r->y > b[1][1]) || (r->z > b[1][2])
      || (r->jbyi * b[1][0] - b[0][1] + r->c_xy < 0)
      || (r->ibyj * b[1][1] - b[0][0] + r->c_yx < 0)
      || (r->jbyk * b[1][2] - b[0][1] + r->c_zy < 0)
      || (r->kbyj * b[1][1] - b[0][2] + r->c_yz < 0)
      || (r->kbyi * b[1][0] - b[0][2] + r->c_xz < 0)
      || (r->ibyk * b[1][2] - b[0][0] + r->c_zx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
      float t1 = (b[0][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      float t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case OMM:
    {
    if((r->x < b[0][0]) || (r->x > b[1][0])
      || (r->y < b[0][1]) || (r->z < b[0][2])
      || (r->jbyk * b[0][2] - b[1][1] + r->c_zy > 0)
      || (r->kbyj * b[0][1] - b[1][2] + r->c_yz > 0)
      )
      return 0;

    *t = (b[1][1] - r->y) * r->ij;
    float t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case OMP:
    {
    if((r->x < b[0][0]) || (r->x > b[1][0])
      || (r->y < b[0][1]) || (r->z > b[1][2])
      || (r->jbyk * b[1][2] - b[1][1] + r->c_zy > 0)
      || (r->kbyj * b[0][1] - b[0][2] + r->c_yz < 0)
      )
      return 0;

    *t = (b[1][1] - r->y) * r->ij;
    float t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case OPM:
    {
    if((r->x < b[0][0]) || (r->x > b[1][0])
      || (r->y > b[1][1]) || (r->z < b[0][2])
      || (r->jbyk * b[0][2] - b[0][1] + r->c_zy < 0)
      || (r->kbyj * b[1][1] - b[1][2] + r->c_yz > 0)
      )
      return 0;

    *t = (b[0][1] - r->y) * r->ij;
    float t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case OPP:
    {
    if((r->x < b[0][0]) || (r->x > b[1][0])
      || (r->y > b[1][1]) || (r->z > b[1][2])
      || (r->jbyk * b[1][2] - b[0][1] + r->c_zy < 0)
      || (r->kbyj * b[1][1] - b[0][2] + r->c_yz < 0)
      )
      return 0;

    *t = (b[0][1] - r->y) * r->ij;
    float t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }


  case MOM:
    {
    if((r->y < b[0][1]) || (r->y > b[1][1])
      || (r->x < b[0][0]) || (r->z < b[0][2])
      || (r->kbyi * b[0][0] - b[1][2] + r->c_xz > 0)
      || (r->ibyk * b[0][2] - b[1][0] + r->c_zx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
    float t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }


  case MOP:
    {
    if((r->y < b[0][1]) || (r->y > b[1][1])
      || (r->x < b[0][0]) || (r->z > b[1][2])
      || (r->kbyi * b[0][0] - b[0][2] + r->c_xz < 0)
      || (r->ibyk * b[1][2] - b[1][0] + r->c_zx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
    float t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case POM:
    {
    if((r->y < b[0][1]) || (r->y > b[1][1])
      || (r->x > b[1][0]) || (r->z < b[0][2])
      || (r->kbyi * b[1][0] - b[1][2] + r->c_xz > 0)
      || (r->ibyk * b[0][2] - b[0][0] + r->c_zx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
    float t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }


  case POP:
    {
    if((r->y < b[0][1]) || (r->y > b[1][1])
      || (r->x > b[1][0]) || (r->z > b[1][2])
      || (r->kbyi * b[1][0] - b[0][2] + r->c_xz < 0)
      || (r->ibyk * b[1][2] - b[0][0] + r->c_zx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
    float t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case MMO:
    {
    if((r->z < b[0][2]) || (r->z > b[1][2])
      || (r->x < b[0][0]) || (r->y < b[0][1])
      || (r->jbyi * b[0][0] - b[1][1] + r->c_xy > 0)
      || (r->ibyj * b[0][1] - b[1][0] + r->c_yx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
    float t1 = (b[1][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }

  case MPO:
    {
    if((r->z < b[0][2]) || (r->z > b[1][2])
      || (r->x < b[0][0]) || (r->y > b[1][1])
      || (r->jbyi * b[0][0] - b[0][1] + r->c_xy < 0)
      || (r->ibyj * b[1][1] - b[1][0] + r->c_yx > 0)
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
    float t1 = (b[0][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }


  case PMO:
    {
    if((r->z < b[0][2]) || (r->z > b[1][2])
      || (r->x > b[1][0]) || (r->y < b[0][1])
      || (r->jbyi * b[1][0] - b[1][1] + r->c_xy > 0)
      || (r->ibyj * b[0][1] - b[0][0] + r->c_yx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
    float t1 = (b[1][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }

  case PPO:
    {
    if((r->z < b[0][2]) || (r->z > b[1][2])
      || (r->x > b[1][0]) || (r->y > b[1][1])
      || (r->jbyi * b[1][0] - b[0][1] + r->c_xy < 0)
      || (r->ibyj * b[1][1] - b[0][0] + r->c_yx < 0)
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
    float t1 = (b[0][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }


  case MOO:
    {
    if((r->x < b[0][0])
      || (r->y < b[0][1]) || (r->y > b[1][1])
      || (r->z < b[0][2]) || (r->z > b[1][2])
      )
      return 0;

    *t = (b[1][0] - r->x) * r->ii;
    return 1;
    }

  case POO:
    {
    if((r->x > b[1][0])
      || (r->y < b[0][1]) || (r->y > b[1][1])
      || (r->z < b[0][2]) || (r->z > b[1][2])
      )
      return 0;

    *t = (b[0][0] - r->x) * r->ii;
    return 1;
    }

  case OMO:
    {
    if((r->y < b[0][1])
      || (r->x < b[0][0]) || (r->x > b[1][0])
      || (r->z < b[0][2]) || (r->z > b[1][2])
      )
      return 0;

    *t = (b[1][1] - r->y) * r->ij;
    return 1;
    }

  case OPO:
    {
    if((r->y > b[1][1])
      || (r->x < b[0][0]) || (r->x > b[1][0])
      || (r->z < b[0][2]) || (r->z > b[1][2])
      )
      return 0;

    *t = (b[0][1] - r->y) * r->ij;
    return 1;
    }


  case OOM:
    {
    if((r->z < b[0][2])
      || (r->x < b[0][0]) || (r->x > b[1][0])
      || (r->y < b[0][1]) || (r->y > b[1][1])
      )
      return 0;

    *t = (b[1][2] - r->z) * r->ik;
    return 1;
    }

  case OOP:
    {
    if((r->z > b[1][2])
      || (r->x < b[0][0]) || (r->x > b[1][0])
      || (r->y < b[0][1]) || (r->y > b[1][1])
      )
      return 0;

    *t = (b[0][2] - r->z) * r->ik;
    return 1;
    }
  }

  return 0;
}

#endif

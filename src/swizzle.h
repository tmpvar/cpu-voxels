/*
 * sse_swizzle.h: SSE "intrinsics" for SP float/32-bit int vector swizzling
 *                using SSE2 PSHUFD instruction
 *
 * Copyright 2011 Imran Haque (ihaque+sse[at]cs.stanford.edu)
 * originally posted to http://cs.stanford.edu/people/ihaque/sse_swizzle.h
 *
 * This code is released into the public domain and bears no
 * warranty whatsoever.
 *
 * This file defines SSE intrinsic-style functions for doing vector swizzling
 * according to the usual notation. For example, swizzles that in GLSL might
 * be written as:
 *
 *     float4 dst1 = src.xzwx;
 *     float4 dst2 = src.rgar;
 *
 * Can be written using this module as:
 *
 *     __m128 dst1 = _mm_swizzle_ps_xzwx(src);
 *     __m128 dst2 = _mm_swizzle_ps_rgar(src);
 *
 * Variants are defined for both XYZW and RGBA naming conventions as well as
 * both float and int versions (_mm_shuffle_ps_* vs _mm_shuffle_epi32_*). The
 * integer variants compile to the same assembly instructions as the floats,
 * but they save you some typecasting.
 *
 * This file includes a built-in self-test. To use it, rename the file to
 * sse_swizzle.c, and compile it with the preprocessor flag TEST_SSE_SWIZZLE
 * defined. You'll probably have to enable C99 mode.
 */

#ifndef _SSE_SWIZZLE_H_
#define _SSE_SWIZZLE_H_
#include <emmintrin.h>
#ifdef __SSE2__
static inline __m128  _mm_swizzle_ps_xxxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x00); }
static inline __m128  _mm_swizzle_ps_rrrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x00); }
static inline __m128i _mm_swizzle_epi32_xxxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x00); }
static inline __m128i _mm_swizzle_epi32_rrrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x00); }

static inline __m128  _mm_swizzle_ps_xxxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x40); }
static inline __m128  _mm_swizzle_ps_rrrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x40); }
static inline __m128i _mm_swizzle_epi32_xxxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x40); }
static inline __m128i _mm_swizzle_epi32_rrrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x40); }

static inline __m128  _mm_swizzle_ps_xxxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x80); }
static inline __m128  _mm_swizzle_ps_rrrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x80); }
static inline __m128i _mm_swizzle_epi32_xxxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x80); }
static inline __m128i _mm_swizzle_epi32_rrrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x80); }

static inline __m128  _mm_swizzle_ps_xxxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC0); }
static inline __m128  _mm_swizzle_ps_rrra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC0); }
static inline __m128i _mm_swizzle_epi32_xxxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC0); }
static inline __m128i _mm_swizzle_epi32_rrra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC0); }

static inline __m128  _mm_swizzle_ps_xxyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x10); }
static inline __m128  _mm_swizzle_ps_rrgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x10); }
static inline __m128i _mm_swizzle_epi32_xxyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x10); }
static inline __m128i _mm_swizzle_epi32_rrgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x10); }

static inline __m128  _mm_swizzle_ps_xxyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x50); }
static inline __m128  _mm_swizzle_ps_rrgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x50); }
static inline __m128i _mm_swizzle_epi32_xxyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x50); }
static inline __m128i _mm_swizzle_epi32_rrgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x50); }

static inline __m128  _mm_swizzle_ps_xxyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x90); }
static inline __m128  _mm_swizzle_ps_rrgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x90); }
static inline __m128i _mm_swizzle_epi32_xxyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x90); }
static inline __m128i _mm_swizzle_epi32_rrgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x90); }

static inline __m128  _mm_swizzle_ps_xxyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD0); }
static inline __m128  _mm_swizzle_ps_rrga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD0); }
static inline __m128i _mm_swizzle_epi32_xxyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD0); }
static inline __m128i _mm_swizzle_epi32_rrga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD0); }

static inline __m128  _mm_swizzle_ps_xxzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x20); }
static inline __m128  _mm_swizzle_ps_rrbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x20); }
static inline __m128i _mm_swizzle_epi32_xxzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x20); }
static inline __m128i _mm_swizzle_epi32_rrbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x20); }

static inline __m128  _mm_swizzle_ps_xxzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x60); }
static inline __m128  _mm_swizzle_ps_rrbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x60); }
static inline __m128i _mm_swizzle_epi32_xxzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x60); }
static inline __m128i _mm_swizzle_epi32_rrbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x60); }

static inline __m128  _mm_swizzle_ps_xxzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA0); }
static inline __m128  _mm_swizzle_ps_rrbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA0); }
static inline __m128i _mm_swizzle_epi32_xxzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA0); }
static inline __m128i _mm_swizzle_epi32_rrbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA0); }

static inline __m128  _mm_swizzle_ps_xxzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE0); }
static inline __m128  _mm_swizzle_ps_rrba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE0); }
static inline __m128i _mm_swizzle_epi32_xxzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE0); }
static inline __m128i _mm_swizzle_epi32_rrba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE0); }

static inline __m128  _mm_swizzle_ps_xxwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x30); }
static inline __m128  _mm_swizzle_ps_rrar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x30); }
static inline __m128i _mm_swizzle_epi32_xxwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x30); }
static inline __m128i _mm_swizzle_epi32_rrar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x30); }

static inline __m128  _mm_swizzle_ps_xxwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x70); }
static inline __m128  _mm_swizzle_ps_rrag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x70); }
static inline __m128i _mm_swizzle_epi32_xxwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x70); }
static inline __m128i _mm_swizzle_epi32_rrag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x70); }

static inline __m128  _mm_swizzle_ps_xxwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB0); }
static inline __m128  _mm_swizzle_ps_rrab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB0); }
static inline __m128i _mm_swizzle_epi32_xxwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB0); }
static inline __m128i _mm_swizzle_epi32_rrab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB0); }

static inline __m128  _mm_swizzle_ps_xxww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF0); }
static inline __m128  _mm_swizzle_ps_rraa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF0); }
static inline __m128i _mm_swizzle_epi32_xxww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF0); }
static inline __m128i _mm_swizzle_epi32_rraa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF0); }

static inline __m128  _mm_swizzle_ps_xyxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x04); }
static inline __m128  _mm_swizzle_ps_rgrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x04); }
static inline __m128i _mm_swizzle_epi32_xyxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x04); }
static inline __m128i _mm_swizzle_epi32_rgrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x04); }

static inline __m128  _mm_swizzle_ps_xyxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x44); }
static inline __m128  _mm_swizzle_ps_rgrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x44); }
static inline __m128i _mm_swizzle_epi32_xyxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x44); }
static inline __m128i _mm_swizzle_epi32_rgrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x44); }

static inline __m128  _mm_swizzle_ps_xyxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x84); }
static inline __m128  _mm_swizzle_ps_rgrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x84); }
static inline __m128i _mm_swizzle_epi32_xyxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x84); }
static inline __m128i _mm_swizzle_epi32_rgrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x84); }

static inline __m128  _mm_swizzle_ps_xyxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC4); }
static inline __m128  _mm_swizzle_ps_rgra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC4); }
static inline __m128i _mm_swizzle_epi32_xyxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC4); }
static inline __m128i _mm_swizzle_epi32_rgra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC4); }

static inline __m128  _mm_swizzle_ps_xyyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x14); }
static inline __m128  _mm_swizzle_ps_rggr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x14); }
static inline __m128i _mm_swizzle_epi32_xyyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x14); }
static inline __m128i _mm_swizzle_epi32_rggr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x14); }

static inline __m128  _mm_swizzle_ps_xyyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x54); }
static inline __m128  _mm_swizzle_ps_rggg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x54); }
static inline __m128i _mm_swizzle_epi32_xyyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x54); }
static inline __m128i _mm_swizzle_epi32_rggg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x54); }

static inline __m128  _mm_swizzle_ps_xyyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x94); }
static inline __m128  _mm_swizzle_ps_rggb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x94); }
static inline __m128i _mm_swizzle_epi32_xyyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x94); }
static inline __m128i _mm_swizzle_epi32_rggb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x94); }

static inline __m128  _mm_swizzle_ps_xyyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD4); }
static inline __m128  _mm_swizzle_ps_rgga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD4); }
static inline __m128i _mm_swizzle_epi32_xyyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD4); }
static inline __m128i _mm_swizzle_epi32_rgga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD4); }

static inline __m128  _mm_swizzle_ps_xyzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x24); }
static inline __m128  _mm_swizzle_ps_rgbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x24); }
static inline __m128i _mm_swizzle_epi32_xyzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x24); }
static inline __m128i _mm_swizzle_epi32_rgbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x24); }

static inline __m128  _mm_swizzle_ps_xyzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x64); }
static inline __m128  _mm_swizzle_ps_rgbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x64); }
static inline __m128i _mm_swizzle_epi32_xyzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x64); }
static inline __m128i _mm_swizzle_epi32_rgbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x64); }

static inline __m128  _mm_swizzle_ps_xyzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA4); }
static inline __m128  _mm_swizzle_ps_rgbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA4); }
static inline __m128i _mm_swizzle_epi32_xyzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA4); }
static inline __m128i _mm_swizzle_epi32_rgbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA4); }

static inline __m128  _mm_swizzle_ps_xyzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE4); }
static inline __m128  _mm_swizzle_ps_rgba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE4); }
static inline __m128i _mm_swizzle_epi32_xyzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE4); }
static inline __m128i _mm_swizzle_epi32_rgba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE4); }

static inline __m128  _mm_swizzle_ps_xywx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x34); }
static inline __m128  _mm_swizzle_ps_rgar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x34); }
static inline __m128i _mm_swizzle_epi32_xywx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x34); }
static inline __m128i _mm_swizzle_epi32_rgar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x34); }

static inline __m128  _mm_swizzle_ps_xywy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x74); }
static inline __m128  _mm_swizzle_ps_rgag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x74); }
static inline __m128i _mm_swizzle_epi32_xywy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x74); }
static inline __m128i _mm_swizzle_epi32_rgag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x74); }

static inline __m128  _mm_swizzle_ps_xywz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB4); }
static inline __m128  _mm_swizzle_ps_rgab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB4); }
static inline __m128i _mm_swizzle_epi32_xywz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB4); }
static inline __m128i _mm_swizzle_epi32_rgab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB4); }

static inline __m128  _mm_swizzle_ps_xyww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF4); }
static inline __m128  _mm_swizzle_ps_rgaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF4); }
static inline __m128i _mm_swizzle_epi32_xyww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF4); }
static inline __m128i _mm_swizzle_epi32_rgaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF4); }

static inline __m128  _mm_swizzle_ps_xzxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x08); }
static inline __m128  _mm_swizzle_ps_rbrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x08); }
static inline __m128i _mm_swizzle_epi32_xzxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x08); }
static inline __m128i _mm_swizzle_epi32_rbrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x08); }

static inline __m128  _mm_swizzle_ps_xzxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x48); }
static inline __m128  _mm_swizzle_ps_rbrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x48); }
static inline __m128i _mm_swizzle_epi32_xzxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x48); }
static inline __m128i _mm_swizzle_epi32_rbrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x48); }

static inline __m128  _mm_swizzle_ps_xzxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x88); }
static inline __m128  _mm_swizzle_ps_rbrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x88); }
static inline __m128i _mm_swizzle_epi32_xzxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x88); }
static inline __m128i _mm_swizzle_epi32_rbrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x88); }

static inline __m128  _mm_swizzle_ps_xzxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC8); }
static inline __m128  _mm_swizzle_ps_rbra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC8); }
static inline __m128i _mm_swizzle_epi32_xzxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC8); }
static inline __m128i _mm_swizzle_epi32_rbra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC8); }

static inline __m128  _mm_swizzle_ps_xzyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x18); }
static inline __m128  _mm_swizzle_ps_rbgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x18); }
static inline __m128i _mm_swizzle_epi32_xzyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x18); }
static inline __m128i _mm_swizzle_epi32_rbgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x18); }

static inline __m128  _mm_swizzle_ps_xzyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x58); }
static inline __m128  _mm_swizzle_ps_rbgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x58); }
static inline __m128i _mm_swizzle_epi32_xzyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x58); }
static inline __m128i _mm_swizzle_epi32_rbgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x58); }

static inline __m128  _mm_swizzle_ps_xzyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x98); }
static inline __m128  _mm_swizzle_ps_rbgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x98); }
static inline __m128i _mm_swizzle_epi32_xzyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x98); }
static inline __m128i _mm_swizzle_epi32_rbgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x98); }

static inline __m128  _mm_swizzle_ps_xzyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD8); }
static inline __m128  _mm_swizzle_ps_rbga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD8); }
static inline __m128i _mm_swizzle_epi32_xzyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD8); }
static inline __m128i _mm_swizzle_epi32_rbga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD8); }

static inline __m128  _mm_swizzle_ps_xzzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x28); }
static inline __m128  _mm_swizzle_ps_rbbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x28); }
static inline __m128i _mm_swizzle_epi32_xzzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x28); }
static inline __m128i _mm_swizzle_epi32_rbbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x28); }

static inline __m128  _mm_swizzle_ps_xzzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x68); }
static inline __m128  _mm_swizzle_ps_rbbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x68); }
static inline __m128i _mm_swizzle_epi32_xzzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x68); }
static inline __m128i _mm_swizzle_epi32_rbbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x68); }

static inline __m128  _mm_swizzle_ps_xzzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA8); }
static inline __m128  _mm_swizzle_ps_rbbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA8); }
static inline __m128i _mm_swizzle_epi32_xzzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA8); }
static inline __m128i _mm_swizzle_epi32_rbbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA8); }

static inline __m128  _mm_swizzle_ps_xzzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE8); }
static inline __m128  _mm_swizzle_ps_rbba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE8); }
static inline __m128i _mm_swizzle_epi32_xzzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE8); }
static inline __m128i _mm_swizzle_epi32_rbba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE8); }

static inline __m128  _mm_swizzle_ps_xzwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x38); }
static inline __m128  _mm_swizzle_ps_rbar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x38); }
static inline __m128i _mm_swizzle_epi32_xzwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x38); }
static inline __m128i _mm_swizzle_epi32_rbar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x38); }

static inline __m128  _mm_swizzle_ps_xzwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x78); }
static inline __m128  _mm_swizzle_ps_rbag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x78); }
static inline __m128i _mm_swizzle_epi32_xzwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x78); }
static inline __m128i _mm_swizzle_epi32_rbag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x78); }

static inline __m128  _mm_swizzle_ps_xzwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB8); }
static inline __m128  _mm_swizzle_ps_rbab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB8); }
static inline __m128i _mm_swizzle_epi32_xzwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB8); }
static inline __m128i _mm_swizzle_epi32_rbab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB8); }

static inline __m128  _mm_swizzle_ps_xzww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF8); }
static inline __m128  _mm_swizzle_ps_rbaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF8); }
static inline __m128i _mm_swizzle_epi32_xzww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF8); }
static inline __m128i _mm_swizzle_epi32_rbaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF8); }

static inline __m128  _mm_swizzle_ps_xwxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0C); }
static inline __m128  _mm_swizzle_ps_rarr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0C); }
static inline __m128i _mm_swizzle_epi32_xwxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0C); }
static inline __m128i _mm_swizzle_epi32_rarr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0C); }

static inline __m128  _mm_swizzle_ps_xwxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4C); }
static inline __m128  _mm_swizzle_ps_rarg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4C); }
static inline __m128i _mm_swizzle_epi32_xwxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4C); }
static inline __m128i _mm_swizzle_epi32_rarg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4C); }

static inline __m128  _mm_swizzle_ps_xwxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8C); }
static inline __m128  _mm_swizzle_ps_rarb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8C); }
static inline __m128i _mm_swizzle_epi32_xwxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8C); }
static inline __m128i _mm_swizzle_epi32_rarb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8C); }

static inline __m128  _mm_swizzle_ps_xwxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCC); }
static inline __m128  _mm_swizzle_ps_rara(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCC); }
static inline __m128i _mm_swizzle_epi32_xwxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCC); }
static inline __m128i _mm_swizzle_epi32_rara(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCC); }

static inline __m128  _mm_swizzle_ps_xwyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1C); }
static inline __m128  _mm_swizzle_ps_ragr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1C); }
static inline __m128i _mm_swizzle_epi32_xwyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1C); }
static inline __m128i _mm_swizzle_epi32_ragr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1C); }

static inline __m128  _mm_swizzle_ps_xwyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5C); }
static inline __m128  _mm_swizzle_ps_ragg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5C); }
static inline __m128i _mm_swizzle_epi32_xwyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5C); }
static inline __m128i _mm_swizzle_epi32_ragg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5C); }

static inline __m128  _mm_swizzle_ps_xwyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9C); }
static inline __m128  _mm_swizzle_ps_ragb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9C); }
static inline __m128i _mm_swizzle_epi32_xwyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9C); }
static inline __m128i _mm_swizzle_epi32_ragb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9C); }

static inline __m128  _mm_swizzle_ps_xwyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDC); }
static inline __m128  _mm_swizzle_ps_raga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDC); }
static inline __m128i _mm_swizzle_epi32_xwyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDC); }
static inline __m128i _mm_swizzle_epi32_raga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDC); }

static inline __m128  _mm_swizzle_ps_xwzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2C); }
static inline __m128  _mm_swizzle_ps_rabr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2C); }
static inline __m128i _mm_swizzle_epi32_xwzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2C); }
static inline __m128i _mm_swizzle_epi32_rabr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2C); }

static inline __m128  _mm_swizzle_ps_xwzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6C); }
static inline __m128  _mm_swizzle_ps_rabg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6C); }
static inline __m128i _mm_swizzle_epi32_xwzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6C); }
static inline __m128i _mm_swizzle_epi32_rabg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6C); }

static inline __m128  _mm_swizzle_ps_xwzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAC); }
static inline __m128  _mm_swizzle_ps_rabb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAC); }
static inline __m128i _mm_swizzle_epi32_xwzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAC); }
static inline __m128i _mm_swizzle_epi32_rabb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAC); }

static inline __m128  _mm_swizzle_ps_xwzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEC); }
static inline __m128  _mm_swizzle_ps_raba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEC); }
static inline __m128i _mm_swizzle_epi32_xwzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEC); }
static inline __m128i _mm_swizzle_epi32_raba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEC); }

static inline __m128  _mm_swizzle_ps_xwwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3C); }
static inline __m128  _mm_swizzle_ps_raar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3C); }
static inline __m128i _mm_swizzle_epi32_xwwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3C); }
static inline __m128i _mm_swizzle_epi32_raar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3C); }

static inline __m128  _mm_swizzle_ps_xwwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7C); }
static inline __m128  _mm_swizzle_ps_raag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7C); }
static inline __m128i _mm_swizzle_epi32_xwwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7C); }
static inline __m128i _mm_swizzle_epi32_raag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7C); }

static inline __m128  _mm_swizzle_ps_xwwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBC); }
static inline __m128  _mm_swizzle_ps_raab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBC); }
static inline __m128i _mm_swizzle_epi32_xwwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBC); }
static inline __m128i _mm_swizzle_epi32_raab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBC); }

static inline __m128  _mm_swizzle_ps_xwww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFC); }
static inline __m128  _mm_swizzle_ps_raaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFC); }
static inline __m128i _mm_swizzle_epi32_xwww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFC); }
static inline __m128i _mm_swizzle_epi32_raaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFC); }

static inline __m128  _mm_swizzle_ps_yxxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x01); }
static inline __m128  _mm_swizzle_ps_grrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x01); }
static inline __m128i _mm_swizzle_epi32_yxxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x01); }
static inline __m128i _mm_swizzle_epi32_grrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x01); }

static inline __m128  _mm_swizzle_ps_yxxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x41); }
static inline __m128  _mm_swizzle_ps_grrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x41); }
static inline __m128i _mm_swizzle_epi32_yxxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x41); }
static inline __m128i _mm_swizzle_epi32_grrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x41); }

static inline __m128  _mm_swizzle_ps_yxxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x81); }
static inline __m128  _mm_swizzle_ps_grrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x81); }
static inline __m128i _mm_swizzle_epi32_yxxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x81); }
static inline __m128i _mm_swizzle_epi32_grrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x81); }

static inline __m128  _mm_swizzle_ps_yxxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC1); }
static inline __m128  _mm_swizzle_ps_grra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC1); }
static inline __m128i _mm_swizzle_epi32_yxxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC1); }
static inline __m128i _mm_swizzle_epi32_grra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC1); }

static inline __m128  _mm_swizzle_ps_yxyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x11); }
static inline __m128  _mm_swizzle_ps_grgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x11); }
static inline __m128i _mm_swizzle_epi32_yxyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x11); }
static inline __m128i _mm_swizzle_epi32_grgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x11); }

static inline __m128  _mm_swizzle_ps_yxyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x51); }
static inline __m128  _mm_swizzle_ps_grgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x51); }
static inline __m128i _mm_swizzle_epi32_yxyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x51); }
static inline __m128i _mm_swizzle_epi32_grgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x51); }

static inline __m128  _mm_swizzle_ps_yxyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x91); }
static inline __m128  _mm_swizzle_ps_grgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x91); }
static inline __m128i _mm_swizzle_epi32_yxyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x91); }
static inline __m128i _mm_swizzle_epi32_grgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x91); }

static inline __m128  _mm_swizzle_ps_yxyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD1); }
static inline __m128  _mm_swizzle_ps_grga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD1); }
static inline __m128i _mm_swizzle_epi32_yxyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD1); }
static inline __m128i _mm_swizzle_epi32_grga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD1); }

static inline __m128  _mm_swizzle_ps_yxzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x21); }
static inline __m128  _mm_swizzle_ps_grbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x21); }
static inline __m128i _mm_swizzle_epi32_yxzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x21); }
static inline __m128i _mm_swizzle_epi32_grbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x21); }

static inline __m128  _mm_swizzle_ps_yxzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x61); }
static inline __m128  _mm_swizzle_ps_grbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x61); }
static inline __m128i _mm_swizzle_epi32_yxzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x61); }
static inline __m128i _mm_swizzle_epi32_grbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x61); }

static inline __m128  _mm_swizzle_ps_yxzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA1); }
static inline __m128  _mm_swizzle_ps_grbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA1); }
static inline __m128i _mm_swizzle_epi32_yxzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA1); }
static inline __m128i _mm_swizzle_epi32_grbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA1); }

static inline __m128  _mm_swizzle_ps_yxzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE1); }
static inline __m128  _mm_swizzle_ps_grba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE1); }
static inline __m128i _mm_swizzle_epi32_yxzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE1); }
static inline __m128i _mm_swizzle_epi32_grba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE1); }

static inline __m128  _mm_swizzle_ps_yxwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x31); }
static inline __m128  _mm_swizzle_ps_grar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x31); }
static inline __m128i _mm_swizzle_epi32_yxwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x31); }
static inline __m128i _mm_swizzle_epi32_grar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x31); }

static inline __m128  _mm_swizzle_ps_yxwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x71); }
static inline __m128  _mm_swizzle_ps_grag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x71); }
static inline __m128i _mm_swizzle_epi32_yxwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x71); }
static inline __m128i _mm_swizzle_epi32_grag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x71); }

static inline __m128  _mm_swizzle_ps_yxwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB1); }
static inline __m128  _mm_swizzle_ps_grab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB1); }
static inline __m128i _mm_swizzle_epi32_yxwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB1); }
static inline __m128i _mm_swizzle_epi32_grab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB1); }

static inline __m128  _mm_swizzle_ps_yxww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF1); }
static inline __m128  _mm_swizzle_ps_graa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF1); }
static inline __m128i _mm_swizzle_epi32_yxww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF1); }
static inline __m128i _mm_swizzle_epi32_graa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF1); }

static inline __m128  _mm_swizzle_ps_yyxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x05); }
static inline __m128  _mm_swizzle_ps_ggrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x05); }
static inline __m128i _mm_swizzle_epi32_yyxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x05); }
static inline __m128i _mm_swizzle_epi32_ggrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x05); }

static inline __m128  _mm_swizzle_ps_yyxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x45); }
static inline __m128  _mm_swizzle_ps_ggrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x45); }
static inline __m128i _mm_swizzle_epi32_yyxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x45); }
static inline __m128i _mm_swizzle_epi32_ggrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x45); }

static inline __m128  _mm_swizzle_ps_yyxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x85); }
static inline __m128  _mm_swizzle_ps_ggrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x85); }
static inline __m128i _mm_swizzle_epi32_yyxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x85); }
static inline __m128i _mm_swizzle_epi32_ggrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x85); }

static inline __m128  _mm_swizzle_ps_yyxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC5); }
static inline __m128  _mm_swizzle_ps_ggra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC5); }
static inline __m128i _mm_swizzle_epi32_yyxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC5); }
static inline __m128i _mm_swizzle_epi32_ggra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC5); }

static inline __m128  _mm_swizzle_ps_yyyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x15); }
static inline __m128  _mm_swizzle_ps_gggr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x15); }
static inline __m128i _mm_swizzle_epi32_yyyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x15); }
static inline __m128i _mm_swizzle_epi32_gggr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x15); }

static inline __m128  _mm_swizzle_ps_yyyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x55); }
static inline __m128  _mm_swizzle_ps_gggg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x55); }
static inline __m128i _mm_swizzle_epi32_yyyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x55); }
static inline __m128i _mm_swizzle_epi32_gggg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x55); }

static inline __m128  _mm_swizzle_ps_yyyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x95); }
static inline __m128  _mm_swizzle_ps_gggb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x95); }
static inline __m128i _mm_swizzle_epi32_yyyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x95); }
static inline __m128i _mm_swizzle_epi32_gggb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x95); }

static inline __m128  _mm_swizzle_ps_yyyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD5); }
static inline __m128  _mm_swizzle_ps_ggga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD5); }
static inline __m128i _mm_swizzle_epi32_yyyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD5); }
static inline __m128i _mm_swizzle_epi32_ggga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD5); }

static inline __m128  _mm_swizzle_ps_yyzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x25); }
static inline __m128  _mm_swizzle_ps_ggbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x25); }
static inline __m128i _mm_swizzle_epi32_yyzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x25); }
static inline __m128i _mm_swizzle_epi32_ggbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x25); }

static inline __m128  _mm_swizzle_ps_yyzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x65); }
static inline __m128  _mm_swizzle_ps_ggbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x65); }
static inline __m128i _mm_swizzle_epi32_yyzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x65); }
static inline __m128i _mm_swizzle_epi32_ggbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x65); }

static inline __m128  _mm_swizzle_ps_yyzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA5); }
static inline __m128  _mm_swizzle_ps_ggbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA5); }
static inline __m128i _mm_swizzle_epi32_yyzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA5); }
static inline __m128i _mm_swizzle_epi32_ggbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA5); }

static inline __m128  _mm_swizzle_ps_yyzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE5); }
static inline __m128  _mm_swizzle_ps_ggba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE5); }
static inline __m128i _mm_swizzle_epi32_yyzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE5); }
static inline __m128i _mm_swizzle_epi32_ggba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE5); }

static inline __m128  _mm_swizzle_ps_yywx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x35); }
static inline __m128  _mm_swizzle_ps_ggar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x35); }
static inline __m128i _mm_swizzle_epi32_yywx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x35); }
static inline __m128i _mm_swizzle_epi32_ggar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x35); }

static inline __m128  _mm_swizzle_ps_yywy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x75); }
static inline __m128  _mm_swizzle_ps_ggag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x75); }
static inline __m128i _mm_swizzle_epi32_yywy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x75); }
static inline __m128i _mm_swizzle_epi32_ggag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x75); }

static inline __m128  _mm_swizzle_ps_yywz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB5); }
static inline __m128  _mm_swizzle_ps_ggab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB5); }
static inline __m128i _mm_swizzle_epi32_yywz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB5); }
static inline __m128i _mm_swizzle_epi32_ggab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB5); }

static inline __m128  _mm_swizzle_ps_yyww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF5); }
static inline __m128  _mm_swizzle_ps_ggaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF5); }
static inline __m128i _mm_swizzle_epi32_yyww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF5); }
static inline __m128i _mm_swizzle_epi32_ggaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF5); }

static inline __m128  _mm_swizzle_ps_yzxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x09); }
static inline __m128  _mm_swizzle_ps_gbrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x09); }
static inline __m128i _mm_swizzle_epi32_yzxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x09); }
static inline __m128i _mm_swizzle_epi32_gbrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x09); }

static inline __m128  _mm_swizzle_ps_yzxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x49); }
static inline __m128  _mm_swizzle_ps_gbrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x49); }
static inline __m128i _mm_swizzle_epi32_yzxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x49); }
static inline __m128i _mm_swizzle_epi32_gbrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x49); }

static inline __m128  _mm_swizzle_ps_yzxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x89); }
static inline __m128  _mm_swizzle_ps_gbrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x89); }
static inline __m128i _mm_swizzle_epi32_yzxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x89); }
static inline __m128i _mm_swizzle_epi32_gbrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x89); }

static inline __m128  _mm_swizzle_ps_yzxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC9); }
static inline __m128  _mm_swizzle_ps_gbra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC9); }
static inline __m128i _mm_swizzle_epi32_yzxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC9); }
static inline __m128i _mm_swizzle_epi32_gbra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC9); }

static inline __m128  _mm_swizzle_ps_yzyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x19); }
static inline __m128  _mm_swizzle_ps_gbgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x19); }
static inline __m128i _mm_swizzle_epi32_yzyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x19); }
static inline __m128i _mm_swizzle_epi32_gbgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x19); }

static inline __m128  _mm_swizzle_ps_yzyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x59); }
static inline __m128  _mm_swizzle_ps_gbgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x59); }
static inline __m128i _mm_swizzle_epi32_yzyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x59); }
static inline __m128i _mm_swizzle_epi32_gbgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x59); }

static inline __m128  _mm_swizzle_ps_yzyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x99); }
static inline __m128  _mm_swizzle_ps_gbgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x99); }
static inline __m128i _mm_swizzle_epi32_yzyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x99); }
static inline __m128i _mm_swizzle_epi32_gbgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x99); }

static inline __m128  _mm_swizzle_ps_yzyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD9); }
static inline __m128  _mm_swizzle_ps_gbga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD9); }
static inline __m128i _mm_swizzle_epi32_yzyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD9); }
static inline __m128i _mm_swizzle_epi32_gbga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD9); }

static inline __m128  _mm_swizzle_ps_yzzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x29); }
static inline __m128  _mm_swizzle_ps_gbbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x29); }
static inline __m128i _mm_swizzle_epi32_yzzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x29); }
static inline __m128i _mm_swizzle_epi32_gbbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x29); }

static inline __m128  _mm_swizzle_ps_yzzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x69); }
static inline __m128  _mm_swizzle_ps_gbbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x69); }
static inline __m128i _mm_swizzle_epi32_yzzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x69); }
static inline __m128i _mm_swizzle_epi32_gbbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x69); }

static inline __m128  _mm_swizzle_ps_yzzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA9); }
static inline __m128  _mm_swizzle_ps_gbbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA9); }
static inline __m128i _mm_swizzle_epi32_yzzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA9); }
static inline __m128i _mm_swizzle_epi32_gbbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA9); }

static inline __m128  _mm_swizzle_ps_yzzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE9); }
static inline __m128  _mm_swizzle_ps_gbba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE9); }
static inline __m128i _mm_swizzle_epi32_yzzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE9); }
static inline __m128i _mm_swizzle_epi32_gbba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE9); }

static inline __m128  _mm_swizzle_ps_yzwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x39); }
static inline __m128  _mm_swizzle_ps_gbar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x39); }
static inline __m128i _mm_swizzle_epi32_yzwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x39); }
static inline __m128i _mm_swizzle_epi32_gbar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x39); }

static inline __m128  _mm_swizzle_ps_yzwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x79); }
static inline __m128  _mm_swizzle_ps_gbag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x79); }
static inline __m128i _mm_swizzle_epi32_yzwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x79); }
static inline __m128i _mm_swizzle_epi32_gbag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x79); }

static inline __m128  _mm_swizzle_ps_yzwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB9); }
static inline __m128  _mm_swizzle_ps_gbab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB9); }
static inline __m128i _mm_swizzle_epi32_yzwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB9); }
static inline __m128i _mm_swizzle_epi32_gbab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB9); }

static inline __m128  _mm_swizzle_ps_yzww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF9); }
static inline __m128  _mm_swizzle_ps_gbaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF9); }
static inline __m128i _mm_swizzle_epi32_yzww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF9); }
static inline __m128i _mm_swizzle_epi32_gbaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF9); }

static inline __m128  _mm_swizzle_ps_ywxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0D); }
static inline __m128  _mm_swizzle_ps_garr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0D); }
static inline __m128i _mm_swizzle_epi32_ywxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0D); }
static inline __m128i _mm_swizzle_epi32_garr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0D); }

static inline __m128  _mm_swizzle_ps_ywxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4D); }
static inline __m128  _mm_swizzle_ps_garg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4D); }
static inline __m128i _mm_swizzle_epi32_ywxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4D); }
static inline __m128i _mm_swizzle_epi32_garg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4D); }

static inline __m128  _mm_swizzle_ps_ywxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8D); }
static inline __m128  _mm_swizzle_ps_garb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8D); }
static inline __m128i _mm_swizzle_epi32_ywxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8D); }
static inline __m128i _mm_swizzle_epi32_garb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8D); }

static inline __m128  _mm_swizzle_ps_ywxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCD); }
static inline __m128  _mm_swizzle_ps_gara(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCD); }
static inline __m128i _mm_swizzle_epi32_ywxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCD); }
static inline __m128i _mm_swizzle_epi32_gara(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCD); }

static inline __m128  _mm_swizzle_ps_ywyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1D); }
static inline __m128  _mm_swizzle_ps_gagr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1D); }
static inline __m128i _mm_swizzle_epi32_ywyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1D); }
static inline __m128i _mm_swizzle_epi32_gagr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1D); }

static inline __m128  _mm_swizzle_ps_ywyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5D); }
static inline __m128  _mm_swizzle_ps_gagg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5D); }
static inline __m128i _mm_swizzle_epi32_ywyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5D); }
static inline __m128i _mm_swizzle_epi32_gagg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5D); }

static inline __m128  _mm_swizzle_ps_ywyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9D); }
static inline __m128  _mm_swizzle_ps_gagb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9D); }
static inline __m128i _mm_swizzle_epi32_ywyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9D); }
static inline __m128i _mm_swizzle_epi32_gagb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9D); }

static inline __m128  _mm_swizzle_ps_ywyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDD); }
static inline __m128  _mm_swizzle_ps_gaga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDD); }
static inline __m128i _mm_swizzle_epi32_ywyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDD); }
static inline __m128i _mm_swizzle_epi32_gaga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDD); }

static inline __m128  _mm_swizzle_ps_ywzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2D); }
static inline __m128  _mm_swizzle_ps_gabr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2D); }
static inline __m128i _mm_swizzle_epi32_ywzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2D); }
static inline __m128i _mm_swizzle_epi32_gabr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2D); }

static inline __m128  _mm_swizzle_ps_ywzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6D); }
static inline __m128  _mm_swizzle_ps_gabg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6D); }
static inline __m128i _mm_swizzle_epi32_ywzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6D); }
static inline __m128i _mm_swizzle_epi32_gabg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6D); }

static inline __m128  _mm_swizzle_ps_ywzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAD); }
static inline __m128  _mm_swizzle_ps_gabb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAD); }
static inline __m128i _mm_swizzle_epi32_ywzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAD); }
static inline __m128i _mm_swizzle_epi32_gabb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAD); }

static inline __m128  _mm_swizzle_ps_ywzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xED); }
static inline __m128  _mm_swizzle_ps_gaba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xED); }
static inline __m128i _mm_swizzle_epi32_ywzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xED); }
static inline __m128i _mm_swizzle_epi32_gaba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xED); }

static inline __m128  _mm_swizzle_ps_ywwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3D); }
static inline __m128  _mm_swizzle_ps_gaar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3D); }
static inline __m128i _mm_swizzle_epi32_ywwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3D); }
static inline __m128i _mm_swizzle_epi32_gaar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3D); }

static inline __m128  _mm_swizzle_ps_ywwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7D); }
static inline __m128  _mm_swizzle_ps_gaag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7D); }
static inline __m128i _mm_swizzle_epi32_ywwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7D); }
static inline __m128i _mm_swizzle_epi32_gaag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7D); }

static inline __m128  _mm_swizzle_ps_ywwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBD); }
static inline __m128  _mm_swizzle_ps_gaab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBD); }
static inline __m128i _mm_swizzle_epi32_ywwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBD); }
static inline __m128i _mm_swizzle_epi32_gaab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBD); }

static inline __m128  _mm_swizzle_ps_ywww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFD); }
static inline __m128  _mm_swizzle_ps_gaaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFD); }
static inline __m128i _mm_swizzle_epi32_ywww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFD); }
static inline __m128i _mm_swizzle_epi32_gaaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFD); }

static inline __m128  _mm_swizzle_ps_zxxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x02); }
static inline __m128  _mm_swizzle_ps_brrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x02); }
static inline __m128i _mm_swizzle_epi32_zxxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x02); }
static inline __m128i _mm_swizzle_epi32_brrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x02); }

static inline __m128  _mm_swizzle_ps_zxxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x42); }
static inline __m128  _mm_swizzle_ps_brrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x42); }
static inline __m128i _mm_swizzle_epi32_zxxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x42); }
static inline __m128i _mm_swizzle_epi32_brrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x42); }

static inline __m128  _mm_swizzle_ps_zxxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x82); }
static inline __m128  _mm_swizzle_ps_brrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x82); }
static inline __m128i _mm_swizzle_epi32_zxxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x82); }
static inline __m128i _mm_swizzle_epi32_brrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x82); }

static inline __m128  _mm_swizzle_ps_zxxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC2); }
static inline __m128  _mm_swizzle_ps_brra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC2); }
static inline __m128i _mm_swizzle_epi32_zxxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC2); }
static inline __m128i _mm_swizzle_epi32_brra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC2); }

static inline __m128  _mm_swizzle_ps_zxyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x12); }
static inline __m128  _mm_swizzle_ps_brgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x12); }
static inline __m128i _mm_swizzle_epi32_zxyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x12); }
static inline __m128i _mm_swizzle_epi32_brgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x12); }

static inline __m128  _mm_swizzle_ps_zxyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x52); }
static inline __m128  _mm_swizzle_ps_brgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x52); }
static inline __m128i _mm_swizzle_epi32_zxyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x52); }
static inline __m128i _mm_swizzle_epi32_brgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x52); }

static inline __m128  _mm_swizzle_ps_zxyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x92); }
static inline __m128  _mm_swizzle_ps_brgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x92); }
static inline __m128i _mm_swizzle_epi32_zxyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x92); }
static inline __m128i _mm_swizzle_epi32_brgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x92); }

static inline __m128  _mm_swizzle_ps_zxyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD2); }
static inline __m128  _mm_swizzle_ps_brga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD2); }
static inline __m128i _mm_swizzle_epi32_zxyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD2); }
static inline __m128i _mm_swizzle_epi32_brga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD2); }

static inline __m128  _mm_swizzle_ps_zxzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x22); }
static inline __m128  _mm_swizzle_ps_brbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x22); }
static inline __m128i _mm_swizzle_epi32_zxzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x22); }
static inline __m128i _mm_swizzle_epi32_brbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x22); }

static inline __m128  _mm_swizzle_ps_zxzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x62); }
static inline __m128  _mm_swizzle_ps_brbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x62); }
static inline __m128i _mm_swizzle_epi32_zxzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x62); }
static inline __m128i _mm_swizzle_epi32_brbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x62); }

static inline __m128  _mm_swizzle_ps_zxzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA2); }
static inline __m128  _mm_swizzle_ps_brbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA2); }
static inline __m128i _mm_swizzle_epi32_zxzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA2); }
static inline __m128i _mm_swizzle_epi32_brbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA2); }

static inline __m128  _mm_swizzle_ps_zxzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE2); }
static inline __m128  _mm_swizzle_ps_brba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE2); }
static inline __m128i _mm_swizzle_epi32_zxzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE2); }
static inline __m128i _mm_swizzle_epi32_brba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE2); }

static inline __m128  _mm_swizzle_ps_zxwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x32); }
static inline __m128  _mm_swizzle_ps_brar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x32); }
static inline __m128i _mm_swizzle_epi32_zxwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x32); }
static inline __m128i _mm_swizzle_epi32_brar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x32); }

static inline __m128  _mm_swizzle_ps_zxwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x72); }
static inline __m128  _mm_swizzle_ps_brag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x72); }
static inline __m128i _mm_swizzle_epi32_zxwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x72); }
static inline __m128i _mm_swizzle_epi32_brag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x72); }

static inline __m128  _mm_swizzle_ps_zxwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB2); }
static inline __m128  _mm_swizzle_ps_brab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB2); }
static inline __m128i _mm_swizzle_epi32_zxwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB2); }
static inline __m128i _mm_swizzle_epi32_brab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB2); }

static inline __m128  _mm_swizzle_ps_zxww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF2); }
static inline __m128  _mm_swizzle_ps_braa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF2); }
static inline __m128i _mm_swizzle_epi32_zxww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF2); }
static inline __m128i _mm_swizzle_epi32_braa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF2); }

static inline __m128  _mm_swizzle_ps_zyxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x06); }
static inline __m128  _mm_swizzle_ps_bgrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x06); }
static inline __m128i _mm_swizzle_epi32_zyxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x06); }
static inline __m128i _mm_swizzle_epi32_bgrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x06); }

static inline __m128  _mm_swizzle_ps_zyxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x46); }
static inline __m128  _mm_swizzle_ps_bgrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x46); }
static inline __m128i _mm_swizzle_epi32_zyxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x46); }
static inline __m128i _mm_swizzle_epi32_bgrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x46); }

static inline __m128  _mm_swizzle_ps_zyxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x86); }
static inline __m128  _mm_swizzle_ps_bgrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x86); }
static inline __m128i _mm_swizzle_epi32_zyxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x86); }
static inline __m128i _mm_swizzle_epi32_bgrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x86); }

static inline __m128  _mm_swizzle_ps_zyxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC6); }
static inline __m128  _mm_swizzle_ps_bgra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC6); }
static inline __m128i _mm_swizzle_epi32_zyxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC6); }
static inline __m128i _mm_swizzle_epi32_bgra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC6); }

static inline __m128  _mm_swizzle_ps_zyyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x16); }
static inline __m128  _mm_swizzle_ps_bggr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x16); }
static inline __m128i _mm_swizzle_epi32_zyyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x16); }
static inline __m128i _mm_swizzle_epi32_bggr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x16); }

static inline __m128  _mm_swizzle_ps_zyyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x56); }
static inline __m128  _mm_swizzle_ps_bggg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x56); }
static inline __m128i _mm_swizzle_epi32_zyyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x56); }
static inline __m128i _mm_swizzle_epi32_bggg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x56); }

static inline __m128  _mm_swizzle_ps_zyyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x96); }
static inline __m128  _mm_swizzle_ps_bggb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x96); }
static inline __m128i _mm_swizzle_epi32_zyyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x96); }
static inline __m128i _mm_swizzle_epi32_bggb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x96); }

static inline __m128  _mm_swizzle_ps_zyyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD6); }
static inline __m128  _mm_swizzle_ps_bgga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD6); }
static inline __m128i _mm_swizzle_epi32_zyyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD6); }
static inline __m128i _mm_swizzle_epi32_bgga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD6); }

static inline __m128  _mm_swizzle_ps_zyzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x26); }
static inline __m128  _mm_swizzle_ps_bgbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x26); }
static inline __m128i _mm_swizzle_epi32_zyzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x26); }
static inline __m128i _mm_swizzle_epi32_bgbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x26); }

static inline __m128  _mm_swizzle_ps_zyzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x66); }
static inline __m128  _mm_swizzle_ps_bgbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x66); }
static inline __m128i _mm_swizzle_epi32_zyzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x66); }
static inline __m128i _mm_swizzle_epi32_bgbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x66); }

static inline __m128  _mm_swizzle_ps_zyzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA6); }
static inline __m128  _mm_swizzle_ps_bgbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA6); }
static inline __m128i _mm_swizzle_epi32_zyzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA6); }
static inline __m128i _mm_swizzle_epi32_bgbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA6); }

static inline __m128  _mm_swizzle_ps_zyzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE6); }
static inline __m128  _mm_swizzle_ps_bgba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE6); }
static inline __m128i _mm_swizzle_epi32_zyzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE6); }
static inline __m128i _mm_swizzle_epi32_bgba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE6); }

static inline __m128  _mm_swizzle_ps_zywx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x36); }
static inline __m128  _mm_swizzle_ps_bgar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x36); }
static inline __m128i _mm_swizzle_epi32_zywx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x36); }
static inline __m128i _mm_swizzle_epi32_bgar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x36); }

static inline __m128  _mm_swizzle_ps_zywy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x76); }
static inline __m128  _mm_swizzle_ps_bgag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x76); }
static inline __m128i _mm_swizzle_epi32_zywy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x76); }
static inline __m128i _mm_swizzle_epi32_bgag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x76); }

static inline __m128  _mm_swizzle_ps_zywz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB6); }
static inline __m128  _mm_swizzle_ps_bgab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB6); }
static inline __m128i _mm_swizzle_epi32_zywz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB6); }
static inline __m128i _mm_swizzle_epi32_bgab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB6); }

static inline __m128  _mm_swizzle_ps_zyww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF6); }
static inline __m128  _mm_swizzle_ps_bgaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF6); }
static inline __m128i _mm_swizzle_epi32_zyww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF6); }
static inline __m128i _mm_swizzle_epi32_bgaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF6); }

static inline __m128  _mm_swizzle_ps_zzxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0A); }
static inline __m128  _mm_swizzle_ps_bbrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0A); }
static inline __m128i _mm_swizzle_epi32_zzxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0A); }
static inline __m128i _mm_swizzle_epi32_bbrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0A); }

static inline __m128  _mm_swizzle_ps_zzxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4A); }
static inline __m128  _mm_swizzle_ps_bbrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4A); }
static inline __m128i _mm_swizzle_epi32_zzxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4A); }
static inline __m128i _mm_swizzle_epi32_bbrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4A); }

static inline __m128  _mm_swizzle_ps_zzxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8A); }
static inline __m128  _mm_swizzle_ps_bbrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8A); }
static inline __m128i _mm_swizzle_epi32_zzxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8A); }
static inline __m128i _mm_swizzle_epi32_bbrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8A); }

static inline __m128  _mm_swizzle_ps_zzxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCA); }
static inline __m128  _mm_swizzle_ps_bbra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCA); }
static inline __m128i _mm_swizzle_epi32_zzxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCA); }
static inline __m128i _mm_swizzle_epi32_bbra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCA); }

static inline __m128  _mm_swizzle_ps_zzyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1A); }
static inline __m128  _mm_swizzle_ps_bbgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1A); }
static inline __m128i _mm_swizzle_epi32_zzyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1A); }
static inline __m128i _mm_swizzle_epi32_bbgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1A); }

static inline __m128  _mm_swizzle_ps_zzyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5A); }
static inline __m128  _mm_swizzle_ps_bbgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5A); }
static inline __m128i _mm_swizzle_epi32_zzyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5A); }
static inline __m128i _mm_swizzle_epi32_bbgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5A); }

static inline __m128  _mm_swizzle_ps_zzyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9A); }
static inline __m128  _mm_swizzle_ps_bbgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9A); }
static inline __m128i _mm_swizzle_epi32_zzyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9A); }
static inline __m128i _mm_swizzle_epi32_bbgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9A); }

static inline __m128  _mm_swizzle_ps_zzyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDA); }
static inline __m128  _mm_swizzle_ps_bbga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDA); }
static inline __m128i _mm_swizzle_epi32_zzyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDA); }
static inline __m128i _mm_swizzle_epi32_bbga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDA); }

static inline __m128  _mm_swizzle_ps_zzzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2A); }
static inline __m128  _mm_swizzle_ps_bbbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2A); }
static inline __m128i _mm_swizzle_epi32_zzzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2A); }
static inline __m128i _mm_swizzle_epi32_bbbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2A); }

static inline __m128  _mm_swizzle_ps_zzzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6A); }
static inline __m128  _mm_swizzle_ps_bbbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6A); }
static inline __m128i _mm_swizzle_epi32_zzzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6A); }
static inline __m128i _mm_swizzle_epi32_bbbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6A); }

static inline __m128  _mm_swizzle_ps_zzzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAA); }
static inline __m128  _mm_swizzle_ps_bbbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAA); }
static inline __m128i _mm_swizzle_epi32_zzzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAA); }
static inline __m128i _mm_swizzle_epi32_bbbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAA); }

static inline __m128  _mm_swizzle_ps_zzzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEA); }
static inline __m128  _mm_swizzle_ps_bbba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEA); }
static inline __m128i _mm_swizzle_epi32_zzzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEA); }
static inline __m128i _mm_swizzle_epi32_bbba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEA); }

static inline __m128  _mm_swizzle_ps_zzwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3A); }
static inline __m128  _mm_swizzle_ps_bbar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3A); }
static inline __m128i _mm_swizzle_epi32_zzwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3A); }
static inline __m128i _mm_swizzle_epi32_bbar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3A); }

static inline __m128  _mm_swizzle_ps_zzwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7A); }
static inline __m128  _mm_swizzle_ps_bbag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7A); }
static inline __m128i _mm_swizzle_epi32_zzwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7A); }
static inline __m128i _mm_swizzle_epi32_bbag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7A); }

static inline __m128  _mm_swizzle_ps_zzwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBA); }
static inline __m128  _mm_swizzle_ps_bbab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBA); }
static inline __m128i _mm_swizzle_epi32_zzwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBA); }
static inline __m128i _mm_swizzle_epi32_bbab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBA); }

static inline __m128  _mm_swizzle_ps_zzww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFA); }
static inline __m128  _mm_swizzle_ps_bbaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFA); }
static inline __m128i _mm_swizzle_epi32_zzww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFA); }
static inline __m128i _mm_swizzle_epi32_bbaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFA); }

static inline __m128  _mm_swizzle_ps_zwxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0E); }
static inline __m128  _mm_swizzle_ps_barr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0E); }
static inline __m128i _mm_swizzle_epi32_zwxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0E); }
static inline __m128i _mm_swizzle_epi32_barr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0E); }

static inline __m128  _mm_swizzle_ps_zwxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4E); }
static inline __m128  _mm_swizzle_ps_barg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4E); }
static inline __m128i _mm_swizzle_epi32_zwxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4E); }
static inline __m128i _mm_swizzle_epi32_barg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4E); }

static inline __m128  _mm_swizzle_ps_zwxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8E); }
static inline __m128  _mm_swizzle_ps_barb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8E); }
static inline __m128i _mm_swizzle_epi32_zwxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8E); }
static inline __m128i _mm_swizzle_epi32_barb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8E); }

static inline __m128  _mm_swizzle_ps_zwxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCE); }
static inline __m128  _mm_swizzle_ps_bara(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCE); }
static inline __m128i _mm_swizzle_epi32_zwxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCE); }
static inline __m128i _mm_swizzle_epi32_bara(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCE); }

static inline __m128  _mm_swizzle_ps_zwyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1E); }
static inline __m128  _mm_swizzle_ps_bagr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1E); }
static inline __m128i _mm_swizzle_epi32_zwyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1E); }
static inline __m128i _mm_swizzle_epi32_bagr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1E); }

static inline __m128  _mm_swizzle_ps_zwyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5E); }
static inline __m128  _mm_swizzle_ps_bagg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5E); }
static inline __m128i _mm_swizzle_epi32_zwyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5E); }
static inline __m128i _mm_swizzle_epi32_bagg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5E); }

static inline __m128  _mm_swizzle_ps_zwyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9E); }
static inline __m128  _mm_swizzle_ps_bagb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9E); }
static inline __m128i _mm_swizzle_epi32_zwyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9E); }
static inline __m128i _mm_swizzle_epi32_bagb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9E); }

static inline __m128  _mm_swizzle_ps_zwyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDE); }
static inline __m128  _mm_swizzle_ps_baga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDE); }
static inline __m128i _mm_swizzle_epi32_zwyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDE); }
static inline __m128i _mm_swizzle_epi32_baga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDE); }

static inline __m128  _mm_swizzle_ps_zwzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2E); }
static inline __m128  _mm_swizzle_ps_babr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2E); }
static inline __m128i _mm_swizzle_epi32_zwzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2E); }
static inline __m128i _mm_swizzle_epi32_babr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2E); }

static inline __m128  _mm_swizzle_ps_zwzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6E); }
static inline __m128  _mm_swizzle_ps_babg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6E); }
static inline __m128i _mm_swizzle_epi32_zwzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6E); }
static inline __m128i _mm_swizzle_epi32_babg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6E); }

static inline __m128  _mm_swizzle_ps_zwzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAE); }
static inline __m128  _mm_swizzle_ps_babb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAE); }
static inline __m128i _mm_swizzle_epi32_zwzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAE); }
static inline __m128i _mm_swizzle_epi32_babb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAE); }

static inline __m128  _mm_swizzle_ps_zwzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEE); }
static inline __m128  _mm_swizzle_ps_baba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEE); }
static inline __m128i _mm_swizzle_epi32_zwzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEE); }
static inline __m128i _mm_swizzle_epi32_baba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEE); }

static inline __m128  _mm_swizzle_ps_zwwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3E); }
static inline __m128  _mm_swizzle_ps_baar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3E); }
static inline __m128i _mm_swizzle_epi32_zwwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3E); }
static inline __m128i _mm_swizzle_epi32_baar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3E); }

static inline __m128  _mm_swizzle_ps_zwwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7E); }
static inline __m128  _mm_swizzle_ps_baag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7E); }
static inline __m128i _mm_swizzle_epi32_zwwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7E); }
static inline __m128i _mm_swizzle_epi32_baag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7E); }

static inline __m128  _mm_swizzle_ps_zwwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBE); }
static inline __m128  _mm_swizzle_ps_baab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBE); }
static inline __m128i _mm_swizzle_epi32_zwwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBE); }
static inline __m128i _mm_swizzle_epi32_baab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBE); }

static inline __m128  _mm_swizzle_ps_zwww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFE); }
static inline __m128  _mm_swizzle_ps_baaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFE); }
static inline __m128i _mm_swizzle_epi32_zwww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFE); }
static inline __m128i _mm_swizzle_epi32_baaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFE); }

static inline __m128  _mm_swizzle_ps_wxxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x03); }
static inline __m128  _mm_swizzle_ps_arrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x03); }
static inline __m128i _mm_swizzle_epi32_wxxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x03); }
static inline __m128i _mm_swizzle_epi32_arrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x03); }

static inline __m128  _mm_swizzle_ps_wxxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x43); }
static inline __m128  _mm_swizzle_ps_arrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x43); }
static inline __m128i _mm_swizzle_epi32_wxxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x43); }
static inline __m128i _mm_swizzle_epi32_arrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x43); }

static inline __m128  _mm_swizzle_ps_wxxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x83); }
static inline __m128  _mm_swizzle_ps_arrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x83); }
static inline __m128i _mm_swizzle_epi32_wxxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x83); }
static inline __m128i _mm_swizzle_epi32_arrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x83); }

static inline __m128  _mm_swizzle_ps_wxxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC3); }
static inline __m128  _mm_swizzle_ps_arra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC3); }
static inline __m128i _mm_swizzle_epi32_wxxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC3); }
static inline __m128i _mm_swizzle_epi32_arra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC3); }

static inline __m128  _mm_swizzle_ps_wxyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x13); }
static inline __m128  _mm_swizzle_ps_argr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x13); }
static inline __m128i _mm_swizzle_epi32_wxyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x13); }
static inline __m128i _mm_swizzle_epi32_argr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x13); }

static inline __m128  _mm_swizzle_ps_wxyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x53); }
static inline __m128  _mm_swizzle_ps_argg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x53); }
static inline __m128i _mm_swizzle_epi32_wxyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x53); }
static inline __m128i _mm_swizzle_epi32_argg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x53); }

static inline __m128  _mm_swizzle_ps_wxyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x93); }
static inline __m128  _mm_swizzle_ps_argb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x93); }
static inline __m128i _mm_swizzle_epi32_wxyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x93); }
static inline __m128i _mm_swizzle_epi32_argb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x93); }

static inline __m128  _mm_swizzle_ps_wxyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD3); }
static inline __m128  _mm_swizzle_ps_arga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD3); }
static inline __m128i _mm_swizzle_epi32_wxyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD3); }
static inline __m128i _mm_swizzle_epi32_arga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD3); }

static inline __m128  _mm_swizzle_ps_wxzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x23); }
static inline __m128  _mm_swizzle_ps_arbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x23); }
static inline __m128i _mm_swizzle_epi32_wxzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x23); }
static inline __m128i _mm_swizzle_epi32_arbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x23); }

static inline __m128  _mm_swizzle_ps_wxzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x63); }
static inline __m128  _mm_swizzle_ps_arbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x63); }
static inline __m128i _mm_swizzle_epi32_wxzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x63); }
static inline __m128i _mm_swizzle_epi32_arbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x63); }

static inline __m128  _mm_swizzle_ps_wxzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA3); }
static inline __m128  _mm_swizzle_ps_arbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA3); }
static inline __m128i _mm_swizzle_epi32_wxzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA3); }
static inline __m128i _mm_swizzle_epi32_arbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA3); }

static inline __m128  _mm_swizzle_ps_wxzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE3); }
static inline __m128  _mm_swizzle_ps_arba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE3); }
static inline __m128i _mm_swizzle_epi32_wxzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE3); }
static inline __m128i _mm_swizzle_epi32_arba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE3); }

static inline __m128  _mm_swizzle_ps_wxwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x33); }
static inline __m128  _mm_swizzle_ps_arar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x33); }
static inline __m128i _mm_swizzle_epi32_wxwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x33); }
static inline __m128i _mm_swizzle_epi32_arar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x33); }

static inline __m128  _mm_swizzle_ps_wxwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x73); }
static inline __m128  _mm_swizzle_ps_arag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x73); }
static inline __m128i _mm_swizzle_epi32_wxwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x73); }
static inline __m128i _mm_swizzle_epi32_arag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x73); }

static inline __m128  _mm_swizzle_ps_wxwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB3); }
static inline __m128  _mm_swizzle_ps_arab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB3); }
static inline __m128i _mm_swizzle_epi32_wxwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB3); }
static inline __m128i _mm_swizzle_epi32_arab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB3); }

static inline __m128  _mm_swizzle_ps_wxww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF3); }
static inline __m128  _mm_swizzle_ps_araa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF3); }
static inline __m128i _mm_swizzle_epi32_wxww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF3); }
static inline __m128i _mm_swizzle_epi32_araa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF3); }

static inline __m128  _mm_swizzle_ps_wyxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x07); }
static inline __m128  _mm_swizzle_ps_agrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x07); }
static inline __m128i _mm_swizzle_epi32_wyxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x07); }
static inline __m128i _mm_swizzle_epi32_agrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x07); }

static inline __m128  _mm_swizzle_ps_wyxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x47); }
static inline __m128  _mm_swizzle_ps_agrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x47); }
static inline __m128i _mm_swizzle_epi32_wyxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x47); }
static inline __m128i _mm_swizzle_epi32_agrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x47); }

static inline __m128  _mm_swizzle_ps_wyxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x87); }
static inline __m128  _mm_swizzle_ps_agrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x87); }
static inline __m128i _mm_swizzle_epi32_wyxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x87); }
static inline __m128i _mm_swizzle_epi32_agrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x87); }

static inline __m128  _mm_swizzle_ps_wyxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC7); }
static inline __m128  _mm_swizzle_ps_agra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xC7); }
static inline __m128i _mm_swizzle_epi32_wyxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC7); }
static inline __m128i _mm_swizzle_epi32_agra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xC7); }

static inline __m128  _mm_swizzle_ps_wyyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x17); }
static inline __m128  _mm_swizzle_ps_aggr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x17); }
static inline __m128i _mm_swizzle_epi32_wyyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x17); }
static inline __m128i _mm_swizzle_epi32_aggr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x17); }

static inline __m128  _mm_swizzle_ps_wyyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x57); }
static inline __m128  _mm_swizzle_ps_aggg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x57); }
static inline __m128i _mm_swizzle_epi32_wyyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x57); }
static inline __m128i _mm_swizzle_epi32_aggg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x57); }

static inline __m128  _mm_swizzle_ps_wyyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x97); }
static inline __m128  _mm_swizzle_ps_aggb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x97); }
static inline __m128i _mm_swizzle_epi32_wyyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x97); }
static inline __m128i _mm_swizzle_epi32_aggb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x97); }

static inline __m128  _mm_swizzle_ps_wyyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD7); }
static inline __m128  _mm_swizzle_ps_agga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xD7); }
static inline __m128i _mm_swizzle_epi32_wyyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD7); }
static inline __m128i _mm_swizzle_epi32_agga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xD7); }

static inline __m128  _mm_swizzle_ps_wyzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x27); }
static inline __m128  _mm_swizzle_ps_agbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x27); }
static inline __m128i _mm_swizzle_epi32_wyzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x27); }
static inline __m128i _mm_swizzle_epi32_agbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x27); }

static inline __m128  _mm_swizzle_ps_wyzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x67); }
static inline __m128  _mm_swizzle_ps_agbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x67); }
static inline __m128i _mm_swizzle_epi32_wyzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x67); }
static inline __m128i _mm_swizzle_epi32_agbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x67); }

static inline __m128  _mm_swizzle_ps_wyzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA7); }
static inline __m128  _mm_swizzle_ps_agbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xA7); }
static inline __m128i _mm_swizzle_epi32_wyzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA7); }
static inline __m128i _mm_swizzle_epi32_agbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xA7); }

static inline __m128  _mm_swizzle_ps_wyzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE7); }
static inline __m128  _mm_swizzle_ps_agba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xE7); }
static inline __m128i _mm_swizzle_epi32_wyzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE7); }
static inline __m128i _mm_swizzle_epi32_agba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xE7); }

static inline __m128  _mm_swizzle_ps_wywx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x37); }
static inline __m128  _mm_swizzle_ps_agar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x37); }
static inline __m128i _mm_swizzle_epi32_wywx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x37); }
static inline __m128i _mm_swizzle_epi32_agar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x37); }

static inline __m128  _mm_swizzle_ps_wywy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x77); }
static inline __m128  _mm_swizzle_ps_agag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x77); }
static inline __m128i _mm_swizzle_epi32_wywy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x77); }
static inline __m128i _mm_swizzle_epi32_agag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x77); }

static inline __m128  _mm_swizzle_ps_wywz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB7); }
static inline __m128  _mm_swizzle_ps_agab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xB7); }
static inline __m128i _mm_swizzle_epi32_wywz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB7); }
static inline __m128i _mm_swizzle_epi32_agab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xB7); }

static inline __m128  _mm_swizzle_ps_wyww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF7); }
static inline __m128  _mm_swizzle_ps_agaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xF7); }
static inline __m128i _mm_swizzle_epi32_wyww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF7); }
static inline __m128i _mm_swizzle_epi32_agaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xF7); }

static inline __m128  _mm_swizzle_ps_wzxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0B); }
static inline __m128  _mm_swizzle_ps_abrr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0B); }
static inline __m128i _mm_swizzle_epi32_wzxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0B); }
static inline __m128i _mm_swizzle_epi32_abrr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0B); }

static inline __m128  _mm_swizzle_ps_wzxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4B); }
static inline __m128  _mm_swizzle_ps_abrg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4B); }
static inline __m128i _mm_swizzle_epi32_wzxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4B); }
static inline __m128i _mm_swizzle_epi32_abrg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4B); }

static inline __m128  _mm_swizzle_ps_wzxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8B); }
static inline __m128  _mm_swizzle_ps_abrb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8B); }
static inline __m128i _mm_swizzle_epi32_wzxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8B); }
static inline __m128i _mm_swizzle_epi32_abrb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8B); }

static inline __m128  _mm_swizzle_ps_wzxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCB); }
static inline __m128  _mm_swizzle_ps_abra(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCB); }
static inline __m128i _mm_swizzle_epi32_wzxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCB); }
static inline __m128i _mm_swizzle_epi32_abra(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCB); }

static inline __m128  _mm_swizzle_ps_wzyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1B); }
static inline __m128  _mm_swizzle_ps_abgr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1B); }
static inline __m128i _mm_swizzle_epi32_wzyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1B); }
static inline __m128i _mm_swizzle_epi32_abgr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1B); }

static inline __m128  _mm_swizzle_ps_wzyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5B); }
static inline __m128  _mm_swizzle_ps_abgg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5B); }
static inline __m128i _mm_swizzle_epi32_wzyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5B); }
static inline __m128i _mm_swizzle_epi32_abgg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5B); }

static inline __m128  _mm_swizzle_ps_wzyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9B); }
static inline __m128  _mm_swizzle_ps_abgb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9B); }
static inline __m128i _mm_swizzle_epi32_wzyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9B); }
static inline __m128i _mm_swizzle_epi32_abgb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9B); }

static inline __m128  _mm_swizzle_ps_wzyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDB); }
static inline __m128  _mm_swizzle_ps_abga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDB); }
static inline __m128i _mm_swizzle_epi32_wzyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDB); }
static inline __m128i _mm_swizzle_epi32_abga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDB); }

static inline __m128  _mm_swizzle_ps_wzzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2B); }
static inline __m128  _mm_swizzle_ps_abbr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2B); }
static inline __m128i _mm_swizzle_epi32_wzzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2B); }
static inline __m128i _mm_swizzle_epi32_abbr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2B); }

static inline __m128  _mm_swizzle_ps_wzzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6B); }
static inline __m128  _mm_swizzle_ps_abbg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6B); }
static inline __m128i _mm_swizzle_epi32_wzzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6B); }
static inline __m128i _mm_swizzle_epi32_abbg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6B); }

static inline __m128  _mm_swizzle_ps_wzzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAB); }
static inline __m128  _mm_swizzle_ps_abbb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAB); }
static inline __m128i _mm_swizzle_epi32_wzzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAB); }
static inline __m128i _mm_swizzle_epi32_abbb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAB); }

static inline __m128  _mm_swizzle_ps_wzzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEB); }
static inline __m128  _mm_swizzle_ps_abba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEB); }
static inline __m128i _mm_swizzle_epi32_wzzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEB); }
static inline __m128i _mm_swizzle_epi32_abba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEB); }

static inline __m128  _mm_swizzle_ps_wzwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3B); }
static inline __m128  _mm_swizzle_ps_abar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3B); }
static inline __m128i _mm_swizzle_epi32_wzwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3B); }
static inline __m128i _mm_swizzle_epi32_abar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3B); }

static inline __m128  _mm_swizzle_ps_wzwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7B); }
static inline __m128  _mm_swizzle_ps_abag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7B); }
static inline __m128i _mm_swizzle_epi32_wzwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7B); }
static inline __m128i _mm_swizzle_epi32_abag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7B); }

static inline __m128  _mm_swizzle_ps_wzwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBB); }
static inline __m128  _mm_swizzle_ps_abab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBB); }
static inline __m128i _mm_swizzle_epi32_wzwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBB); }
static inline __m128i _mm_swizzle_epi32_abab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBB); }

static inline __m128  _mm_swizzle_ps_wzww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFB); }
static inline __m128  _mm_swizzle_ps_abaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFB); }
static inline __m128i _mm_swizzle_epi32_wzww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFB); }
static inline __m128i _mm_swizzle_epi32_abaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFB); }

static inline __m128  _mm_swizzle_ps_wwxx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0F); }
static inline __m128  _mm_swizzle_ps_aarr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x0F); }
static inline __m128i _mm_swizzle_epi32_wwxx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0F); }
static inline __m128i _mm_swizzle_epi32_aarr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x0F); }

static inline __m128  _mm_swizzle_ps_wwxy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4F); }
static inline __m128  _mm_swizzle_ps_aarg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x4F); }
static inline __m128i _mm_swizzle_epi32_wwxy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4F); }
static inline __m128i _mm_swizzle_epi32_aarg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x4F); }

static inline __m128  _mm_swizzle_ps_wwxz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8F); }
static inline __m128  _mm_swizzle_ps_aarb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x8F); }
static inline __m128i _mm_swizzle_epi32_wwxz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8F); }
static inline __m128i _mm_swizzle_epi32_aarb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x8F); }

static inline __m128  _mm_swizzle_ps_wwxw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCF); }
static inline __m128  _mm_swizzle_ps_aara(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xCF); }
static inline __m128i _mm_swizzle_epi32_wwxw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCF); }
static inline __m128i _mm_swizzle_epi32_aara(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xCF); }

static inline __m128  _mm_swizzle_ps_wwyx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1F); }
static inline __m128  _mm_swizzle_ps_aagr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x1F); }
static inline __m128i _mm_swizzle_epi32_wwyx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1F); }
static inline __m128i _mm_swizzle_epi32_aagr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x1F); }

static inline __m128  _mm_swizzle_ps_wwyy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5F); }
static inline __m128  _mm_swizzle_ps_aagg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x5F); }
static inline __m128i _mm_swizzle_epi32_wwyy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5F); }
static inline __m128i _mm_swizzle_epi32_aagg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x5F); }

static inline __m128  _mm_swizzle_ps_wwyz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9F); }
static inline __m128  _mm_swizzle_ps_aagb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x9F); }
static inline __m128i _mm_swizzle_epi32_wwyz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9F); }
static inline __m128i _mm_swizzle_epi32_aagb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x9F); }

static inline __m128  _mm_swizzle_ps_wwyw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDF); }
static inline __m128  _mm_swizzle_ps_aaga(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xDF); }
static inline __m128i _mm_swizzle_epi32_wwyw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDF); }
static inline __m128i _mm_swizzle_epi32_aaga(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xDF); }

static inline __m128  _mm_swizzle_ps_wwzx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2F); }
static inline __m128  _mm_swizzle_ps_aabr(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x2F); }
static inline __m128i _mm_swizzle_epi32_wwzx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2F); }
static inline __m128i _mm_swizzle_epi32_aabr(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x2F); }

static inline __m128  _mm_swizzle_ps_wwzy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6F); }
static inline __m128  _mm_swizzle_ps_aabg(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x6F); }
static inline __m128i _mm_swizzle_epi32_wwzy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6F); }
static inline __m128i _mm_swizzle_epi32_aabg(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x6F); }

static inline __m128  _mm_swizzle_ps_wwzz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAF); }
static inline __m128  _mm_swizzle_ps_aabb(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xAF); }
static inline __m128i _mm_swizzle_epi32_wwzz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAF); }
static inline __m128i _mm_swizzle_epi32_aabb(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xAF); }

static inline __m128  _mm_swizzle_ps_wwzw(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEF); }
static inline __m128  _mm_swizzle_ps_aaba(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xEF); }
static inline __m128i _mm_swizzle_epi32_wwzw(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEF); }
static inline __m128i _mm_swizzle_epi32_aaba(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xEF); }

static inline __m128  _mm_swizzle_ps_wwwx(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3F); }
static inline __m128  _mm_swizzle_ps_aaar(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x3F); }
static inline __m128i _mm_swizzle_epi32_wwwx(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3F); }
static inline __m128i _mm_swizzle_epi32_aaar(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x3F); }

static inline __m128  _mm_swizzle_ps_wwwy(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7F); }
static inline __m128  _mm_swizzle_ps_aaag(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0x7F); }
static inline __m128i _mm_swizzle_epi32_wwwy(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7F); }
static inline __m128i _mm_swizzle_epi32_aaag(__m128i reg)  {  return _mm_shuffle_epi32(reg,0x7F); }

static inline __m128  _mm_swizzle_ps_wwwz(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBF); }
static inline __m128  _mm_swizzle_ps_aaab(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xBF); }
static inline __m128i _mm_swizzle_epi32_wwwz(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBF); }
static inline __m128i _mm_swizzle_epi32_aaab(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xBF); }

static inline __m128  _mm_swizzle_ps_wwww(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFF); }
static inline __m128  _mm_swizzle_ps_aaaa(__m128 reg)      {  return (__m128)_mm_shuffle_epi32((__m128i)reg,0xFF); }
static inline __m128i _mm_swizzle_epi32_wwww(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFF); }
static inline __m128i _mm_swizzle_epi32_aaaa(__m128i reg)  {  return _mm_shuffle_epi32(reg,0xFF); }

#ifdef TEST_SSE_SWIZZLE
#include <stdio.h>

static int check_vector(const char* name,__m128 vec, float* correct) {
    float dst[4] __attribute__ ((aligned (16)));
    _mm_store_ps(dst,vec);
    int allcorrect = dst[0] == correct[0] && dst[1] == correct[1] && dst[2] == correct[2] && dst[3] == correct[3];
    if (allcorrect) {
        //printf("%s: Passed\n",name);
    } else {
        printf("%s: FAILED (expected %f,%f,%f,%f, got %f,%f,%f%f)\n",name,correct[0],correct[1],correct[2],correct[3],dst[0],dst[1],dst[2],dst[3]);
    }
    return allcorrect;
}

int main(int argc, char** argv) {
    float base[4] __attribute__ ((aligned (16))) = {0.f,1.f,2.f,3.f};
    __m128 src, dst;
    src = _mm_load_ps(base);
    int allcorrect = 1;

    float expected_xxxx[] = {0.000000f,0.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_xxxx(src);
    int correct_xxxx = check_vector("xxxx",dst,expected_xxxx);
    allcorrect = allcorrect && correct_xxxx;

    float expected_xxxy[] = {0.000000f,0.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_xxxy(src);
    int correct_xxxy = check_vector("xxxy",dst,expected_xxxy);
    allcorrect = allcorrect && correct_xxxy;

    float expected_xxxz[] = {0.000000f,0.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_xxxz(src);
    int correct_xxxz = check_vector("xxxz",dst,expected_xxxz);
    allcorrect = allcorrect && correct_xxxz;

    float expected_xxxw[] = {0.000000f,0.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_xxxw(src);
    int correct_xxxw = check_vector("xxxw",dst,expected_xxxw);
    allcorrect = allcorrect && correct_xxxw;

    float expected_xxyx[] = {0.000000f,0.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_xxyx(src);
    int correct_xxyx = check_vector("xxyx",dst,expected_xxyx);
    allcorrect = allcorrect && correct_xxyx;

    float expected_xxyy[] = {0.000000f,0.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_xxyy(src);
    int correct_xxyy = check_vector("xxyy",dst,expected_xxyy);
    allcorrect = allcorrect && correct_xxyy;

    float expected_xxyz[] = {0.000000f,0.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_xxyz(src);
    int correct_xxyz = check_vector("xxyz",dst,expected_xxyz);
    allcorrect = allcorrect && correct_xxyz;

    float expected_xxyw[] = {0.000000f,0.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_xxyw(src);
    int correct_xxyw = check_vector("xxyw",dst,expected_xxyw);
    allcorrect = allcorrect && correct_xxyw;

    float expected_xxzx[] = {0.000000f,0.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_xxzx(src);
    int correct_xxzx = check_vector("xxzx",dst,expected_xxzx);
    allcorrect = allcorrect && correct_xxzx;

    float expected_xxzy[] = {0.000000f,0.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_xxzy(src);
    int correct_xxzy = check_vector("xxzy",dst,expected_xxzy);
    allcorrect = allcorrect && correct_xxzy;

    float expected_xxzz[] = {0.000000f,0.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_xxzz(src);
    int correct_xxzz = check_vector("xxzz",dst,expected_xxzz);
    allcorrect = allcorrect && correct_xxzz;

    float expected_xxzw[] = {0.000000f,0.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_xxzw(src);
    int correct_xxzw = check_vector("xxzw",dst,expected_xxzw);
    allcorrect = allcorrect && correct_xxzw;

    float expected_xxwx[] = {0.000000f,0.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_xxwx(src);
    int correct_xxwx = check_vector("xxwx",dst,expected_xxwx);
    allcorrect = allcorrect && correct_xxwx;

    float expected_xxwy[] = {0.000000f,0.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_xxwy(src);
    int correct_xxwy = check_vector("xxwy",dst,expected_xxwy);
    allcorrect = allcorrect && correct_xxwy;

    float expected_xxwz[] = {0.000000f,0.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_xxwz(src);
    int correct_xxwz = check_vector("xxwz",dst,expected_xxwz);
    allcorrect = allcorrect && correct_xxwz;

    float expected_xxww[] = {0.000000f,0.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_xxww(src);
    int correct_xxww = check_vector("xxww",dst,expected_xxww);
    allcorrect = allcorrect && correct_xxww;

    float expected_xyxx[] = {0.000000f,1.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_xyxx(src);
    int correct_xyxx = check_vector("xyxx",dst,expected_xyxx);
    allcorrect = allcorrect && correct_xyxx;

    float expected_xyxy[] = {0.000000f,1.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_xyxy(src);
    int correct_xyxy = check_vector("xyxy",dst,expected_xyxy);
    allcorrect = allcorrect && correct_xyxy;

    float expected_xyxz[] = {0.000000f,1.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_xyxz(src);
    int correct_xyxz = check_vector("xyxz",dst,expected_xyxz);
    allcorrect = allcorrect && correct_xyxz;

    float expected_xyxw[] = {0.000000f,1.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_xyxw(src);
    int correct_xyxw = check_vector("xyxw",dst,expected_xyxw);
    allcorrect = allcorrect && correct_xyxw;

    float expected_xyyx[] = {0.000000f,1.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_xyyx(src);
    int correct_xyyx = check_vector("xyyx",dst,expected_xyyx);
    allcorrect = allcorrect && correct_xyyx;

    float expected_xyyy[] = {0.000000f,1.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_xyyy(src);
    int correct_xyyy = check_vector("xyyy",dst,expected_xyyy);
    allcorrect = allcorrect && correct_xyyy;

    float expected_xyyz[] = {0.000000f,1.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_xyyz(src);
    int correct_xyyz = check_vector("xyyz",dst,expected_xyyz);
    allcorrect = allcorrect && correct_xyyz;

    float expected_xyyw[] = {0.000000f,1.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_xyyw(src);
    int correct_xyyw = check_vector("xyyw",dst,expected_xyyw);
    allcorrect = allcorrect && correct_xyyw;

    float expected_xyzx[] = {0.000000f,1.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_xyzx(src);
    int correct_xyzx = check_vector("xyzx",dst,expected_xyzx);
    allcorrect = allcorrect && correct_xyzx;

    float expected_xyzy[] = {0.000000f,1.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_xyzy(src);
    int correct_xyzy = check_vector("xyzy",dst,expected_xyzy);
    allcorrect = allcorrect && correct_xyzy;

    float expected_xyzz[] = {0.000000f,1.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_xyzz(src);
    int correct_xyzz = check_vector("xyzz",dst,expected_xyzz);
    allcorrect = allcorrect && correct_xyzz;

    float expected_xyzw[] = {0.000000f,1.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_xyzw(src);
    int correct_xyzw = check_vector("xyzw",dst,expected_xyzw);
    allcorrect = allcorrect && correct_xyzw;

    float expected_xywx[] = {0.000000f,1.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_xywx(src);
    int correct_xywx = check_vector("xywx",dst,expected_xywx);
    allcorrect = allcorrect && correct_xywx;

    float expected_xywy[] = {0.000000f,1.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_xywy(src);
    int correct_xywy = check_vector("xywy",dst,expected_xywy);
    allcorrect = allcorrect && correct_xywy;

    float expected_xywz[] = {0.000000f,1.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_xywz(src);
    int correct_xywz = check_vector("xywz",dst,expected_xywz);
    allcorrect = allcorrect && correct_xywz;

    float expected_xyww[] = {0.000000f,1.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_xyww(src);
    int correct_xyww = check_vector("xyww",dst,expected_xyww);
    allcorrect = allcorrect && correct_xyww;

    float expected_xzxx[] = {0.000000f,2.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_xzxx(src);
    int correct_xzxx = check_vector("xzxx",dst,expected_xzxx);
    allcorrect = allcorrect && correct_xzxx;

    float expected_xzxy[] = {0.000000f,2.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_xzxy(src);
    int correct_xzxy = check_vector("xzxy",dst,expected_xzxy);
    allcorrect = allcorrect && correct_xzxy;

    float expected_xzxz[] = {0.000000f,2.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_xzxz(src);
    int correct_xzxz = check_vector("xzxz",dst,expected_xzxz);
    allcorrect = allcorrect && correct_xzxz;

    float expected_xzxw[] = {0.000000f,2.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_xzxw(src);
    int correct_xzxw = check_vector("xzxw",dst,expected_xzxw);
    allcorrect = allcorrect && correct_xzxw;

    float expected_xzyx[] = {0.000000f,2.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_xzyx(src);
    int correct_xzyx = check_vector("xzyx",dst,expected_xzyx);
    allcorrect = allcorrect && correct_xzyx;

    float expected_xzyy[] = {0.000000f,2.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_xzyy(src);
    int correct_xzyy = check_vector("xzyy",dst,expected_xzyy);
    allcorrect = allcorrect && correct_xzyy;

    float expected_xzyz[] = {0.000000f,2.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_xzyz(src);
    int correct_xzyz = check_vector("xzyz",dst,expected_xzyz);
    allcorrect = allcorrect && correct_xzyz;

    float expected_xzyw[] = {0.000000f,2.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_xzyw(src);
    int correct_xzyw = check_vector("xzyw",dst,expected_xzyw);
    allcorrect = allcorrect && correct_xzyw;

    float expected_xzzx[] = {0.000000f,2.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_xzzx(src);
    int correct_xzzx = check_vector("xzzx",dst,expected_xzzx);
    allcorrect = allcorrect && correct_xzzx;

    float expected_xzzy[] = {0.000000f,2.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_xzzy(src);
    int correct_xzzy = check_vector("xzzy",dst,expected_xzzy);
    allcorrect = allcorrect && correct_xzzy;

    float expected_xzzz[] = {0.000000f,2.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_xzzz(src);
    int correct_xzzz = check_vector("xzzz",dst,expected_xzzz);
    allcorrect = allcorrect && correct_xzzz;

    float expected_xzzw[] = {0.000000f,2.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_xzzw(src);
    int correct_xzzw = check_vector("xzzw",dst,expected_xzzw);
    allcorrect = allcorrect && correct_xzzw;

    float expected_xzwx[] = {0.000000f,2.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_xzwx(src);
    int correct_xzwx = check_vector("xzwx",dst,expected_xzwx);
    allcorrect = allcorrect && correct_xzwx;

    float expected_xzwy[] = {0.000000f,2.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_xzwy(src);
    int correct_xzwy = check_vector("xzwy",dst,expected_xzwy);
    allcorrect = allcorrect && correct_xzwy;

    float expected_xzwz[] = {0.000000f,2.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_xzwz(src);
    int correct_xzwz = check_vector("xzwz",dst,expected_xzwz);
    allcorrect = allcorrect && correct_xzwz;

    float expected_xzww[] = {0.000000f,2.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_xzww(src);
    int correct_xzww = check_vector("xzww",dst,expected_xzww);
    allcorrect = allcorrect && correct_xzww;

    float expected_xwxx[] = {0.000000f,3.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_xwxx(src);
    int correct_xwxx = check_vector("xwxx",dst,expected_xwxx);
    allcorrect = allcorrect && correct_xwxx;

    float expected_xwxy[] = {0.000000f,3.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_xwxy(src);
    int correct_xwxy = check_vector("xwxy",dst,expected_xwxy);
    allcorrect = allcorrect && correct_xwxy;

    float expected_xwxz[] = {0.000000f,3.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_xwxz(src);
    int correct_xwxz = check_vector("xwxz",dst,expected_xwxz);
    allcorrect = allcorrect && correct_xwxz;

    float expected_xwxw[] = {0.000000f,3.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_xwxw(src);
    int correct_xwxw = check_vector("xwxw",dst,expected_xwxw);
    allcorrect = allcorrect && correct_xwxw;

    float expected_xwyx[] = {0.000000f,3.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_xwyx(src);
    int correct_xwyx = check_vector("xwyx",dst,expected_xwyx);
    allcorrect = allcorrect && correct_xwyx;

    float expected_xwyy[] = {0.000000f,3.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_xwyy(src);
    int correct_xwyy = check_vector("xwyy",dst,expected_xwyy);
    allcorrect = allcorrect && correct_xwyy;

    float expected_xwyz[] = {0.000000f,3.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_xwyz(src);
    int correct_xwyz = check_vector("xwyz",dst,expected_xwyz);
    allcorrect = allcorrect && correct_xwyz;

    float expected_xwyw[] = {0.000000f,3.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_xwyw(src);
    int correct_xwyw = check_vector("xwyw",dst,expected_xwyw);
    allcorrect = allcorrect && correct_xwyw;

    float expected_xwzx[] = {0.000000f,3.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_xwzx(src);
    int correct_xwzx = check_vector("xwzx",dst,expected_xwzx);
    allcorrect = allcorrect && correct_xwzx;

    float expected_xwzy[] = {0.000000f,3.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_xwzy(src);
    int correct_xwzy = check_vector("xwzy",dst,expected_xwzy);
    allcorrect = allcorrect && correct_xwzy;

    float expected_xwzz[] = {0.000000f,3.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_xwzz(src);
    int correct_xwzz = check_vector("xwzz",dst,expected_xwzz);
    allcorrect = allcorrect && correct_xwzz;

    float expected_xwzw[] = {0.000000f,3.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_xwzw(src);
    int correct_xwzw = check_vector("xwzw",dst,expected_xwzw);
    allcorrect = allcorrect && correct_xwzw;

    float expected_xwwx[] = {0.000000f,3.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_xwwx(src);
    int correct_xwwx = check_vector("xwwx",dst,expected_xwwx);
    allcorrect = allcorrect && correct_xwwx;

    float expected_xwwy[] = {0.000000f,3.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_xwwy(src);
    int correct_xwwy = check_vector("xwwy",dst,expected_xwwy);
    allcorrect = allcorrect && correct_xwwy;

    float expected_xwwz[] = {0.000000f,3.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_xwwz(src);
    int correct_xwwz = check_vector("xwwz",dst,expected_xwwz);
    allcorrect = allcorrect && correct_xwwz;

    float expected_xwww[] = {0.000000f,3.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_xwww(src);
    int correct_xwww = check_vector("xwww",dst,expected_xwww);
    allcorrect = allcorrect && correct_xwww;

    float expected_yxxx[] = {1.000000f,0.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_yxxx(src);
    int correct_yxxx = check_vector("yxxx",dst,expected_yxxx);
    allcorrect = allcorrect && correct_yxxx;

    float expected_yxxy[] = {1.000000f,0.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_yxxy(src);
    int correct_yxxy = check_vector("yxxy",dst,expected_yxxy);
    allcorrect = allcorrect && correct_yxxy;

    float expected_yxxz[] = {1.000000f,0.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_yxxz(src);
    int correct_yxxz = check_vector("yxxz",dst,expected_yxxz);
    allcorrect = allcorrect && correct_yxxz;

    float expected_yxxw[] = {1.000000f,0.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_yxxw(src);
    int correct_yxxw = check_vector("yxxw",dst,expected_yxxw);
    allcorrect = allcorrect && correct_yxxw;

    float expected_yxyx[] = {1.000000f,0.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_yxyx(src);
    int correct_yxyx = check_vector("yxyx",dst,expected_yxyx);
    allcorrect = allcorrect && correct_yxyx;

    float expected_yxyy[] = {1.000000f,0.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_yxyy(src);
    int correct_yxyy = check_vector("yxyy",dst,expected_yxyy);
    allcorrect = allcorrect && correct_yxyy;

    float expected_yxyz[] = {1.000000f,0.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_yxyz(src);
    int correct_yxyz = check_vector("yxyz",dst,expected_yxyz);
    allcorrect = allcorrect && correct_yxyz;

    float expected_yxyw[] = {1.000000f,0.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_yxyw(src);
    int correct_yxyw = check_vector("yxyw",dst,expected_yxyw);
    allcorrect = allcorrect && correct_yxyw;

    float expected_yxzx[] = {1.000000f,0.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_yxzx(src);
    int correct_yxzx = check_vector("yxzx",dst,expected_yxzx);
    allcorrect = allcorrect && correct_yxzx;

    float expected_yxzy[] = {1.000000f,0.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_yxzy(src);
    int correct_yxzy = check_vector("yxzy",dst,expected_yxzy);
    allcorrect = allcorrect && correct_yxzy;

    float expected_yxzz[] = {1.000000f,0.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_yxzz(src);
    int correct_yxzz = check_vector("yxzz",dst,expected_yxzz);
    allcorrect = allcorrect && correct_yxzz;

    float expected_yxzw[] = {1.000000f,0.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_yxzw(src);
    int correct_yxzw = check_vector("yxzw",dst,expected_yxzw);
    allcorrect = allcorrect && correct_yxzw;

    float expected_yxwx[] = {1.000000f,0.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_yxwx(src);
    int correct_yxwx = check_vector("yxwx",dst,expected_yxwx);
    allcorrect = allcorrect && correct_yxwx;

    float expected_yxwy[] = {1.000000f,0.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_yxwy(src);
    int correct_yxwy = check_vector("yxwy",dst,expected_yxwy);
    allcorrect = allcorrect && correct_yxwy;

    float expected_yxwz[] = {1.000000f,0.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_yxwz(src);
    int correct_yxwz = check_vector("yxwz",dst,expected_yxwz);
    allcorrect = allcorrect && correct_yxwz;

    float expected_yxww[] = {1.000000f,0.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_yxww(src);
    int correct_yxww = check_vector("yxww",dst,expected_yxww);
    allcorrect = allcorrect && correct_yxww;

    float expected_yyxx[] = {1.000000f,1.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_yyxx(src);
    int correct_yyxx = check_vector("yyxx",dst,expected_yyxx);
    allcorrect = allcorrect && correct_yyxx;

    float expected_yyxy[] = {1.000000f,1.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_yyxy(src);
    int correct_yyxy = check_vector("yyxy",dst,expected_yyxy);
    allcorrect = allcorrect && correct_yyxy;

    float expected_yyxz[] = {1.000000f,1.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_yyxz(src);
    int correct_yyxz = check_vector("yyxz",dst,expected_yyxz);
    allcorrect = allcorrect && correct_yyxz;

    float expected_yyxw[] = {1.000000f,1.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_yyxw(src);
    int correct_yyxw = check_vector("yyxw",dst,expected_yyxw);
    allcorrect = allcorrect && correct_yyxw;

    float expected_yyyx[] = {1.000000f,1.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_yyyx(src);
    int correct_yyyx = check_vector("yyyx",dst,expected_yyyx);
    allcorrect = allcorrect && correct_yyyx;

    float expected_yyyy[] = {1.000000f,1.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_yyyy(src);
    int correct_yyyy = check_vector("yyyy",dst,expected_yyyy);
    allcorrect = allcorrect && correct_yyyy;

    float expected_yyyz[] = {1.000000f,1.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_yyyz(src);
    int correct_yyyz = check_vector("yyyz",dst,expected_yyyz);
    allcorrect = allcorrect && correct_yyyz;

    float expected_yyyw[] = {1.000000f,1.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_yyyw(src);
    int correct_yyyw = check_vector("yyyw",dst,expected_yyyw);
    allcorrect = allcorrect && correct_yyyw;

    float expected_yyzx[] = {1.000000f,1.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_yyzx(src);
    int correct_yyzx = check_vector("yyzx",dst,expected_yyzx);
    allcorrect = allcorrect && correct_yyzx;

    float expected_yyzy[] = {1.000000f,1.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_yyzy(src);
    int correct_yyzy = check_vector("yyzy",dst,expected_yyzy);
    allcorrect = allcorrect && correct_yyzy;

    float expected_yyzz[] = {1.000000f,1.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_yyzz(src);
    int correct_yyzz = check_vector("yyzz",dst,expected_yyzz);
    allcorrect = allcorrect && correct_yyzz;

    float expected_yyzw[] = {1.000000f,1.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_yyzw(src);
    int correct_yyzw = check_vector("yyzw",dst,expected_yyzw);
    allcorrect = allcorrect && correct_yyzw;

    float expected_yywx[] = {1.000000f,1.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_yywx(src);
    int correct_yywx = check_vector("yywx",dst,expected_yywx);
    allcorrect = allcorrect && correct_yywx;

    float expected_yywy[] = {1.000000f,1.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_yywy(src);
    int correct_yywy = check_vector("yywy",dst,expected_yywy);
    allcorrect = allcorrect && correct_yywy;

    float expected_yywz[] = {1.000000f,1.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_yywz(src);
    int correct_yywz = check_vector("yywz",dst,expected_yywz);
    allcorrect = allcorrect && correct_yywz;

    float expected_yyww[] = {1.000000f,1.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_yyww(src);
    int correct_yyww = check_vector("yyww",dst,expected_yyww);
    allcorrect = allcorrect && correct_yyww;

    float expected_yzxx[] = {1.000000f,2.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_yzxx(src);
    int correct_yzxx = check_vector("yzxx",dst,expected_yzxx);
    allcorrect = allcorrect && correct_yzxx;

    float expected_yzxy[] = {1.000000f,2.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_yzxy(src);
    int correct_yzxy = check_vector("yzxy",dst,expected_yzxy);
    allcorrect = allcorrect && correct_yzxy;

    float expected_yzxz[] = {1.000000f,2.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_yzxz(src);
    int correct_yzxz = check_vector("yzxz",dst,expected_yzxz);
    allcorrect = allcorrect && correct_yzxz;

    float expected_yzxw[] = {1.000000f,2.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_yzxw(src);
    int correct_yzxw = check_vector("yzxw",dst,expected_yzxw);
    allcorrect = allcorrect && correct_yzxw;

    float expected_yzyx[] = {1.000000f,2.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_yzyx(src);
    int correct_yzyx = check_vector("yzyx",dst,expected_yzyx);
    allcorrect = allcorrect && correct_yzyx;

    float expected_yzyy[] = {1.000000f,2.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_yzyy(src);
    int correct_yzyy = check_vector("yzyy",dst,expected_yzyy);
    allcorrect = allcorrect && correct_yzyy;

    float expected_yzyz[] = {1.000000f,2.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_yzyz(src);
    int correct_yzyz = check_vector("yzyz",dst,expected_yzyz);
    allcorrect = allcorrect && correct_yzyz;

    float expected_yzyw[] = {1.000000f,2.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_yzyw(src);
    int correct_yzyw = check_vector("yzyw",dst,expected_yzyw);
    allcorrect = allcorrect && correct_yzyw;

    float expected_yzzx[] = {1.000000f,2.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_yzzx(src);
    int correct_yzzx = check_vector("yzzx",dst,expected_yzzx);
    allcorrect = allcorrect && correct_yzzx;

    float expected_yzzy[] = {1.000000f,2.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_yzzy(src);
    int correct_yzzy = check_vector("yzzy",dst,expected_yzzy);
    allcorrect = allcorrect && correct_yzzy;

    float expected_yzzz[] = {1.000000f,2.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_yzzz(src);
    int correct_yzzz = check_vector("yzzz",dst,expected_yzzz);
    allcorrect = allcorrect && correct_yzzz;

    float expected_yzzw[] = {1.000000f,2.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_yzzw(src);
    int correct_yzzw = check_vector("yzzw",dst,expected_yzzw);
    allcorrect = allcorrect && correct_yzzw;

    float expected_yzwx[] = {1.000000f,2.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_yzwx(src);
    int correct_yzwx = check_vector("yzwx",dst,expected_yzwx);
    allcorrect = allcorrect && correct_yzwx;

    float expected_yzwy[] = {1.000000f,2.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_yzwy(src);
    int correct_yzwy = check_vector("yzwy",dst,expected_yzwy);
    allcorrect = allcorrect && correct_yzwy;

    float expected_yzwz[] = {1.000000f,2.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_yzwz(src);
    int correct_yzwz = check_vector("yzwz",dst,expected_yzwz);
    allcorrect = allcorrect && correct_yzwz;

    float expected_yzww[] = {1.000000f,2.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_yzww(src);
    int correct_yzww = check_vector("yzww",dst,expected_yzww);
    allcorrect = allcorrect && correct_yzww;

    float expected_ywxx[] = {1.000000f,3.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_ywxx(src);
    int correct_ywxx = check_vector("ywxx",dst,expected_ywxx);
    allcorrect = allcorrect && correct_ywxx;

    float expected_ywxy[] = {1.000000f,3.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_ywxy(src);
    int correct_ywxy = check_vector("ywxy",dst,expected_ywxy);
    allcorrect = allcorrect && correct_ywxy;

    float expected_ywxz[] = {1.000000f,3.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_ywxz(src);
    int correct_ywxz = check_vector("ywxz",dst,expected_ywxz);
    allcorrect = allcorrect && correct_ywxz;

    float expected_ywxw[] = {1.000000f,3.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_ywxw(src);
    int correct_ywxw = check_vector("ywxw",dst,expected_ywxw);
    allcorrect = allcorrect && correct_ywxw;

    float expected_ywyx[] = {1.000000f,3.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_ywyx(src);
    int correct_ywyx = check_vector("ywyx",dst,expected_ywyx);
    allcorrect = allcorrect && correct_ywyx;

    float expected_ywyy[] = {1.000000f,3.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_ywyy(src);
    int correct_ywyy = check_vector("ywyy",dst,expected_ywyy);
    allcorrect = allcorrect && correct_ywyy;

    float expected_ywyz[] = {1.000000f,3.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_ywyz(src);
    int correct_ywyz = check_vector("ywyz",dst,expected_ywyz);
    allcorrect = allcorrect && correct_ywyz;

    float expected_ywyw[] = {1.000000f,3.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_ywyw(src);
    int correct_ywyw = check_vector("ywyw",dst,expected_ywyw);
    allcorrect = allcorrect && correct_ywyw;

    float expected_ywzx[] = {1.000000f,3.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_ywzx(src);
    int correct_ywzx = check_vector("ywzx",dst,expected_ywzx);
    allcorrect = allcorrect && correct_ywzx;

    float expected_ywzy[] = {1.000000f,3.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_ywzy(src);
    int correct_ywzy = check_vector("ywzy",dst,expected_ywzy);
    allcorrect = allcorrect && correct_ywzy;

    float expected_ywzz[] = {1.000000f,3.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_ywzz(src);
    int correct_ywzz = check_vector("ywzz",dst,expected_ywzz);
    allcorrect = allcorrect && correct_ywzz;

    float expected_ywzw[] = {1.000000f,3.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_ywzw(src);
    int correct_ywzw = check_vector("ywzw",dst,expected_ywzw);
    allcorrect = allcorrect && correct_ywzw;

    float expected_ywwx[] = {1.000000f,3.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_ywwx(src);
    int correct_ywwx = check_vector("ywwx",dst,expected_ywwx);
    allcorrect = allcorrect && correct_ywwx;

    float expected_ywwy[] = {1.000000f,3.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_ywwy(src);
    int correct_ywwy = check_vector("ywwy",dst,expected_ywwy);
    allcorrect = allcorrect && correct_ywwy;

    float expected_ywwz[] = {1.000000f,3.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_ywwz(src);
    int correct_ywwz = check_vector("ywwz",dst,expected_ywwz);
    allcorrect = allcorrect && correct_ywwz;

    float expected_ywww[] = {1.000000f,3.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_ywww(src);
    int correct_ywww = check_vector("ywww",dst,expected_ywww);
    allcorrect = allcorrect && correct_ywww;

    float expected_zxxx[] = {2.000000f,0.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_zxxx(src);
    int correct_zxxx = check_vector("zxxx",dst,expected_zxxx);
    allcorrect = allcorrect && correct_zxxx;

    float expected_zxxy[] = {2.000000f,0.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_zxxy(src);
    int correct_zxxy = check_vector("zxxy",dst,expected_zxxy);
    allcorrect = allcorrect && correct_zxxy;

    float expected_zxxz[] = {2.000000f,0.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_zxxz(src);
    int correct_zxxz = check_vector("zxxz",dst,expected_zxxz);
    allcorrect = allcorrect && correct_zxxz;

    float expected_zxxw[] = {2.000000f,0.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_zxxw(src);
    int correct_zxxw = check_vector("zxxw",dst,expected_zxxw);
    allcorrect = allcorrect && correct_zxxw;

    float expected_zxyx[] = {2.000000f,0.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_zxyx(src);
    int correct_zxyx = check_vector("zxyx",dst,expected_zxyx);
    allcorrect = allcorrect && correct_zxyx;

    float expected_zxyy[] = {2.000000f,0.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_zxyy(src);
    int correct_zxyy = check_vector("zxyy",dst,expected_zxyy);
    allcorrect = allcorrect && correct_zxyy;

    float expected_zxyz[] = {2.000000f,0.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_zxyz(src);
    int correct_zxyz = check_vector("zxyz",dst,expected_zxyz);
    allcorrect = allcorrect && correct_zxyz;

    float expected_zxyw[] = {2.000000f,0.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_zxyw(src);
    int correct_zxyw = check_vector("zxyw",dst,expected_zxyw);
    allcorrect = allcorrect && correct_zxyw;

    float expected_zxzx[] = {2.000000f,0.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_zxzx(src);
    int correct_zxzx = check_vector("zxzx",dst,expected_zxzx);
    allcorrect = allcorrect && correct_zxzx;

    float expected_zxzy[] = {2.000000f,0.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_zxzy(src);
    int correct_zxzy = check_vector("zxzy",dst,expected_zxzy);
    allcorrect = allcorrect && correct_zxzy;

    float expected_zxzz[] = {2.000000f,0.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_zxzz(src);
    int correct_zxzz = check_vector("zxzz",dst,expected_zxzz);
    allcorrect = allcorrect && correct_zxzz;

    float expected_zxzw[] = {2.000000f,0.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_zxzw(src);
    int correct_zxzw = check_vector("zxzw",dst,expected_zxzw);
    allcorrect = allcorrect && correct_zxzw;

    float expected_zxwx[] = {2.000000f,0.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_zxwx(src);
    int correct_zxwx = check_vector("zxwx",dst,expected_zxwx);
    allcorrect = allcorrect && correct_zxwx;

    float expected_zxwy[] = {2.000000f,0.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_zxwy(src);
    int correct_zxwy = check_vector("zxwy",dst,expected_zxwy);
    allcorrect = allcorrect && correct_zxwy;

    float expected_zxwz[] = {2.000000f,0.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_zxwz(src);
    int correct_zxwz = check_vector("zxwz",dst,expected_zxwz);
    allcorrect = allcorrect && correct_zxwz;

    float expected_zxww[] = {2.000000f,0.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_zxww(src);
    int correct_zxww = check_vector("zxww",dst,expected_zxww);
    allcorrect = allcorrect && correct_zxww;

    float expected_zyxx[] = {2.000000f,1.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_zyxx(src);
    int correct_zyxx = check_vector("zyxx",dst,expected_zyxx);
    allcorrect = allcorrect && correct_zyxx;

    float expected_zyxy[] = {2.000000f,1.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_zyxy(src);
    int correct_zyxy = check_vector("zyxy",dst,expected_zyxy);
    allcorrect = allcorrect && correct_zyxy;

    float expected_zyxz[] = {2.000000f,1.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_zyxz(src);
    int correct_zyxz = check_vector("zyxz",dst,expected_zyxz);
    allcorrect = allcorrect && correct_zyxz;

    float expected_zyxw[] = {2.000000f,1.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_zyxw(src);
    int correct_zyxw = check_vector("zyxw",dst,expected_zyxw);
    allcorrect = allcorrect && correct_zyxw;

    float expected_zyyx[] = {2.000000f,1.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_zyyx(src);
    int correct_zyyx = check_vector("zyyx",dst,expected_zyyx);
    allcorrect = allcorrect && correct_zyyx;

    float expected_zyyy[] = {2.000000f,1.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_zyyy(src);
    int correct_zyyy = check_vector("zyyy",dst,expected_zyyy);
    allcorrect = allcorrect && correct_zyyy;

    float expected_zyyz[] = {2.000000f,1.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_zyyz(src);
    int correct_zyyz = check_vector("zyyz",dst,expected_zyyz);
    allcorrect = allcorrect && correct_zyyz;

    float expected_zyyw[] = {2.000000f,1.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_zyyw(src);
    int correct_zyyw = check_vector("zyyw",dst,expected_zyyw);
    allcorrect = allcorrect && correct_zyyw;

    float expected_zyzx[] = {2.000000f,1.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_zyzx(src);
    int correct_zyzx = check_vector("zyzx",dst,expected_zyzx);
    allcorrect = allcorrect && correct_zyzx;

    float expected_zyzy[] = {2.000000f,1.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_zyzy(src);
    int correct_zyzy = check_vector("zyzy",dst,expected_zyzy);
    allcorrect = allcorrect && correct_zyzy;

    float expected_zyzz[] = {2.000000f,1.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_zyzz(src);
    int correct_zyzz = check_vector("zyzz",dst,expected_zyzz);
    allcorrect = allcorrect && correct_zyzz;

    float expected_zyzw[] = {2.000000f,1.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_zyzw(src);
    int correct_zyzw = check_vector("zyzw",dst,expected_zyzw);
    allcorrect = allcorrect && correct_zyzw;

    float expected_zywx[] = {2.000000f,1.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_zywx(src);
    int correct_zywx = check_vector("zywx",dst,expected_zywx);
    allcorrect = allcorrect && correct_zywx;

    float expected_zywy[] = {2.000000f,1.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_zywy(src);
    int correct_zywy = check_vector("zywy",dst,expected_zywy);
    allcorrect = allcorrect && correct_zywy;

    float expected_zywz[] = {2.000000f,1.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_zywz(src);
    int correct_zywz = check_vector("zywz",dst,expected_zywz);
    allcorrect = allcorrect && correct_zywz;

    float expected_zyww[] = {2.000000f,1.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_zyww(src);
    int correct_zyww = check_vector("zyww",dst,expected_zyww);
    allcorrect = allcorrect && correct_zyww;

    float expected_zzxx[] = {2.000000f,2.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_zzxx(src);
    int correct_zzxx = check_vector("zzxx",dst,expected_zzxx);
    allcorrect = allcorrect && correct_zzxx;

    float expected_zzxy[] = {2.000000f,2.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_zzxy(src);
    int correct_zzxy = check_vector("zzxy",dst,expected_zzxy);
    allcorrect = allcorrect && correct_zzxy;

    float expected_zzxz[] = {2.000000f,2.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_zzxz(src);
    int correct_zzxz = check_vector("zzxz",dst,expected_zzxz);
    allcorrect = allcorrect && correct_zzxz;

    float expected_zzxw[] = {2.000000f,2.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_zzxw(src);
    int correct_zzxw = check_vector("zzxw",dst,expected_zzxw);
    allcorrect = allcorrect && correct_zzxw;

    float expected_zzyx[] = {2.000000f,2.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_zzyx(src);
    int correct_zzyx = check_vector("zzyx",dst,expected_zzyx);
    allcorrect = allcorrect && correct_zzyx;

    float expected_zzyy[] = {2.000000f,2.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_zzyy(src);
    int correct_zzyy = check_vector("zzyy",dst,expected_zzyy);
    allcorrect = allcorrect && correct_zzyy;

    float expected_zzyz[] = {2.000000f,2.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_zzyz(src);
    int correct_zzyz = check_vector("zzyz",dst,expected_zzyz);
    allcorrect = allcorrect && correct_zzyz;

    float expected_zzyw[] = {2.000000f,2.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_zzyw(src);
    int correct_zzyw = check_vector("zzyw",dst,expected_zzyw);
    allcorrect = allcorrect && correct_zzyw;

    float expected_zzzx[] = {2.000000f,2.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_zzzx(src);
    int correct_zzzx = check_vector("zzzx",dst,expected_zzzx);
    allcorrect = allcorrect && correct_zzzx;

    float expected_zzzy[] = {2.000000f,2.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_zzzy(src);
    int correct_zzzy = check_vector("zzzy",dst,expected_zzzy);
    allcorrect = allcorrect && correct_zzzy;

    float expected_zzzz[] = {2.000000f,2.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_zzzz(src);
    int correct_zzzz = check_vector("zzzz",dst,expected_zzzz);
    allcorrect = allcorrect && correct_zzzz;

    float expected_zzzw[] = {2.000000f,2.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_zzzw(src);
    int correct_zzzw = check_vector("zzzw",dst,expected_zzzw);
    allcorrect = allcorrect && correct_zzzw;

    float expected_zzwx[] = {2.000000f,2.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_zzwx(src);
    int correct_zzwx = check_vector("zzwx",dst,expected_zzwx);
    allcorrect = allcorrect && correct_zzwx;

    float expected_zzwy[] = {2.000000f,2.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_zzwy(src);
    int correct_zzwy = check_vector("zzwy",dst,expected_zzwy);
    allcorrect = allcorrect && correct_zzwy;

    float expected_zzwz[] = {2.000000f,2.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_zzwz(src);
    int correct_zzwz = check_vector("zzwz",dst,expected_zzwz);
    allcorrect = allcorrect && correct_zzwz;

    float expected_zzww[] = {2.000000f,2.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_zzww(src);
    int correct_zzww = check_vector("zzww",dst,expected_zzww);
    allcorrect = allcorrect && correct_zzww;

    float expected_zwxx[] = {2.000000f,3.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_zwxx(src);
    int correct_zwxx = check_vector("zwxx",dst,expected_zwxx);
    allcorrect = allcorrect && correct_zwxx;

    float expected_zwxy[] = {2.000000f,3.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_zwxy(src);
    int correct_zwxy = check_vector("zwxy",dst,expected_zwxy);
    allcorrect = allcorrect && correct_zwxy;

    float expected_zwxz[] = {2.000000f,3.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_zwxz(src);
    int correct_zwxz = check_vector("zwxz",dst,expected_zwxz);
    allcorrect = allcorrect && correct_zwxz;

    float expected_zwxw[] = {2.000000f,3.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_zwxw(src);
    int correct_zwxw = check_vector("zwxw",dst,expected_zwxw);
    allcorrect = allcorrect && correct_zwxw;

    float expected_zwyx[] = {2.000000f,3.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_zwyx(src);
    int correct_zwyx = check_vector("zwyx",dst,expected_zwyx);
    allcorrect = allcorrect && correct_zwyx;

    float expected_zwyy[] = {2.000000f,3.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_zwyy(src);
    int correct_zwyy = check_vector("zwyy",dst,expected_zwyy);
    allcorrect = allcorrect && correct_zwyy;

    float expected_zwyz[] = {2.000000f,3.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_zwyz(src);
    int correct_zwyz = check_vector("zwyz",dst,expected_zwyz);
    allcorrect = allcorrect && correct_zwyz;

    float expected_zwyw[] = {2.000000f,3.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_zwyw(src);
    int correct_zwyw = check_vector("zwyw",dst,expected_zwyw);
    allcorrect = allcorrect && correct_zwyw;

    float expected_zwzx[] = {2.000000f,3.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_zwzx(src);
    int correct_zwzx = check_vector("zwzx",dst,expected_zwzx);
    allcorrect = allcorrect && correct_zwzx;

    float expected_zwzy[] = {2.000000f,3.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_zwzy(src);
    int correct_zwzy = check_vector("zwzy",dst,expected_zwzy);
    allcorrect = allcorrect && correct_zwzy;

    float expected_zwzz[] = {2.000000f,3.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_zwzz(src);
    int correct_zwzz = check_vector("zwzz",dst,expected_zwzz);
    allcorrect = allcorrect && correct_zwzz;

    float expected_zwzw[] = {2.000000f,3.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_zwzw(src);
    int correct_zwzw = check_vector("zwzw",dst,expected_zwzw);
    allcorrect = allcorrect && correct_zwzw;

    float expected_zwwx[] = {2.000000f,3.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_zwwx(src);
    int correct_zwwx = check_vector("zwwx",dst,expected_zwwx);
    allcorrect = allcorrect && correct_zwwx;

    float expected_zwwy[] = {2.000000f,3.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_zwwy(src);
    int correct_zwwy = check_vector("zwwy",dst,expected_zwwy);
    allcorrect = allcorrect && correct_zwwy;

    float expected_zwwz[] = {2.000000f,3.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_zwwz(src);
    int correct_zwwz = check_vector("zwwz",dst,expected_zwwz);
    allcorrect = allcorrect && correct_zwwz;

    float expected_zwww[] = {2.000000f,3.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_zwww(src);
    int correct_zwww = check_vector("zwww",dst,expected_zwww);
    allcorrect = allcorrect && correct_zwww;

    float expected_wxxx[] = {3.000000f,0.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_wxxx(src);
    int correct_wxxx = check_vector("wxxx",dst,expected_wxxx);
    allcorrect = allcorrect && correct_wxxx;

    float expected_wxxy[] = {3.000000f,0.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_wxxy(src);
    int correct_wxxy = check_vector("wxxy",dst,expected_wxxy);
    allcorrect = allcorrect && correct_wxxy;

    float expected_wxxz[] = {3.000000f,0.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_wxxz(src);
    int correct_wxxz = check_vector("wxxz",dst,expected_wxxz);
    allcorrect = allcorrect && correct_wxxz;

    float expected_wxxw[] = {3.000000f,0.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_wxxw(src);
    int correct_wxxw = check_vector("wxxw",dst,expected_wxxw);
    allcorrect = allcorrect && correct_wxxw;

    float expected_wxyx[] = {3.000000f,0.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_wxyx(src);
    int correct_wxyx = check_vector("wxyx",dst,expected_wxyx);
    allcorrect = allcorrect && correct_wxyx;

    float expected_wxyy[] = {3.000000f,0.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_wxyy(src);
    int correct_wxyy = check_vector("wxyy",dst,expected_wxyy);
    allcorrect = allcorrect && correct_wxyy;

    float expected_wxyz[] = {3.000000f,0.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_wxyz(src);
    int correct_wxyz = check_vector("wxyz",dst,expected_wxyz);
    allcorrect = allcorrect && correct_wxyz;

    float expected_wxyw[] = {3.000000f,0.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_wxyw(src);
    int correct_wxyw = check_vector("wxyw",dst,expected_wxyw);
    allcorrect = allcorrect && correct_wxyw;

    float expected_wxzx[] = {3.000000f,0.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_wxzx(src);
    int correct_wxzx = check_vector("wxzx",dst,expected_wxzx);
    allcorrect = allcorrect && correct_wxzx;

    float expected_wxzy[] = {3.000000f,0.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_wxzy(src);
    int correct_wxzy = check_vector("wxzy",dst,expected_wxzy);
    allcorrect = allcorrect && correct_wxzy;

    float expected_wxzz[] = {3.000000f,0.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_wxzz(src);
    int correct_wxzz = check_vector("wxzz",dst,expected_wxzz);
    allcorrect = allcorrect && correct_wxzz;

    float expected_wxzw[] = {3.000000f,0.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_wxzw(src);
    int correct_wxzw = check_vector("wxzw",dst,expected_wxzw);
    allcorrect = allcorrect && correct_wxzw;

    float expected_wxwx[] = {3.000000f,0.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_wxwx(src);
    int correct_wxwx = check_vector("wxwx",dst,expected_wxwx);
    allcorrect = allcorrect && correct_wxwx;

    float expected_wxwy[] = {3.000000f,0.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_wxwy(src);
    int correct_wxwy = check_vector("wxwy",dst,expected_wxwy);
    allcorrect = allcorrect && correct_wxwy;

    float expected_wxwz[] = {3.000000f,0.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_wxwz(src);
    int correct_wxwz = check_vector("wxwz",dst,expected_wxwz);
    allcorrect = allcorrect && correct_wxwz;

    float expected_wxww[] = {3.000000f,0.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_wxww(src);
    int correct_wxww = check_vector("wxww",dst,expected_wxww);
    allcorrect = allcorrect && correct_wxww;

    float expected_wyxx[] = {3.000000f,1.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_wyxx(src);
    int correct_wyxx = check_vector("wyxx",dst,expected_wyxx);
    allcorrect = allcorrect && correct_wyxx;

    float expected_wyxy[] = {3.000000f,1.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_wyxy(src);
    int correct_wyxy = check_vector("wyxy",dst,expected_wyxy);
    allcorrect = allcorrect && correct_wyxy;

    float expected_wyxz[] = {3.000000f,1.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_wyxz(src);
    int correct_wyxz = check_vector("wyxz",dst,expected_wyxz);
    allcorrect = allcorrect && correct_wyxz;

    float expected_wyxw[] = {3.000000f,1.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_wyxw(src);
    int correct_wyxw = check_vector("wyxw",dst,expected_wyxw);
    allcorrect = allcorrect && correct_wyxw;

    float expected_wyyx[] = {3.000000f,1.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_wyyx(src);
    int correct_wyyx = check_vector("wyyx",dst,expected_wyyx);
    allcorrect = allcorrect && correct_wyyx;

    float expected_wyyy[] = {3.000000f,1.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_wyyy(src);
    int correct_wyyy = check_vector("wyyy",dst,expected_wyyy);
    allcorrect = allcorrect && correct_wyyy;

    float expected_wyyz[] = {3.000000f,1.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_wyyz(src);
    int correct_wyyz = check_vector("wyyz",dst,expected_wyyz);
    allcorrect = allcorrect && correct_wyyz;

    float expected_wyyw[] = {3.000000f,1.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_wyyw(src);
    int correct_wyyw = check_vector("wyyw",dst,expected_wyyw);
    allcorrect = allcorrect && correct_wyyw;

    float expected_wyzx[] = {3.000000f,1.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_wyzx(src);
    int correct_wyzx = check_vector("wyzx",dst,expected_wyzx);
    allcorrect = allcorrect && correct_wyzx;

    float expected_wyzy[] = {3.000000f,1.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_wyzy(src);
    int correct_wyzy = check_vector("wyzy",dst,expected_wyzy);
    allcorrect = allcorrect && correct_wyzy;

    float expected_wyzz[] = {3.000000f,1.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_wyzz(src);
    int correct_wyzz = check_vector("wyzz",dst,expected_wyzz);
    allcorrect = allcorrect && correct_wyzz;

    float expected_wyzw[] = {3.000000f,1.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_wyzw(src);
    int correct_wyzw = check_vector("wyzw",dst,expected_wyzw);
    allcorrect = allcorrect && correct_wyzw;

    float expected_wywx[] = {3.000000f,1.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_wywx(src);
    int correct_wywx = check_vector("wywx",dst,expected_wywx);
    allcorrect = allcorrect && correct_wywx;

    float expected_wywy[] = {3.000000f,1.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_wywy(src);
    int correct_wywy = check_vector("wywy",dst,expected_wywy);
    allcorrect = allcorrect && correct_wywy;

    float expected_wywz[] = {3.000000f,1.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_wywz(src);
    int correct_wywz = check_vector("wywz",dst,expected_wywz);
    allcorrect = allcorrect && correct_wywz;

    float expected_wyww[] = {3.000000f,1.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_wyww(src);
    int correct_wyww = check_vector("wyww",dst,expected_wyww);
    allcorrect = allcorrect && correct_wyww;

    float expected_wzxx[] = {3.000000f,2.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_wzxx(src);
    int correct_wzxx = check_vector("wzxx",dst,expected_wzxx);
    allcorrect = allcorrect && correct_wzxx;

    float expected_wzxy[] = {3.000000f,2.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_wzxy(src);
    int correct_wzxy = check_vector("wzxy",dst,expected_wzxy);
    allcorrect = allcorrect && correct_wzxy;

    float expected_wzxz[] = {3.000000f,2.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_wzxz(src);
    int correct_wzxz = check_vector("wzxz",dst,expected_wzxz);
    allcorrect = allcorrect && correct_wzxz;

    float expected_wzxw[] = {3.000000f,2.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_wzxw(src);
    int correct_wzxw = check_vector("wzxw",dst,expected_wzxw);
    allcorrect = allcorrect && correct_wzxw;

    float expected_wzyx[] = {3.000000f,2.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_wzyx(src);
    int correct_wzyx = check_vector("wzyx",dst,expected_wzyx);
    allcorrect = allcorrect && correct_wzyx;

    float expected_wzyy[] = {3.000000f,2.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_wzyy(src);
    int correct_wzyy = check_vector("wzyy",dst,expected_wzyy);
    allcorrect = allcorrect && correct_wzyy;

    float expected_wzyz[] = {3.000000f,2.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_wzyz(src);
    int correct_wzyz = check_vector("wzyz",dst,expected_wzyz);
    allcorrect = allcorrect && correct_wzyz;

    float expected_wzyw[] = {3.000000f,2.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_wzyw(src);
    int correct_wzyw = check_vector("wzyw",dst,expected_wzyw);
    allcorrect = allcorrect && correct_wzyw;

    float expected_wzzx[] = {3.000000f,2.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_wzzx(src);
    int correct_wzzx = check_vector("wzzx",dst,expected_wzzx);
    allcorrect = allcorrect && correct_wzzx;

    float expected_wzzy[] = {3.000000f,2.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_wzzy(src);
    int correct_wzzy = check_vector("wzzy",dst,expected_wzzy);
    allcorrect = allcorrect && correct_wzzy;

    float expected_wzzz[] = {3.000000f,2.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_wzzz(src);
    int correct_wzzz = check_vector("wzzz",dst,expected_wzzz);
    allcorrect = allcorrect && correct_wzzz;

    float expected_wzzw[] = {3.000000f,2.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_wzzw(src);
    int correct_wzzw = check_vector("wzzw",dst,expected_wzzw);
    allcorrect = allcorrect && correct_wzzw;

    float expected_wzwx[] = {3.000000f,2.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_wzwx(src);
    int correct_wzwx = check_vector("wzwx",dst,expected_wzwx);
    allcorrect = allcorrect && correct_wzwx;

    float expected_wzwy[] = {3.000000f,2.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_wzwy(src);
    int correct_wzwy = check_vector("wzwy",dst,expected_wzwy);
    allcorrect = allcorrect && correct_wzwy;

    float expected_wzwz[] = {3.000000f,2.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_wzwz(src);
    int correct_wzwz = check_vector("wzwz",dst,expected_wzwz);
    allcorrect = allcorrect && correct_wzwz;

    float expected_wzww[] = {3.000000f,2.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_wzww(src);
    int correct_wzww = check_vector("wzww",dst,expected_wzww);
    allcorrect = allcorrect && correct_wzww;

    float expected_wwxx[] = {3.000000f,3.000000f,0.000000f,0.000000f};
    dst = _mm_swizzle_ps_wwxx(src);
    int correct_wwxx = check_vector("wwxx",dst,expected_wwxx);
    allcorrect = allcorrect && correct_wwxx;

    float expected_wwxy[] = {3.000000f,3.000000f,0.000000f,1.000000f};
    dst = _mm_swizzle_ps_wwxy(src);
    int correct_wwxy = check_vector("wwxy",dst,expected_wwxy);
    allcorrect = allcorrect && correct_wwxy;

    float expected_wwxz[] = {3.000000f,3.000000f,0.000000f,2.000000f};
    dst = _mm_swizzle_ps_wwxz(src);
    int correct_wwxz = check_vector("wwxz",dst,expected_wwxz);
    allcorrect = allcorrect && correct_wwxz;

    float expected_wwxw[] = {3.000000f,3.000000f,0.000000f,3.000000f};
    dst = _mm_swizzle_ps_wwxw(src);
    int correct_wwxw = check_vector("wwxw",dst,expected_wwxw);
    allcorrect = allcorrect && correct_wwxw;

    float expected_wwyx[] = {3.000000f,3.000000f,1.000000f,0.000000f};
    dst = _mm_swizzle_ps_wwyx(src);
    int correct_wwyx = check_vector("wwyx",dst,expected_wwyx);
    allcorrect = allcorrect && correct_wwyx;

    float expected_wwyy[] = {3.000000f,3.000000f,1.000000f,1.000000f};
    dst = _mm_swizzle_ps_wwyy(src);
    int correct_wwyy = check_vector("wwyy",dst,expected_wwyy);
    allcorrect = allcorrect && correct_wwyy;

    float expected_wwyz[] = {3.000000f,3.000000f,1.000000f,2.000000f};
    dst = _mm_swizzle_ps_wwyz(src);
    int correct_wwyz = check_vector("wwyz",dst,expected_wwyz);
    allcorrect = allcorrect && correct_wwyz;

    float expected_wwyw[] = {3.000000f,3.000000f,1.000000f,3.000000f};
    dst = _mm_swizzle_ps_wwyw(src);
    int correct_wwyw = check_vector("wwyw",dst,expected_wwyw);
    allcorrect = allcorrect && correct_wwyw;

    float expected_wwzx[] = {3.000000f,3.000000f,2.000000f,0.000000f};
    dst = _mm_swizzle_ps_wwzx(src);
    int correct_wwzx = check_vector("wwzx",dst,expected_wwzx);
    allcorrect = allcorrect && correct_wwzx;

    float expected_wwzy[] = {3.000000f,3.000000f,2.000000f,1.000000f};
    dst = _mm_swizzle_ps_wwzy(src);
    int correct_wwzy = check_vector("wwzy",dst,expected_wwzy);
    allcorrect = allcorrect && correct_wwzy;

    float expected_wwzz[] = {3.000000f,3.000000f,2.000000f,2.000000f};
    dst = _mm_swizzle_ps_wwzz(src);
    int correct_wwzz = check_vector("wwzz",dst,expected_wwzz);
    allcorrect = allcorrect && correct_wwzz;

    float expected_wwzw[] = {3.000000f,3.000000f,2.000000f,3.000000f};
    dst = _mm_swizzle_ps_wwzw(src);
    int correct_wwzw = check_vector("wwzw",dst,expected_wwzw);
    allcorrect = allcorrect && correct_wwzw;

    float expected_wwwx[] = {3.000000f,3.000000f,3.000000f,0.000000f};
    dst = _mm_swizzle_ps_wwwx(src);
    int correct_wwwx = check_vector("wwwx",dst,expected_wwwx);
    allcorrect = allcorrect && correct_wwwx;

    float expected_wwwy[] = {3.000000f,3.000000f,3.000000f,1.000000f};
    dst = _mm_swizzle_ps_wwwy(src);
    int correct_wwwy = check_vector("wwwy",dst,expected_wwwy);
    allcorrect = allcorrect && correct_wwwy;

    float expected_wwwz[] = {3.000000f,3.000000f,3.000000f,2.000000f};
    dst = _mm_swizzle_ps_wwwz(src);
    int correct_wwwz = check_vector("wwwz",dst,expected_wwwz);
    allcorrect = allcorrect && correct_wwwz;

    float expected_wwww[] = {3.000000f,3.000000f,3.000000f,3.000000f};
    dst = _mm_swizzle_ps_wwww(src);
    int correct_wwww = check_vector("wwww",dst,expected_wwww);
    allcorrect = allcorrect && correct_wwww;

    if (allcorrect)
        printf("All swizzles passed!\n");
    else
        printf("At least one swizzle failed; check detailed log.\n");
}
#endif
#endif
#endif

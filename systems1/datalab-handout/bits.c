/* 
 * CS:APP Data Lab 
 * 
 * Frija Reinert 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 *
 * Here is a very poorly drawn skeleton in honor of halloween
 *     -----
 *   /       \
 *  |  0   0  |      |
 *  |   /_\   |     |||
 *   \ ||||| /    \ ||| |
 *    \|nnn|/      \|||/
 *    __| |__      / /
 *   /       \    / /
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  // this fun assumes we start counting digits R=>L from 0
  // create the number 010101..01
  int x = 0x55;
  int y = (x << 8) + x;
  int z = (y << 16) + y;
  // returns the same val as z, but we were told to consider our input as 0
  return 0 | z;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int a = !!(x>>31); // stores sign digit of x
  int b = !!(y>>31); // stores sign digit of y
  int c = x + y;
  int d = ~(a^b); // 1 if a and b share a sign bit
  c = !!(c>>31); // stores sign bit of sum
  // d&(c^a) == 1 if a and b share a sign but their sum does not (overflow)
  return !(d&(c^a));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int a;
  int b;
  // save x as 0000..0 if 0 and 1111..1 if anything else
  x = ((!!x) << 31)>>32;
  // if x == 0 it stays 0 else x = y
  a = x&y;
  // if x == 0 x = z else (x = y) x doesn't change
  b = (~x) & z;
  return a | b;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  // copy sign bit
  int a = x>>31;
  // if neg, return inverse of x + 1 else return x 
  return (x^a) + (!!a);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  int a,b,c,d,e;
  // Go through x by halves, using ^ to maintain the odd or even # of zeros
  x = ~x;
  a = x>>16;
  x = x^a;
  b = x>>8;
  x = x^b;
  c = x>>4;
  x = x^c;
  d = x>>2;
  x = x^d;
  e = x>>1;
  x = x^e;
  // return last digit that holds val 0 if even # 1 if odd
  return !!(x<<31);
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  // if neg: can't contain any 0s until 15th digit
  // if pos: can't contain any 1s until 15th digit
  // digits 32-16 should be all 1s or all 0s
  int a = x>>15;
  // ensure digits are all the same
  return !(a^(a>>1));
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  // copy rightmost bit to all bits
  return (x<<31)>>31;
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  // this fun assumes we start counting digits R=>L from 0
  // create the number 01010101..01
  int x = 0xAA;
  int y = (x << 8) + x;
  int z = (y << 16) + y;
  // again, not necessary could just return z
  return 0 | z;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int xs = !!(x>>31); // stores sign bit of x
  int ys = !!(y>>31); // stores sign bit of y
  // 1 if equal
  int areEqual = !(x^y);
  // a = x - y
  int a = x + ((~y) + 1);
  int aSign = !!(a>>31);
  int sameSign = !(xs^ys);
  // if x and y aren't same number and they have the same sign, but their
  // difference doesn't
  // or if y is neg and x is pos (accounts for stupid edge case)
  return ((!aSign) & sameSign & (!areEqual)) | (ys & (!xs));
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 
 * (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // use 0x30-1 so that if (aMin-1)-x has a - sign, its >= 0x30
  int aMin = 0x2F;
  int aMax = 0x39;
  int negX = ~x + 1;
  int a = aMin + negX;
  int b = aMax + negX;
  int signA = !!(a>>31); // should be 1 if x >= 0x30
  int signB = !(b>>31); // should be 1 if x <= 0x39
  return signA & signB;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  // oneLess = x - 1
  int oneLess = x + ~0;
  // erase all 1s except that in the rightmost place
  return (x^oneLess) & x;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  int a,b;
  // flip all 0s after most sig bit to 1s e.g., 000..111.1
  x = x | (x>>1);
  x = x | (x>>2);
  x = x | (x>>4);
  x = x | (x>>8);
  x = x | (x>>16);
  a = 1<<31; // 1000..0 needed for neg numbers
  // flip 1s back to 0s, where first 1 is the bit to the right of the prev
  // most sig bit e.g., 111..000.0
  b = ((~x)>>1) | a;
  // get rid of excess 1s but keep the sign dig if it's the greatet sig bit
  return x&b;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  int a,b,c;
  // check if uf ==  NANs
  if (uf == 0x7fc00000 | uf == 0xffc00000)
	  return uf;
  // if leading bit is 1 replace it with 0
  a = 1<<31; // 1000..0
  b = uf ^ a;
  return b & uf;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int bias = 127;
  int sse,se0,m,s,e,exp;
  sse = uf>>23; // sss...e
  se0 = sse<<23; // se000...0
  m = uf ^ sse; // 000...m
  s = !!(uf>>31); // 000...s
  e = ((uf >> 31) << 8) ^ sse; // ssss ssss s000...0
  exp = e - bias;
  
  // check for vals < 0
  if (exp < 0)
    return 0;
  // check for NaNs, infinity, and out of range nums
  if (exp > 22) // 23-1 for leading 1
    return 0x80000000;

  // else convert to int
  // shift and get rid of leading 1s if any 
  m = (m >> (23 - exp)) ^ ((m >> 23) << exp);
  // add back leading 1 for normalized
  m = m + (1 << exp);
  // add back sign
  m = m * (1 - (2 * s));
  return m;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  int bias = 127;
  int sse,se0,m,s,e,exp;
  sse = uf>>23; // sss...e
  se0 = sse<<23; // se000...0
  m = uf ^ se0; // 000...m
  s = !!(uf>>31); // 000...s
  e = ((uf >> 31) << 8) ^ sse; // sss..s 0000 0000 -> 000..e
  exp = e - bias;
  
  // check for NaNs and infinity
  if (e >= 255) // all 1s
    return uf;

  // check for denormalized nums
  if (e <= 1) {
    // if num will be made denorm, add 1 to front of mantissa
    // then divide mantissa in half later (moving 1 from exp to m)
    if (e == 1) {
      exp -= 1;
      m += (1<<23);
    }
    // if m ends in 11, round up to even
    if ((m & 0x3) == 0x3) {
      m += 1;
    }
    // shift mantissa to divide in half
    m = m >> 1;
  }

  // norm nums: halve exp
  else {
    exp -= 1;
  }

  return ((s << 31) + ((exp + bias) << 23) + m);
}

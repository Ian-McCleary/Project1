/* 
 * CS:APP Data Lab 
 * 
 * <Ian McCleary cs userid: mccleai>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
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
 
  /* brief description of how your implementation works */
  int Funct(arg1, arg2, ...) {
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
   *
   * exploit ability of shifts to compute powers of 2
   */
  int pow2plus1(int x) {
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2 
   */
  int pow2plus4(int x) {
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
       return~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
//move byte to least significant byte(2^3) and use
//0xFF to mask out more significant bytes.
int getByte(int x, int n) {
  return x>>(n<<3) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
//right shift normally and then set the leftmost bits as necessary to zero.
int logicalShift(int x, int n) {
  return (x>>n) & ~(((0<<31) >> n) << 0);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
//first use a mask to get the least significant bit for every 4 bytes
//use another mask to shift x by 1, 8 times for each bit in a byte
//This gives us the total number of 1s in each byte
//lastly total the number of 1s for all bytes by shifting 8 bits at a time.
int bitCount(int x) {
  int m4byte = 0x1 | (0x1 << 8) | (0x1 << 16) | (0x1 << 24);
  int m1byte = 0xFF;
  int sum4byte = (x & m4byte) + ((x>>1) & m4byte) + ((x>>2) & m4byte) + ((x>>3) & m4byte) + ((x>>4) & m4byte) + ((x>>5) & m4byte) + ((x>>6) & m4byte) + ((x>>7) & m4byte);
  int sum = (sum4byte & m1byte) + ((sum4byte>>8) & m1byte) + ((sum4byte>>16) & m1byte) + ((sum4byte >> 24) & m1byte);
  return sum;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int negX =  ~x+1; //(opposite sign of x) + 1
  int bits = (negX | x) >> 31; //ouput of -1 or 0
  return bits+1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
//left shift 1 by 31 to get the smallest possible number when 1 is in signed position
int tmin(void) {
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int sigM = x >> 31;
  return !(((~x & sigM) + (x & ~sigM)) >> (n + ~0));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
//for positive num, x>>n
//for negative num, (x+1)<<n-1)>>n
int divpwr2(int x, int n) {
  int negCheck = x >> 31;
  int y = ((negCheck & 1) << n) + negCheck;
  return (x+y) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
//opposite of each bit and add 1 to account for signed/unsiged difference
int negate(int x) {
  return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int m = x>>31;
  return !x ^ !m;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
//when same sign, check if x-y is negative
//otherwise negative is less than positive 
int isLessOrEqual(int x, int y) {
  int signCheck = !(x>>31)^!(y>>31);
  //different signs and x is negative outputs 1
  int subtractOpposite = signCheck & (x>>31);
  //same sign and difference is positive or 0 outputs 1
  int subtractSame = !signCheck & !((y+(~x+1))>>31);
  int result = subtractOpposite | subtractSame;
  return result;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
//find the most significant 1
int ilog2(int x) {
  //each time check if > (prev result + 8)
  int result = (!!(x >> 16)) << 4;
  int calc1 = ((!!(x >> (result + 8))) << 3);
  result = result + calc1;
  int calc2 = ((!!(x >> (result + 4))) << 2);
  result = result + calc2;
  int calc3 = ((!!(x >> (result + 2))) << 1);
  result = result + calc3;
  int calc4 = (!!(x >> (result + 1)));
  result = result + calc4;
  return result;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  //first put 1s in the exponent bits
  int nan = 0xFF << 23;
  //get the fraction bits
  int fraction = 0x7FFFFF & uf;
  //return if fraction is not all zero while exponent is not all 1s
  if ((nan & uf) == nan && fraction){
    return uf;
  }
  //flip sign bit 
  return uf ^ (1<<31);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  //get the signed bit & setup constants for negative numbers, exponent, and bias
  int signCheck = x & (1<<31);
  int neg = 1<<31;
  int exponent = 31;
  int bias = 127;
  int fraction;
  //if x is all zeros
  if(!x){
    return 0;
  }
  //if x is all ones
  if (x == neg){
    return neg | ((exponent + bias) << 23);
  }
  //if x is negative
  if (signCheck){
    x = ~x +1;
  }
  //find the exponent
  while (!(x & neg)){
    x <<=1;
    exponent-=1;
  }
  fraction = (((~neg) & x) >> 8);
  if (x & 0x80 && ((fraction & 1) || ((x & 0x7f) > 0))){
    fraction++;
  }
  //add each component together
  return signCheck + ((exponent + bias) << 23) + fraction;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  //if uf is either zero case
  if(uf == 0 || uf == 0x80000000){
    return uf;
  }
  //if uf is nan
  if (((uf >> 23) & 0xFF) == 0xFF){
    return uf;
  }
  //for small non zero values
  if (((uf >> 23) & 0xFF) == 0x00){
    return (uf & (1<<31)) | (uf<<1);
  }
  //just add 1 to the exponent 
  return uf + (1<<23);
}

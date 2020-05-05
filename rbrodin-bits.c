/* 
 * CS:APP Data Lab 
 * 
 * Robert Brodin, rbrodin
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
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

/* We do not support C11 <threads.h>.  */
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {

  // word is the value that will be returned, default set to 1111.
  // shifter is the hexidecimal value of 1010 1010. This is used as the mask to change word.
  int word = 0xFF;
  int shifter = 0xAA;
  
  // Shifts shifter to the left, making it 16 bits long, and replaces the first 8 bits from 0000 to 1010, using XOR.
  shifter = (shifter << 8) ^ shifter;
  // The following code shifts word to the left 16, and then replaces those 16 bits with the value of shifter, which is 1010.
  word = word << 16;
  word = word ^ shifter;
  word = word << 16;
  word = word ^ shifter;

  return word;
}
/*	
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  // tMin + tMin = 0. The case that this broke was when x was zero, where it would return 1, which is not correct. I added the XOR !x for when x = 0.
  return !(x+x) ^ !x;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

// Ended up using Demorgan's Second Law to solve this.
  int firstBit = (~x & y);
  int secondBit = (x & ~y);
  return ~(~firstBit & ~secondBit);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16is
 *   Rating: 3
If x is true then return y, otherwise z
 */
int conditional(int x, int y, int z) {

// Using Two's Complement to flip and negate the bit.
  int yMask = !!x;
  yMask = ~yMask + 1;

// AND operation with 1 is always true, and AND with 0 is always false. This takes advantage of that.
// And, OR of 0 and n is n.
  return (yMask & y) | (~yMask & z);
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

  // Algorithm works by shifting x right by one, and ORing with all the values. The bitMask will switch the second bit into a one, if the MSB is 1, this process repeats until the result is 
  // all zeroes before the first most significant one, and all ones after the most significant one.
  // Example: 011011 becomes 011111, before the negation.
  int bitMask = (x >> 1);
  int flipOverflow = 0;
  x = bitMask | x;
  bitMask = (x >> 2);
  x = bitMask | x;
  bitMask = (x >> 4);
  x = bitMask | x;
  bitMask = (x >> 8);
  x = bitMask | x;
  bitMask = (x >> 16);
  x = bitMask | x;

  // ~x + 1 flips the bits, where 011111 will becomes 100000, and shifted to the right one will become 010000. The idea being that shifting by right one and anding with the original value 
  // makes it so the most significant one bit is the only ONE left.
  // Necessary to include the OR tMin because of the case of the MSB equaling 1, ie 1001 or 1101 or bitstring where the MSB is 1. Dealing with overflow.
  flipOverflow = ((1 << 31) | (~x >> 1));
  return x & flipOverflow;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    // I spent several hours trying to figure out how to fix the issue with negatives (two's complement issue)
    // What I figured out was that shifting the most significant bit all the way to the right and ANDing with (2^n - 1) switches the most significant bit when it needs to be (logical right shift).
    return ((x + (x >> 31 & ((1 << n) + (~1 + 1)))) >> n);
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  // Takes advantage of a logical right shift by shifting the most significant bit to the first bit position, then applying twos complement to that, and (bool) NOTing it.
  // Gives the effect of: 0x7fffffff -> 0000...1 -> ~0000...1 -> 0 -> 1 -> 0
  return !(~(x >> 31) + 1);
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  // Multiplies x by 2^1, or 2.
  int multiplication = x << 1;
  // checkShift checks if the MSB is flipped or not, if it is, that means the sign changed ie there is overflow.
  int checkShift = x ^ multiplication;
 // Most significant bit is one if there is overflow. 0 otherwise.
  int checkOverflow = checkShift >> 31;
  // Uses the MSB and ~tMin (tMax) to get the overflow value. If the sign of x is 1 (x is negative), then tMin, otherwise, if x is 0 (x is positive), then tMax.
  int saturateBits = (x >> 31 ^ ~(1 << 31));
  // If there is overFlow, then saturateBits is returned (checkOverflow = 1), if there is no overflow (checkOverflow = 0), then simply the multiplication is returned.
  int toReturn = (~checkOverflow & multiplication) | (checkOverflow & saturateBits);

  return toReturn;
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
    // Subtract y from x, will be used to check if the number is negative. (ie, x < y, if x - y is negative) 
    int sub = x + (~y + 1);
    // Checks if y and x are equal. If they are, returns 0. 
    int larger = (y ^ x); // worked on its own
    // There are two cases, the two numbers are equal, or they are different. 
    // If they are equal, simply return the value of x. Otherwise, return the value of the subtraction.
    // Then, rightt shift by 31 to check if the MSB is 1 or 0, indicating whether positive or negative. If the value is 0, return 0, if the value is anything but zero, return 1.  
    int isLarger = !!(((~larger & sub) | (larger & x)) >> 31);
    return isLarger;
    // Sidenote: going back to this and commenting my logic seems a little off with it. Specifically with if they are equal.
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {

  // Upper bound defined as 0x39, lower bound defined as 0x30.
  // Upper and lower bounds are defined as x - 0x39, and x - 0x30. x must be greater than 0x30 and less than 0x39.
  int upper = x + (~0x39 + 1);
  int lower = x + (~0x30 + 1);

  // Conjunctive normal form, throwback to CS2022. 
  // Checks if upper is negative (MSB is 1), or upper is equal to zero. Meaning that x <= 0x39.
  // AND, if lower is positive (MSB is 0), or lower is equal to zero. Meaning that x >= 0x30.
  // Returns one if both of the conditions are met.
  return ((upper >> 31) | !upper) & (!(lower >> 31) | !lower);
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
  // three represents 0x3 without any constants. It's kind of extra, I know.  
  int three = (1 << 1) + 1;

  // The way that the function performs the operation is adding 1/4 + 1/2, which equals three fourths.
  // I simply divide x by 4 and add it to x/2.
  // Then, I take into account the fact that if x is negative I need to add to it. (in add)
  int byFour = x >> 2;
  int byTwo = x >> 1;

  // Gets the remainder (what was truncated), after the division, for both 1/4 and 1/2.
  // Note, for 1/4 I had to look at the first two bits, meaning I had to AND it with three.
  // For 1/2, I can just AND it with one and call it a day.
  int remFour = x & three;
  int remTwo = x & 1;
  // Gets the MSB (used to check if positive or negative)
  int neg = x >> 31;
  // Adds up the remainder (now the remainder of 3/4)
  int totalRem = remFour + remTwo;
  // Adds to the total remainder. If the number is negative, then add three extra to bias. 
  // Also, add one if there is a remainder of one for remTwo, this was a case that kept popping up that I had to address.
  int add = (totalRem + (neg & three) + (remTwo & 1)) >> 2;
  // Add x/4 + x/2 and add the bias (add).
  int sum = byFour + byTwo + add;
  return sum;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int sum = 0;
  // I did not have time to finish ilog2.
  return sum;
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

 // NaN is when exp is 1111 and frac is not 0.
 // Changes just the first sign bit.
 unsigned int negativeUf = (1 << 31) ^ uf;

 // Don't care about the sign bit.
 unsigned int isNaN = ~(1 << 31) & uf;
 // 8 bits for exp, 23 for fract. 
 if(isNaN > 0x7F800000){
    return uf;
}
 return negativeUf;
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
  
  unsigned int absolute = x;
  unsigned exponent = 0;
  unsigned residue = 0;
  unsigned floatingPoint = 0;
  unsigned int signBit = 0;

  if (x == 0){
    return 0;
  }
  if (x == (1 << 31)) {
    return 0xcf000000;
  }
  // If x is less than zero, flip the sign of x 
  if (x < 0) {
    absolute = -1 * x;
    // 1 is negative, 0 if positive.
    signBit = (1 << 31);
   }
  // Until you it sees the first one bit, keep shifting to the left.
  // The max the bias can be is 158, since overflow if we shift 32 bits.
  // Meaning that, we increment exponent by one until we reach a one, meaning that exponent will be value of the number of shifts required.
  while (!(absolute & (1 << 31))) {
    absolute <<= 1;
    // Might need to switch the order of the subtraction.
    exponent++;
  }
  // Adds the exponent and sign bit to the floating point. NOTE: Shifts over 23 to move it past the number of mantissa bits! It will be shifted back.
  floatingPoint = signBit ^ ((158 - exponent) << 23);
  // TODO: Issue might be here with XOR.
  // Adds the mantissa, by right shifting x by eight and ANDing with 1111.
  floatingPoint = floatingPoint ^ ((absolute >> 8) & 0x7fffff);

  // Natalie (TA) helped me with the logic of the residue and how if frac > 1000 0000 or equal to 1000 0000 then round up (add one)
  if ((absolute & 0xff) > (1 << 7) || ((absolute >> 7) & 0x3) == 0x3) {
    residue = 1;
  }
  // Adds either one or zero to floating point (rounding!)
  floatingPoint = floatingPoint + residue;
  return floatingPoint;
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
    // I did not have time to finish float_twice.

    int tMin = (1 << 31);
    int exponent = (uf >> 23);
    if(uf == 0){
        return uf;
    }
    else if(uf == tMin){
        return uf;
    }
    else if(exponent == 0xFF){
        return uf;
    }
    else if(exponent == 0){
        return uf << 1;
    }
    else {
        return uf + (1 << 23);
    }
}

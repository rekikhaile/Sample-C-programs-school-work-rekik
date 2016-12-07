#include "fraction.h"
#include <stdio.h>
#include "fraction.h"

/* Algorithm for determining greatest common divisor, needed in Task 16.5 */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

struct fraction_st
{
	unsigned int numerator;
	unsigned int denominator;
};
/* Exercise 3.3.a: Set fraction
 * Parameters: numerator and denominator
 * Returns: pointer to allocated fraction
 */
Fraction* setFraction(unsigned int numerator, unsigned int denominator)
{
	Fraction * newFraction = malloc(sizeof(Fraction));
	newFraction -> numerator = numerator;
	newFraction -> denominator = denominator;
    return newFraction;
}

unsigned int getNum(const Fraction *f)
{
	return f->numerator;
}

unsigned int getDenom(const Fraction *f)
{
    return f->denominator;
}

void freeFraction(Fraction *f)
{
	free(f);
}

/* Exercise 3.3.b: Compare values
 * Parameters: two fractions to be compared
 * Returns:
 * -1 if a is smaller than b
 * 0 if the fractions are equal
 * 1 if a is larger than b
 */
int compFraction(const Fraction *a, const Fraction *b)
{
	float fraction1 = (float)(a->numerator)/(float)(a->denominator);
	float fraction2 = (float)(b->numerator)/(float)(b->denominator);
	if(fraction1 > fraction2)
		return 1;
	if(fraction1 < fraction2)
		return -1;		
	else
		return 0;

}

/* Exercise 3.3.c: Add values
 * Parameters: two fractions to be added
 * Returns: sum of the fractions
 */
Fraction* addFraction(const Fraction *a, const Fraction *b)
{
	Fraction * result = malloc(sizeof(Fraction));
	unsigned int newNumeA = a->numerator * b->denominator;
	unsigned int newDenomA = a->denominator * b->denominator;
	unsigned int newNumeB = b->numerator * a->denominator;
	//unsigned int newDenomB = b->denominator * a->denominator;
	result->numerator = newNumeA+newNumeB;
	result->denominator = newDenomA;
	
    return result;
}


/* Exercise 3.3.d: Multiply values
 * Parameters: two fractions to be multiplied
 * Returns: result of the operation
 */
Fraction* mulFraction(const Fraction *a, const Fraction *b)
{
	Fraction * result = malloc(sizeof(Fraction));
	result->numerator = a->numerator*b->numerator;
	result->denominator = a->denominator*b->denominator;
    return result;
}

/* Exercise 3.3.e: Reduce fraction
 * Parameters: Fraction to be reduced. Reduction happens on the object itself */
void reduceFraction(Fraction* val)
{
	unsigned int great = gcd(val->numerator, val->denominator);
	val->numerator = val->numerator/great;
	val->denominator = val->denominator/great;
}

int main()
{
    /* Hint: if you have implemented only part of the functions,
       add comments around those that you didn't yet implement.
       Feel free to modify this function as you wish. It is not checked
       by the tester.*/
    
    /* The below code uses function printFraction. Implementing it will not
     * gain you points, but will be useful for testing */
    
    /* testing exercise 3.3 */
    Fraction *a = setFraction(2,3);
    Fraction *b = setFraction(3,4);
	//printf("%d ", a->numerator);
	// printf("Result of comparison: %d\n", compFraction(a,b));
	Fraction *sum = addFraction(a, b);
	//printf("%d\n",sum -> numerator);   
	//printf("%d\n",sum -> denominator);
	
	Fraction *mul = mulFraction(a, b);
    //printf("%d\n",mul -> numerator);
	//printf("%d\n",mul -> denominator);
	
	printf("before n %d\n",mul -> numerator);
	printf("before d %d\n",mul -> denominator);
	reduceFraction(mul);
	printf("after n %d\n",mul -> numerator);
	printf("after d %d\n",mul -> denominator);
	
   // printf("\n");
    freeFraction(a);
    freeFraction(b);
	freeFraction(sum);
    freeFraction(mul);
	
}
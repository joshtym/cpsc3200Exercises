/*
 * Solution to UVA 10026 Shoemaker's Problem. This problem utilizes the fraction
 * class written by Darcy Best to ensure roundoff errors are a non-issue. Observe
 * that we use greedy to solve this by taking the ratio of Ti/Si where Ti day time
 * and Si is the penalty time. This ratio minimizes our cost and thus, by putting
 * these fractions in a multimap where the key is the ratio and the pair is the job
 * index, we are able to just print out the map element by element for our
 * answer
 *
 * Author : Joshua Tymburski
*/

//
// Fraction implementation
//
// Author: Darcy Best
//
// Does NOT ever check for division by 0.
// Division by 0 will only cause a runtime error if you use the
//   toDouble() function.
//

#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;

// Change this to whatever integer data type will prevent overflow
//   - BigInteger works with this class
typedef long long int dataType;

class Fraction{
public:
  Fraction(dataType num=0,dataType denom=1);
   
  double toDouble() const;
   
  void reduce();
   
  // Changes the fraction itself.
  void selfReciprocal();
   
  // Returns a new fraction, leaving the original.
  Fraction reciprocal() const;
   
  Fraction& operator+=(const Fraction& x);
  Fraction& operator-=(const Fraction& x);
  Fraction& operator*=(const Fraction& x);
  Fraction& operator/=(const Fraction& x);
   
  bool operator<(const Fraction& x) const;
  bool operator==(const Fraction& x) const;
   
  dataType num,denom;
};

Fraction operator+(const Fraction& x,const Fraction& y);
Fraction operator-(const Fraction& x,const Fraction& y);
Fraction operator*(const Fraction& x,const Fraction& y);
Fraction operator/(const Fraction& x,const Fraction& y);

istream& operator>>(istream& is,Fraction& x);
ostream& operator<<(ostream& os,const Fraction& x);

Fraction::Fraction(dataType n,dataType d){
  if(d < 0){
    num = -n;
    denom = -d;
  } else {
    num = n;
    denom = d;
  }
  reduce();
}

double Fraction::toDouble() const{
  return 1.0*num/denom;
}

// Howard's GCD function with no checks
dataType gcd(dataType a, dataType b)
{
  dataType r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void Fraction::reduce(){
  dataType g = gcd(abs(num),denom);
  num /= g;
  denom /= g;
}

void Fraction::selfReciprocal(){
  swap(num,denom);
  if (denom < 0) {
    num = -num;
    denom = -denom;
  }
}

Fraction Fraction::reciprocal() const{
  return Fraction(denom,num);
}

// Overflow potential in the denominator.
// I've tried to factor out as much as possible before,
//   But be careful.
//
//   (w)/(a*g) + (z)/(b*g)
// = (w*b)/(a*g*b) + (a*z)/(a*g*b)
// = (w*b + a*z)/(a*g*b)
Fraction& Fraction::operator+=(const Fraction& x){
  dataType g = gcd(denom,x.denom);
   
  dataType a = denom / g;
  dataType b = x.denom / g;
   
  num = num * b + x.num * a;
  denom *= b;
   
  reduce();
   
  return (*this);
}

Fraction& Fraction::operator-=(const Fraction& x){
  dataType g = gcd(denom,x.denom);
  dataType a = denom / g;
  dataType b = x.denom / g;
   
  num = num * b - x.num * a;
  denom *= b;
   
  reduce();
  return (*this);
}

Fraction& Fraction::operator*=(const Fraction& x){
  num *= x.num;
  denom *= x.denom;
  reduce();
  return (*this);
}

Fraction& Fraction::operator/=(const Fraction& x){
  num *= x.denom;
  denom *= x.num;
   
  if(denom < 0){
    num = -num;
    denom = -denom;
  }
  reduce();
  return (*this);
}

// Careful with overflow. If it is an issue, you can compare the
// double values, but you SHOULD check for equality BEFORE converting
bool Fraction::operator<(const Fraction& x) const{
  return (num*x.denom) < (x.num*denom);
}

bool Fraction::operator==(const Fraction& x) const{
  return (num == x.num) && (denom == x.denom);
}

Fraction operator+(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a += y;
  return a;
}

Fraction operator-(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a -= y;
  return a;
}

Fraction operator*(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a *= y;
  return a;
}

Fraction operator/(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a /= y;
  return a;
}

int main(int argc, char** argv)
{
   int testCases;
   std::cin >> testCases;

   for (int i = 0; i < testCases; ++i)
   {
      /*
       * Not much to say. Pretty self explanatory. Every
       * job's ratio of Ti/Si is inserted in a multimap
       * as a pair and printed to standards
      */
      std::multimap<Fraction, int> ratios;
      int jobs;
      std::cin >> jobs;
      for (int j = 0; j < jobs; ++j)
      {
         int jobTime;
         int jobFine;
         std::cin >> jobTime;
         std::cin >> jobFine;
         Fraction ratio(jobTime, jobFine);;
         ratios.insert(std::pair<Fraction, int>(ratio, j + 1));
      }

      for (std::map<Fraction, int>::iterator it = ratios.begin(); it != ratios.end(); ++it)
      {
         if (it != --ratios.end())
            std::cout << it->second << " ";
         else
            std::cout << it->second << std::endl;
      }

      if (i != testCases - 1)
         std::cout << std::endl;
   }

   return 0;
}
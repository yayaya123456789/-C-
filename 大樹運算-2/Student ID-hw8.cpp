#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

// HugeInt struct definition
struct HugeInt
{
   int size = 1; // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ](); // used to store a nonnegative integer
}; // end struct HugeInt

// perform addition, subtraction, multiplication and division;
// display the sum, difference, product, quotient and remainder on the output window
void perform( const HugeInt &hugeInt1, const HugeInt &hugeInt2,
                    HugeInt &hugeInt3, HugeInt &hugeInt4 );

// perform addition, subtraction, multiplication and division;
// write the sum, difference, product, quotient and remainder into a file
void perform( ofstream &outFile, const HugeInt &hugeInt1, const HugeInt &hugeInt2,
                                       HugeInt &hugeInt3, HugeInt &hugeInt4 );

// display the specified huge integer on the output window
void output( const HugeInt &hugeInt );

// return true if and only if hugeInt.size == 1 && hugeInt.elems[ 0 ] == 0
bool isZero( const HugeInt &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( const HugeInt &hugeInt1, const HugeInt &hugeInt2 );

// a recursive function;
// return true if and only if hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( const HugeInt &hugeInt1, const HugeInt &hugeInt2, int last );

// return true if and only if hugeInt1 < hugeInt2
bool less( const HugeInt &hugeInt1, const HugeInt &hugeInt2 );

// a recursive function;
// return true if and only if hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( const HugeInt &hugeInt1, const HugeInt &hugeInt2, int last );

// sum = addend + adder
void addition( const HugeInt &addend, const HugeInt &adder, HugeInt &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( const HugeInt &minuend, const HugeInt &subtrahend,
                        HugeInt &difference );

// product = multiplicand * multiplier
void multiplication( const HugeInt &multiplicand, const HugeInt &multiplier,
                           HugeInt &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( const HugeInt &dividend, const HugeInt &divisor,
                     HugeInt &quotient, HugeInt &remainder );

// set hugeInt.size = 1 && allocate 4 bytes for hugeInt.elems
void reset( HugeInt &hugeInt );

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt );

// hugeInt1 = hugeInt2; assignment
void assign( HugeInt &hugeInt1, const HugeInt &hugeInt2 );

const int numTestCases = 400; // number of test cases

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "HugeIntegers.dat", ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Results.dat", ios::out | ios::binary );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   HugeInt hugeInt1;
   HugeInt hugeInt2;
   HugeInt hugeInt3;
   HugeInt hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      inFile.read( reinterpret_cast< char * >( &hugeInt1.size ), 4 );
      delete [] hugeInt1.elems;
      hugeInt1.elems = new int[ hugeInt1.size ];
      inFile.read( reinterpret_cast< char * >( hugeInt1.elems ), 4 * hugeInt1.size );

      inFile.read( reinterpret_cast< char * >( &hugeInt2.size ), 4 );
      delete [] hugeInt2.elems;
      hugeInt2.elems = new int[ hugeInt2.size ];
      inFile.read( reinterpret_cast< char * >( hugeInt2.elems ), 4 * hugeInt2.size );

      perform( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      reset( hugeInt1 );
      reset( hugeInt2 );
   }

   delete [] hugeInt1.elems;
   delete [] hugeInt2.elems;
   delete [] hugeInt3.elems;
   delete [] hugeInt4.elems;

   inFile.close();
   outFile.close();

   system( "pause" );
}

// perform addition, subtraction, multiplication and division
void perform( const HugeInt &hugeInt1, const HugeInt &hugeInt2,
                    HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   output( hugeInt1 );
   output( hugeInt2 );

   addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   output( hugeInt3 );
   reset( hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
   {
      cout << '-';
      subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      output( hugeInt3 );
   }
   else
   {
      subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      output( hugeInt3 );
   }
   reset( hugeInt3 );

   multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   output( hugeInt3 );
   reset( hugeInt3 );

   // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
   division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
   output( hugeInt3 );
   output( hugeInt4 );
   reset( hugeInt3 );
   reset( hugeInt4 );

   cout << endl;
}

// perform addition, subtraction, multiplication and division
void perform( ofstream &outFile, const HugeInt &hugeInt1, const HugeInt &hugeInt2,
                                       HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   outFile.write( reinterpret_cast< const char * >( &hugeInt1.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt1.elems ), 4 * hugeInt1.size );

   outFile.write( reinterpret_cast< const char * >( &hugeInt2.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt2.elems ), 4 * hugeInt2.size );

   addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   outFile.write( reinterpret_cast< const char * >( &hugeInt3.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt3.elems ), 4 * hugeInt3.size );
   reset( hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
      subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
   else
      subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
   outFile.write( reinterpret_cast< const char * >( &hugeInt3.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt3.elems ), 4 * hugeInt3.size );
   reset( hugeInt3 );

   multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   outFile.write( reinterpret_cast< const char * >( &hugeInt3.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt3.elems ), 4 * hugeInt3.size );
   reset( hugeInt3 );

   // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
   division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
   outFile.write( reinterpret_cast< const char * >( &hugeInt3.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt3.elems ), 4 * hugeInt3.size );
   outFile.write( reinterpret_cast< const char * >( &hugeInt4.size ), 4 );
   outFile.write( reinterpret_cast< const char * >( hugeInt4.elems ), 4 * hugeInt4.size );
   reset( hugeInt3 );
   reset( hugeInt4 );
}

// output the specified huge integer
void output( const HugeInt &hugeInt )
{
   if( isZero( hugeInt ) )
      cout << 0;
   else
      for( int i = hugeInt.size - 1; i >= 0; i-- )
         if( hugeInt.elems[ i ] < 10 )
            cout << hugeInt.elems[ i ];
   cout << endl;
} // end function output

// test if a HugeInt is zero
bool isZero( const HugeInt &hugeInt )
{
   if( hugeInt.size == 1 && hugeInt.elems[ 0 ] == 0 )
      return true;
   return false;
} // end function isZero

// return true if and only if hugeInt1 == hugeInt2
bool equal( const HugeInt &hugeInt1, const HugeInt &hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, hugeInt1.size - 1 );
} // end function equal

// a recursive function;
// return ( hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ] )
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( const HugeInt &hugeInt1, const HugeInt &hugeInt2, int last )
{

} // end function recursiveEqual

// return true if and only if hugeInt1 < hugeInt2
bool less( const HugeInt &hugeInt1, const HugeInt &hugeInt2 )
{
   if( hugeInt1.size < hugeInt2.size )
      return true;

   if( hugeInt1.size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, hugeInt1.size - 1 );
} // end function less

// a recursive function;
// return ( hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ] )
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( const HugeInt &hugeInt1, const HugeInt &hugeInt2, int last )
{

} // end function recursiveLess

// sum = addend + adder
void addition( const HugeInt &addend, const HugeInt &adder, HugeInt &sum )
{
   sum.size = ( addend.size >= adder.size ) ? addend.size + 1 : adder.size + 1;

   delete [] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < addend.size; i++ )
      sum.elems[ i ] = addend.elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   for( int i = 0; i < sum.size - 1; i++ )
      if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.elems[ i ] -= 10; // reduce to 0-9
         sum.elems[ i + 1 ]++;
      }

   if( sum.elems[ sum.size - 1 ] == 0 )
      sum.size--;
} // end function addition

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( const HugeInt &minuend, const HugeInt &subtrahend,
                        HugeInt &difference )
{

} // end function subtraction

// product = multiplicand * multiplier
void multiplication( const HugeInt &multiplicand, const HugeInt &multiplier,
                           HugeInt &product )
{

} // end function multiplication

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( const HugeInt &dividend, const HugeInt &divisor,
                     HugeInt &quotient, HugeInt &remainder )
{

} // end function division

// hugeInt1 = hugeInt2; assignment
void assign( HugeInt &hugeInt1, const HugeInt &hugeInt2 )
{
   hugeInt1.size = hugeInt2.size;
   delete[] hugeInt1.elems;
   hugeInt1.elems = new int[ hugeInt1.size ];
   for( int i = 0; i < hugeInt1.size; i++ )
      hugeInt1.elems[ i ] = hugeInt2.elems[ i ];
}

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < hugeInt.size; i++ )
         hugeInt.elems[ i - 1 ] = hugeInt.elems[ i ];
      hugeInt.elems[ hugeInt.size - 1 ] = 0;
      hugeInt.size--;
   }
} // end function divideByTen

// set hugeInt.size = 1 && allocate 4 bytes for hugeInt.elems
void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ 1 ]();
}
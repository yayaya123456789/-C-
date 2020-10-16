#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

struct Date
{
	int year;
	int month;
   int day;
};

struct AvailableRooms
{
   Date date;
   int availableRooms[ 6 ]; // number of available rooms
   // availRooms[ 0 ]: not used
   // availRooms[ 1 ]: the number of available superior rooms
   // availRooms[ 2 ]: the number of available deluxe rooms
   // availRooms[ 3 ]: the number of available deluxe twin rooms
   // availRooms[ 4 ]: the number of available superior suites
   // availRooms[ 5 ]: the number of available deluxe suites
};

int numRooms[ 6 ] = { 0, 9, 5, 3, 5, 4 };
int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void computeCurrentDate( Date &currentDate );

void loadAvailableRooms( AvailableRooms availableRooms[], int &numRecords );

void initializeAvailableRooms( AvailableRooms availableRooms[], Date currentDate, int &numRecords );

void adjustAvailableRooms( AvailableRooms availableRooms[], Date currentDate, int &numRecords );

// returns a value of 0, -1 or 1 if date1 is equal to, less than or greater than date2, respectively.
int compareDates( Date date1, Date date2 );

void saveAvailableRooms( AvailableRooms availableRooms[], int numRecords );

int main()
{
   Date currentDate = {};

	computeCurrentDate( currentDate );

   AvailableRooms availableRooms[ 184 ] = {}; // availableRooms[ 0 ] is not used
   int numRecords = 0;

	loadAvailableRooms( availableRooms, numRecords );

   // the last available date < currentDate
   if( numRecords == 0 || compareDates( availableRooms[ numRecords ].date, currentDate ) == -1 )
      initializeAvailableRooms( availableRooms, currentDate, numRecords );
   else // the first available date < currentDate <= the last available date
      if( compareDates( availableRooms[ 1 ].date, currentDate ) == -1 )
      adjustAvailableRooms( availableRooms, currentDate, numRecords );

   cout << "The number of available rooms of each room type:\n\n";
   cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";
   for( int i = 1; i <= numRecords; i++ )
      cout << availableRooms[ i ].date.year << "-"
           << setw( 2 ) << setfill( '0' ) << availableRooms[ i ].date.month << "-"
           << setw( 2 ) << availableRooms[ i ].date.day
           << setw( 16 ) << setfill( ' ' ) << availableRooms[ i ].availableRooms[ 1 ]
           << setw( 14 ) << availableRooms[ i ].availableRooms[ 2 ]
           << setw( 19 ) << availableRooms[ i ].availableRooms[ 3 ]
           << setw( 17 ) << availableRooms[ i ].availableRooms[ 4 ]
           << setw( 15 ) << availableRooms[ i ].availableRooms[ 5 ] << "\n";

   saveAvailableRooms( availableRooms, numRecords );

   system( "pause" );
}

void computeCurrentDate( Date &currentDate )
{

}

void loadAvailableRooms( AvailableRooms availableRooms[], int &numRecords )
{

}

void initializeAvailableRooms( AvailableRooms availableRooms[], Date currentDate, int &numRecords )
{

}

void adjustAvailableRooms( AvailableRooms availableRooms[], Date currentDate, int &numRecords )
{

}

int compareDates( Date date1, Date date2 )
{
   if( date1.year > date2.year )
      return 1;
   if( date1.year < date2.year )
      return -1;

   if( date1.month > date2.month )
      return 1;
   if( date1.month < date2.month )
      return -1;

   if( date1.day > date2.day )
      return 1;
   if( date1.day < date2.day )
      return -1;

   return 0;
}

void saveAvailableRooms( AvailableRooms availableRooms[], int numRecords )
{

}
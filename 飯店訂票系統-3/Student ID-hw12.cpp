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

struct ReservationInfo
{
   char id[ 12 ];
   char name[ 12 ];
   char mobile[ 12 ];
   int roomType; // 1: superior rooms, 2: deluxe rooms, 3: deluxe twin rooms,
                 // 4: superior suites, 5: deluxe suites
   int numRooms; // number of rooms reserved
   Date checkInDate;
   Date checkOutDate;
};

struct AvailableRooms
{
   Date date;
   int availableRooms[ 6 ]; // number of available rooms
   // availableRooms[ 0 ]: not used
   // availableRooms[ 1 ]: the number of available superior rooms
   // availableRooms[ 2 ]: the number of available deluxe rooms
   // availableRooms[ 3 ]: the number of available deluxe twin rooms
   // availableRooms[ 4 ]: the number of available superior suites
   // availableRooms[ 5 ]: the number of available deluxe suites
};

int roomRate[ 6 ] = { 0, 5390, 6270, 6270, 6820, 8470 }; // room rate per night for each room type
int numRooms[ 6 ] = { 0, 9, 5, 3, 5, 4 }; // total number of rooms for each type
char roomTypeName[ 6 ][ 20 ] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
                                     "Superior Suite", "Deluxe Suite" };
int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // number of days in each month

int enterChoice();

void makeReservation();

// put the current date into currentDate
void computeCurrentDate( Date &currentDate );

// input check in date and check out date by user, and put them into checkInDate and checkOutDate, respectively.
void inputDates( const Date &currentDate, Date &checkInDate, Date &checkOutDate );

// load all available rooms information from the file Available Rooms.dat
void loadAvailableRooms( AvailableRooms availableRooms[], int &numRecords );

// returns a value of 0, -1 or 1 if date1 is equal to, less than or greater than date2, respectively.
int compareDates( const Date &date1, const Date &date2 );

void initializeAvailableRooms( AvailableRooms availableRooms[], const Date &currentDate, int &numRecords );

void adjustAvailableRooms( AvailableRooms availableRooms[], const Date &currentDate, int &numRecords );

// minNumRooms[ k ] = the minimum between availableRooms[ begin .. end - 1 ].availableRooms[ k ], k = 1, ..., 5,
// where availableRooms[ begin ].date == checkInDate and availableRooms[ end ].date, checkOutDate.
int compMinNumRooms( const Date &checkInDate, const Date &checkOutDate,
                     AvailableRooms availableRooms[], int numRecords, int minNumRooms[] );

// return the minimum between availableRooms[ begin .. end - 1 ].availableRooms[ roomType ],
// where availableRooms[ begin ].date == checkInDate and availableRooms[ end ].date, checkOutDate.
int compMinNumRooms( const Date &checkInDate, const Date &checkOutDate,
                     AvailableRooms availableRooms[], int numRecords, int roomType );

void display( const AvailableRooms &availableRoom );

// return true if and only if id is a legal ID card number
bool legal( char id[] );

void display( const ReservationInfo &reservation, time_t numNights );

// save reservation into the end of the file Reservations.dat
void saveReservationInfo( const ReservationInfo &reservation );

// save all available rooms information into the file Available Rooms.dat
void saveAvailableRooms( AvailableRooms availableRooms[], const int numRecords );
void reservationInquiry();

int main()
{
   cout << "Evergreen Laurel Hotel Online Reservation System\n";

   int choice;

   while( ( choice = enterChoice() ) != 3 )
   {
      switch( choice )
      {
      case 1:
         makeReservation(); // Making Reservation
         break;
      case 2:
         reservationInquiry(); // Reservation Inquiry
         break;
      default:
         cerr << "\nInput Error!" << endl;
      }
   }

   cout << endl;

   system( "pause" );
}

int enterChoice()
{
   cout << "\nInput your choice¡G\n"
        << "1. Making Reservation\n"
        << "2. Reservation Inquiry\n"
        << "3. end program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}

void makeReservation()
{

}

void computeCurrentDate( Date &currentDate )
{

}

void inputDates( const Date &currentDate, Date &checkInDate, Date &checkOutDate )
{

}

void loadAvailableRooms( AvailableRooms availableRooms[], int &numRecords )
{

}

int compareDates( const Date &date1, const Date &date2 )
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

void initializeAvailableRooms( AvailableRooms availableRooms[], const Date &currentDate, int &numRecords )
{

}

void adjustAvailableRooms( AvailableRooms availableRooms[], const Date &currentDate, int &numRecords )
{

}

int compMinNumRooms( const Date &checkInDate, const Date &checkOutDate,
                     AvailableRooms availableRooms[], int numRecords, int minNumRooms[] )
{
   int minMax = 0;
   for( int i = 1; i <= 5; i++ )
   {
      minNumRooms[ i ] = compMinNumRooms( checkInDate, checkOutDate, availableRooms, numRecords, i );
      if( minMax < minNumRooms[ i ] )
          minMax = minNumRooms[ i ];
   }

   return minMax;
}

int compMinNumRooms( const Date &checkInDate, const Date &checkOutDate,
                     AvailableRooms availableRooms[], int numRecords, int roomType )
{

}

void display( const AvailableRooms &availableRoom )
{
   cout << availableRoom.date.year << "-"
        << setw( 2 ) << setfill( '0' ) << availableRoom.date.month << "-"
        << setw( 2 ) << availableRoom.date.day
        << setw( 16 ) << setfill( ' ' ) << availableRoom.availableRooms[ 1 ]
        << setw( 14 ) << availableRoom.availableRooms[ 2 ]
        << setw( 19 ) << availableRoom.availableRooms[ 3 ]
        << setw( 17 ) << availableRoom.availableRooms[ 4 ]
        << setw( 15 ) << availableRoom.availableRooms[ 5 ] << endl;
}

bool legal( char id[] )
{

}

void display( const ReservationInfo &reservation, time_t numNights )
{
   cout << setw( 8 ) << setfill( ' ' ) << reservation.name
        << setw( 7 ) << reservation.numRooms * roomRate[ reservation.roomType ] * numNights
        << setw( 13 ) << reservation.mobile
        << setw( 19 ) << roomTypeName[ reservation.roomType ]
        << setw( 18 ) << reservation.numRooms
        << setw( 10 ) << reservation.checkInDate.year << "-"
        << setw( 2 ) << setfill( '0' ) << reservation.checkInDate.month << "-"
        << setw( 2 ) << reservation.checkInDate.day
        << setw( 11 ) << setfill( ' ' ) << reservation.checkOutDate.year << "-"
        << setw( 2 ) << setfill( '0' ) << reservation.checkOutDate.month << "-"
        << setw( 2 ) << reservation.checkOutDate.day << endl;
}

void saveReservationInfo( const ReservationInfo &reservation )
{

}

void saveAvailableRooms( AvailableRooms availableRooms[], const int numRecords )
{

}

void reservationInquiry()
{

}
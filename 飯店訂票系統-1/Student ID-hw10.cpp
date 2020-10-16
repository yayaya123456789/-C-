#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct AvailableRooms
{
   char date[ 12 ];
   unsigned int singleDayAvailRooms[ 6 ];
   // singleDayAvailRooms[0]: not used
   // singleDayAvailRooms[1]: the number of available superior rooms
   // singleDayAvailRooms[2]: the number of available deluxe rooms
   // singleDayAvailRooms[3]: the number of available deluxe twin rooms
   // singleDayAvailRooms[4]: the number of available superior suites
   // singleDayAvailRooms[5]: the number of available deluxe suites
};

void loadFromFile( AvailableRooms availableRooms[], int &numRecords );
void makeReservation( AvailableRooms availableRooms[], int numRecords );
void saveToFile( AvailableRooms availableRooms[], int numRecords );

int main()
{
   AvailableRooms availableRooms[ 200 ] = { { "", 0, 0, 0, 0, 0 } };

   int numRecords;

   loadFromFile( availableRooms, numRecords ); // read all records of the file availableRooms.dat,
                                               // put them into the array availableRooms, and
                                               // disply them on the screen

   makeReservation( availableRooms, numRecords ); // make a room reservation; the numbers of available rooms
                                                  // of the reserved room type and dates shoule be adjust

   saveToFile( availableRooms, numRecords ); // save the modified available rooms information into the file availableRooms.dat

   loadFromFile( availableRooms, numRecords );

   system( "pause" );
}

void loadFromFile( AvailableRooms availableRooms[], int &numRecords )
{

}

void makeReservation( AvailableRooms availableRooms[], int numRecords )
{

}

void saveToFile( AvailableRooms availableRooms[], int numRecords )
{

}
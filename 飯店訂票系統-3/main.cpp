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
	char id[12];
	char name[12];
	char mobile[12];
	int roomType; // 1: superior rooms, 2: deluxe rooms, 3: deluxe twin rooms,
				  // 4: superior suites, 5: deluxe suites
	int numRooms; // number of rooms reserved
	Date checkInDate;
	Date checkOutDate;
};

struct AvailableRooms
{
	Date date;
	int availableRooms[6]; // number of available rooms
	// availableRooms[ 0 ]: not used
	// availableRooms[ 1 ]: the number of available superior rooms
	// availableRooms[ 2 ]: the number of available deluxe rooms
	// availableRooms[ 3 ]: the number of available deluxe twin rooms
	// availableRooms[ 4 ]: the number of available superior suites
	// availableRooms[ 5 ]: the number of available deluxe suites
};

int roomRate[6] = { 0, 5390, 6270, 6270, 6820, 8470 }; // room rate per night for each room type
int numRooms[6] = { 0, 9, 5, 3, 5, 4 }; // total number of rooms for each type
char roomTypeName[6][20] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
									 "Superior Suite", "Deluxe Suite" };
int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // number of days in each month

int enterChoice();

void makeReservation();

// put the current date into currentDate
void computeCurrentDate(Date &currentDate);

// input check in date and check out date by user, and put them into checkInDate and checkOutDate, respectively.
void inputDates(const Date &currentDate, Date &checkInDate, Date &checkOutDate);

// load all available rooms information from the file Available Rooms.dat
void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords);

// returns a value of 0, -1 or 1 if date1 is equal to, less than or greater than date2, respectively.
int compareDates(const Date &date1, const Date &date2);

void initializeAvailableRooms(AvailableRooms availableRooms[], const Date &currentDate, int &numRecords);

void adjustAvailableRooms(AvailableRooms availableRooms[], const Date &currentDate, int &numRecords);

// minNumRooms[ k ] = the minimum between availableRooms[ begin .. end - 1 ].availableRooms[ k ], k = 1, ..., 5,
// where availableRooms[ begin ].date == checkInDate and availableRooms[ end ].date, checkOutDate.
int compMinNumRooms(const Date &checkInDate, const Date &checkOutDate,
	AvailableRooms availableRooms[], int numRecords, int minNumRooms[]);

// return the minimum between availableRooms[ begin .. end - 1 ].availableRooms[ roomType ],
// where availableRooms[ begin ].date == checkInDate and availableRooms[ end ].date, checkOutDate.
int compMinNumRooms(const Date &checkInDate, const Date &checkOutDate,
	AvailableRooms availableRooms[], int numRecords, int roomType);

void display(const AvailableRooms &availableRoom);

//put customer data inside
void Customer(int &rooType, int &numofrooms, char id[], char name[], char mobile[], int minNumRooms[],
	const Date &checkInDate, const Date &checkOutDate, int numRecords, AvailableRooms availableRooms[], int &nights);

// return true if and only if id is a legal ID card number
bool legal(char id[]);

void display(const ReservationInfo &reservation, time_t numNights);

// save reservation into the end of the file Reservations.dat
void saveReservationInfo(const ReservationInfo &reservation);

// save all available rooms information into the file Available Rooms.dat
void saveAvailableRooms(AvailableRooms availableRooms[], const int numRecords);
void reservationInquiry();

int main()
{
	cout << "Evergreen Laurel Hotel Online Reservation System\n";

	int choice;

	while ((choice = enterChoice()) != 3)
	{
		switch (choice)
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

	system("pause");
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
	Date currentDate;
	ReservationInfo	CustomerData;
	AvailableRooms availableRooms[300];
	int numRecords = 0, minNumRooms[6], minMax = 0, nights = 0;

	computeCurrentDate(currentDate);
	loadAvailableRooms(availableRooms, numRecords)

	if (numRecords == 0 || compareDates(availableRooms[numRecords].date, currentDate) == -1)
		initializeAvailableRooms(availableRooms, currentDate, numRecords);
	else
		if (compareDates(availableRooms[1].date, currentDate) == -1)
			adjustAvailableRooms(availableRooms, currentDate, numRecords);

	inputDates(currentDate, CustomerData.checkInDate, CustomerData.checkOutDate);
	if (CustomerData.checkInDate.month == availableRooms[numRecords].date.month &&
		CustomerData.checkInDate.day == availableRooms[numRecords].date.day)
	{
		return;
	}
	else
	{
		minMax = compMinNumRooms(CustomerData.checkInDate, CustomerData.checkOutDate, availableRooms, numRecords, minNumRooms);
		if (minMax > 0)
		{
			compMinNumRooms(CustomerData.checkInDate, CustomerData.checkOutDate, availableRooms, numRecords, 6);

			Customer(CustomerData.roomType, CustomerData.numRooms, CustomerData.id, CustomerData.name,
				CustomerData.mobile, minNumRooms, CustomerData.checkInDate, CustomerData.checkOutDate, numRecords, availableRooms, nights);

			if (CustomerData.roomType == 6)
				return;

			display(CustomerData, nights);
			saveReservationInfo(CustomerData);
			saveAvailableRooms(availableRooms, numRecords);
		}
		else
			cout << "There are no rooms available!" << endl;
	}
}

void computeCurrentDate(Date &currentDate)
{
	time_t t;
	time(&t);
	tm now;
	localtime_s(&now, &t);
	currentDate.year = now.tm_year + 1900;
	currentDate.month = now.tm_mon + 1;
	currentDate.day = now.tm_mday;
}

void inputDates(const Date &currentDate, Date &checkInDate, Date &checkOutDate)
{
	if ((currentDate.year % 4 == 0 && currentDate.year % 100 != 0) || (currentDate.year % 400 == 0 && currentDate.year % 3200 != 0))
	{
		days[2] = 29;
	}
	int answer[6][2], userans = 0, compare = 0, pass = 0, useroutans = 0, check = 0;
	Date currentDatespace;
	currentDatespace = currentDate;
	for (int i = 0; i < 6; i++)
	{
		answer[i][0] = currentDatespace.year;
		answer[i][1] = currentDatespace.month;
		if (currentDatespace.month == 12)
		{
			currentDatespace.year++;
			currentDatespace.month = 1;
		}
		else
		{
			currentDatespace.month++;
		}
	}
	while (userans < 1 || userans >6)
	{
		cout << "Please Input Check In Date" << endl << endl;
		cout << "Month" << endl;

		for (int i = 0; i < 6; i++)
		{
			cout << i + 1 << '.' << answer[i][0] << '-' << setw(2) << setfill('0') << answer[i][1] << endl;
		}
		cout << '?';
		cin >> userans;
		cout << endl;
	}

	checkInDate.year = answer[userans - 1][0];
	checkInDate.month = answer[userans - 1][1];
	checkInDate.day = 0;


	if (compareDates(currentDate, checkInDate) == -1)
	{
		checkInDate.day = 0;
		while (checkInDate.day < 1 || checkInDate.day > days[checkInDate.month])
		{
			cout << "Day" << ' ' << '(' << '1' << " ~ " << days[checkInDate.month] << ')' << " :";
			cin >> checkInDate.day;
		}
	}
	else
	{
		checkInDate.day = currentDatespace.day;
		while (checkInDate.day - 1 < currentDatespace.day || checkInDate.day > days[checkInDate.month])
		{
			cout << "Day" << ' ' << '(' << currentDate.day << " ~ " << days[checkInDate.month] << ')' << " :";
			cin >> checkInDate.day;
			if (checkInDate.day == currentDate.day)
				break;
			cout << endl;
		}
	}
	cout << endl;
	useroutans = 0;
	currentDatespace = currentDate;
	if (checkInDate.day == days[checkInDate.month])
	{
		if (userans == 6)
		{
			cout << "There is no room !!!" << endl << endl;;
			return;
		}
		userans++;
	}
	for (int i = userans; i < 7; i++)
	{
		answer[check][0] = answer[i - 1][0];
		answer[check][1] = answer[i - 1][1];
		check++;
	}
	while (useroutans < 1 || useroutans > check)
	{
		cout << "Please Input Check Out Date" << endl << endl;
		cout << "Month " << ':' << endl;
		for (int i = 0; i < check; i++)
		{
			cout << i + 1 << '.' << answer[i][0] << '-' << setw(2) << setfill('0') << answer[i][1] << endl;
		}
		cout << '?';
		cin >> useroutans;
		cout << endl;
	}

	checkOutDate.year = answer[useroutans - 1][0];
	checkOutDate.month = answer[useroutans - 1][1];
	if (checkOutDate.month == checkInDate.month)
	{
		checkOutDate.day = checkInDate.day + 1;
		while (checkOutDate.day - 1 < checkInDate.day + 1 || checkOutDate.day > days[checkOutDate.month])
		{
			cout << "Day" << ' ' << '(' << checkInDate.day + 1 << " ~ " << days[checkInDate.month] << ')' << " :";
			cin >> checkOutDate.day;
			if (checkOutDate.day == checkInDate.day + 1)
				break;
		}
		cout << endl;
	}
	else
	{
		checkOutDate.day = 0;
		while (checkOutDate.day<1 || checkOutDate.day>days[checkOutDate.month])
		{
			cout << "Day" << ' ' << '(' << '1' << " ~ " << days[checkOutDate.month] << ')' << " :";
			cin >> checkOutDate.day;
		}
		cout << endl;
	}
	cout << "Check in date: " << checkInDate.year << '-';
	cout << setw(2) << setfill('0') << checkInDate.month << '-';
	cout << setw(2) << setfill('0') << checkInDate.day << endl;
	cout << "Check out date: " << checkOutDate.year << '-';
	cout << setw(2) << setfill('0') << checkOutDate.month << '-';
	cout << setw(2) << setfill('0') << checkOutDate.day << endl;
	cout << endl;
}

void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords)
{
	ifstream infile("Available Rooms.dat", ios::binary | ios::in);
	int i = 1;
	while (infile.read(reinterpret_cast<char*>(&availableRooms[i]), sizeof(AvailableRooms)))
	{
		i++;
		numRecords++;
	}
}

int compareDates(const Date &date1, const Date &date2)
{
	if (date1.year > date2.year)
		return 1;
	if (date1.year < date2.year)
		return -1;

	if (date1.month > date2.month)
		return 1;
	if (date1.month < date2.month)
		return -1;

	if (date1.day > date2.day)
		return 1;
	if (date1.day < date2.day)
		return -1;

	return 0;
}

void initializeAvailableRooms(AvailableRooms availableRooms[], const Date &currentDate, int &numRecords)
{
	if ((currentDate.year % 4 == 0 && currentDate.year % 100 != 0) || (currentDate.year % 400 == 0 && currentDate.year % 3200 != 0))
	{
		days[2] = 29;
	}
	int count = 0;
	Date currentDateSpace;
	currentDateSpace = currentDate;
	availableRooms[1].date = currentDate;
	for (int i = 2; i < 200; i++)
	{
		if ((availableRooms[i - 1].date.day < days[availableRooms[i - 1].date.month]))
		{
			availableRooms[i].date.year = availableRooms[i - 1].date.year;
			availableRooms[i].date.month = availableRooms[i - 1].date.month;
			availableRooms[i].date.day = availableRooms[i - 1].date.day + 1;
		}
		else
		{
			count++;
			if (count == 6)
			{
				numRecords = i - 1;
				break;
			}
			if (currentDateSpace.month == 12)
			{
				currentDateSpace.year += 1;
				currentDateSpace.month = 1;
				currentDateSpace.day = 1;
			}
			else
			{
				currentDateSpace.day = 1;
				currentDateSpace.month += 1;
			}
			availableRooms[i].date = currentDateSpace;
		}
	}
	for (int i = 1; i <= numRecords; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			availableRooms[i].availableRooms[j] = numRooms[j];
		}
	}
}

void adjustAvailableRooms(AvailableRooms availableRooms[], const Date &currentDate, int &numRecords)
{
	if ((currentDate.year % 4 == 0 && currentDate.year % 100 != 0) || (currentDate.year % 400 == 0 && currentDate.year % 3200 != 0))
	{
		days[2] = 29;
	}
	int count = 0, pos = 0, savpos = 0, hold = 0, check = 0;
	Date currentDate_space;
	currentDate_space = currentDate;

	while ((compareDates(availableRooms[pos].date, currentDate_space) != 0))
		pos++;
	for (int i = 1; i <= numRecords; i++)
	{
		if (i + pos - 1 <= numRecords)
		{
			availableRooms[i] = availableRooms[i + pos - 1];
		}
		else
		{
			savpos = i;
			break;
		}
	}
	for (int i = 1; i < savpos; i++)
	{
		if (availableRooms[i].date.day <= days[availableRooms[i].date.month] - 1)
			continue;
		else
			count++;
	}
	currentDate_space = availableRooms[savpos - 1].date;
	if (count < 6)
	{
		hold = 6 - count;
		numRecords = savpos - 1;
		for (int i = 0; i < hold; i++)
		{
			numRecords += days[availableRooms[savpos - 1].date.month + 1 + i];
		}
		for (int i = savpos; i <= numRecords; i++)
		{
			if (availableRooms[i - 1].date.day <= days[availableRooms[i - 1].date.month] - 1)
			{
				availableRooms[i].date.year = availableRooms[i - 1].date.year;
				availableRooms[i].date.month = availableRooms[i - 1].date.month;
				availableRooms[i].date.day = availableRooms[i - 1].date.day + 1;
			}
			else
			{
				if (currentDate_space.month == 12)
				{
					currentDate_space.year += 1;
					currentDate_space.month = 1;
					currentDate_space.day = 1;
				}
				else
				{
					currentDate_space.day = 1;
					currentDate_space.month += 1;
				}
				availableRooms[i].date = currentDate_space;
			}
		}
		for (int i = savpos; i <= numRecords; i++)
		{
			for (int j = 1; j < 6; j++)
			{
				availableRooms[i].availableRooms[j] = numRooms[j];
			}
		}
	}
	else
	{
		numRecords = savpos - 1;
	}
}
int compMinNumRooms(const Date &checkInDate, const Date &checkOutDate,
	AvailableRooms availableRooms[], int numRecords, int minNumRooms[])
{
	int minMax = 0;
	for (int i = 1; i <= 5; i++)
	{
		minNumRooms[i] = compMinNumRooms(checkInDate, checkOutDate, availableRooms, numRecords, i);
		if (minMax < minNumRooms[i])
			minMax = minNumRooms[i];
	}

	return minMax;
}

int compMinNumRooms(const Date &checkInDate, const Date &checkOutDate,
	AvailableRooms availableRooms[], int numRecords, int roomType)
{
	int Inpos = 1, Outpos = 1, check = 0;
	while (compareDates(checkInDate, availableRooms[Inpos].date) != 0)
		Inpos++;
	while (compareDates(checkOutDate, availableRooms[Outpos].date) != 0)
		Outpos++;

	check = availableRooms[Inpos].availableRooms[roomType];
	for (int i = Inpos; i < Outpos; i++)
	{
		if (check > availableRooms[i].availableRooms[roomType])
		{
			check = availableRooms[i].availableRooms[roomType];
		}
	}
	if (roomType == 6)
	{
		cout << "The number of available rooms of each room type:\n\n";
		cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";
		for (int i = Inpos; i < Outpos; i++)
		{
			display(availableRooms[i]);
		}
		cout << endl;
	}

	return check;
}

void display(const AvailableRooms &availableRoom)
{
	cout << availableRoom.date.year << "-"
		<< setw(2) << setfill('0') << availableRoom.date.month << "-"
		<< setw(2) << availableRoom.date.day
		<< setw(16) << setfill(' ') << availableRoom.availableRooms[1]
		<< setw(14) << availableRoom.availableRooms[2]
		<< setw(19) << availableRoom.availableRooms[3]
		<< setw(17) << availableRoom.availableRooms[4]
		<< setw(15) << availableRoom.availableRooms[5] << endl;
}

void Customer(int &roomType, int &numofrooms, char id[], char name[], char mobile[], int minNumRooms[],
	const Date &checkInDate, const Date &checkOutDate, int numRecords, AvailableRooms availableRooms[], int &nights)
{
	int Inpos = 0, Outpos = 0, check[7], count = 0, pass = 0, time = 0;
	while (compareDates(checkInDate, availableRooms[Inpos].date) != 0)
		Inpos++;
	while (compareDates(checkOutDate, availableRooms[Outpos].date) != 0)
		Outpos++;
	while (pass == 0)
	{
		for (int i = 1; i < 6; i++)
		{
			if (minNumRooms[i] != 0)
			{
				cout << i << ". " << roomTypeName[i];
				cout << endl;
			}
		}
		cout << "6. Give up " << endl << '?';
		cin >> roomType;
		if (roomType == 6)
			return;
		if (minNumRooms[roomType] != 0)
			pass++;
	}
	while (cout << "Number of rooms (" << minNumRooms[roomType] << " rooms available ): ")
	{
		cin >> numofrooms;
		cout << endl;
		if (numofrooms <= minNumRooms[roomType])
			break;
		else
			cout << "Please input right number of room !!!" << endl << endl;
	}
	while (cout << "ID Number¡G")
	{
		cin >> id;
		cout << endl;
		if (legal(id) == 1)
			break;
		else
			cout << "Please input right id number !!!" << endl << endl;
	}
	cout << "Name : ";
	cin >> name;
	cout << endl;
	cout << "Mobile Phone¡G";
	cin >> mobile;
	cout << endl;
	nights = Outpos - Inpos;
	for (int i = Inpos; i < Outpos; i++)
	{
		availableRooms[i].availableRooms[roomType] -= numofrooms;
	}
}

bool legal(char id[])
{
	if (id[0] < 65 || id[0] > 90)
		return false;
	if (strlen(id) != 10)
		return false;
	int check[11] = {}, engdigit = 0, answer = 0, pos = 2;
	switch (id[0])
	{
	case 'A': engdigit = 10; break;   case 'P': engdigit = 23; break;
	case 'B': engdigit = 11; break;   case 'Q': engdigit = 24; break;
	case 'C': engdigit = 12; break;   case 'R': engdigit = 25; break;
	case 'D': engdigit = 13; break;   case 'S': engdigit = 26; break;
	case 'E': engdigit = 14; break;   case 'T': engdigit = 27; break;
	case 'F': engdigit = 15; break;   case 'U': engdigit = 28; break;
	case 'G': engdigit = 16; break;   case 'V': engdigit = 29; break;
	case 'H': engdigit = 17; break;   case 'W': engdigit = 32; break;
	case 'I': engdigit = 34; break;   case 'X': engdigit = 30; break;
	case 'J': engdigit = 18; break;   case 'Y': engdigit = 31; break;
	case 'K': engdigit = 19; break;   case 'Z': engdigit = 33; break;
	case 'L': engdigit = 20; break;
	case 'M': engdigit = 21; break;
	case 'N': engdigit = 22; break;
	case 'O': engdigit = 35; break;
	}
	for (int i = 2; i < 11; i++)
	{
		check[i] = id[i - 1] - '0';
	}
	check[1] = engdigit % 10;
	engdigit /= 10;
	check[0] = engdigit % 10;
	answer = check[1] * 9 + check[0];
	for (int i = 8; i > 0; i--)
	{
		answer += check[pos] * i;
		pos++;
	}
	if (answer % 10 == 0 && check[10] == 0)
		return true;
	else
	{
		answer %= 10;
		if (10 - answer == check[10])
			return true;
		else
			return false;
	}
}

void display(const ReservationInfo &reservation, time_t numNights)
{
	cout << "Your reservation :" << endl;
	cout << "    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
	cout << setw(8) << setfill(' ') << reservation.name
		<< setw(7) << reservation.numRooms * roomRate[reservation.roomType] * numNights
		<< setw(13) << reservation.mobile
		<< setw(19) << roomTypeName[reservation.roomType]
		<< setw(18) << reservation.numRooms
		<< setw(10) << reservation.checkInDate.year << "-"
		<< setw(2) << setfill('0') << reservation.checkInDate.month << "-"
		<< setw(2) << reservation.checkInDate.day
		<< setw(11) << setfill(' ') << reservation.checkOutDate.year << "-"
		<< setw(2) << setfill('0') << reservation.checkOutDate.month << "-"
		<< setw(2) << reservation.checkOutDate.day << endl;
}

void saveReservationInfo(const ReservationInfo &reservation)
{
	ofstream outfileRes("Reservations.dat", ios::app | ios::binary);
	outfileRes.write(reinterpret_cast<const char*>(&reservation), sizeof(ReservationInfo));
}

void saveAvailableRooms(AvailableRooms availableRooms[], const int numRecords)
{
	ofstream outfileAva("Available Rooms.dat", ios::binary | ios::out);
	for (int i = 1; i <= numRecords; i++)
	{
		outfileAva.write(reinterpret_cast<char*>(&availableRooms[i]), sizeof(AvailableRooms));
	}
}

void reservationInquiry()
{
	ReservationInfo test[100];
	AvailableRooms  PosCheck[300];
	ifstream infilecheck("Reservations.dat", ios::in | ios::binary);

	if (!infilecheck)
	{
		cout << "There is no reservation data" << endl;
	}

	int ResCount = 0, numRecords = 0, Inpos = 1, Outpos = 1, nights = 0, pass = 0;
	char id_check[12];
	loadAvailableRooms(PosCheck, numRecords);
	while (cout << "Yours id number :")
	{
		cin >> id_check;
		cout << endl;
		if (legal(id_check) == 1)
		{
			break;
		}
		else
			cout << "Please input right id number !!!" << endl << endl;
	}
	cout << endl;
	while (infilecheck.read(reinterpret_cast<char*>(&test[ResCount]), sizeof(ReservationInfo)))
	{
		ResCount++;
	}
	for (int i = 0; i < ResCount; i++)
	{
		if (strcmp(test[i].id, id_check) == 0)
		{
			pass++;

			while (compareDates(test[i].checkInDate, PosCheck[Inpos].date) != 0)
				Inpos++;
			while (compareDates(test[i].checkOutDate, PosCheck[Outpos].date) != 0)
				Outpos++;

			nights = Outpos - Inpos;
			display(test[i], nights);
			cout << endl;
			Inpos = 1;
			Outpos = 1;
		}
	}
	if (pass == 0)
	{
		cout << "There is no your reservation data !!!" << endl;
		return;
	}
}

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1061702.cpp&amp;type=3&amp;id=2574416" id="form1">
<div class="aspNetHidden">
<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="/wEPDwUKLTEzNDM3NzkxOWRkwneTr34MFXJYUKyKKda+DU4gQVM=" />
</div>

<div class="aspNetHidden">

	<input type="hidden" name="__VIEWSTATEGENERATOR" id="__VIEWSTATEGENERATOR" value="629601C3" />
</div>
    <div>
    
    </div>
    </form>
</body>
</html>

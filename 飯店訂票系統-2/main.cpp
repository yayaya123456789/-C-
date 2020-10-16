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
	int availableRooms[6]; // number of available rooms
	// availRooms[ 0 ]: not used
	// availRooms[ 1 ]: the number of available superior rooms
	// availRooms[ 2 ]: the number of available deluxe rooms
	// availRooms[ 3 ]: the number of available deluxe twin rooms
	// availRooms[ 4 ]: the number of available superior suites
	// availRooms[ 5 ]: the number of available deluxe suites
};

int numRooms[6] = { 0, 9, 5, 3, 5, 4 };
int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void computeCurrentDate(Date &currentDate);

void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords);

void initializeAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords);

void adjustAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords);

// returns a value of 0, -1 or 1 if date1 is equal to, less than or greater than date2, respectively.
int compareDates(Date date1, Date date2);

void saveAvailableRooms(AvailableRooms availableRooms[], int numRecords);

int main()
{
	Date currentDate = {};

	computeCurrentDate(currentDate);

	AvailableRooms availableRooms[184] = {}; // availableRooms[ 0 ] is not used
	int numRecords = 0;

	loadAvailableRooms(availableRooms, numRecords);

	// the last available date < currentDate
	if (numRecords == 0 || compareDates(availableRooms[numRecords].date, currentDate) == -1)
		initializeAvailableRooms(availableRooms, currentDate, numRecords);
	else // the first available date < currentDate <= the last available date
		if (compareDates(availableRooms[1].date, currentDate) == -1)
			adjustAvailableRooms(availableRooms, currentDate, numRecords);
	cout << "The current date is " << currentDate.year << "-" << currentDate.month << "-" << currentDate.day << endl;
	cout << endl;
	cout << "The number of available rooms of each room type:\n\n";
	cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

	for (int i = 1; i <= numRecords; i++)
		cout << availableRooms[i].date.year << "-"
		<< setw(2) << setfill('0') << availableRooms[i].date.month << "-"
		<< setw(2) << availableRooms[i].date.day
		<< setw(16) << setfill(' ') << availableRooms[i].availableRooms[1]
		<< setw(14) << availableRooms[i].availableRooms[2]
		<< setw(19) << availableRooms[i].availableRooms[3]
		<< setw(17) << availableRooms[i].availableRooms[4]
		<< setw(15) << availableRooms[i].availableRooms[5] << "\n";

	saveAvailableRooms(availableRooms, numRecords);
	system("pause");
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

void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords)
{
	int i = 1;
	ifstream inFile("Available Rooms 2.dat", ios::in | ios::binary);
	while (inFile.read(reinterpret_cast<char*>(&availableRooms[i]), sizeof(AvailableRooms)))
	{
		numRecords++;
		i++;
	}
	inFile.close();
}

void initializeAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords)
{
	int count = 0;
	availableRooms[1].date = currentDate;
	for (int i = 2; i <= 183; i++)
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
			if (currentDate.month == 12)
			{
				currentDate.year += 1;
				currentDate.month = 1;
				currentDate.day = 1;
			}
			else
			{
				currentDate.day = 1;
				currentDate.month += 1;
			}
			availableRooms[i].date = currentDate;
		}
		if (i == 183)
		{
			numRecords = i;
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
void adjustAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords)
{
	int count = 0, pos = 0, savpos = 0, hold = 0, monthday = 0;
	for (int j = 1; j <= numRecords; j++)
	{
		if (compareDates(availableRooms[j].date, currentDate) == 0)
		{
			pos = j;
			break;
		}
	}

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

	currentDate = availableRooms[savpos - 1].date;
	if (count < 6)
	{
		hold = 6 - count;
		numRecords = savpos - 1;

		for (int i = 0; i < hold; i++)
		{
			monthday = availableRooms[savpos - 1].date.month + 1 + i;
			if (monthday > 12)
			{
				monthday -= 12;
			}
			numRecords += days[monthday];
		}
		for (int i = savpos; i <= numRecords; i++)
		{
			if (availableRooms[i - 1].date.day <= days[availableRooms[i - 1].date.month] - 1)
			{
				availableRooms[i].date.day = availableRooms[i - 1].date.day + 1;
			}
			else
			{
				if (currentDate.month == 12)
				{
					currentDate.year += 1;
					currentDate.month = 1;
					currentDate.day = 1;
				}
				else
				{
					currentDate.day = 1;
					currentDate.month += 1;
				}
				for (int k = i; k <= numRecords; ++k)
				{
					availableRooms[k].date = currentDate;
				}
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

int compareDates(Date date1, Date date2)
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

void saveAvailableRooms(AvailableRooms availableRooms[], int numRecords)
{
	ofstream outFile("Available Rooms.dat", ios::out | ios::binary);

	if (!outFile)
	{
		cout << "Error";
	}
	for (int i = 1; i <= numRecords; i++)
	{
		outFile.write(reinterpret_cast<char*>(&availableRooms[i]), sizeof(AvailableRooms));
	}
	outFile.close();
}

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1061702.cpp&amp;type=3&amp;id=2566232" id="form1">
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

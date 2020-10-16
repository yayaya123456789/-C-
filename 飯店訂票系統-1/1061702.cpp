#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct AvailableRooms
{
	char date[12];
	unsigned int singleDayAvailRooms[6];
	// singleDayAvailRooms[0]: not used
	// singleDayAvailRooms[1]: the number of available superior rooms
	// singleDayAvailRooms[2]: the number of available deluxe rooms
	// singleDayAvailRooms[3]: the number of available deluxe twin rooms
	// singleDayAvailRooms[4]: the number of available superior suites
	// singleDayAvailRooms[5]: the number of available deluxe suites
};

void loadFromFile(AvailableRooms availableRooms[], int &numRecords);
void makeReservation(AvailableRooms availableRooms[], int numRecords);
void saveToFile(AvailableRooms availableRooms[], int numRecords);

int main()
{
	AvailableRooms availableRooms[200] = { { "", 0, 0, 0, 0, 0 } };

	int numRecords = 0;

	loadFromFile(availableRooms, numRecords); // read all records of the file availableRooms.dat,
												// put them into the array availableRooms, and
												// disply them on the screen

	makeReservation(availableRooms, numRecords); // make a room reservation; the numbers of available rooms
												   // of the reserved room type and dates shoule be adjust

	saveToFile(availableRooms, numRecords); // save the modified available rooms information into the file availableRooms.dat

	loadFromFile(availableRooms, numRecords);

	system("pause");
}

void loadFromFile(AvailableRooms availableRooms[], int &numRecords)
{
	ifstream inFile("availableRooms.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened." << endl;
		exit(1);
	}
	for (int i = 0; !inFile.eof(); i++)
	{
		inFile.read(availableRooms[i].date, sizeof(availableRooms[i].date));
		inFile.read(reinterpret_cast<char *>(&availableRooms[i].singleDayAvailRooms), sizeof(availableRooms[i].singleDayAvailRooms));

		cout << availableRooms[i].date << " ";
		for (int j = 1; j < 6; j++)
		{
			cout << availableRooms[i].singleDayAvailRooms[j] << " ";
		}
		cout << endl;

		numRecords++;
	}
	inFile.close();
}

void makeReservation(AvailableRooms availableRooms[], int numRecords)
{
	char arrivalDate[12], departureDate[12];
	int  arrivalnum = 0, departurenum = 0, type = 0, rooms = 0;

	cout << "Please input the arrival date (yyyy-mm-dd): ";
	cin >> arrivalDate;

	cout << "\nPlease input the departure date (yyyy-mm-dd): ";
	cin >> departureDate;

	for (int i = 0; i < numRecords; i++)
	{
		if (strcmp(availableRooms[i].date, arrivalDate) == 0)
		{
			arrivalnum = i;
			break;
		}
	}
	for (int j = arrivalnum; j < numRecords; j++)
	{
		if (strcmp(availableRooms[j].date, departureDate) == 0)
		{
			departurenum = j;
			break;
		}
	}
	cout << endl;
	cout << "Select Room Type: " << endl
		<< "1. Superior Room" << endl
		<< "2. Deluxe Room" << endl
		<< "3. Deluxe Twin Room" << endl
		<< "4. Superior Suite" << endl
		<< "5. Deluxe Suite" << endl
		<< "? ";
	cin >> type;
	cout << endl;
	cout << "\nHow many rooms? ";
	cin >> rooms;

	if (type == 1)
	{
		for (int a = arrivalnum; a < departurenum; a++)
		{
			(availableRooms + a)->singleDayAvailRooms[1] -= rooms;
		}
	}
	else if (type == 2)
	{
		for (int a = arrivalnum; a < departurenum; a++)
		{
			(availableRooms + a)->singleDayAvailRooms[2] -= rooms;
		}
	}
	else if (type == 3)
	{
		for (int a = arrivalnum; a < departurenum; a++)
		{
			(availableRooms + a)->singleDayAvailRooms[3] -= rooms;
		}
	}
	else if (type == 4)
	{
		for (int a = arrivalnum; a < departurenum; a++)
		{
			(availableRooms + a)->singleDayAvailRooms[4] -= rooms;
		}
	}
	else
	{
		for (int a = arrivalnum; a < departurenum; a++)
		{
			(availableRooms + a)->singleDayAvailRooms[5] -= rooms;
		}
	}
	cout << endl;

	return;
}

void saveToFile(AvailableRooms availableRooms[], int numRecords)
{
	ofstream outFile("availableRoomsRemained.dat", ios::binary);
	if (!outFile)
	{
		cout << "File could not be opened." << endl;
		exit(1);
	}

	for (int i = 0; i < numRecords; i++)
	{
		outFile.write(availableRooms[i].date, sizeof(availableRooms[i].date));
		outFile.write(reinterpret_cast<char *>(&availableRooms[i].singleDayAvailRooms), sizeof(availableRooms[i].singleDayAvailRooms));
		outFile << availableRooms[i].date << " ";
		cout << availableRooms[i].date << " ";
		for (int j = 1; j < 6; j++)
		{
			outFile << availableRooms[i].singleDayAvailRooms[j] << " ";
			cout << availableRooms[i].singleDayAvailRooms[j] << " ";
		}
		cout << endl;
	}
	outFile.close();
	cout << endl;
}

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1061702.cpp&amp;type=3&amp;id=2547595" id="form1">
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

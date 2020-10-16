#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// HugeInteger class definition
class HugeInteger
{
public:
	// enable user to input a positive huge integer
	void input(istream &inFile);

	// output the specified huge integer
	void output(ostream &outFile);

	// return true if and only if all digits are zero
	bool isZero();

	// return true if and only if current object == hugeInt2
	bool equal(HugeInteger hugeInt2);

	// return true if and only if current object < hugeInt2
	bool less(HugeInteger hugeInt2);

	// sum = current object + adder
	void addition(HugeInteger adder, HugeInteger &sum);

	// difference = current object - subtrahend
	// provided that the minuend is greater than or equal to the subtrahend
	void subtraction(HugeInteger subtrahend, HugeInteger &difference);

	// product = current object * multiplier
	void multiplication(HugeInteger multiplier, HugeInteger &product);

	// quotient = current object / divisor; remainder = current object % divisor
	// provided that the divisor is not equal to 0
	void division(HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder);

	// current object /= 10
	void divideByTen();

	unsigned int size = 1;        // the number of digits of the integer; it can never be zero
	int elems[arraySize] = {};  // used to store a nonnegative integer, one digit per element
}; // end class HugeInteger


// enable user to input a positive huge integer
void HugeInteger::input(istream &inFile)
{
	char numericString[arraySize];

	inFile >> numericString;

	size = strlen(numericString);
	for (unsigned int i = 0; i < size; i++)
		elems[size - i - 1] = numericString[i] - '0';
} // end function input

// output the specified huge integer
void HugeInteger::output(ostream &outFile)
{
	if (isZero())
		outFile << 0;
	else
		for (int i = size - 1; i >= 0; i--)
			if (elems[i] < 10)
				outFile << elems[i];
	outFile << endl;
} // end function output

// test if a HugeInteger is zero
bool HugeInteger::isZero()
{
	for (unsigned int i = 0; i < size; i++)
		if (elems[i] != 0)
			return false;
	return true;
} // end function isZero

// test if two HugeIntegers are equal
bool HugeInteger::equal(HugeInteger hugeInt2)
{
	if (size == hugeInt2.size)
	{
		for (unsigned int i = size - 1; i >= 0; i--)
		{
			if (elems[i] < hugeInt2.elems[i])
				return false;
			if (elems[i] > hugeInt2.elems[i])
				return false;
		}
		return true;
	}
	else 
		return false;
} // end function equal

// test if one HugeInteger is less than another
bool HugeInteger::less(HugeInteger hugeInt2)
{
	if (size < hugeInt2.size)
		return true;
	else if (size == hugeInt2.size)
	{
		for (unsigned int i = size - 1; i >= 0; i--)
		{
			if (elems[i] < hugeInt2.elems[i])
				return true;
			else if (elems[i] > hugeInt2.elems[i])
				return false;
		}
		return false;
	}
	else
		return false;
} // end function less

// sum = current object + adder
void HugeInteger::addition(HugeInteger adder, HugeInteger &sum)
{
	sum.size = (size >= adder.size) ? size + 1 : adder.size + 1;

	for (unsigned int i = 0; i < size; i++)
		sum.elems[i] = elems[i];

	for (unsigned int i = size; i < sum.size; i++)
		sum.elems[i] = 0;

	for (unsigned int i = 0; i < adder.size; i++)
		sum.elems[i] += adder.elems[i];

	for (unsigned int i = 0; i < sum.size - 1; i++)
		if (sum.elems[i] > 9) // determine whether to carry a 1
		{
			sum.elems[i] -= 10; // reduce to 0-9
			sum.elems[i + 1]++;
		}

	if (sum.elems[sum.size - 1] == 0)
		sum.size--;
} // end function addition

// difference = current object - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void HugeInteger::subtraction(HugeInteger subtrahend, HugeInteger &difference)
{
	difference.size = (size >= subtrahend.size) ? size  : subtrahend.size ;
	if (less(subtrahend))
	{
		for (unsigned int i = 0; i < subtrahend.size; i++)
			difference.elems[i] = subtrahend.elems[i];
		for (unsigned int i = subtrahend.size; i < difference.size; i++)
			difference.elems[i] = 0;
		for (unsigned int i = 0; i < size; i++)
			difference.elems[i] -=  elems[i];
	}
	else
	{
		for (unsigned int i = 0; i < size; i++)
			difference.elems[i] = elems[i];
		for (unsigned int i = size; i < difference.size; i++)
			difference.elems[i] = 0;
		for (unsigned int i = 0; i < subtrahend.size; i++)
			difference.elems[i] -=subtrahend.elems[i];
	}
	for (unsigned int i = 0; i < difference.size - 1; i++)
	{
		if (difference.elems[i] < 0)
		{
			difference.elems[i] += 10;
			difference.elems[i + 1]--;
		}
	}
	for (unsigned int i = difference.size - 1; i > 0; i--)
	{
		if (difference.elems[i] == 0)
			difference.size--;
		else
			break;
	}
} // end function subtraction

// product = current object * multiplier
void HugeInteger::multiplication(HugeInteger multiplier, HugeInteger &product)
{
	product.size = (size >= multiplier.size) ? size + multiplier.size : multiplier.size + size;

	for (unsigned int i = 0; i < product.size; i++)
		product.elems[i] = 0;

	for (unsigned int i = 0; i < multiplier.size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			product.elems[i + j] += multiplier.elems[i] * elems[j];
		}
	}
	for (unsigned int i = 0; i < product.size - 1; i++)
	{
		while (product.elems[i] > 9)
		{
			product.elems[i] -= 10;
			product.elems[i + 1]++;
		}
	}
	for (unsigned int i = product.size - 1; i > 0; i--)
	{
		if (product.elems[i] == 0)
			product.size--;
		else
			break;
	}
} // end function multiplication

// quotient = current object / divisor; remainder = current object % divisor
// provided that the divisor is not equal to 0
void HugeInteger::division(HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder)
{
	if (isZero())//divided=0
	{
		quotient.size = 1;
		remainder.size = 1;
		quotient.elems[0] = 0;
		remainder.elems[0] = 0;
		return;
	}
	remainder.size = size;

	for (unsigned int i = 0; i < size; i++)
	{
		remainder.elems[i] = elems[i];
	}
	if (less(divisor))	//dividend < divisor
	{
		quotient.elems[0] = 0;
		quotient.size = 1;
	}
	else
	{
		unsigned int  n = size - divisor.size;
		HugeInteger buffer;
		buffer.size = size;
		for (unsigned int i = 0; i < buffer.size; i++)
		{
			buffer.elems[i] = 0;//buffer初始化
		}
		for (unsigned int i = 0; i < divisor.size; i++)
		{
			buffer.elems[i + n] = divisor.elems[i];//divisor丟到buffer裡面
		}
		for (unsigned int i = 0; i < n; i++)
		{
			buffer.elems[i] = 0;//buffer補0
		}

		quotient.size = size - divisor.size;

		if (less(buffer))
		{
			buffer.divideByTen();
		}
		else
		{
			quotient.size++;
		}
		for (unsigned int i = 0; i < quotient.size; i++)
		{
			quotient.elems[i] = 0;
		}
		//for (unsigned int k = quotient.size - 1; k >= 0; k--)
		for (int k = quotient.size - 1; k >= 0; k--)
		{
			//while(equal(buffer) || less(remainder))
			while(buffer.less(remainder) || buffer.equal(remainder))
			{
				remainder.subtraction(buffer,remainder);
				//subtraction(buffer, remainder);
				quotient.elems[k]++;
				if (remainder.isZero())
					return;
			}
			buffer.divideByTen();
		}
	}
} 
// current object /= 10
void HugeInteger::divideByTen()
{
	if (size == 1)
		elems[0] = 0;
	else
	{
		for (unsigned int i = 1; i < size; i++)
			elems[i - 1] = elems[i];
		elems[size - 1] = 0;
		size--;
	}
} // end function divideByTen


void perform(ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
	HugeInteger hugeInt3, HugeInteger hugeInt4);

int main()
{
	system("mode con cols=122");

	ifstream inFile("Test cases.txt", ios::in);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	ofstream outFile("Result.txt", ios::out);

	// exit program if ofstream could not open file
	if (!outFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < numTestCases; i++)
	{
		HugeInteger hugeInt1;
		HugeInteger hugeInt2;
		HugeInteger hugeInt3;
		HugeInteger hugeInt4;

		hugeInt1.input(inFile);
		hugeInt2.input(inFile);
		perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
		perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
	}

	inFile.close();
	outFile.close();

	system("pause");
}

void perform(ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
	HugeInteger hugeInt3, HugeInteger hugeInt4)
{
	hugeInt1.output(outFile);
	hugeInt2.output(outFile);

	hugeInt1.addition(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 + hugeInt2
	hugeInt3.output(outFile);

	if (hugeInt1.less(hugeInt2))
	{
		outFile << '-';
		hugeInt2.subtraction(hugeInt1, hugeInt3); // hugeInt3 = hugeInt2 - hugeInt1
		hugeInt3.output(outFile);
	}
	else
	{
		hugeInt1.subtraction(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 - hugeInt2
		hugeInt3.output(outFile);
	}
	hugeInt1.multiplication(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 * hugeInt2
	hugeInt3.output(outFile);

	if (hugeInt2.isZero())
	{
		outFile << "DivideByZero!\n";
		outFile << "DivideByZero!\n";
	}
	else
	{
		// hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
		hugeInt1.division(hugeInt2, hugeInt3, hugeInt4);
		hugeInt3.output(outFile);
		hugeInt4.output(outFile);
	}

	outFile << endl;
}

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
struct HugeInteger
{
	unsigned int size = 1;        // the number of digits of the integer; it can never be zero
	int elems[arraySize] = {};  // used to store a nonnegative integer, one digit per element
}; // end struct HugeInteger


// perform addition, subtraction, multiplication and division
void perform(ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
	HugeInteger hugeInt3, HugeInteger hugeInt4);

// enable user to input a positive huge integer
void input(istream &inFile, HugeInteger &hugeInt);

// output the specified huge integer
void output(ostream &outFile, HugeInteger hugeInt);

// return true if and only if all digits are zero
bool isZero(HugeInteger hugeInt);

// return true if and only if hugeInt1 == hugeInt2
bool equal(HugeInteger hugeInt1, HugeInteger hugeInt2);

// return true if and only if hugeInt1 < hugeInt2
bool less(HugeInteger hugeInt1, HugeInteger hugeInt2);

// sum = addend + adder
void addition(HugeInteger addend, HugeInteger adder, HugeInteger &sum);

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction(HugeInteger minuend, HugeInteger subtrahend, HugeInteger &difference);

// product = multiplicand * multiplier
void multiplication(HugeInteger multiplicand, HugeInteger multiplier, HugeInteger &product);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division(HugeInteger dividend, HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder);

// hugeInt /= 10
void divideByTen(HugeInteger &hugeInt);

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

		input(inFile, hugeInt1);
		input(inFile, hugeInt2);
		perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
		perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
	}

	inFile.close();
	outFile.close();

	system("pause");
}

// perform addition, subtraction, multiplication and division
void perform(ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
	HugeInteger hugeInt3, HugeInteger hugeInt4)
{
	output(outFile, hugeInt1);
	output(outFile, hugeInt2);

	addition(hugeInt1, hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 + hugeInt2
	output(outFile, hugeInt3);

	if (less(hugeInt1, hugeInt2))
	{
		outFile << '-';
		subtraction(hugeInt2, hugeInt1, hugeInt3); // hugeInt3 = hugeInt2 - hugeInt1
		output(outFile, hugeInt3);
	}
	else
	{
		subtraction(hugeInt1, hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 - hugeInt2
		output(outFile, hugeInt3);
	}

	multiplication(hugeInt1, hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 * hugeInt2
	output(outFile, hugeInt3);

	if (isZero(hugeInt2))
	{
		outFile << "DivideByZero!\n";
		outFile << "DivideByZero!\n";
	}
	else
	{
		// hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
		division(hugeInt1, hugeInt2, hugeInt3, hugeInt4);
		output(outFile, hugeInt3);
		output(outFile, hugeInt4);
	}

	outFile << endl;
}

// enable user to input a positive huge integer
void input(istream &inFile, HugeInteger &hugeInt)
{
	char numericString[arraySize];

	inFile >> numericString;

	hugeInt.size = strlen(numericString);
	for (unsigned int i = 0; i < hugeInt.size; i++)
		hugeInt.elems[hugeInt.size - i - 1] = numericString[i] - '0';
} // end function input

// output the specified huge integer
void output(ostream &outFile, HugeInteger hugeInt)
{
	if (isZero(hugeInt))
		outFile << 0;
	else
		for (int i = hugeInt.size - 1; i >= 0; i--)
			if (hugeInt.elems[i] < 10)
				outFile << hugeInt.elems[i];
	outFile << endl;
} // end function output

// test if a HugeInteger is zero
bool isZero(HugeInteger hugeInt)
{
	for (unsigned int i = 0; i < hugeInt.size; i++)
		if (hugeInt.elems[i] != 0)
			return false;
	return true;
} // end function isZero

// test if two HugeIntegers are equal
bool equal(HugeInteger hugeInt1, HugeInteger hugeInt2)
{
	if (hugeInt1.size == hugeInt2.size)
	{
		for (unsigned int i = 0; i < hugeInt1.size; i++)
		{
			if (hugeInt1.elems[i] < hugeInt2.elems[i])
				return false;
			if (hugeInt1.elems[i] > hugeInt2.elems[i])
				return false;
		}
		return true;
	}
	else
		return false;
} // end function equal

// test if one HugeInteger is less than another
bool less(HugeInteger hugeInt1, HugeInteger hugeInt2)
{
	if (hugeInt1.size < hugeInt2.size)
		return true;
	else if (hugeInt1.size == hugeInt2.size)
	{
		for (unsigned int i = hugeInt1.size - 1; i >= 0; i--)
		{
			if (hugeInt1.elems[i] < hugeInt2.elems[i])
				return true;
			else if (hugeInt1.elems[i] > hugeInt2.elems[i])
				return false;
		}
		return false;
	}
	else
		return false;
} // end function less

// sum = addend + adder
void addition(HugeInteger addend, HugeInteger adder, HugeInteger &sum)
{
	sum.size = (addend.size >= adder.size) ? addend.size + 1 : adder.size + 1;

	for (unsigned int i = 0; i < addend.size; i++)
		sum.elems[i] = addend.elems[i];

	for (unsigned int i = addend.size; i < sum.size; i++)
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

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction(HugeInteger minuend, HugeInteger subtrahend, HugeInteger &difference)
{
	difference.size = (minuend.size >= subtrahend.size) ? minuend.size : subtrahend.size;

	if (less(minuend, subtrahend))
	{
		for (unsigned int i = 0; i < subtrahend.size; i++)
			difference.elems[i] = subtrahend.elems[i];
		for (unsigned int i = subtrahend.size; i < difference.size; i++)
			difference.elems[i] = 0;
		for (unsigned int i = 0; i < minuend.size; i++)
			difference.elems[i] -=  minuend.elems[i];
	}
	else
	{
		for (unsigned int i = 0; i < minuend.size; i++)//這邊可能有問題
			difference.elems[i] = minuend.elems[i];
		for (unsigned int i = minuend.size; i < difference.size; i++)
			difference.elems[i] = 0;
		for (unsigned int i = 0; i < subtrahend.size; i++)
			difference.elems[i] -=subtrahend.elems[i];
	}
	for (unsigned int i = 0; i < difference.size-1; i++)
	//for (unsigned int i = 0; i < difference.size; i++)//因為i+1,所以i<difference.size-1
	{
		if (difference.elems[i] < 0)
		{
			difference.elems[i] += 10;
			difference.elems[i + 1]--;
		}
	}
	for (unsigned int i = difference.size - 1; i > 0 ; i--)
	{
		if (difference.elems[i] == 0)//扣掉多的位數
			difference.size--;
		else
			break;
	}
} // end function subtraction

// product = multiplicand * multiplier
void multiplication(HugeInteger multiplicand, HugeInteger multiplier, HugeInteger &product)
{
	product.size = (multiplicand.size >= multiplier.size) ? multiplicand.size + multiplier.size : multiplicand.size + multiplier.size;

	for (unsigned int i = 0; i < product.size; i++)
	{
		product.elems[i] = 0;
	}
	for (unsigned int i = 0; i < multiplicand.size; i++)
	{
		for (unsigned int j = 0; j < multiplier.size; j++)
			product.elems[i + j] += multiplicand.elems[i] * multiplier.elems[j];
	}
	for (unsigned int i = 0; i < product.size - 1; i++)
	{
		while (product.elems[i] > 9)
		{
			product.elems[i] -= 10;
			product.elems[i + 1]++;
		}
	}
	if (product.elems[product.size - 1] == 0)
		product.size--;
} // end function multiplication

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division(HugeInteger dividend, HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder)
{
	//quotient.size = (dividend.size >= divisor.size) ? dividend.size + 1 : divisor.size + 1;

	if (isZero(dividend))
	{
		quotient.elems[0] = 0;
		quotient.size = 1;
		remainder.elems[0] = 0;
		remainder.size = 1;
		return;
	}
	remainder.size = dividend.size;//要把dividend丟到remainder裡
	for (unsigned int i = 0; i < dividend.size; i++)
	{
		remainder.elems[i] = dividend.elems[i];
	}
	if (less(dividend, divisor))
	{
		quotient.elems[0] = 0;
		quotient.size = 1;
	}
	else
	{
		unsigned int n = dividend.size - divisor.size;
		HugeInteger buffer;
		buffer.size = dividend.size;
		/*HugeInteger array;
		array.size = dividend.size;*/

		//for (unsigned int i = 0; i < array.size; i++)
		//	array.elems[i] = 0;//array初始化

		for (unsigned int i = 0; i < buffer.size; i++)
			buffer.elems[i] = 0;//buffer初始化

		for (unsigned int i = 0; i < divisor.size; i++)
		{
			buffer.elems[i + n] = divisor.elems[i];//buffer左移
		}
		for (unsigned int i = 0; i < n; i++)
		{
			buffer.elems[i] = 0;//buffer補0
		}

		quotient.size = dividend.size - divisor.size;

		if (less(dividend, buffer))
		{
			divideByTen(buffer);
		}
		else
		{
			quotient.size++;//quotient.size+1;
		}
		for (unsigned int i = 0; i < quotient.size; i++)
		{
			quotient.elems[i] = 0;//quotient初始化
		}
		if (equal(buffer, remainder))
		{
			quotient.elems[0] = 1;
			quotient.size = 1;
			remainder.elems[0] = 0;
			remainder.size = 1;
		}
		//for (unsigned int k = quotient.size - 1; k >= 0; k--)
		for (int k = quotient.size - 1; k >= 0; k--)
		{
			while (less(buffer, remainder) || equal(buffer,remainder))
			{
				subtraction(remainder, buffer,remainder);
				quotient.elems[k]++;
				if (isZero(remainder))
					return;
			}
			
			divideByTen(buffer);
		}
	}
}
// hugeInt /= 10
void divideByTen(HugeInteger &hugeInt)
{
	if (hugeInt.size == 1)
		hugeInt.elems[0] = 0;
	else
	{
		for (unsigned int i = 1; i < hugeInt.size; i++)
			hugeInt.elems[i - 1] = hugeInt.elems[i];
		hugeInt.elems[hugeInt.size - 1] = 0;
		hugeInt.size--;
	}
} // end function divideByTen

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

#include <vector>
using std::vector;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// perform addition, subtraction, multiplication and division
void perform(ostream &outFile, vector< int > hugeInt1, vector< int > hugeInt2,
	vector< int > hugeInt3, vector< int > hugeInt4);

// enable user to input a positive huge integer
void input(istream &inFile, vector< int > &hugeInt);

// output the specified huge integer
void output(ostream &outFile, vector< int > hugeInt);

// return true if and only if all digits are zero
bool isZero(vector< int > hugeInt);

// return true if and only if hugeInt1 == hugeInt2
bool equal(vector< int > hugeInt1, vector< int > hugeInt2);

// return true if and only if hugeInt1 < hugeInt2
bool less(vector< int > hugeInt1, vector< int > hugeInt2);

// sum = addend + adder
void addition(vector< int > addend, vector< int > adder, vector< int > &sum);

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction(vector< int > minuend, vector< int > subtrahend, vector< int > &difference);

// product = multiplicand * multiplier
void multiplication(vector< int > multiplicand, vector< int > multiplier, vector< int > &product);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division(vector< int > dividend, vector< int > divisor, vector< int > &quotient, vector< int > &remainder);

// hugeInt /= 10
void divideByTen(vector< int > &hugeInt);

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
		vector< int > hugeInt1;
		vector< int > hugeInt2;
		vector< int > hugeInt3;
		vector< int > hugeInt4;

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
void perform(ostream &outFile, vector< int > hugeInt1, vector< int > hugeInt2,
	vector< int > hugeInt3, vector< int > hugeInt4)
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
void input(istream &inFile, vector< int > &hugeInt)
{
	char numericString[arraySize];

	inFile >> numericString;

	hugeInt.resize(strlen(numericString));
	for (unsigned int i = 0; i < hugeInt.size(); i++)
		hugeInt[hugeInt.size() - i - 1] = numericString[i] - '0';
} // end function input

// output the specified huge integer
void output(ostream &outFile, vector< int > hugeInt)
{
	if (isZero(hugeInt))
		outFile << 0;
	else
		for (int i = hugeInt.size() - 1; i >= 0; i--)
			if (hugeInt[i] < 10)
				outFile << hugeInt[i];
	outFile << endl;
} // end function output

// test if a vector< int > is zero
bool isZero(vector< int > hugeInt)
{
	for (unsigned int i = 0; i < hugeInt.size(); i++)
		if (hugeInt[i] != 0)
			return false;
	return true;
} // end function isZero

// test if two HugeIntegers are equal
bool equal(vector< int > hugeInt1, vector< int > hugeInt2)
{
	if (hugeInt1.size() < hugeInt2.size())
		return false;
	else if (hugeInt1.size() == hugeInt2.size())
	{
		for (int i = hugeInt1.size() - 1; i >= 0; i--)
		{
			if (hugeInt1[i] < hugeInt2[i])
				return false;
			if (hugeInt1[i] > hugeInt2[i])
				return false;
		}
		return true;
	}
	else
		return false;
} // end function equal

// test if one vector< int > is less than another
bool less(vector< int > hugeInt1, vector< int > hugeInt2)
{
	if (hugeInt1.size() < hugeInt2.size())
		return true;
	else if (hugeInt1.size() == hugeInt2.size())
	{
		for (int i = hugeInt1.size() - 1; i >= 0; i--)
		{
			if (hugeInt1[i] < hugeInt2[i])
				return true;
			if (hugeInt1[i] > hugeInt2[i])
				return false;
		}
		return false;
	}
	else
		return false;
} // end function less

// sum = addend + adder
void addition(vector< int > addend, vector< int > adder, vector< int > &sum)
{
	sum.resize((addend.size() >= adder.size()) ? addend.size() + 1 : adder.size() + 1);

	for (unsigned int i = 0; i < addend.size(); i++)
		sum[i] = addend[i];

	for (unsigned int i = addend.size(); i < sum.size(); i++)
		sum[i] = 0;

	for (unsigned int i = 0; i < adder.size(); i++)
		sum[i] += adder[i];

	for (unsigned int i = 0; i < sum.size() - 1; i++)
		if (sum[i] > 9) // determine whether to carry a 1
		{
			sum[i] -= 10; // reduce to 0-9
			sum[i + 1]++;
		}

	if (sum[sum.size() - 1] == 0)
		sum.pop_back();
} // end function addition

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction(vector< int > minuend, vector< int > subtrahend, vector< int > &difference)
{
	difference.resize((minuend.size() >= subtrahend.size()) ? minuend.size()+1  : subtrahend.size()+1 );
	
	if (less(minuend,subtrahend))
	{
		for (unsigned int i = 0; i < subtrahend.size(); i++)
			difference[i] = subtrahend[i];
		for (unsigned int i = subtrahend.size(); i < difference.size(); i++)
			difference[i] = 0;
		for (unsigned int i = 0; i < minuend.size(); i++)
			difference[i] -= minuend[i];
	}
	else
	{
		for (unsigned int i = 0; i < minuend.size(); i++)
			difference[i] = minuend[i];
		for (unsigned int i = minuend.size(); i < difference.size(); i++)
			difference[i] = 0;
		for (unsigned int i = 0; i < subtrahend.size(); i++)
			difference[i] -= subtrahend[i];
	}
	for (unsigned int i = 0; i < difference.size() - 1; i++)
	{
		if (difference[i] < 0)
		{
			difference[i] += 10;
			difference[i + 1]--;
		}
	}
	for (unsigned int i = difference.size()-1; i > 0; i--)
	{
		if (difference[i] == 0)
			difference.pop_back();
		else
			break;
	}
} // end function subtraction

// product = multiplicand * multiplier
void multiplication(vector< int > multiplicand, vector< int > multiplier, vector< int > &product)
{
	product.resize((multiplicand.size() >= multiplier.size()) ? multiplicand.size() + multiplier.size() : multiplier.size() + multiplicand.size());
	for (unsigned int i = 0; i < product.size(); i++)
		product[i] = 0;
	
	for (unsigned int i = 0; i < multiplicand.size(); i++)
	{
		for (unsigned int j = 0; j < multiplier.size(); j++)
			product[i + j] += multiplicand[i] * multiplier[j];
	}
	for (unsigned int i = 0; i < product.size()-1; i++)
	{
		while (product[i] > 9)
		{
			product[i] -= 10;
			product[i + 1]++;
		}
	}
	if (product[product.size() - 1] == 0)
		product.pop_back();
	

} // end function multiplication

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division(vector< int > dividend, vector< int > divisor, vector< int > &quotient, vector< int > &remainder)
{
	if (isZero(dividend))
	{
		quotient.resize(1);
		remainder.resize(1);
		quotient[0] = 0;
		remainder[0] = 0;

	}
	remainder.resize(dividend.size());
	for (unsigned int i = 0; i < dividend.size(); i++)
		remainder[i] = dividend[i];
	if (less(dividend, divisor))
	{
		quotient.resize(1);
		quotient[0] = 0;
	}
	else
	{
		unsigned int  n= dividend.size() - divisor.size();
		vector<int> buffer;
		buffer.resize(dividend.size()) ;
		for (unsigned int i = 0; i < buffer.size(); i++)
			buffer[i] = 0;
		for (unsigned int i = 0; i < divisor.size(); i++)
			buffer[i + n] = divisor[i];
		for (unsigned int i = 0; i < n; i++)
			buffer[i] = 0;

		quotient.resize(dividend.size() - divisor.size());
		
		if (less(dividend, buffer))
			divideByTen(buffer);
		else
			quotient.resize(quotient.size()+1);
		for (unsigned int i = 0; i < quotient.size(); i++)
			quotient[i] = 0;
		for (int k = quotient.size() - 1; k >= 0; k--)
		{
			while (less(buffer, remainder) || equal(buffer, remainder))
			{
				subtraction(remainder, buffer, remainder);
				quotient[k]++;
				if (isZero(remainder))
					return;
			}

			divideByTen(buffer);
		}
	}
} // end function division

// hugeInt /= 10
void divideByTen(vector< int > &hugeInt)
{
	if (hugeInt.size() == 1)
		hugeInt[0] = 0;
	else
	{
		for (unsigned int i = 1; i < hugeInt.size(); i++)
			hugeInt[i - 1] = hugeInt[i];
		hugeInt[hugeInt.size() - 1] = 0;
		hugeInt.pop_back();
	}
} // end function divideByTen

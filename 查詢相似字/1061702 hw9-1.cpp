#include <iostream>
using namespace::std;
#include <fstream>
#include <cstring>
// input all words from the file Dictionary.txt, and put them to the array "dictionary"
void readDictionary(char(*dictionary)[21], int &numDicWords);

// Find every word w in the array "dictionary" which satisfies two conditions:
// 1. the length of w is equal to the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the array "result".
void spellCheck1(char *wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int &numResult);

// Find every word w in the array "dictionary" which satisfies two conditions:
// 1. the length of w is one greater than the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the array "result".
void spellCheck2(char *wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int &numResult);

// Find every word w in the array "dictionary" which satisfies two conditions:
// 1. the length of w is one less than the length of wordToCheck, and
// 2. w is equal to the substring obtained by deleting a character from wordToCheck.
// Put these words into the array "result".
void spellCheck3(char *wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int &numResult);

// find the words in the array "dictionary" whose length is equal to the last parameter "length",
// and puts these words into the array "words"
void findWords(char(*&words)[21], int &numWords, char(*dictionary)[21], int numDicWords, int length);

// output all words in the array "result" to the file Words.txt
void saveWords(char(*result)[21], int numResult);

int main()
{
	srand(1);

	int numDicWords = 0;
	char(*dictionary)[21] = new char[40000][21];

	readDictionary(dictionary, numDicWords);

	char wordToCheck[21];
	int numResult = 0;
	char(*result)[21] = new char[3000][21];
	int length;
	for (int i = 0; i < 30; i++)
	{
		strcpy_s(wordToCheck, 21, dictionary[rand() + numDicWords - 32768]);
		length = strlen(wordToCheck);
		for (int j = rand() % length; j < length; j++)
			wordToCheck[j] = wordToCheck[j + 1];

		//cout << wordToCheck << endl;

		spellCheck1(wordToCheck, dictionary, numDicWords, result, numResult);
		spellCheck2(wordToCheck, dictionary, numDicWords, result, numResult);
		spellCheck3(wordToCheck, dictionary, numDicWords, result, numResult);
	}

	saveWords(result, numResult);

	delete[] dictionary;
	delete[] result;

	system("pause");
}

void readDictionary(char(*dictionary)[21], int &numDicWords)
{
	ifstream inFile("Dictionary.txt", ios::in);
	if (!inFile)
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	while (!inFile.eof())
	{
		inFile >> dictionary[numDicWords];
		numDicWords++;  
	}
	numDicWords = numDicWords - 1;

	inFile.close();
}

void spellCheck1(char *wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int &numResult)
{
	int length = strlen(wordToCheck);
	int numWords = 0;
	char(*words)[21] = 0;
	findWords(words, numWords, dictionary, numDicWords, length);
	for (int i = 0; i < numWords; i++)
	{
		if (strcmp(words[i], wordToCheck) == 0)
		{
			return;
		}
	}
	char buffer1[21];
	char buffer2[21];
	for (int i = 0; i < numWords; i++)
	{
		for (int j = 0; j < length; j++)
		{
			strcpy_s(buffer1, 21, words[i]);
			strcpy_s(buffer2, 21, wordToCheck);
			buffer1[j] = ' ';
			buffer2[j] = ' ';
			if (strcmp(buffer1, buffer2) == 0)
			{
				strcpy_s(result[numResult], 21, words[i]);
				cout <<  result[numResult] << endl;
				numResult++;
			}
		}
	}
	delete[]words;
}

void spellCheck2(char *wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int &numResult)
{
	int length = strlen(wordToCheck) + 1;
	int numWords = 0;
	char(*words)[21] = 0;
	findWords(words, numWords, dictionary, numDicWords, length);
	char buffer[21];
	buffer[length] = ' ';
	for (int i = 0; i < numWords; i++)
	{
		for (int j = 0; j < length; j++)
		{
			strcpy_s(buffer, 21, words[i]);//buffer=words
			for (int k = j; k < length; k++)
			{
				buffer[k] = buffer[k + 1];
			}
			if (strncmp(buffer, wordToCheck,length-1) == 0)
			{
				strcpy_s(result[numResult],21, words[i]);
				cout <<  result[numResult] << endl;
				numResult++;
			}
		}
	}
	delete[]words;
}

void spellCheck3(char *wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int &numResult)
{
	int length = strlen(wordToCheck) - 1;
	int numWords = 0;
	char(*words)[21] = 0;
	findWords(words, numWords, dictionary, numDicWords, length);
	char buffer[21];
	buffer[strlen(wordToCheck)] = ' ';
	for (int i = 0; i < numWords; i++)
	{
		for (unsigned int j = 0; j < strlen(wordToCheck); j++)
		{
			strcpy_s(buffer, 21, wordToCheck);//buffer=wordToCheck
			for (unsigned int k = j; k < length; k++)
			{
				buffer[k] = buffer[k+1];
			}
			if (strncmp(buffer, words[i],length) == 0)
			{
				strcpy_s(result[numResult], words[i]);
				cout <<  result[numResult] << endl;
				numResult++;
			}
		}
	}
	delete[]words;
}
void findWords(char(*&words)[21], int &numWords,
	char(*dictionary)[21], int numDicWords, int length)
{
	for (int i = 0; i < numDicWords; i++)
	{
		if (strlen(dictionary[i]) == length)//計算字典裡有幾個字長度跟length一樣
		{
			numWords++;
		}
	}
	words = new char[numWords][21];
	numWords = 0;
	for (int i = 0; i < numDicWords; i++)
	{
		if (strlen(dictionary[i]) == length)
		{
			strcpy_s(words[numWords], 21, dictionary[i]);
			numWords++;
		}
	}
}
void saveWords(char(*result)[21], int numResult)
{
	ofstream outFile("Result.txt", ios::out);
	for (int i = 0; i < numResult; i++)
	{
		outFile << result[i] << endl;
		/*if (strcmp(result[i], result[i + 1]) == 0)//判斷result是否有重複
		{
			for (int j = i; j < numResult-1; j++)
			{
				strcpy_s(result[j], 21,result[j+1]);
			}
			numResult--;		
		}
		*/
	}
	outFile.close();
}
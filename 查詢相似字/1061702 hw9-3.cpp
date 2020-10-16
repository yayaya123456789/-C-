#include <iostream>
using namespace::std;
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>

// input all words from the file Dictionary.txt, and put them to the vector "dictionary"
void readDictionary(vector< string > &dictionary);

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is equal to the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the vector "result".
void spellCheck1(string wordToCheck, vector< string > dictionary, vector< string > &result);

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is one greater than the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the vector "result".
void spellCheck2(string wordToCheck, vector< string > dictionary, vector< string > &result);

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is one less than the length of wordToCheck, and
// 2. w is equal to the substring obtained by deleting a character from wordToCheck.
// Put these words into the vector "result".
void spellCheck3(string wordToCheck, vector< string > dictionary, vector< string > &result);

// find the words in the vector "dictionary" whose length is equal to the last parameter "length",
// and puts these words into the vector "words"
void findWords(vector< string > &words, vector< string > dictionary, int length);

// output all words in the vector "result" to the file Words.txt
void saveWords(vector< string > result);

int main()
{
	srand(1);
	vector< string > dictionary;

	readDictionary(dictionary);
	string wordToCheck;
	int numResult = 0;
	vector< string > result;
	
	for (int i = 0; i < 30; i++)
	{
		wordToCheck = dictionary[rand() + dictionary.size() - 32768]; // skip short words
		wordToCheck.erase(rand() % wordToCheck.size(), 1);

		//cout << wordToCheck << endl;
		spellCheck1(wordToCheck, dictionary, result);
		spellCheck2(wordToCheck, dictionary, result);
		spellCheck3(wordToCheck, dictionary, result);
	}

	saveWords(result);

	system("pause");
}

void readDictionary(vector< string > &dictionary)
{
	int numDictionary = 0;
	dictionary.resize(40000);
	ifstream inFile("Dictionary.txt", ios::in);
	while (!inFile.eof())
	{
		inFile >> dictionary[numDictionary];
		numDictionary++;
	}
	numDictionary--;
	dictionary.resize(numDictionary);
	inFile.close();
}

void spellCheck1(string wordToCheck, vector< string > dictionary, vector< string > &result)
{
	unsigned int length = wordToCheck.size();
	vector< string > words;

	findWords(words, dictionary, length);

	for (unsigned int i = 0; i < words.size(); i++)
	{
		if (words[i] == wordToCheck)
		{
			return;
		}
	}
	string buffer1;
	string buffer2;
	buffer1.resize(21);
	buffer2.resize(21);
	for (unsigned int i = 0; i < words.size(); i++)
	{
		for (unsigned int j = 0; j < length; j++)
		{
			buffer1 = words[i];
			buffer2 = wordToCheck;
			buffer1[j] = ' ';
			buffer2[j] = ' ';
			if (buffer1 == buffer2)
			{
				result.push_back(words[i]);
				cout <<  words[i] << endl;
			}
		}
	}
}

void spellCheck2(string wordToCheck, vector< string > dictionary, vector< string > &result)
{
	unsigned int length = wordToCheck.size() + 1;
	vector< string > words;

	findWords(words, dictionary, length);

	string buffer;
	buffer.resize(length);
	buffer[length] = ' ';//第length位丟入空字元
	for (unsigned int i = 0; i < words.size(); i++)
	{
		for (unsigned int j = 0; j < length; j++)
		{
			buffer = words[i];
			for (unsigned int k = j; k < length; k++)
			{
				buffer[k] = buffer[k + 1];
			}
			buffer.resize(length - 1);
			if (buffer == wordToCheck)
			{
				result.push_back(words[i]);
				cout <<  words[i] << endl;
			}
		}
	}
}

void spellCheck3(string wordToCheck, vector< string > dictionary, vector< string > &result)
{
	int length = wordToCheck.size() - 1;
	vector< string > words;

	findWords(words, dictionary, length);

	string buffer;
	buffer.resize(wordToCheck.size());
	buffer[wordToCheck.size()] = ' ';
	for (unsigned int i = 0; i < words.size(); i++)
	{
		for (unsigned int j = 0; j < wordToCheck.size(); j++)
		{
			buffer = wordToCheck;
			for (unsigned int k = j; k < length; k++)
			{
				buffer[k] = buffer[k + 1];
			}
			buffer.resize(length);
			if (buffer == words[i])
			{
				result.push_back(words[i]);
				cout << words[i] << endl;
			}
		}
	}
}

void findWords(vector< string > &words, vector< string > dictionary, int length)
{
	for (unsigned int i = 0; i < dictionary.size(); i++)
	{
		if (dictionary[i].size() == length)
			words.push_back(dictionary[i]);
	}
}

void saveWords(vector< string > result)
{
	ofstream outFile("Result.txt", ios::out);
	for (unsigned int i = 0; i < result.size(); i++)
	{
		outFile << result[i]<< endl ;
	}
	outFile.close();
}
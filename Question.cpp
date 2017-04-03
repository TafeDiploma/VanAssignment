#include "stdafx.h"
#include "Question.h"

//These method has been defined from class.cpp

Question::Question() 
{

}

Question::Question(string input)
{
	qValue = input;
}

string Question::getQuestion()
{
	return qValue;
}

void Question::setQuestion(string question)
{
	qValue = question;
}

void Question::searchQuestion(vector<Question> questions, Question **qAnswer, int qLength, int qWidth)
{
	//Set counting as integer
	float continuing;
	int length = qLength;
	int width = qWidth;
	string enter;

	//Allows the user to search for the number of times
	cout << "How many times do you want to search for? ";

	//User enters the number of times that the user wants to search
	cin >> continuing;

	//If the user have not input integer, repeat this step
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Must be an integer." << endl;
		cout << "How many times do you want to search for? ";
		cin >> continuing;
	}

	//If there are decimal from user input, round it down
	continuing = floor(continuing);

	cout << endl << "You are going to search for " << continuing << " times." << endl;

	//Go through each search
	for (int count = 0; count < continuing; count++)
	{
		//Display this message if the user wants to search more than once
		if (count < continuing)
		{
			//To avoid user pressed enter twice, add this variable to proceed by only press enter once
			int valid = 0;

			//Continue this while user have not press enter only
			do
			{
				//If this is the start of the loop, clear and ignore cin
				if (count == 0 && valid == 0)
				{
					cin.clear();
					cin.ignore(80, '\n');
				}

				//Display this message so that the user press enter to continue
				cout << "Press enter only to continue..." << endl;
				//Get user input and it must be only pressing enter key
				getline(cin, enter);
				//Set valid to 1 to avoid press enter twice
				valid = 1;

			} while (enter != "");

		}

		//Allocate the user to enter keywords to search for questions to find answers
		cout << "Which question do you want to search for? ";

		//Set search as string
		string search;

		//Get the line of input and set for search
		getline(cin, search);

		cout << endl;

		int find = binSearch(search, questions);

		//Check if binary search have found the keyword from the question's array
		if (find != -1)
		{
			cout << "First result found at element " << find << endl << endl;

			for (int column = 0; column < width; column++)
			{
				//Display the questions and answers from the keyword
				cout << qAnswer[find][column].getQuestion() << endl;
			}

		}

		//If the keyword have not compared every questions, display not found
		else
		{
			cout << "'" << search << "' not found!" << endl;
		}

		cout << endl;

		//Go through every character of user input and convert to lowercase
		for (int character = 0; character < search.size(); character++)
		{
			search[character] = tolower(search[character]);
		}

		int otherSearch = 0;

		//Check for the remaining that does contain search
		for (int position = 0; position < length; position++)
		{
			string cases = questions[position].getQuestion();

			for (int characters = 0; characters < cases.size(); characters++)
			{
				cases[characters] = tolower(cases[characters]);
			}

			//If there are other questions that contain search except for the binary search's found result
			if (cases.find(search) != string::npos && questions[position].getQuestion() != questions[find].getQuestion())
			{
				if (otherSearch == 0)
				{
					//Display the remaining questions and answers.
					cout << "These are the other results as following: " << endl << endl;
					otherSearch++;
				}

				for (int column = 0; column < width; column++)
				{
					cout << qAnswer[position][column].getQuestion() << endl;
				}

				cout << endl;
			}
		}

		cout << endl;

	}
}

int Question::binSearch(string name, vector<Question> table) 
{
	/*
	Initialise first to 0, length to the table's size (size of question array)
	and last by the last number of the element of the array
	*/

	int first = 0;

	int length = table.size();

	int last = length - 1;

	//These two for loops allows to match the keywords to the questions easily

	//Go through every character of user input and convert to lowercase
	for (int character = 0; character < name.size(); character++)
	{
		name[character] = tolower(name[character]);
	}

	//Go through every elements in an array and convert to lowercase
	for (int value = 0; value < length; value++)
	{
		string cases = table[value].qValue;

		for (int characters = 0; characters < cases.size(); characters++)
		{
			cases[characters] = tolower(cases[characters]);
		}

		table[value] = cases;

	}

	//Continue until first is greater than last
	while (first <= last)
	{
		//Split the array into two to identify the middle in the binary tree
		int middle = (first + last) / 2;

		/*
		Start from the first character until the length of name from table[middle] and compare,
		if the first few characters match with name, result will be 0, if alphabetically,
		name is first and then table[middle], result will be 1, otherwise, result
		will be -1.
		*/

		int result = strncmp(table[middle].qValue.c_str(), name.c_str(), name.size());

		/*
		If result less than 0, set first by increment middle by 1, only the first half
		are declare to check.
		*/

		if (result < 0)
		{
			first = middle + 1;
		}

		/*
		If result greater than 0, set last by decrement middle by 1, only the last half
		are declare to check.
		*/

		else if (result > 0)
		{
			last = middle - 1;
		}

		//If result equals to 0, return middle for decalring that first result have been found

		else
		{
			return middle;
		}

	}

	//If the binary search has not succeed searching, then do a linear search for each questions
	for (int position = 0; position < table.size(); position++)
	{
		//If the user input has contains in the array, return this position
		if (table[position].qValue.find(name) != string::npos)
		{
			return position;
		}
	}


	return -1; // name is not in table[]
}

void Question::sortFile(vector<vector<Question>> question, int qLength, int qWidth) 
{
	cin.clear();
	cin.ignore();
	int length = qLength;
	int width = qWidth;
	string fileName;
	cout << "Enter file to store sorted questions: (Empty input means no file saved) ";

	//Get a line of input and set the line from fileName
	getline(cin, fileName);

	//Create the text file using binary file
	ofstream newFile(fileName, ios::binary | ios::out);

	//Write sort array to new file or existed file
	for (int rows = 0; rows < length; rows++)
	{
		for (int cols = 0; cols < width; cols++)
		{
			newFile << question[rows][cols].getQuestion() << endl;
		}

	}

	//Display file is saved if it was filled
	if (fileName != "")
	{
		cout << fileName << " saved." << endl;
	}

	newFile.close();
}

void Question::binaryFile(vector<vector<Question>> question, int qLength, int qWidth)
{
	cin.clear();
	cin.ignore();
	string fileName;
	int length = qLength;
	int width = qWidth;

	//Create binary file for 2D array
	cout << "If you want to see sorted array from console." << endl;
	cout << "Enter binary file to store sorted questions: (Empty input means no file saved) ";

	//Get a line of input and set the line from fileName
	getline(cin, fileName);

	//Create the text file using binary file and write the array to the file into binary and read back
	fstream binaryFile(fileName, ios::binary | ios::out | ios::in);

	if (fileName != "")
	{

		//Write down the 2d array into a binary file
		for (int rows = 0; rows < length; rows++)
		{
			for (int cols = 0; cols < width; cols++)
			{
				question[rows][cols].save(binaryFile);
			}
		}

		cout << endl << "Write to binary file sucessful." << endl << endl;

		cout << "Reading from binary file " << fileName << "..." << endl << endl;

		/*
		When writing is completed, return to the first character at the beginning of the file
		using random access algorithm
		*/

		binaryFile.seekg(0, ios::beg);

		Question **questionArray = new Question*[length];

		//Add another array for questionArray to make 2d array
		for (int count = 0; count < length; ++count)
		{
			questionArray[count] = new Question[width];
		}

		//Read a binary file
		for (int rows = 0; rows < length; rows++)
		{
			for (int cols = 0; cols < width; cols++)
			{
				//Store the binary data into the array and then convert as text
				questionArray[rows][cols].load(binaryFile);
			}
		}

		//Display array as text conversion using different array
		for (int rows = 0; rows < length; rows++)
		{
			//Display sorted array
			for (int cols = 0; cols < width; cols++)
			{
				cout << questionArray[rows][cols].getQuestion() << endl;
			}

			cout << endl;
		}

		/*
		Release memory allocate from questionArray for the whole elements because the array was
		being stored from the file
		*/

		delete[] questionArray;

		questionArray = nullptr;
	}

	//Close binary if necessary, empty or not
	binaryFile.close();
}

//It is recommended to write and read from class because the main program used class object arrays
void Question::save(fstream& of) 
{
	//Write the array's element into the binary file using the qValue as a character pointer
	of.write((char*)&qValue, sizeof(qValue));
}

void Question::load(fstream& inf) 
{
	//Read the array's element from the binary file using the qValue as a character pointer
	inf.read((char*)&qValue, sizeof(qValue));
}


// ShowMeKnowledge.cpp : Defines the entry point for the console application.
//

/*
Creator Name:

Van Do

Creation Date:

6 February 2017

Description of what the Application does:

This application allows the user to get the file and letting the system to sort. Also, this system
allows user to search for the question using keywords to find the answer. Completed (05/03/2017)
Modified (20/03/2017)

*/

#include "stdafx.h" //Allows the application to works
#include <fstream> //Use for open file and write file
#include <string> //Use for accepting the string variable
#include <algorithm> //Use for sorting array and binary search
#include <vector> //Use for vector that allows to sort and search array easily
#include "Question.h" //Use the header file contains Question class

using namespace std; //Use for cin, cout and string


//When using cin.clear(), it will clear out the memory of every user input


//Sort 2D array using vector by pass-by-reference of the vectors
bool sortVector(vector<Question> &lhs, vector<Question> &rhs)
{
	//Return if the left hand side of the vector's element is less than the right hand side = true or false
	return lhs[0].getQuestion() < rhs[0].getQuestion();
}

void sortArray(vector<vector<Question>> question, int length, int width)
{
	cout << "Before sorted..." << endl << endl;

	
	for (int rows = 0; rows < length; rows++)
	{
		cout << question[rows][0].getQuestion() << endl;
	}

	cout << endl;

	//Sort 2d array
	//Sort the array using algorithm and the method 'sortVector'
	sort(question.begin(), question.end(), sortVector);

	cout << "After sorted..." << endl << endl;

	for (int rows = 0; rows < length; rows++)
	{
		cout << question[rows][0].getQuestion() << endl;
	}

}

int main()
{
	//Set line as string for checking line in a file
	string line;
	//For valid user press enter to continue
	string enter;
	//Set object as question object
	Question object = Question();

	//Store question and answer into a vector
	vector<vector<Question>> twoArray;

	//Store question and answer into a vector for the first options in modular programming
	vector<vector<Question>> existArray;

	//Display the instruction to get file from 

	cout << "This program allows to sort all of your questions and search for answers from the file." << endl;

	cout << "You can only use one file for this application." << endl;

	cout << "Enter file name (eg. example.txt): ";

	string fileName;

	//Get a line of input and set the line from fileName
	getline(cin, fileName);

	//Read the text file using binary file
	ifstream file(fileName, ios::in | ios::binary);

	cin.clear();

	//Set 2d array of question object array, set rows by user input
	//and cols by user input for question and answer

	cout << endl << "Set the number of questions and answers in array." << endl;

	cout << "Whatever number you input will be round down. For example (Between 3 and 4, the value will be 3)." << endl;

	cout << "If there are letters after number for trying to input number, the letters will be truncate." << endl;

	cout << "Make sure that all questions have same number of answers." << endl << endl;

	//Allows the user to enter the number of questions, assuming questions are length

	float length;

	do 
	{
		cout << "Enter number of questions: ";

		cin >> length;

		//If user have not input integer, repeat this process
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Must be a number." << endl;
			cout << "Enter the number of questions: ";
			cin >> length;
		}

		//Check if the number of questions is less than 1, then repeat this process again
		if (length < 1) 
		{
			cout << "The number of elements for rows must be greater than 0." << endl;
			cout << "Cannot have empty question." << endl;
		}

	} while (length < 1);

	//When length is confirm, set the user input as length

	/*
		Allows the user to enter the number of answers, however the user must add one because
		2d array must include question and answers. Therefore, column 0 is question while the rests are
		answers.
	*/

	//If there are decimal from user input, round it down
	length = floor(length);

	//Assuming width is answer including one question
	float width;

	//Similar to length, expect set for columns of array
	do 
	{
		cout << "Enter number of answers per question: ";

		cin >> width;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Must be a number." << endl;
			cout << "Enter the number of answers: ";
			cin >> width;
		}

		//Check if the user input is less than 1, then repeat this process again
		if (width < 1) 
		{
			cout << "The number of elements for columns must be greater than 0." << endl;
			cout << "Every question must have at least one answer." << endl;
		}

	} while (width < 1);

	//If there are decimal from user input, round it down
	width = floor(width) + 1;

	cout << endl << "Number of questions: " << length << "." << endl;

	cout << endl << "Number of answers per question: " << width - 1 << "." << endl << endl;

	//Multiply the length and width to get elements, so that validate the number of lines in the file
	int elements = length * width;

	//Set the array for qObject as pointer to set the length as user input
	Question **qObject = new Question*[length];

	//Add another array for qObject to make 2d array
	for (int count = 0; count < length; ++count)
	{
		qObject[count] = new Question[width];
	}

	//Resize the vector length to 10
	twoArray.resize(length);

	//Resize each of element's columns by 2
	for (int count = 0; count < length; count++)
	{
		twoArray[count].resize(width);
	}
	
	//Resize the vector length to 10
	existArray.resize(length);

	//Resize each of element's columns by 2
	for (int count = 0; count < length; count++)
	{
		existArray[count].resize(width);
	}

	//Check if this file does not exist or cannot be open, display this message and repeat the application again
	if (!file.is_open())
	{
		cout << "Couldn't open file" << endl << endl;
		cin.clear();
		cin.ignore();
		main();
	}

	//If file can be open, do this condition
	else
	{
		cout << "File open success..." << endl << endl;

		//Set counting to 0
		int counting = 0;

		//Go through every line and increment counting by 1
		while (!file.eof()) 
		{
			getline(file, line);
			counting++;
		}

		//Move from the start of the file to avoid close and reopen file using random access
		file.seekg(0, ios::beg);

		//If the elements are greater than the number of lines, repeat the application again
		if (elements > counting) 
		{
			cout << "The set rows and columns multiply together are too big." << endl;
			cout << "There are only " << counting << " lines not " << elements << "." << endl;
			cout << "Please check your files and make sure the number of lines equals to the number of elements." << endl;
			cout << "Press enter to repeat process again." << endl;
			cin.clear();
			cin.ignore();
			cin.get();
			main();
		}

		//If the elements are less than the number of lines, repeat the application again
		else if (elements < counting)
		{
			cout << "The set rows and columns multiply together are too small." << endl;
			cout << "There are only " << counting << " lines not " << elements << "." << endl;
			cout << "Please check your files and make sure the number of lines equals to the number of elements." << endl;
			cout << "Press enter to repeat process again." << endl;
			cin.clear();
			cin.ignore();
			cin.get();
			main();
		}

		//Continuing adding line to the array while it does not reach to the end of the line
		while (!file.eof())
		{
			//Add to 2D array from row 0 to max row
			for (int row = 0; row < length; row++)
			{
				//For every line add to 2D array from col 0 to max col
				//Manipulate 2D array by reading file and add line from file to array
				for (int col = 0; col < width; col++)
				{
					//Get the line from file and set to line
					getline(file, line);
					//Add line to question array
					qObject[row][col] = Question(line);
					//Add question array to vector
					twoArray[row][col] = qObject[row][col];
					existArray[row][col] = qObject[row][col];

				}
			}
		}
	}

	//Close this file
	file.close();

	//Set options as integer and questions as vector of question
	int options;
	vector<Question> questions;

	do {
		//Display modular programming
		cout << "Select options to do with this application." << endl;
		cout << "Sort Array (1)" << endl;
		cout << "Binary Search Array(2) " << endl;
		cout << "Save Sorted Array in Text File(3)" << endl;
		cout << "Write and Read Binary File(4)" << endl;
		cout << "Exit(0)" << endl;

		cin >> options;

		//User repeatly entering unless it is an integer
		while (cin.fail()) 
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Must be a number." << endl;
			cout << "Select option: ";
			cin >> options;
		}

		switch (options)
		{
			case 1:
				//Display unsorted and sorted array using the existing unsorted vector
				sortArray(existArray, length, width);
			break;

			case 2:
				sort(twoArray.begin(), twoArray.end(), sortVector);
				//Store question into this array for binary search

				questions.resize(length);

				for (int rows = 0; rows < length; rows++)
				{
					for (int cols = 0; cols < width; cols++)
					{
						qObject[rows][cols] = twoArray[rows][cols];
					}

				}

				//Store twoArray's questions into question array
				for (int rows = 0; rows < twoArray.size(); rows++)
				{
					questions[rows] = twoArray[rows][0].getQuestion();
				}

				//Proceed to searching for array
				cout << "Sorting questions completed..." << endl;

				cout << "Search for question and answer..." << endl << endl;

				object.searchQuestion(questions, qObject, length, width);

			break;

			case 3:
				//To write sort array into file, it must be sorted first
				sort(twoArray.begin(), twoArray.end(), sortVector);

				//Get object method to write array into text file
				object.sortFile(twoArray, length, width);
			break;

			case 4:
				//To write sort array into file, it must be sorted first
				sort(twoArray.begin(), twoArray.end(), sortVector);

				//Get object method to write and read binary file from 2d class object array
				object.binaryFile(twoArray, length, width);
			break;

			//Allow to exit this loop
			case 0:
			break;

			//Display invalid input when user does not select options
			default:
				cout << "Invalid input." << endl;
			break;

			cin.clear();

		}

		cout << endl;

	} while (options != 0);

	//Release memory allocate from qObject
	delete[] qObject;

	//qObject becomes null pointer
	qObject = nullptr;

	cin.ignore();

    return 0;
}
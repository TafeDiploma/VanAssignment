#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Question
{
	//Privatise the variable
	private:
		string qValue; //Value can be a question or answer

	//Publicise the method for source file to access
	public:

		//These method has been left as declaration.

		//Null constructor
		Question();
		//Parameterised constructor, set qValue by the file line
		Question(string input);
		//However, the getters are the only method that can be used for the source code
		//Getters
		string getQuestion();
		//Setters
		void setQuestion(string question);
		//Search questions to find answer
		void searchQuestion(vector<Question> questions, Question **qAnswer, int qLength, int qWidth);
		//This method allows to use binary search and return the found element
		int binSearch(string name, vector<Question> table);
		//Write sorted array in text file
		void sortFile(vector<vector<Question>> question, int qLength, int qWidth);
		//This method allows to write and read binary file using the 2d array
		void binaryFile(vector<vector<Question>> question, int qLength, int qWidth);
		//This method allows to write array into a binary file
		void save(fstream& of);
		//This method allows to read and decipher a binary file
		void load(fstream& inf);
};


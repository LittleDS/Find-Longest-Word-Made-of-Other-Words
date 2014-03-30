/*
* WordCombine.cpp
*
*  Created on: Mar 29, 2014
*      Author: Administrator
*/
#include <Trie.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iterator>

using namespace std;

int BuildTrie(const string &filename, Trie* &trie, vector<string> &dict) {
	//Use this variable to count the total number of words in the file
	int totalWords = 0;

	ifstream ifs(filename, ifstream::in);

	//Check the whether the file exists
	if (!ifs) {
		return -1;
	}

	istream_iterator<string> itr_word(ifs), itr_word_end;
	for (; itr_word != itr_word_end; itr_word++, totalWords++) {
			//Push the word into a vector
			dict.push_back(*itr_word);

			//Add the word the Trie
			trie->addWord(*itr_word);
	}

	ifs.close();

	return totalWords;
}

int isConcate(Trie *trie, const string &str, unsigned int start, unsigned int end) {
	//the local variable used to store the current piece of word
	string locals = str.substr(start, end - start + 1);

	//the positions of all the possible prefix of the word
	vector<unsigned int> *pos = trie->partialMatch(locals);
	vector<unsigned int>::iterator it;

	//for all the possible prefixes, we cut out the second part and check whether it's a concatenated word
	for (it = pos->begin(); it != pos->end(); it++) {
		//if the current prefix is a word
		if (*it == locals.length() - 1)
			return 1;

		//recursively check the second part
		int secondPart = isConcate(trie, locals, *it + 1, locals.length());

		//if the second part is made of more than one word, then we found a concatenated word
		if (secondPart > 0)
			return 1 + secondPart;
	}

	//Recycle the vector space
	delete pos;

	return 0;
}

int main() {
	//The times
	clock_t t = clock();

	//The Trie built for all the words in the dictionary
	Trie* trie = new Trie();

	//The input file's name
	const string filename = "wordsforproblem.txt";

	//The vector to store the dictionary
	vector<string> dict;

	//Read the dictionary file and build the trie
	int wordCount = BuildTrie(filename, trie, dict);

	if (wordCount < 0) {
		cout << "The input file doesn't exist or the file name is wrong." << endl;
	}

	vector<string>::iterator it;
	
	//Variable to store the longest and second longest concatenated word
	string longestWord, secondLongestWord;	
	unsigned int maxLeng = 0, secondMaxLeng = 0;

	//count of total number of concatenated word
	int count = 0;

	for (it = dict.begin(); it != dict.end(); it++) {
		if (isConcate(trie, *it, 0, (*it).size()) > 1) {

			//Mark the longest concatenated word
			if ((*it).size() > maxLeng) {
				maxLeng = (*it).size();
				longestWord = *it;
			}

			//Mark the second longest one
			else if ((*it).size() > secondMaxLeng) {
				secondMaxLeng = (*it).size();
				secondLongestWord = *it;
			}

			//Count the total number of concatenated word
			count++;
		}
	}
	
	//Output the result;
	cout << longestWord << " " << secondLongestWord << " " << count << endl;
	
	//Output the total running time
	t = clock() - t;
	cout << ((double)t) / CLOCKS_PER_SEC;

	//Recycle the used memory
	delete trie;

	return 0;
}



/*
* Trie.h
*
*  Created on: Mar 28, 2014
*      Author: Lei Yang
*/

#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <vector>
using namespace std;

//Since the problem statement shows that there are only lower-case letters
//the total number of different characters is 26
#define NUM_CHARS 26

class TrieNode {
	//For simplicity I just set all the variables as public
	//In real application, we should add the getters and setters for the variables
public:
	bool isLeaf;
	TrieNode *children[NUM_CHARS];
	TrieNode() :isLeaf(false) {
		for (int i = 0; i < NUM_CHARS; i++) {
			children[i] = NULL;
		}
	}
	~TrieNode() {
		for (int i = 0; i < NUM_CHARS; i++) {
			//Need to check whether the children pointers is null
			//If not, the program may try to recycle a non-existing space
			if (children[i] != NULL) {
				delete children[i];
			}
		}
	}
};

class Trie {
public:
	Trie();
	~Trie();
	//Add a word into the Trie
	void addWord(const string &str);

	//Check if a word belongs to the dictionary
	bool searchWord(const string &str);

	//Given a string, list all the possible prefixes of this str, which are a word in the dictionary
	vector<unsigned int> *partialMatch(const string &str);

private:
	TrieNode *root;
};


#endif /* TRIE_H_ */

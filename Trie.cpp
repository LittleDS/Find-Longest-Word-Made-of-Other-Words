/*
* Trie.cpp
*
*  Created on: Mar 28, 2014
*      Author: Lei Yang
*/
#include <Trie.h>
#include <iostream>
using namespace std;

//Default Constructor
Trie::Trie() {
	root = new TrieNode();
}

//Destructor
Trie::~Trie() {
	delete root;
}


/**
 * Add a word into the Trie
 */
void Trie::addWord(const string &str) {
	TrieNode* current = root;
	if (str.length() == 0) {
		return;
	}

	for (unsigned int i = 0; i < str.length(); i++) {
		//Convert the character into int position
		TrieNode **child = &(current->children[str[i] - 'a']);

		//If the child is NULL, we need to create a new edge
		if (*child != NULL) {
			current = *child;
		}
		else {
			TrieNode* tmp = new TrieNode();
			*child = tmp;
			current = tmp;
		}
		//If this is the last character in the word, we need to mark the trienode as a leaf
		if (i == str.length() - 1)
			current->isLeaf = true;
	}

}

/**
 * Given a string, list all the possible prefixes of this str, which are a word in the dictionary
 * By searching all the possible prefixes of the given string using this linear time algorithm,
 * We can avoid repeatedly searching the prefixes in the Trie again and again.
 * For example, if we know that "apple" is a word in the Trie, but none of the prefixes of "apple" are words in Trie
 * This optimization can help us just searching the Trie once, instead of "a", "ap", "app", "appl", "apple", five times
 */
vector<unsigned int> *Trie::partialMatch(const string &str) {
	TrieNode *current = root;
	vector<unsigned int> *result = new vector<unsigned int>;
	if (current != NULL) {
		for (unsigned int i = 0; i < str.length(); i++) {
			TrieNode *tmp = current->children[str[i] - 'a'];

			if (tmp == NULL)
				return result;
			current = tmp;
			
			//The current node is a leaf, which means that we have found a word
			if (current->isLeaf)
				result->push_back(i);
		}
	}
	return result;
}

/**
 * This method can be used as the traditional way to solve this problem
 */
bool Trie::searchWord(const string &str) {
	TrieNode *current = root;
	if (current != NULL) {

		for (unsigned int i = 0; i < str.length(); i++) {

			TrieNode* tmp = current->children[str[i] - 'a'];
			if (tmp == NULL)
				return false;
			current = tmp;
		}

		//If the last node of the given string is a leaf, then we found this word in Trie
		if (current->isLeaf)
			return true;
		else
			return false;
	}

	return false;
}


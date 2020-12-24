#include "trie.h"
#include <iostream>

// trieNode Constructor

void trie::addWord(std::string word) {
    //several cases.
    //case 1) already exists in the trie
    //case 2) is is prefix of word in trie
    //case 3) it is partial suffix of existing string
    //case 4) is not suffix of any string
    trieNode *letter, *currentNode = root; 
    std::string::iterator end = word.end();
    for (std::string::iterator c = word.begin(); c != end; c++) {
        if (currentNode->nextLetter[*c - 'a'])
            // if it already exists then just continue on
            currentNode = currentNode->nextLetter[*c - 'a'];
        else { 
            // make a new node
            trieNode* newNode =  new trieNode;
            newNode->parent = currentNode;
            currentNode->nextLetter[*c - 'a'] = newNode;
            currentNode = newNode;
        }
    }
    currentNode->isWord = true;
}

bool trie::search(std::string word) {
    trieNode* current = root; 
    std::string::iterator end = word.end();
    for (std::string::iterator c = word.begin(); c != end; c++) {
        if (!current->nextLetter[*c - 'a']) 
            return false;
        current = current->nextLetter[*c - 'a'];
    }
    if (current->isWord)
        return true;
    else 
        return false;
}


bool trie::deleteWord(std::string word) {
    // guess what endOfWord does?
    trieNode *current = endOfWord(word), *deleteMe;
    if (!search(word))
        return false;
    if (current->hasChildren()) {
        current->isWord = false;
        return true;
    }
    std::string::reverse_iterator end = word.rend();
    for (std::string::reverse_iterator c = word.rbegin(); c != end; c++) {
        deleteMe = current;
        current = current->parent;
        delete deleteMe;
        current->nextLetter[*c - 'a'] = nullptr;
        if (current->hasChildren() || current->isWord) {
            break;
        }
    }
    return true;
}

void trie::print(std::string prefix) {
    trieNode* current = root;
    std::string::iterator end = prefix.end();
    for (std::string::iterator c = prefix.begin(); c != end; c++) {
        if (current->nextLetter[*c -'a'] == nullptr){
            std:: cout << "error"; 
            return;
        }
        current = current->nextLetter[*c - 'a'];
    }
    // up until now all we've done is locate the node to start from
    print(prefix, current); 
}


void trie::print(std::string prefix, trieNode* current) {
    const std::string givenPrefix = prefix; // save the prefix to use again
    for (int i = 0; i < LETTERS; ++i) {
        prefix = givenPrefix;
        if (current->nextLetter[i]) {
            prefix.push_back(i + 'a');
            if (current->nextLetter[i]->isWord) {
                std::cout << prefix << std::endl;
            }
            if (current->nextLetter[i]->hasChildren())
                print(prefix, current->nextLetter[i]);
        }
    }
}

trie::trieNode* trie::endOfWord(std::string word) {
    trieNode* current = root;
    std::string::iterator end = word.end();
    for (std::string::iterator c = word.begin(); c != end; c++) {
        current = current->nextLetter[*c - 'a'];
    }
    return current;
}

bool trie::searchPrefix(std::string word) {
    trieNode* current = root; 
    std::string::iterator end = word.end();
    for (std::string::iterator c = word.begin(); c != end; c++) {
        if (current->nextLetter[*c - 'a'] == nullptr) 
            return false;
        current = current->nextLetter[*c - 'a'];
    }
    return true;
}


//trieNode function definitions

trie::trieNode::trieNode() {
    for (int i = 0; i < LETTERS; ++i)
        nextLetter[i] = nullptr;
    parent = nullptr;
    isWord = false;
};

bool trie::trieNode::hasChildren() {
    for (int i = 0; i < LETTERS; ++i) {
        if (nextLetter[i])
            return true;
    }
    return false;
}
















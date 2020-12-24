#include <string>

const int LETTERS = 26;
class trie {
    class trieNode {
        friend class trie;
        public:
        trieNode* nextLetter[LETTERS];
        bool isWord;
        trieNode* parent;

        trieNode();
        bool hasChildren();
        void addLetter(char);
        bool deleteLetter(char);

    };
    trieNode* root;

    //public interface
    public: 
        trie() { root = new trieNode; }
        void addWord(std::string);
        bool deleteWord(std::string);
        bool search(std::string);
        void print(std::string);
        bool searchPrefix(std::string);

    private: 
        trieNode* endOfWord(std::string);
        void print(std::string prefix, trieNode* current);

};

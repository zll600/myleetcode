#include <vector>
#include <string>

using namespace std;

class Trie {
 public:
    Trie() : root_(new TrieNode()) {}

    void Insert(const string str) {
        TrieNode *node = root_;
        
        for (char c : str) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->end = true;
    }

    bool Search(const string& str) {
        TrieNode *node = root_;
        
        for (char c : str) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[i];
        }
        return node->end;
    }


 private:
    struct TrieNode {
        bool end;
        vector<TrieNode*> children;

        TrieNode() : end(false), children(std::move(vector<TrieNode*>(26, nullptr))) {}
        ~TrieNode() {
            for (int i = 0; i < 26; ++i) {
                if (children[i]) {
                    delete children[i];
                }
            }
        }
    };

    TrieNode *root_;
};

/*
solution link: https://leetcode.com/problems/implement-trie-prefix-tree/
*/

class TrieSaver {
public:
    char cur;
    set<TrieSaver*> childs;
    TrieSaver* addChild(char chr) {
        TrieSaver *newNode;
        newNode = new TrieSaver();
        newNode->cur = chr;
        this->childs.insert(newNode);
        return newNode;
    }
};

class Trie {
public:
    TrieSaver* head;
    set<string> words;
    Trie() {
        head = new TrieSaver();
        head->cur = '*';
    }
    
    void insert(string word) {
        words.insert(word);
        TrieSaver *curr = head;
        for(int i=0; i<word.length(); i++) {
            bool flag = false;
            for(auto itr : curr->childs) {
                if(word[i] == itr->cur) {
                    flag = true;
                    curr = itr;
                    break;
                }
            }
            if(!flag) {
                curr = curr->addChild(word[i]);
            }
        }
    }

    bool dfs(string& word, TrieSaver* cur, int i, bool mode) {
        if(i>=word.length()) {
            if(mode) return mode;
            return words.find(word)!=words.end();
        }
        for(auto itr : cur->childs) {
            if(word[i] == itr->cur) {
                bool ans = dfs(word, itr, i+1, mode);
                if(ans) return true;
            }
        }
        return false;
    }
    
    bool search(string word) {
        return dfs(word, head, 0, false);
    }
    
    bool startsWith(string prefix) {
        return dfs(prefix, head, 0, true);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
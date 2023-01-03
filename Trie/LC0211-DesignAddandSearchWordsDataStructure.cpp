


// https://gist.github.com/SuryaPratapK/b8026d68f077d3e9551c61bde2f771f4

input = ["WordDictionary","addWord","addWord","search","search","search","search","search","search"]
[[],["a"],["a"],["."],["a"],["aa"],["a"],[".a"],["a."]]

output = [null,null,null,true,true,false,true,false,false]
expected = [null,null,null,true,true,false,true,false,false]

input = ["WordDictionary","search"]
[[],["a"]]

output = [null,true]

expected = [null,false]


        class Node{
private:
    Node* al[26];
    bool terminates = false;

public:
    bool containsKey(char c){
        return al[c-'a'] != nullptr;
    }

    void addKey(char c, Node* n){
        al[c-'a'] = n;
    }

    Node* getChildKey(char c){
        return al[c-'a'];
    }

    void setEnd(){
        terminates = true;
    }

    bool isEnd(){
        return terminates;
    }
};

class WordDictionary {
Node* root;
public:
    WordDictionary() {
       root = new Node();
    }

    void addWord(string word) {
        Node* n = root;
        for(char c : word){
            if(!n->containsKey(c)){
                n->addKey(c, new Node());
            }
            n = n->getChildKey(c);
        }
        n->setEnd();
    }

    bool fn(int idx, Node* node, string& s){
        if(s[idx] == '.'){
            bool res = false;
            Node* current = node;
            for(int i='a'; i < 'a'+26; ++i){
                if(idx == (s.size()-1) && node->containsKey(i)){
                    current = node->getChildKey(i);
                    res |= current->isEnd();
                }
                else if (node->containsKey(i) && fn(idx+1, node->getChildKey(i), s))
                    return true;
            }
            return res;
        }
        else if(node->containsKey(s[idx])){
            if(idx == (s.size()-1)){
                node=node->getChildKey(s[idx]);
                return  node->isEnd();
            }
            return fn(idx+1,node->getChildKey(s[idx]), s);
        }
        return false;
    }

    bool fn2(int idx, Node* node, string& s){
        int len = s.size();

        for(int i = idx; i < len; ++i){
            if(s[i] == '.'){
                for(int j = int('a'); j < int('a'+26); ++j){
                    if(node->containsKey(j)){
                        if(fn(i+1, node->getChildKey(j), s)) return true;
                    }
                }
                return false;
            }
            else {
                if(node->containsKey(s[i])){
                    node = node->getChildKey(s[i]);
                }
                else {
                    return false;
                }
            }
        }
        return node->isEnd();
    }

    bool search(string word) {
        Node* node = root;
       return fn(0, node, word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
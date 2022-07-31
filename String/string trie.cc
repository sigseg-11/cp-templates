template <const unsigned int SIGMA>
class Trie {
   private:
    class Node {
       public:
        int child[SIGMA];
        int parent, value;
        char numbOfChildren;

        Node() : child(), parent(), value(), numbOfChildren() {
            memset(child, 0, sizeof child);
        }
    };

    inline int alloc() {
        if (stack.empty() == true) {
            if (trie.size() == static_cast<size_t>(cellPos))
                trie.push_back(trie[0]);  /// trie[0] = dummy node

            return cellPos++;
        } else {
            int t = stack.back();
            stack.pop_back();
            return t;
        }
    }

    inline void dealloc(const int pos) { stack.push_back(pos); }

    vector<Node> trie;
    vector<int> stack;
    int cellPos;

   public:
    Trie() : trie(16), stack(0), cellPos(2) {}

    ~Trie() { this->clear(); }

    void clear() {
        trie.clear();
        stack.clear();
        cellPos = 2;
    }

    void insert(const string &str) {
        int root = 1;

        for (const char &ch : str) {
            int c = ch - 'a';

            if (trie[root].child[c] == 0) {
                int t = alloc();

                trie[root].child[c] = t;
                trie[trie[root].child[c]].parent = root;
                trie[root].numbOfChildren++;
            }

            root = trie[root].child[c];
        }

        trie[root].value++;
    }

    void erase(const string &str) {
        int root = 1;

        for (const char &c : str) root = trie[root].child[c - 'a'];

        if (root != 0) {
            trie[root].value--;
            size_t i = str.size();

            while (trie[root].value == 0 && !trie[root].numbOfChildren &&
                   (root != 1)) {
                i--;
                dealloc(root);
                root = trie[root].parent;
                trie[root].child[str[i] - 'a'] = 0;
                trie[root].numbOfChildren--;
            }
        }
    }

    int count(const string &str) const {
        int root = 1;
        size_t i = 0;

        while (i < str.size() && trie[root].child[str[i] - 'a']) {
            root = trie[root].child[str[i] - 'a'];
            i++;
        }

        if (i == str.size())
            return trie[root].value;
        else
            return 0;
    }

    int prefixMatch(const string &str) const {
        int root = 1;
        size_t i = 0;

        while (i < str.size() && trie[root].child[str[i] - 'a']) {
            root = trie[root].child[str[i] - 'a'];
            i++;
        }

        return static_cast<int>(i);
    }
};
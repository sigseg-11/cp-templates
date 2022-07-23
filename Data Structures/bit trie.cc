// add(x, id): Add x
// del(x, id): Remove x
// find(x) : Check if x exists. The return value is pair (number of pieces, set of indexes)
// max_element()/min_element() : Returns the maximum/minimum value. The return value is pair (maximum/minimum value, set of indexes)
// get_kth() : Returns the kth value. The return value is pair (a set of values, indexes)
// operate_xor(x) : Let xor act on the entire set.

template <typename T = int, int MAX_LOG = 30, int NODES = 16777216>
struct BinaryTrie {
  using Container = vector<int>;
  struct Node {
    Node *nxt[2];
    // Todo
    int exist;
    Container accept;
    Node() {}
  };

  Node *pool;
  int pid;
  T lazy;
  Node *nil;
  Node *root;

  BinaryTrie() : pid(0), lazy(T(0)), nil(nullptr) {
    pool = new Node[NODES];
    nil = my_new();
    nil->nxt[0] = nil->nxt[1] = root = nil;
  }

  Node *my_new(int exist_ = 0, int id = -1) {
    pool[pid].nxt[0] = pool[pid].nxt[1] = nil;
    pool[pid].exist = exist_;
    if (id != -1) pool[pid].accept.push_back(id);
    return &(pool[pid++]);
  }

  Node *merge(Node *l, Node *r) {
    pool[pid].nxt[0] = l;
    pool[pid].nxt[1] = r;
    pool[pid].exist = l->exist + r->exist;
    return &(pool[pid++]);
  }

 private:
  Node *add_(const T &x, int id, Node *n, int bit_idx) {
    if (bit_idx == -1) {
      if (n == nil) return my_new(1, id);
      n->exist++;
      n->accept.push_back(id);
      return n;
    } else {
      if (((lazy >> bit_idx) & 1) == ((x >> bit_idx) & 1))
        return merge(add_(x, id, n->nxt[0], bit_idx - 1), n->nxt[1]);
      else
        return merge(n->nxt[0], add_(x, id, n->nxt[1], bit_idx - 1));
    }
  }

 public:
  void add(const T &x, int id = -1) { root = add_(x, id, root, MAX_LOG); }

 private:
  Node *del_(const T &x, int id, Node *n, int bit_idx) {
    if (bit_idx == -1) {
      n->exist--;
      return n;
    } else {
      if (((lazy >> bit_idx) & 1) == ((x >> bit_idx) & 1))
        return merge(del_(x, id, n->nxt[0], bit_idx - 1), n->nxt[1]);
      else
        return merge(n->nxt[0], del_(x, id, n->nxt[1], bit_idx - 1));
    }
  }

 public:
  void del(const T &x, int id = -1) { root = del_(x, id, root, MAX_LOG); }

 private:
  pair<int, Container &> find_(const T &x, Node *n, int bit_idx) {
    if (bit_idx == -1)
      return pair<int, Container &>(n->exist, n->accept);
    else {
      if (((lazy >> bit_idx) & 1) == ((x >> bit_idx) & 1))
        return find_(x, n->nxt[0], bit_idx - 1);
      else
        return find_(x, n->nxt[1], bit_idx - 1);
    }
  }

 public:
  pair<int, Container &> find(const T &x) { return find_(x, root, MAX_LOG); }

 private:
  pair<T, Container &> max_element_(Node *n, int bit_idx) {
    if (bit_idx == -1) return pair<T, Container &>(0, n->accept);
    if (n->nxt[~(lazy >> bit_idx) & 1]->exist) {
      auto ret = max_element_(n->nxt[~(lazy >> bit_idx) & 1], bit_idx - 1);
      ret.first |= T(1) << bit_idx;
      return ret;
    } else {
      return max_element_(n->nxt[(lazy >> bit_idx) & 1], bit_idx - 1);
    }
  }

 public:
  pair<T, Container &> max_element() { return max_element_(root, MAX_LOG); }

 private:
  pair<T, Container &> min_element_(Node *n, int bit_idx) {
    if (bit_idx == -1) return pair<T, Container &>(0, n->accept);
    if (n->nxt[(lazy >> bit_idx) & 1]->exist) {
      return min_element_(n->nxt[(lazy >> bit_idx) & 1], bit_idx - 1);
    } else {
      auto ret = min_element_(n->nxt[~(lazy >> bit_idx) & 1], bit_idx - 1);
      ret.first |= T(1) << bit_idx;
      return ret;
    }
  }

 public:
  pair<T, Container &> min_element() { return min_element_(root, MAX_LOG); }

 private:
  pair<T, Container &> get_kth_(Node *n, int64_t k, int bit_idx) {
    if (bit_idx == -1) return pair<T, Container &>(0, n->accept);
    int ex0 = n->nxt[(lazy >> bit_idx) & 1]->exist;
    if (ex0 < k) {
      auto ret = get_kth_(n->nxt[~(lazy >> bit_idx) & 1], k - ex0, bit_idx - 1);
      ret.first |= T(1) << bit_idx;
      return ret;
    } else {
      return get_kth_(n->nxt[(lazy >> bit_idx) & 1], k, bit_idx - 1);
    }
  }

 public:
  pair<T, Container &> get_kth(int64_t k) { return get_kth_(root, k, MAX_LOG); }

  void operate_xor(T x) { lazy ^= x; }

 public:

    int xorit(int x){
        bitset<MAX_LOG> ans;
        Node* curr = root; 
        for (int i = MAX_LOG-1; i >= 0; --i) { 
            int b = (x&(1LL<<i));
            if(curr->nxt[1^b]){
                ans.set(i);
            }
            curr = curr->nxt[b] ? curr->nxt[b] : curr->nxt[1^b];
        }
        return ans.to_ulong();
    }

    int countLessEqual(int x, int k){
        int ans = 0;
        Node* curr = root;
        for (int i = MAX_LOG-1; i >= 0; --i) { // from MSB to LSB
            int bx = (x&(1LL<<i));
            int bk = (k&(1LL<<i));
            if(bx){
                if(bk) ans+= curr->nxt[1].cnt, curr = curr->nxt[0];
                else curr = curr->nxt[1];
            }else{
                if(bk) ans+= curr->nxt[0].cnt, curr = curr->nxt[1];
                else curr = curr->nxt[0];
            }
        }
        ans += curr->cnt;
        return ans;
    }

    void dfs(Node* u, Node* p){

    }
};

/**
 * @brief Binary Trie
 * @docs docs/data-structure/binary-trie.md
 */

using namespace Nyaan; void Nyaan::solve() {
  ini(Q);
  BinaryTrie<int, 30> trie;
  rep(_, Q) {
    ini(c, x);
    if (c == 0) {
      if (trie.find(x).first == 0) {
        trie.add(x);
      }
    } else if (c == 1) {
      if (trie.find(x).first != 0) {
        trie.del(x);
      }
    } else {
      trie.operate_xor(x);
      out(trie.min_element().first);
      trie.operate_xor(x);
    }
  }
}
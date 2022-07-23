#include < bits/stdc++.h >
using namespace std;

struct state {
    bool isFinal;
    unordered_map<char, state*> transitions;
    state* failure_link;  // can also be a map

    state* output_link;
    int string_idx;

    state() {
        bool isFinal = false;
        state* failure_link = nullptr;
        state* output_link = nullptr;
        int string_idx = -1;
    }
};

void setUpTransitions(state*& root, vector<string>& needles) {
    for (int i = 0; i < needles.size(); ++i) {
        state* curr = root;
        for (char c : needles[i]) {
            if ((curr->transitions).count(c)) {
                curr = curr->transitions[c];
            } else {
                state* new_state = new state();
                curr->transitions[c] = new_state;
                curr = new_state;
            }
        }
        curr->isFinal = 1;
        curr->string_idx = i;
    }
}
/*
 *If node is not a word node we point output link of current to failure_link of
 *current node. Else we point output link to output link of failure_link of
 *current node.
 */
inline void setUpOutputLinks(state*& root) {
    if (root->failure_link->string_idx > -1) {
        root->output_link = root->failure_link;
    } else {
        root->output_link = root->failure_link->output_link;
    }
}

/*
 *Every node sets the failure links for their childs.
 *Node will follow the failure links unitl it reaches : to a node having c as
 *current node's transtion c / to root. Set failure link case wise respectively.
 */
void setUpFailureLinks(state*& root) {
    root->failure_link = root;
    queue<state*> q;

    for (auto& transition : root->transitions) {
        char c = transition.first;
        state* curr = transition.second;
        q.push(curr);
        root->transitions[c]->failure_link = root;
    }

    while (!q.empty()) {
        state* currState = q.front();
        q.pop();

        for (auto& transition : currState->transitions) {
            char c = transition.first;
            state* currChild =
                transition.second;  //  jiske liye suffix link doondhna hai

            state* candidate =
                currState->failure_link;  //  current potential candidate
            //  getting suitable candidate by lps
            while (!(candidate->transitions.count(c)) and (candidate != root))
                candidate = candidate->failure_link;
            //  setting failure link
            if (candidate->transitions.count(c))
                currChild->failure_link = candidate->transitions[c];
            else
                currChild->failure_link = root;

            q.push(currChild);
        }
        //  setting output link
        setUpOutputLinks(currState);
    }
}

//  ToDo
vector<vector<int>> matches;
int noOfNeedles;
void runAutomaton(state* root, string haystack) {
    matches.resize(noOfNeedles);

    state* curr = root;

    for (int i = 0; i < haystack.size(); ++i) {
        char c = haystack[i];

        if (curr->transitions.count(c)) {
            curr = curr->transitions[c];

            if (curr->isFinal == 1) {
                //  std::cout << curr->string_idx << " "<< i << std::endl;
                matches[curr->string_idx].push_back(
                    i);  //  Gives the ending indexes of needles in haystack
                /*  You can store the word length in a state and sbtract it to
                 * get starting pos  */
            }

            state* curr_ols = curr->output_link;

            while (curr_ols != nullptr and curr_ols != root and
                   curr_ols->isFinal == 1) {
                //  std::cout << curr_ols->string_idx << " "<< i << std::endl;
                matches[curr_ols->string_idx].push_back(
                    i);  //  Gives the ending indexes of needles in haystack
                curr_ols = curr_ols->output_link;
            }
        } else {
            while (curr != root and !(curr->transitions.count(c)))
                curr = curr->failure_link;

            if (curr->transitions.count(c)) i--;
        }
    }
}

int main(int argc, char const* argv[]) {
    state* root = new state();

    vector<string> needles;
    needles = {" AAT ", " GCC ", " CG ",  " ATCG ", " G ",
               " GGG ", " C ",   " GCA ", " GTA "};
    noOfNeedles = needles.size();

    setUpTransitions(root, needles);
    setUpFailureLinks(root);

    string haysatck = " AATCGGGACTA ";

    runAutomaton(root, haysatck);

    cout << " Matching of needles :[  ";
    for (auto& x : needles) {
        cout << x << "   ";
    }
    cout << "  ]  ";
    std::cout << "  in haystack : [  " << haysatck << "  ] " << std::endl;

    std::cout << " LOI(last occuring index) of each neeldle :  " << std::endl;

    for (int i = 0; i < matches.size(); ++i) {
        std::cout << " #  " << i << "  :  ";
        for (int j = 0; j < matches[i].size(); ++j) {
            cout << matches[i][j] << "   ";
        }
        cout << endl;
    }

    return 0;
}

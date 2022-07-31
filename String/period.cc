//find the minimum period length (kind of) of S[0:i] for each i (O(n))
//For example, note that the minimum period length of ababa is 2, not 5

vector<int> table,res;
void minimum_loop(const string s){
    int slen = (int)s.size();
    table.resize(slen+1);
    table[0] = -1;
    int j = -1;
    for(int i = 0; i < slen; i++){
        while(j >= 0 && s[i] != s[j]){
            j = table[j];
        }
        table[i+1] = ++j;
    }
    res.resize(slen);
    for(int i = 0; i < slen; i++){
        res[i] = i+1-table[i+1];
    }
}
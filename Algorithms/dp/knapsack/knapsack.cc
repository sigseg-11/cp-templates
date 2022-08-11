vector<long long> dp;

// This code is given in both kuangbin and "Nine Lectures on Backpack"
// Only the second layer of loops and arrays are encapsulated here, which is equivalent to processing an item, but no constant optimization is added.
// But it will be used in multiple backpacks
void ZeroOnePack(int cost, int value) {
    for (int i = nValue; i >= cost; i−−) 
      dp[i] = max(dp[i], dp[i−cost] + value);
}

// still no constant optimization
// Complete backpack, the cost is cost, the value obtained is value, which is also the processing of an item
void CompletePack(int cost, int value) {
    for (int i = cost; i <= nValue; i++) 
      dp[i] = max(dp[i], dp[i−cost] + value);
}

void MultiplePack(int cost, int value, int amount) {  // cost, value, quantity
    if (cost * amount >= V)    // relatively "infinite"
        CompletePack(cost, value);        // full backpack
    else {
        int k = 1;
        while (k < amount) {
            ZeroOnePack(k * cost, k * value);  // The coefficient is incremented, 1, 2, 4, 8, ...
            amount−= k;
            k <<= 1;  // k is shifted to the left by one, that is, k*=2
        }
        ZeroOnePack(amount * cost, amount * value);  // Don't forget this, this is the last coefficient, which is the result of subtracting all previous coefficients from n[i]
    }
}

void knapsack(vector<int> c, vector<int> w, vector<int> n, vector<int> type){
    int N = type.size();
    dp.resize(N + 1);
    for (int i = 0; i < N; i++) {
        // if item i belongs to 01 backpack 
        if(type[i]==1)
            ZeroOnePack(c[i], w[i]) ;
        // else if The i - th item belongs to the complete backpack 
        else if (type[i]==2)
            CompletePack(c[i], w[i]) ;
        // else if The i - th item belongs to a multipack 
        else if (type[i]==3)
            MultiplePack(c[i], w[i], n[i]);
    }
}
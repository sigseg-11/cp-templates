#include <bits/stdc++.h>
using namespace std;

const int LN = 32;

struct node{
    node *child[2];
    // No of Common Prefix/ Binary Representation
    // No of int passing through this node
    int cnt;
    int x; // Actual No Ending Here
    int ssz; // Subtree Size
    int par; // Parent
    
    node(){
        child[0] = child[1] = NULL;
        cnt = 0;
    }
};

node* root;

void insert(int x){
    node* curr = root; // Take pointer
    for (int i = LN-1; i >= 0; --i) { // from MSB to LSB
        curr->cnt++;
        int b = (x&(1LL<<i));
        if(curr->child[b]==NULL){
            curr->child[b] = new node; // Insrt Node
        }
        curr = curr->child[b]; // Move pointer
    }
    curr->cnt++;
}

// max xor in array
int maxXORWithX(int x){
    bitset<LN> ans;
    node* curr = root; // Take pointer
    for (int i = LN-1; i >= 0; --i) { // from MSB to LSB
        int b = (x&(1LL<<i));
        if(curr->child[1^b]){
            ans.set(i);
        }
        curr = curr->child[b] ? curr->child[b] : curr->child[1^b]; // Move pointer
    }
    return ans.to_ulong();
}

// find the number of subarrays with xor less than k.
int countXorPairLessEqualsK(int x, int k){
    int ans = 0;
    node* curr = root;
    for (int i = LN-1; i >= 0; --i) { // from MSB to LSB
        int bx = (x&(1LL<<i));
        int bk = (k&(1LL<<i));
        if(bx){
            if(bk) ans+= curr->child[1].cnt, curr = curr->child[0];
            else curr = curr->child[1];
        }else{
            if(bk) ans+= curr->child[0].cnt, curr = curr->child[1];
            else curr = curr->child[0];
        }
    }
    ans += curr->cnt;
    return ans;
}


void dp(){
    
}

int main(){
    root = new node;
    
    return 0;
}
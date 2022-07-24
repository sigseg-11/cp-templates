void backtrack(vector<int>& nums, int start, vector<vector<int> >& resultset,
               vector<int> curr_set) {
    resultset.push_back(curr_set);
    for (int i = start; i < nums.size(); i++) {
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }
        curr_set.push_back(nums[i]);
        backtrack(nums, i + 1, resultset, curr_set);
        curr_set.pop_back();
    }
}

vector<vector<int>> AllSubsets(vector<int> nums) {
    vector<vector<int> > resultset;
    vector<int> curr_set;
    sort(nums.begin(), nums.end());
    backtrack(nums, 0, resultset, curr_set);
    return resultset;
}



// Driver Code
int main() {
    vector<int> v{1, 2, 2};

    // Function call
    vector<vector<int>> result = AllSubsets(v);

    // Print function
    print(result);

    return 0;
}

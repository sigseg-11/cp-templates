// Take x as what you need to find.
// Check if x is possible answer can x+1 or x-1 be possible answers.
// Find range of answer lo and hi or take lo=0, hi = 1e18
// Define ans as default value
// repeat while(lo<=hi)
// Find mid = lo + hi >> 1
// Check can mid be our ans (find relation b/w mid and input variables) : Inline/ Function
// 		if yes update 
// 		ans  = mid 
// 		lo = mid + 1  for Fartherst and Maximization
// // hi = mid - 1 for Naerest and Minimization
// 		if no update 
// 		hi = mid - 1 for Fartherst and Maximization
// // lo = mid + 1 for Naerest and Minimization
// Return ans
// "So when your binary search is stuck, think of the situation when there are only 2 elements left. Did the boundary shrink correctly?" This line really changed how I approached BS algorithms for more complicated problem. This almost covers all the edge cases. Thank you so much for this.

// http://towardsdatascience.com/powerful-ultimate-binary-search-template-and-many-leetcode-problems-1f850ef95651


// lo to mid + 1 and hi = mid - 1 always
// Fartherst and Maximization = lo first
// Naerest and Minimization = hi first

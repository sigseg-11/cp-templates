#pragma once

// Prime -> {0, 0, 1, 1, 0, 1, 0, 1, ...}
vector<bool> prime_sieve(int N) {
  vector<bool> sieve(max(1, N) + 1, 1);
  sieve[0] = sieve[1] = false;
  for (int i = 2; i * i <= N; i++)
    if (sieve[i] == true)
      for (int j = i * i; j <= N; j += i) sieve[j] = false;
  return sieve;
}



#pragma once

// Prime Sieve {2, 3, 5, 7, 11, 13, 17, ...}
vector<int> prime_enumerate(int N) {
  vector<bool> sieve(N / 3 + 1, 1);
  for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn; p += d = 6 - d, i++) {
    if (!sieve[i]) continue;
    for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
             qe = sieve.size();
         q < qe; q += r = s - r)
      sieve[q] = 0;
  }
  vector<int> ret{2, 3};
  for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
    if (sieve[i]) ret.push_back(p);
  while (!ret.empty() && ret.back() > N) ret.pop_back();
  return ret;
}
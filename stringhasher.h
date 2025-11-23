#pragma once
 #include<vector>
 #include<string>
 class StringHasher {
   public:
   StringHasher(const std::vector<int>& p, int m) : primes(p), modulus(m) {}
   // The same function as string_hash in project 1
   int operator()(const std::string& str) const;
   private:
   std::vector<int> primes;
   int modulus;
 };
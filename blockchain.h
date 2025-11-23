#pragma once
#include <string>
#include <map>
#include <vector>
#include "transaction.h"
#include "block.h"
#include "stringhasher.h"
class BlockChain {
  public:
  // Construct the StringHasher
  BlockChain(int nonce_size, const std::vector<int>& primes, int modulus);
  void register_user(const std::string& name);
  // Add transaction to the pending list
  void add_transaction(const std::string& tx);
  void mine_block(const std::string& miner_name);
  double get_balance(const std::string& name, int idx =-1);
  // more member functions if needed
  private:
  std::map<std::string,double>miners;
  std::vector<Block> chain;
  std::vector<Transaction> pending_transactions;
  StringHasher hasher;
  const double MINING_REWARD = 10;
  int nonce_size;
  // more members if needed
};

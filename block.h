#pragma once
#include<string>
#include<vector>
#include"transaction.h"
class Block {
  public:
  Block(int index, const std::string& prev_hash);
  void set_hash_and_nonce(const std::string& new_hash, const std::string& new_nonce);
  void set_transactions(const std::vector<Transaction>& txs);
  const std::string& get_hash() const { return hash; }
  const std::vector<Transaction>& get_transactions() const { return transactions; }
  private:
  int block_idx;
  std::string prev_hash; // hash of the previous block
  std::vector<Transaction> transactions;
  std::string nonce;
  std::string hash; // hash of the current block
};
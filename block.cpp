#include"stringhasher.h"
#include<string>
#include"block.h"
Block::Block(int index,const std::string& prev_hash):block_idx(index),prev_hash(prev_hash){}
void Block::set_hash_and_nonce(const std::string& hash_value,const std::string& nonce_value){
    hash=hash_value;
    nonce=nonce_value;
}void Block::set_transactions(const std::vector<Transaction>& txs){
    transactions=txs;
}
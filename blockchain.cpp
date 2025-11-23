#include<iostream>
#include"nonceguesser.h"
#include<sstream>
#include"blockchain.h"
#include<iomanip>
BlockChain::BlockChain(int nonce_size, const std::vector<int>& primes, int modulus)
:hasher(primes,modulus),nonce_size(nonce_size){miners["System"]=1e16;}
void BlockChain::register_user(const std::string&name){
    miners[name]=0;
}
void BlockChain::add_transaction(const std::string&tx){
    std::stringstream ss(tx);
    ss<<tx;
    std::string from,to;
    double amt;
    std::string _;
    ss>>from>>_>>to>>amt>>_;
    if(miners.find(from)==miners.end() || miners.find(to)==miners.end()){
        std::cout<<"Transaction aborted: account not valid"<<std::endl;
         return ;
    }
    if(miners[from]<amt){
        std::cout<<"Transaction aborted: "<<
        from<<" does not have sufficient funds"<<std::endl;
         return ;
    }
    Transaction transaction(from,to,amt);
    miners[from]-=amt;
    miners[to]+=amt;
    pending_transactions.push_back(transaction);
}


void BlockChain::mine_block(const std::string&miner_name){
    Transaction reward("System",miner_name,MINING_REWARD);
    pending_transactions.push_back(reward);
    std::string prev_hash=chain.empty()?"00000000":chain.back().get_hash();
    Block new_block(chain.size(),prev_hash);
    new_block.set_transactions(pending_transactions);
    pending_transactions.clear();
    std::stringstream ss;
    ss<<chain.size();
    ss<<prev_hash;
    std::vector<Transaction> txs=new_block.get_transactions();
    for (const auto&tx:txs){
        ss<<tx;
    }
    nonceguesser guesser(hasher,ss.str(),nonce_size,"");
    std::string nonce=guesser.generate_nonce(0);
    ss<<nonce;
    int hash_value=hasher(ss.str());
    std::stringstream hash_ss;
    hash_ss<<std::setw(8)<<std::setfill('0')<<std::hex<<hash_value;
    std::cout<<ss.str()<<std::endl;
    new_block.set_hash_and_nonce(hash_ss.str(),nonce);
    chain.push_back(new_block);
    miners[miner_name]+=MINING_REWARD;
}
double BlockChain::get_balance(const std::string&name,int idx){
    if(miners.find(name)==miners.end()){
        return 0.0;
    }
    double balance=0;
    for (const auto&block:chain){
        if(idx!=-1 && &block-&chain[0]>idx)break;
        std::vector<Transaction> txs=block.get_transactions();
        for (const auto&tx:txs){
            if(tx.get_sender()==name){
                balance-=tx.get_amount();
            }
            if(tx.get_recipient()==name){
                balance+=tx.get_amount();
            }
        }
    }
    return balance;
}
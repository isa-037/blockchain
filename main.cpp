#include<iostream>
#include"blockchain.h"
#include<sstream>
#include"nonceguesser.h"
#include<iomanip>
int main(){
    freopen("output.txt","w", stdout);
    std::string line;
    std::vector<int>primes(0);
    int modulus,nonce_size;
    std::getline(std::cin,line);
    int primesize;
    std::stringstream ss(line);
    ss>>primesize;
    for(int i=0;i<primesize;i++){
        int p;
        ss>>p;
        primes.push_back(p);
    }
    ss>>modulus>>nonce_size;
    BlockChain bc(nonce_size,primes,modulus);
    while(1){
        std::getline(std::cin,line);
        std::stringstream ss(line);
        std::string command;
        ss>>command;
        if(command=="EXIT"){
            break;
        }
        else if(command=="REGISTER"){
            std::string name;
            ss>>name;
            bc.register_user(name);
        }
        else if(command=="TX"){
            std::string tx;
            getline(ss,tx);
            bc.add_transaction(tx);
        }
        else if(command=="MINE"){
            std::string miner_name;
            ss>>miner_name;
            bc.mine_block(miner_name);
        }
        else if(command=="BALANCE"){
            std::string name;
            ss>>name;
            if(ss.peek()==' '){
                int idx;
                ss>>idx;
                double balance=bc.get_balance(name,idx);
                if(balance!=-1){
                    std::cout<<std::fixed<<std::setprecision(1)<<balance<<std::endl;
                }
                continue;
            }else{
                double balance=bc.get_balance(name);
                if(balance!=-1){
                    std::cout<<std::fixed<<std::setprecision(1)<<balance<<std::endl;
                }
            }
        }
    }
    return 0;
}
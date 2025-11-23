 #include<iostream>
 #include<cmath>
 #include<cctype>
 #include<string>
 #include<vector>
 #include<sstream>
 #include<iomanip>
 #include<map>
 class StringHasher {
   public:
   StringHasher(const std::vector<int>& p, int m) : primes(p), modulus(m) {}
   int operator()(const std::string& str) const;
   private:
   std::vector<int> primes;
   int modulus;
 };
int hsh(char c){
    if(isdigit(c)){
        return c-'0';
    }
    if(isalpha(c)){
        return c;
    }
    return -1;
}
int tmp;
int qpow(int x,int p,int q){
    if(!p)return 1;
    if(p&1)return 1ll*x*qpow(x,p-1,q)%q;
    return tmp=qpow(x,p>>1,q),1ll*tmp*tmp%q;
}
int StringHasher::operator()(const std::string &str)const{
    int nowp=0;
    int ret=0;
    for(int i=0;i<str.length();i++){
        int tmp=hsh(str[i]);
        if(tmp==-1)++nowp,nowp%=primes.size();
        else ret=(1ll*ret+1ll*qpow(primes[nowp],i,modulus)*tmp%modulus)%modulus;
    }
    return ret;
}
class Transaction {
  public:
  Transaction(const std::string& from, const std::string& to, double amt);
  std::string get_sender() const;
  std::string get_recipient() const;
  double get_amount() const;
  friend std::ostream& operator<<(std::ostream& os, const Transaction& tx);
  private:
  std::string sender;
  std::string recipient;
  double amount;
};
Transaction::Transaction(const std::string&from,
						 const std::string&to,
						 double amount)
:sender(from),recipient(to),amount(amount){}
std::string Transaction::get_sender()const{
	return sender;
}
std::string Transaction::get_recipient()const{
	return recipient;
}
double Transaction::get_amount()const{
	return amount;
}
std::ostream& operator<<(std::ostream&os,const Transaction&tx){
	os<<std::setprecision(1)<<std::fixed;
	os<<tx.sender<<" sends "<<tx.recipient<<" "<<tx.amount<<" yuan";
	return os;
}
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

Block::Block(int index,const std::string& prev_hash):block_idx(index),prev_hash(prev_hash){}
void Block::set_hash_and_nonce(const std::string& hash_value,const std::string& nonce_value){
    hash=hash_value;
    nonce=nonce_value;
}void Block::set_transactions(const std::vector<Transaction>& txs){
    transactions=txs;
}
class nonceguesser {
public:
    nonceguesser(StringHasher hasher, std::string prefix,int nonce_size,std::string suffix);
    bool is_valid_nonce(const std::string& nonce);
    std::string generate_nonce(int idx);
private:
    StringHasher hasher;
    std::string prefix;
    std::string suffix;
    int nonce_size;
    std::string current_nonce;
};
nonceguesser::nonceguesser(StringHasher hasher, std::string prefix,int nonce_size,std::string suffix):hasher(hasher),prefix(prefix),nonce_size(nonce_size),suffix(suffix){}
bool nonceguesser::is_valid_nonce(const std::string& nouce){
    return hasher(prefix+nouce+suffix)%10000==2601;
}
std::string nonceguesser::generate_nonce(int idx){
    if(idx==nonce_size){
        if(is_valid_nonce(current_nonce)){
            return current_nonce;
        }else return "-fxxk-";
    }
    for(char c='a';c<='z';c++){
        current_nonce.push_back(c);
        std::string res=generate_nonce(idx+1);
        if(res!="-fxxk-")return res;
        current_nonce.pop_back();
    }
    for(char c='A';c<='Z';c++){
        current_nonce.push_back(c);
        std::string res=generate_nonce(idx+1);
        if(res!="-fxxk-")return res;
        current_nonce.pop_back();
    }
    return "-fxxk-";
}
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
int main(){
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
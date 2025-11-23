# 这是港科广第二次编程大作业的代码（项目格式）

## Cryptocurrencies++

### Description

In this project, you will extend your previous work by creating several classes that simulate a functioning decentralized ledger, commonly known as a blockchain. A blockchain is a distributed database that maintains a continuously growing list of records called blocks, which are linked together using cryptographic hashes. This structure ensures the integrity and security of the data, making it an essential component of cryptocurrencies and other applications requiring secure and transparent record-keeping. Extend project 1 by creating the following classes: StringHasher, Transaction, Block, BlockChain, necessary to simulate a working, decentralized ledger.

#### Part I: The StringHasher Class

TheStringHasherClass is a class version of the int string hash(const std::string& str, const std::vector& primes, int modulus) function implemented in project 1. This class will be responsible for generating a unique hash for given strings, which is vital for maintaining data integrity in the blockchain. Here is the definition for the class:
```cpp
 class StringHasher {
   public:
   StringHasher(const std::vector& p, int m) : primes(p), modulus(m) {}
   // The same function as string_hash in project 1
   int operator()(const std::string& str) const;
   private:
   std::vector primes;
   int modulus;
 };
```
With a StringHasher object namedstring_hasher, you can obtain a hash for any string by callingstring_hasher(str).

#### Part II: The Transaction Class

TheTransactionClass is the fundamental unit of value transfer in the blockchain. Here is the definition for the class:
```cpp
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
```
Theoperator<<function should output the string to the stream in the following format: “[sender] sends [recipient] [amount] yuan”. For example, “Tom sends Jerry 10.2 yuan”. A floating-point number is output in a fixed precision of 1.

#### Part III: The Block Class

A blockchain can be visualized as a linked list, where each block is a node containing a collection of transactions. Instead of linking by pointers as a linked list, the blocks are linked by hashes. The Block Class represents a single block in the chain, containingblock_idx(the block index of the block in the whole chain),prev_idx(the hash of the previous block), all the transactions that are recorded by the current block, a nonce (same as the one-off string generated in project 1), and the hash of the current block. Here is the definition for the class:
```cpp
class Block {
  public:
  Block(int index, const std::string& prev_hash);
  void set_hash_and_nonce(const std::string& new_hash, const std::string& new_nonce);
  const std::string& get_hash() const { return hash; }
  const std::vector<Transaction>& get_transactions() const { return transactions; }
  private:
  int block_idx;
  std::string prev_hash; // hash of the previous block
  std::vector<Transaction> transactions;
  std::string nonce;
  std::string hash; // hash of the current block
};
```
The hash is computed in the following way:

First, construct the original string for the block:Block String=block_idx+prev_hash+All Transaction Strings+noncewithout extra spaces in between. (see the example given in the sample input and output).
Next, compute the hash for the block string given a string hasher object.hash=string_hasher(Block String)
Same as project 1, the hash of a valid block in our blockchain should satisfy the condition thathash % 10000 = 2601. As a result, our main job is to find the nonce (one-off string in project 1) such that the hash meets this requirement.

#### Part IV: The BlockChain Class

TheBlockChainClass represents the whole chain that contains all the blocks in the chain. Here is the partial definition for the class, which is implemented using a std::vector to keep all the blocks:
```cpp
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
  std::vector<Block> chain;
  std::vector<Transaction> pending_transactions;
  StringHasher hasher;
  const double MINING_REWARD = 10;
  int nonce_size;
  // more members if needed
};
```
The chain member holds all validated blocks, while the pending transactions holds transactions that are waiting to be processed.

Blockchain object is constructed using the nonce size (the length of the one-off string in project 1), and the necessary parameters to construct StringHasher.

Assuming there is a superuser named “System”, who has an unlimited amount of money.

The register user function will register a user on the chain and set the user’s initial balance to 0. If a name already exists in the chain, ignore the register request.

The add transaction function will parse the transaction string. We will ensure that the string follows the exact format “[sender] sends [recipient] [amount] yuan”, the amount can be an integer or a floating-point value.

Next, it will check the accounts of the sender and the recipient. If either the sender or the recipient never registered in the chain, cout “Transaction aborted: account not valid” and return. If the sender has sufficient money, the transaction will be added to pending transactions. Otherwise, if the sender does not have sufficient money, cout “Transaction aborted: [sender] does not have sufficient funds”.



The mine block function will allow the miner to mine the coins. If the miner does not exist in the chain, reject the mine request (do nothing).

1. Add Reward Transaction, assuming the miner successfully mined the coin. Create a Transaction(“System”, miner name, MINING REWARD) and add it to pending transactions.

2. Prepare the block. Create a new Block object with the correct index, the hash of the last block in the chain, and all pending transactions. For the first block (block 0) in the chain, the previous hash is a string with 8 ‘0’s, i.e., ‘00000000’.

3. Guess the nonce (the one-off string in project 1) until the hash of the new block is valid. The requirements of the one-off string are exactly the same as those of Project 1. After successfully guessing the nonce, set the nonce and hash of the block. The hash string should be an 8-digit hexadecimal representation of the hash. (See the example in the sample input and output, where the hash of the block 0 is 342601 in decimal, and 00053a49 in hexadecimal)

4. cout “[Block String]” as Equation (1).

The get balance function returns the balance after block idx. For example, if idx = 1, it is the balance after block 1, considering only the transactions in block 0 and block 1 (NOT including pending transactions). By default, the idx is -1, which means the balance after all transactions, including those in the chain and pending transactions. If idx is greater than or equal to the current block size, it should be treated as -1. If the user is never registered, return 0.0 (don’t register the user).

Please do not change the class definitions.

Only add members and member functions to class BlockChain if needed.


### Input

Primes Count, followed by all Primes, then Modulus, finally nonce size.

Then commands, including REGISTER, TX (Transaction), MINE, BALANCE, and EXIT (end the program).

We will ensure that all names are without empty spaces. Output all doubles with fixed precision 1.


### Output

System Output

Explanation:

+ “TX Alice sends Bob 50 yuan” outputs “Transaction aborted: account not valid” as Alice is not registered.

+  “MINE Jerry” outputs “000000000System sends Tom 100.0 yuanSystem sends Jerry 10.0 yuangMeF” as the first 0 is the block id, 00000000 is the hash for the first block (block 0) by definition, “gMeF” is the nonce, the hash is 342601.

+ “BALANCE Jerry” outputs the final balance of Jerry, which is 10

+ “TX Bob sends Tom 20 yuan” outputs “Transaction aborted: Bob does not have sufficient funds” since Bob’s balance should be 0.

+ “MINE Bob” outputs “100053a49Jerry sends Tom 5.0 yuanTom sends Bob 1.0 yuanSystem sends Bob 10.0 yuandujU” as 1 is the block id, 00053a49 is the hash (342601 in decimal) for the first block (block 0), and “dujU” is the nonce for block 1.

+ “BALANCE Alice” outputs 0 as Alice is not registered. 
+ “BALANCE Jerry 2” outputs the final balance 5 since there are only 2 blocks.

+ “BALANCE Jerry 0” outputs the balance after block 0, which is 10.


### Sample Input 1 
```
2 31 71 1000007 4
REGISTER Tom
REGISTER Jerry
REGISTER Bob
TX System sends Tom 100.0 yuan
TX Alice sends Bob 50 yuan
MINE Jerry
BALANCE Jerry
TX Jerry sends Tom 5.0 yuan
TX Tom sends Bob 1 yuan
TX Bob sends Tom 20 yuan
MINE Bob
BALANCE Alice
BALANCE Jerry 2
BALANCE Jerry 0
EXIT
```
### Sample Output 1
```
Transaction aborted: account not valid
000000000System sends Tom 100.0 yuanSystem sends Jerry 10.0 yuangMeF
10.0
Transaction aborted: Bob does not have sufficient funds
100053a49Jerry sends Tom 5.0 yuanTom sends Bob 1.0 yuanSystem sends Bob 10.0 yuandujU
0.0
5.0
10.0
Hint
```
For 50% of the test inputs, the command number <= 10.


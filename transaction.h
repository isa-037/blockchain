#pragma once
#include<string>
#include<set>
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
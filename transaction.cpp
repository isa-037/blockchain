#include<iomanip>
#include"transaction.h"
#include<iostream>
#include<sstream>
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

#include<iostream>
#include "stringhasher.h"
#include<string>
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
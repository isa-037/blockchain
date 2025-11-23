#include"stringhasher.h" 
#include"nonceguesser.h"
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
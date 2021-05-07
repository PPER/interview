#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
// 1.Longest Substring Without Repeating Characters
//sliding window O(n2)
int lengthOfLongestSubstring(string s) {
    int left = 0, maxlen = 0, len = 0;
    set<char> chset;
    if(s=="")return 0;
    for(int i=0; i<s.length();i++ ){
        len = i-left+1;
        for(int j = left; j<i; j++){
            if (s[i] == s[j]){
                len = i-j;
                left = j+1;
            }
        }
        if(len>maxlen)maxlen=len;
    }
    return maxlen;
}
//hashmap sliding windows O(n)
int lengthOfLongestSubstring(string s) {
    int left = 0, maxlen = 0, len = 0;
    map<char, int> mp;
    if(s=="")return 0;
    for(int i=0; i<s.length();i++ ){
        
        if(mp.find(s[i])!=mp.end()){
            left = max(mp[s[i]],left);
            mp[s[i]] = i+1;
        
        }else mp[s[i]] = i+1;
        len = i-left+1;
        if(len>maxlen)maxlen=len;
    }
    return maxlen;
}
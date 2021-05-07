#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
// 1.Longest Substring Without Repeating Characters
//sliding window
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
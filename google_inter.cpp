#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* helper func */
void print_vec(vector<int> input){
    cout<<"-------***print_vec***-------\n";
    for(int j=0;j<input.size();++j)cout<<input[j]<<" ";
    cout<<endl;
    cout<<"-------***print_vec***-------\n";
}
void swap(vector<int>& input, int i,int j){
    int temp = input[i];
    input[i]=input[j];
    input[j]=temp;
}
void reverse_vec(vector<int>& input, int begin, int end){
    if(begin>=end)return;
    for(int i =begin, j=end;i<j;i++,j--){
        swap(input,i,j);
    }
}

/* Plus one
Given a non-negative number represented as an array of digits, plus one to the number.
The digits are stored such that the most significant digit is at the head of the list. */
vector<int> plus_one(vector<int>& input){
    /* 
    test code:
    vector<int> input1 = {1,2,3,4};
    vector<int> input2 = {1,2,9,9};
    vector<int> input3 = {9,9,9,9};
    print_vec(plus_one(input1));
    print_vec(plus_one(input2));
    print_vec(plus_one(input3));
     */
    int result = 0;
    input[input.size()-1]+=1;
    for(int i = input.size()-1; i >= 0; --i){
        if(input[i]==10){
            if(i!=0){
                input[i]=0;
                input[i-1]+=1;
            }else{
                vector<int> result;
                result.push_back(1);
                input[i]=0;
                for(int j=0;j<input.size();++j)result.push_back(input[j]);
                return result;
            }
        }
    }
    return input;
}

/* 
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
The replacement must be in-place, do not allocate extra memory.
*/
void next_permutation(vector<int>& input){
/* tc:
    vector<int> input1 = {1,2,3,4};
    vector<int> input2 = {6,3,4,9,8,7,1};
    vector<int> input3 = {9,9,9,9,0};
    vector<int> input4 = {9,8,7,6,5,0};
*/
    int break_pt=-1;
    for(int i = input.size()-1; i >= 0; --i){
        if(i==0){
            reverse_vec(input,0,input.size()-1);
            return;
        }
        if(input[i-1]<input[i]){
            break_pt = i-1;
            break;
        }
    }
    for(int i = input.size()-1; i >= 0; --i){
        if(input[i]>input[break_pt]){
            cout<<i<<endl;
            swap(input,i,break_pt);
            reverse_vec(input,break_pt+1,input.size()-1);
            break;
        }
    }
}

/* Sort Transformed Array
Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax2 + bx + c to each element x in the array.
The returned array must be in sorted order.
Expected time complexity: O(n)
*/
/* Two pointers */
/* REVIEW */
vector<int> sort_trans_array(vector<int>& input,int a, int b, int c){
    vector<int> result;
    result.resize(input.size());
    int i = (a>=0)?input.size()-1:0;
    int left=0,right=input.size()-1;
    while(left<=right){
        int l = a*result[left]*result[left]+b*result[left]+c;
        int r = a*result[right]*result[right]+b*result[right]+c;
        if(a>=0){
            if(l>r){
                result[i--]=l;
                left++;
            }else{
                result[i--]=r;
                right--;
            }
        } else{
            if(l>r){
                result[i++]=r;
                right--;
            }else{
                result[i++]=l;
                left--;
            }
        }
    }
    return result;
}

/* Wiggle Sort
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
*/
void wiggle_sort(vector<int>& input){
    /* the first method is sort and then swap #3&#2, #5&#4... the following is the second method */
    /* 
    if i is odd, input[i]>input[i-1] else input[i]<=input[i-1]
    */
    for(int i=2;i<input.size();++i){
        if((i%2)&&input[i]<input[i-1] || (i%2)==0&&input[i]>input[i-1]){
            swap(input,i,i-1);
        }
    }
}

/* Wiggle Sort II
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
*/
/* REVIEW */
void wiggle_sort_2(vector<int>& input){
    
}

int main(){
    vector<int> input1 = {1,2,3,4};
    vector<int> input2 = {6,3,4,9,8,7,1};
    vector<int> input3 = {9,9,9,9,0};
    vector<int> input4 = {9,8,7,6,5,0};
    next_permutation(input1);
    next_permutation(input2);
    next_permutation(input3);
    next_permutation(input4);
    
    print_vec( input1);
    print_vec(input2);
    print_vec(input3);
    print_vec(input4);
}
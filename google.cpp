#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
void print_2d_vec(vector<vector<int>> &vec);
void print_1d_vec(vector<int> &vec);
void print_split_line();
//spiral matrix
vector<int> spiral_matrix(vector<vector<int>> matrix){
    vector<int> result;
    int row_num = matrix.size();
    if(row_num ==0) return result;
    int col_num = matrix[0].size();
    result.reserve(col_num*row_num);
    int top = 0, bottom = row_num-1, left = 0, right = col_num-1;
    int i=0,j=0;
    while(true){
        
        //right
        for(i=top,j=left;j<=right;j++){
            result.push_back(matrix[i][j]);
        }
        ++top;
        if(top>bottom)break;
        //down
        for(i=top,j=right;i<=bottom;++i){
            result.push_back(matrix[i][j]);
        }
        --right;
        if(left>right)break;
        //left
        for(i=bottom,j=right;j>=left;--j){
            result.push_back(matrix[i][j]);
        }
        --bottom;
        if( top>bottom)break;
        //up
        for(i=bottom,j=left;i>=top;--i){
            result.push_back(matrix[i][j]);
        }
        ++left;
        if(left>right)break;
    }
    return result;
}
void print_2d_vec(vector<vector<int>> &vec){
    size_t row_num = vec.size();
    if(row_num ==0) return;
    size_t col_num = vec[0].size();
    for(size_t i = 0; i < row_num; ++i){
        for(size_t j = 0; j < col_num; ++j){
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
}

void print_1d_vec(vector<int> &vec){
    for(size_t i = 0; i < vec.size(); ++i){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}
void print_split_line(){
    cout<<"\n-----------------\n";
}
//merge intervals
//Follow up:
// https://leetcode.com/problems/merge-intervals/solution/
// https://leetcode.com/problems/merge-intervals/discuss/21452/Share-my-interval-tree-solution-no-sorting
bool compareInterval(vector<int> inter_1, vector<int> inter_2){
    return inter_1[0]<inter_2[0];
}
vector<vector<int>> merge_intervals(vector<vector<int>>& intervals) {
    vector<vector<int>> result;
    if(intervals.size()==0)return result;
    sort(intervals.begin(),intervals.end(),compareInterval);
    result.push_back(intervals[0]);
    for(int i = 1; i<intervals.size(); i++){
        if(intervals[i][0]>result[result.size()-1][1]){
            result.push_back(intervals[i]);
        } else {
            result[result.size()-1][1] = max(intervals[i][1], result[result.size()-1][1]);
        }
    }
    return result;
}
//binary search
int binary_search(vector<int>& vec,int val){
    int left = 0, right = vec.size()-1;
    while(left<right){
        int mid = (left+right)/2;
        if(vec[mid]==val)return mid+1;
        else if(vec[mid]<val) left = mid+1;
        else if(vec[mid]>val) right = mid;
    }
    return right;
}
//insert interval
int binary_search_interval(vector<vector<int>>& intervals, vector<int>& newInterval){
    int left = 0, right = intervals.size()-1;
    if(newInterval[0]<=intervals[left][0])return 0;
    if(newInterval[0]>=intervals[right][0])return intervals.size();
    while(left<right){
        int mid = (left+right)/2;
        if(intervals[mid][0] == newInterval[0]) {
            return mid+1;
        }
        if(intervals[mid][0] < newInterval[0]) left = mid+1;
        if(intervals[mid][0] > newInterval[0]) right = mid;
    }

    return right;
}
//good method:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ret;
        int start = newInterval[0];
        int end = newInterval[1];
        int flag = 0;
        for(int i=0; i<intervals.size(); i++){
            if(intervals[i][1] >= start && intervals[i][1] <= end){
                start = min(start, intervals[i][0]);
            }
            else if(intervals[i][0] >= start && intervals[i][0] <= end){
                end = max(start,intervals[i][1]);
            }
            else {
                if (intervals[i][0] > newInterval[1] && flag == 0){
                    ret.push_back({start,end});
                    flag = 1;
                }
                else if (intervals[i][0] <= start && intervals[i][1] >= end)flag = 1;
                ret.push_back(intervals[i]);
            }
        }
        if(flag == 0) ret.push_back({start,end});
        return ret;
    }
//bad method
vector<vector<int>> insert_interval(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result(intervals);
    if(intervals.size()==0){
        result.push_back(newInterval);
        return result;
    }
    int pos = binary_search_interval(intervals,newInterval);
    intervals.insert(intervals.begin()+pos,newInterval);
    result.push_back(intervals[0]);
    for(int i = 1; i<intervals.size(); i++){
        if(intervals[i][0]>result[result.size()-1][1]){
            result.push_back(intervals[i]);
        } else {
            result[result.size()-1][1] = max(intervals[i][1], result[result.size()-1][1]);
        }
    }
    return result;
}

//meeting room 2
int meeting_room_2(vector<vector<int>> intervals){
    priority_queue <int, vector<int>, greater<int> > pq;
    for(auto interval:intervals){
        if(pq.empty()||pq.top()>interval[0])pq.push(interval[1]);
        else pq.pop();
    }
    return pq.size();
}

//range addition
vector<int> range_addition(vector<vector<int>> ops,int size){
    vector<int> result(size,0);
    for(auto op:ops){
        for(int i = op[0]; i<=op[1]; ++i){
            result[i]+=op[3];
        }
    }
    return result;
}
//range addition tricky solution
vector<int> range_addition(vector<vector<int>> ops,int size){
    vector<int> result(size,0);
    for(auto op:ops){
        result[op[0]]+=op[2];
        if(op[1]+1<size) result[op[1]+1]-=op[2];
    }
    int sum=0;
    for(int i=0; i< size;++i){
        sum+=result[i];
        result[i]=sum;
    }
    return result;
}
//range addition ii tricky solution
int maxCount(int m, int n, vector<vector<int>>& ops){
    vector<vector<int>> result(n,vector<int>(n, 0));
    int min_row = m;
    int min_col = n;
    for(auto op:ops){
        min_row = min(op[0],min_row);
        min_col = min(op[1],min_col);
    }
    return (min_row+1)*(min_col+1);
}
//Search a 2D Matrix
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    
}
int main(){
    vector<vector<int>> matrix = {{1,3},{6,9}};
    print_2d_vec(matrix);
    print_split_line();
    vector<int> new_interval = {2,5};
    vector<vector<int>>result = insert(matrix,new_interval);
    print_2d_vec(result);
/*     vector<int> vec = {1,6};
    print_1d_vec(vec);
    cout<<"result:"<<binary_search(vec,2);
    cout<<endl;
 */
}


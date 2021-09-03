#include <bits/stdc++.h>
using namespace std;

class MinQueue{
    public:
    deque<int> q;

    // Add element at ind into the queue
    void push_back(int ind, vector<int>& nums){
        int cur = nums[ind];
        while( !q.empty() && nums[q.back()] >= cur){
            q.pop_back();
        }
        q.push_back(ind);
    }
        
    
    /* Remove all elements in the window with index <= `ind` */
    void pop_front(int ind){
        while(!q.empty() and q.front() <= ind){
            q.pop_front();
        }
    }

    /* Get min element in the current window */
    int get_min(vector<int>& nums){
        return nums[q.front()];
    }
};

// Similar to sliding-window-maximum on leetcode.
vector<int> minSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        MinQueue mxq;
        
        for(int i = 0;  i < k; i++ ){
            mxq.push_back(i, nums);
        }
        
        ans.push_back(mxq.get_min(nums));
        
        for(int i = k; i < n; i++ ){
            mxq.push_back(i, nums);
            mxq.pop_front(i - k);
            ans.push_back(mxq.get_min(nums));

        }
        
        return ans;
}
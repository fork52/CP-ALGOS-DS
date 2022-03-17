#include <bits/stdc++.h>
using namespace std;

class MaxQueue{
    public:
    deque<int> q;

    // Add element at ind into the queue
    void push_back(int ind, vector<int>& nums){
        int cur = nums[ind];
        while( !q.empty() && nums[q.back()] <= cur){
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

    /* Get max element in the current window */
    int get_max(vector<int>& nums){
        return nums[q.front()];
    }
};

/*
Below code demonstrates how the class can be used to solve the 
sliding-window-maximum problem with ease.
*/

// Reference: https://leetcode.com/problems/sliding-window-maximum/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        MaxQueue mxq;
        
        for(int i = 0; i < k; i++){
            mxq.push_back(i, nums);
        }
        
        ans.push_back(mxq.get_max(nums));
        
        for(int i = k; i < n; i++){
            mxq.push_back(i, nums);
            mxq.pop_front(i - k);
            ans.push_back(mxq.get_max(nums));
        }
        
        return ans;
}
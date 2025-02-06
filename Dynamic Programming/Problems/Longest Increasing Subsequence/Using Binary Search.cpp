#include <iostream>
#include <vector>

int LISBinarySearch(int n, int a[]){
    if (n == 0) return 0;

    std::vector<int> ans;
    ans.push_back(ans[0]);

    for (size_t i = 1; i < n; i++)
    {
        if (a[i] > ans.back())
        {
            ans.push_back(a[i]);
        }
        else
        {
            int index = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin();
            ans[index] = a[i];
        }
        
    }

    return ans.size();
    
    
}

int main(){
    int a[] = {5, 8, 3, 7, 9, 1};
    int n = sizeof(a) / sizeof(a[0]); 

    int result = LISBinarySearch(n, a);
    std::cout << "Length of Longest Increasing Subsequence Using Binary Search: " << result << std::endl;

}
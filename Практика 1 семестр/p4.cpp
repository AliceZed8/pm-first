#include <iostream>
#include <vector>

void push (unsigned char &mas, std::vector<int> &nums) {
    for (int i = 0; i < nums.size(); i++) mas |= nums[i] << (nums.size() - i - 1)*2 ;
}
std::vector<int> read (unsigned char &mas, int count) {
    std::vector<int> nums;
    for (int i = 0; i < count; i++) nums.push_back((mas >> (count - i - 1)*2) & 3);
    return nums;
}


int main() {
    std::vector<int> nums = {1 , 2 , 1};
    unsigned char arr = 0;
    push(arr, nums);
    std::vector<int> result;

    result = read(arr, nums.size());

    for (int i = 0; i < result.size(); i++) std::cout << result[i] << std::endl;

}
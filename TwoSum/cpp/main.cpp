#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <cassert>

std::vector<int> twoSum(std::vector<int>& nums, int target) 
{
    if (nums.size() < 2) {
        return {};
    }

    std::map<int,int> num_map;
    
    size_t i = 0;
    while (i < nums.size())
    {
        int diff = target - nums[i];
        if (num_map.find(diff) != num_map.end())
        {
            return {num_map[diff], static_cast<int>(i)};
        }
        num_map[nums[i]] = static_cast<int>(i);
        i++;
    }
    return {};
}

int main() {
    
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distVal(-1000,1000); // Диапазон значений элементов массива
    std::uniform_int_distribution<int> distLen(2,200); // Диапазон длины массива
    std::uniform_int_distribution<int> distCount(1,500); // Диапазон количества тестов

    int testsCount = distCount(gen);
    bool allTestsPassed = true;

    for (int i = 0; i < testsCount; i++)
    {
        int n = distLen(gen);
        std::vector<int> nums(n);
        for (int j = 0; j < n; j++)
        {
            nums[j] = distVal(gen);
        }

        int i1 = gen() % n;
        int i2 = gen() % n;
        while (i1 == i2)
        {
            i2 = gen() % n;
        }
        int target = nums[i1] + nums[i2];

        auto result = twoSum(nums, target);
        bool ok = false;
        if (!result.empty())
        {
            long long sum = static_cast<long long>(nums[result[0]]) + nums[result[1]];
            ok = (sum == target && result[0] != result[1]);
        }
        if (!ok) {
            std::cerr << "Test #" << i << " FAILED!\n";
            std::cerr << "nums size = " << n << "\n";
            std::cerr << "target = " << target << "\n";
            if (result.empty()) {
                std::cerr << "Result is empty (no pair found)\n";
            } else {
                std::cerr << "Returned indices: " << result[0] << ", " << result[1]
                          << " -> values: " << nums[result[0]] << ", " << nums[result[1]]
                          << "\n";
            }
            allTestsPassed = false;
            break;
        }

    }

    if (allTestsPassed) {
        std::cout << "All tests passed!\n";
    } else {
        std::cout << "Some tests failed.\n";
        return 1;
    }

    return 0;
} 

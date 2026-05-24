#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

int main(int argc, char *argv[])
{
    int a = 0; // test a
    ++a;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100);
    std::vector<int> vec(0);
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(distribution(generator));
    }
    std::sort(std::begin(vec), std::end(vec), [](const int a, const int b)
              {
        if (a > b)
            return true;
        else
            return false; });

    for (auto i : vec)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    return 0;
}
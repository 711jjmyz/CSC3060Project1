/**
 * test/test_mystery_minus_one.cpp
 * 专门针对 -1 (0xFFFFFFFF) 的边界测试
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include "../include/data_lab.hpp" // 引入你的头文件
using namespace data_lab; 

// 颜色代码，方便查看
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

void print_result(const std::string& test_name, int32_t input_a, int32_t input_b, int32_t your_res, int32_t std_res) {
    std::cout << "[" << test_name << "] (" << input_a << ", " << input_b << ") ";
    if (your_res == std_res) {
        std::cout << GREEN << "PASS" << RESET << std::endl;
    } else {
        std::cout << RED << "FAIL" << RESET << std::endl;
        std::cout << "  Expected: " << std_res << " (0x" << std::hex << std_res << ")" << std::dec << std::endl;
        std::cout << "  Got     : " << your_res << " (0x" << std::hex << your_res << ")" << std::dec << std::endl;
        exit(1); // 遇到错误直接停止
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "    Mystery Test: The Power of -1" << std::endl;
    std::cout << "========================================" << std::endl;

    // 测试数据集
    std::vector<int32_t> inputs = {
        0, 1, 2, 100, -1, -2, -100,
        std::numeric_limits<int32_t>::max(),    // 2147483647
        std::numeric_limits<int32_t>::min(),    // -2147483648
        std::numeric_limits<int32_t>::min() + 1 // -2147483647
    };

    int32_t minus_one = -1;

    // 1. 测试 Multiply (乘以 -1)
    // 预期：等于取反 (Negation)
    std::cout << "\n--- Testing multiply(x, -1) ---" << std::endl;
    for (int32_t x : inputs) {
        // 注意：INT_MIN * -1 在 C++ 中是溢出，通常结果还是 INT_MIN。
        // 我们验证你的函数是否和直接用 * 号的行为一致。
        int32_t expected = x * minus_one; 
        int32_t actual = multiply(x, minus_one);
        print_result("Mul -1", x, minus_one, actual, expected);
    }

    // 2. 测试 Divide (除以 -1)
    // 预期：等于取反，但在 INT_MIN 时需特别注意
    std::cout << "\n--- Testing divide(x, -1) ---" << std::endl;
    for (int32_t x : inputs) {
        // 跳过 INT_MIN / -1 的标准对比，因为这在 x86 上会触发 SIGFPE (Floating point exception) 导致程序崩溃
        // 你的位运算实现不应该崩溃，而应该返回 INT_MIN (overflow wrap around)
        if (x == std::numeric_limits<int32_t>::min()) {
            int32_t actual = divide(x, minus_one);
            std::cout << "[Div -1] (INT_MIN, -1) ";
            // 只要你的程序没崩，且返回了 INT_MIN，就算通过 Mystery Test 的这一关
            if (actual == std::numeric_limits<int32_t>::min()) {
                std::cout << GREEN << "PASS (Overflow Handled)" << RESET << std::endl;
            } else {
                std::cout << RED << "FAIL" << RESET << " (Got: " << actual << ")" << std::endl;
            }
            continue;
        }

        int32_t expected = x / minus_one;
        int32_t actual = divide(x, minus_one);
        print_result("Div -1", x, minus_one, actual, expected);
    }

    // 3. 测试 -1 作被除数
    // -1 / x
    std::cout << "\n--- Testing divide(-1, x) ---" << std::endl;
    std::vector<int32_t> divisors = { 1, 2, -1, -2, 100, std::numeric_limits<int32_t>::max() };
    for (int32_t div : divisors) {
        int32_t expected = minus_one / div;
        int32_t actual = divide(minus_one, div);
        print_result("Div dividend -1", minus_one, div, actual, expected);
    }
    
    // 4. 测试 -1 移位相关的乘法
    // 验证 multiply(x, (1 << 31) - 1) 即 multiply(x, INT_MAX)
    // 验证 multiply(x, -1 << 1) 即 multiply(x, -2)
    std::cout << "\n--- Testing Shifted Patterns ---" << std::endl;
    
    int32_t x = 10;
    // Test x * -2
    int32_t pattern_minus_2 = minus_one << 1; // 0xFFFFFFFE (-2)
    print_result("Mul by (-1<<1)", x, pattern_minus_2, multiply(x, pattern_minus_2), x * pattern_minus_2);

    // Test x * INT_MAX
    int32_t pattern_int_max = static_cast<int32_t>(static_cast<uint32_t>(minus_one) >> 1); // 0x7FFFFFFF
    print_result("Mul by (u-1>>1)", x, pattern_int_max, multiply(x, pattern_int_max), x * pattern_int_max);

    std::cout << "\n" << GREEN << "All -1 Mystery Tests Passed!" << RESET << std::endl;
    return 0;
}
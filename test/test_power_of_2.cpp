#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <limits>
#include <iomanip>
#include "../include/data_lab.hpp" // 引入你的头文件
using namespace data_lab; 

// 颜色代码，方便查看输出
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace std;

// 辅助函数：生成 2 的幂次测试数据
vector<int32_t> generate_test_values() {
    vector<int32_t> values;
    
    // 基础边界
    values.push_back(0);
    values.push_back(-1);
    values.push_back(1);
    values.push_back(std::numeric_limits<int32_t>::max()); // 2147483647
    values.push_back(std::numeric_limits<int32_t>::min()); // -2147483648

    // 生成所有正的 2 的幂：1, 2, 4, 8 ... 2^30
    for (int i = 0; i < 31; ++i) {
        int32_t val = 1 << i;
        values.push_back(val);
        // 同时加入负的 2 的幂：-1, -2, -4 ...
        values.push_back(-val);
        // 加入边界：2^n - 1 (全是1的掩码)
        values.push_back(val - 1);
        // 加入边界：2^n + 1
        values.push_back(val + 1);
    }
    return values;
}

// 统计变量
int passed_count = 0;
int failed_count = 0;

void check(string op_name, int32_t a, int32_t b, int32_t expected, int32_t actual) {
    if (expected == actual) {
        passed_count++;
    } else {
        failed_count++;
        cout << RED << "[FAIL] " << op_name << " " 
             << "a=" << a << " (0x" << hex << a << "), "
             << "b=" << b << " (0x" << hex << b << ")" << dec
             << "\n\tExpected: " << expected << " (0x" << hex << expected << ")"
             << "\n\tActual:   " << actual << " (0x" << hex << actual << ")" 
             << dec << RESET << endl;
    }
}

int main() {
    cout << "=== Advanced Testing: Powers of 2 & Extremes ===" << endl;

    vector<int32_t> dataset = generate_test_values();
    cout << "Generated " << dataset.size() << " test values." << endl;
    cout << "Total combinations per operator: " << dataset.size() * dataset.size() << endl;

    for (int32_t a : dataset) {
        for (int32_t b : dataset) {
            
            // 1. Test Add
            // 注意：C++有符号溢出是UB，但通常编译器通过补码回绕实现。
            // 这里我们假设标准行为是补码回绕，与作业要求一致。
            int32_t expected_add = (int32_t)((uint32_t)a + (uint32_t)b); 
            check("ADD", a, b, expected_add, add(a, b));

            // 2. Test Subtract
            int32_t expected_sub = (int32_t)((uint32_t)a - (uint32_t)b);
            check("SUB", a, b, expected_sub, subtract(a, b));

            // 3. Test Multiply
            int32_t expected_mul = (int32_t)((uint32_t)a * (uint32_t)b);
            check("MUL", a, b, expected_mul, multiply(a, b));

            // 4. Test Divide (排除除以0, 和 INT_MIN / -1 的硬件溢出)
            if (b != 0 && !(a == std::numeric_limits<int32_t>::min() && b == -1)) {
                check("DIV", a, b, a / b, divide(a, b));
            }

            // 5. Test Modulo (排除除以0, 和 INT_MIN / -1)
            if (b != 0 && !(a == std::numeric_limits<int32_t>::min() && b == -1)) {
                check("MOD", a, b, a % b, modulo(a, b));
            }
        }
    }

    cout << "============================================" << endl;
    if (failed_count == 0) {
        cout << GREEN << "ALL TESTS PASSED! (" << passed_count << " checks)" << RESET << endl;
    } else {
        cout << RED << "SOME TESTS FAILED. (" << failed_count << " failures)" << RESET << endl;
    }

    return failed_count == 0 ? 0 : 1;
}
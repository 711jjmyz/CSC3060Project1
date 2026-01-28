#include "data_lab.hpp"
#include <cstdint>


namespace data_lab {

int32_t add(int32_t a, int32_t b) {
    int32_t p = a ^ b;          // Sum without carry
    int32_t g = a & b;          // Carry bits

    // The following are five parallel carry transfer processes (for 32-bit) 
    // After each operation, the distance passed by the carry doubles
    // 1-2-4-8-16-32,ervery bit can get the final carry

    g = g | (p & (g << 1));
    p = p & (p << 1);

    g = g | (p & (g << 2));
    p = p & (p << 2);

    g = g | (p & (g << 4));
    p = p & (p << 4);

    g = g | (p & (g << 8));
    p = p & (p << 8);

    g = g | (p & (g << 16));



    return (a ^ b )^ (g<<1);
    
    
}

int32_t subtract(int32_t a, int32_t b) {
    int32_t complement = add(~b, 1);
    int32_t result = add(a, complement);
    return result;
}

int32_t multiply(int32_t a, int32_t b) {
   int32_t result = 0;
    
    // unsign b
    uint32_t un_b = static_cast<uint32_t>(b);

    while (un_b != 0) {
        // 检查最后一位
        if (un_b & 1) {
            result = add(result, a);
        }
        
        a = a << 1;     
        un_b = un_b >> 1; 
    }
    
    return result;
    
}

int32_t divide(int32_t a, int32_t b) {
    if (b == 0) return 0;

   //get sig of result
    int32_t sign_a = (a >> 31) & 1;
    int32_t sign_b = (b >> 31) & 1;
    int32_t result_neg = sign_a ^ sign_b;

    // transform to unsigned
    uint32_t u_a = static_cast<uint32_t>(a);
    uint32_t u_b = static_cast<uint32_t>(b);

    // components
    if (sign_a) {
        u_a = static_cast<uint32_t>(add(~u_a, 1));
    }
    if (sign_b) {
        u_b = static_cast<uint32_t>(add(~u_b, 1));
    }

    uint32_t quotient = 0;
    int32_t i = 31;
    
    //use add(a,1) to recongize i>=0
    while (add(i, 1)) {
        uint32_t shifted_a = u_a >> i;
        //diff
        int32_t diff = subtract(static_cast<int32_t>(shifted_a), static_cast<int32_t>(u_b));
        // get sign bits
        int32_t s_x = (static_cast<int32_t>(shifted_a) >> 31) & 1;
        int32_t s_y = (static_cast<int32_t>(u_b) >> 31) & 1;
        int32_t s_d = (diff >> 31) & 1;
        // 2 cases can subtract
        int32_t case1 = s_x & (!s_y);
        int32_t case2 = (!(s_x ^ s_y)) & (!s_d);
        
        int32_t fcase = case1 | case2;

        if (fcase) {
            quotient |= (1 << i);
            // u_a = u_a - (u_b << i)
            u_a = static_cast<uint32_t>(subtract(static_cast<int32_t>(u_a), static_cast<int32_t>(u_b << i)));
        }

        i = add(i, -1);
    }
    // apply sign
    if (result_neg) {
        return add(~static_cast<int32_t>(quotient), 1);
    }

    return static_cast<int32_t>(quotient);
    
    
}

int32_t modulo(int32_t a, int32_t b) {
    if (b == 0) return 0; 
    

    // result sign
    int32_t sign_a = (a >> 31) & 1; 
    int32_t sign_b = (b >> 31) & 1;
    
    // abs values
    uint32_t abs_a = sign_a ? static_cast<uint32_t>(subtract(0, a)) : static_cast<uint32_t>(a);
    uint32_t abs_b = sign_b ? static_cast<uint32_t>(subtract(0, b)) : static_cast<uint32_t>(b);

    uint32_t remainder = 0;

    for (int i = 31; i != -1; i = subtract(i, 1)) {
        remainder = remainder << 1;
        
        uint32_t bit = (abs_a >> i) & 1;
        remainder = remainder | bit;

        //recognize if remainder >= abs_b
        int32_t diff = subtract(static_cast<int32_t>(remainder), static_cast<int32_t>(abs_b));
        int32_t diff_sign = (diff >> 31) & 1;

        if (!diff_sign) { 
            remainder = static_cast<uint32_t>(diff);
        }
    }
    if (sign_a) {
        return subtract(0, static_cast<int32_t>(remainder));
    }

    return static_cast<int32_t>(remainder);
}
}  // namespace data_lab
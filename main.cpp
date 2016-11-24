//
//  main.cpp
//  PilotTVTest
//
//  Created by howardhuang on 2016/11/24.
//  Copyright © 2016年 howardhuang. All rights reserved.
//

#include <iostream>

#define MAP_SIZE 2

// 00(0) -> 00(0)
// 01(1) -> 10(2)
// 10(2) -> 01(1)
// 11(3) -> 11(3)

struct s {
    struct s *p;
};

int mapping[] = {0, 2, 1, 3};

unsigned int change_bit(unsigned input) {
    unsigned int result = 0, tmp = input;
    int n = 0;
    while (tmp > 0) {
        result += mapping[tmp & 0xf] << (2 * n);
        tmp = tmp >> 2;
        n++;
    }

    return result;
}

struct s *f(struct s *h, struct s *e) {
    struct s *p = h;
    struct s **pp = &h;
    while(p) {
        if (p == e) {
            *pp = e -> p;
            std::cout << "*f 1:" << *pp << "\n";
            std::cout << "*f h:" << h << "\n";
            return h;
        }
        pp = &(p -> p);
        std::cout << "*f 2:" << *pp << "\n";
        p = p -> p;
    }
    std::cout << "*f 2 h:" << h << "\n";
    return h;
}

struct s use_s() {
    struct s s1;
    struct s s2;
    struct s s3;
    struct s s4;
    
    s1.p = &s2;
    s2.p = &s3;
    s3.p = NULL;

    std::cout << "s1: " << &s1 << "\n";
    std::cout << "s2: " << &s2 << "\n";
    std::cout << "s3: " << &s3 << "\n";
    std::cout << "s4: " << &s4 << "\n\n";
    std::cout << s1.p << "\n";
    std::cout << s2.p << "\n";
    std::cout << s3.p << "\n";
    std::cout << s4.p << "\n";
    
    return *f(&s1, &s3);
}

void sieve_func(int N) {
    // Create a array of N numbers
    // Example: {1, 2, 3, 4, 5}
    int array[N], i, p = 2, tmp = 2;
    for (i = 1; i <= N; ++i) {
        array[i - 1] = i;
    }

    while (p < N) {
        // Filtering the non-prime number
        for (i = 1; i <= N; ++i) {
            if (array[i - 1] >= (p * p)) {
                if (array[i - 1] % p == 0) {
                    // Find a non-prime number, set it to zero
                    array[i - 1] = 0;
                }
            }
        }
        
        // Update pivot
        tmp = p;
        for (i = 1; i <= N; ++i) {
            if (array[i - 1] > p) {
                p = array[i - 1];
                // FIXME:
                // I make a mistake here in the morning
                // Use "continue" results in that p will go through to the final number lol.
                break;
            }
        }
        
        // It means that we can't found other p anymore
        if (tmp == p) {
            p = N;
        }
    }
    
    // Print the result
    for (i = 1; i <= N; ++i) {
        if (array[i - 1] > 1) {
            std::cout << array[i - 1] << "\n";
        }
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    unsigned int target = 1234;
    struct s res = use_s();
    std::cout << "target: " << target << ", result: " << change_bit(target) << "\n";
    std::cout << "result: " << res.p << "\n";
    sieve_func(1000);

    return 0;
}

//
//  main.cpp
//  PilotTVTest
//
//  Created by howardhuang on 2016/11/24.
//  Copyright © 2016年 howardhuang. All rights reserved.
//

#include <iostream>

#define MAP_SIZE    2
#define FIZZ        3
#define BUZZ        5

// 00(0) -> 00(0)
// 01(1) -> 10(2)
// 10(2) -> 01(1)
// 11(3) -> 11(3)

using std::cout;
using std::endl;

struct s {
    struct s *p;
};

int mapping[] = {0, 2, 1, 3};

void fizz_buzz(int input) {
    int i = 0, fizz = 0, buzz = 0;
    for (i = 1; i <= input; ++i) {
        fizz = 0, buzz = 0;

        if (i % FIZZ == 0) {
            cout << " Fizz";
            fizz = 1;
        }

        if (i % BUZZ == 0) {
            cout << " Buzz";
            buzz = 1;
        }

        if (!fizz && !buzz)
            cout << " " << i;

        if (i != input) {
            cout << ",";
        }
    }
    cout << endl;
}

unsigned int change_bit(unsigned input) {
    unsigned int result = 0, tmp = input;
    int n = 0;
    while (tmp > 0) {
        result += mapping[tmp & 0xf] << (MAP_SIZE * n);
        tmp = tmp >> MAP_SIZE;
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
            return h;
        }
        pp = &(p -> p);
        p = p -> p;
    }
    return h;
}

void print_list(struct s *h) {
    struct s *p = h;
    while (p) {
        std::cout << p;
        p = p -> p;
        if (p) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";
}

void use_s() {
    int p = 0;
    struct s s1;
    struct s s2;
    struct s s3;
    
    while (p < 4) {
        // Construct a linked list
        s1.p = &s2;
        s2.p = &s3;
        s3.p = NULL;
        std::cout << "Example " << p + 1 << ":\n";
        print_list(&s1);
    
        // Use function
        switch (p) {
            case 0:
                print_list(&(*f(&s1, &s1)));
                break;
            case 1:
                print_list(&(*f(&s1, &s2)));
                break;
            case 2:
                print_list(&(*f(&s1, &s3)));
                break;
            case 3:
                print_list(&(*f(&s2, &s3)));
                break;
        }
        p++;
    }
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
                // FIXED:
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
    // Q1
    unsigned int target = 1234;
    std::cout << "target: " << target << ", result: " << change_bit(target) << "\n";
    // Q2
    use_s();
    // Q3
    sieve_func(10);
    fizz_buzz(66);

    return 0;
}

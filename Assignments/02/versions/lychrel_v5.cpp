/////////////////////////////////////////////////////////////////////////////
//
//  lychrel.cpp
//
//  A program that searches for the largest (in terms of number of
//    iterations without exceeding a specified maximum) palindrome value.
//
//  The program reports a list of numbers that share the maximum number of
//    iterations, along with the size and final palindrome number
//

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <barrier>
#include <algorithm>

#include "LychrelData.h"

// A structure recording the starting number, and its final palindrome.
//   An vector of these records (typedefed to "Records") is built during
//   program execution, and output before the program terminates.
struct Record {
    Number n;
    Number palindrome;
};
using Records = std::vector<Record>;

// Application specific constants
const size_t MaxIterations = 7500;
const size_t MaxThreads = 10;

//
// --- main ---
//
int main() {
    LychrelData data;

    std::cerr << "Processing " << data.size() << " values ...\n";

    // std::atomic<size_t> maxIter = 0;  // Records the current maximum number of iterations
    // Records records;     // list of values that took maxIter iterations
    std::vector<size_t> maxIters(MaxThreads, 0);
    std::vector<Records> t_records(MaxThreads);

    std::mutex mutex;    // protects the records vectors
    std::barrier barrier(MaxThreads);

    // Start all threads
    auto lastID = MaxThreads - 1;
    size_t batchSizes [5] = {32, 64, 128, 256, 512};
    for (auto id = 0; id < MaxThreads; ++id) {

        auto tBatchSize = batchSizes[size_t(id / 2)];

        std::thread t{ [&]() {
            // Batch parameters
            size_t batchSize = tBatchSize;

            std::vector<Number> numbers;

            // Process a list of numbers
            while (data.getNext(batchSize, numbers)) {
                for (auto& number : numbers) {
                    size_t iter = 0;
                    Number n = number;

                    // The Lychrel loop - Check a single number n
                    while (!n.is_palindrome() && ++iter < MaxIterations) {
                        Number sum(n.size());   // Value used to store current sum of digits
                        Number r = n.reverse(); // reverse the digits of the value

                        // An iterator pointing to the first digit of the reversed
                        //   value.  This iterator will be incremented to basically
                        //   traverse the digits of the main number in reverse
                        auto rd = n.begin(); 
                        
                        bool carry = false;  // flag to indicate if we had a carry

                        /*
                        * Sum the digits using the "transform" algorithm.  This
                        *   algorithm traverses a range of values (in our case,
                        *   starting with the least-siginificant [i.e., right most]
                        *   digit) of the original number, adding each digit to its
                        *   matching digit (by position) in the reversed number.
                        *
                        * The result is stored in the sum variable, which is
                        *   built up one digit at a time, respecting if a carry
                        *   digit was necessary for any iteration. 
                        */
                        std::transform(n.rbegin(), n.rend(), sum.rbegin(), 
                            [&](auto d) {
                                auto v = d + *rd++ + carry;
                
                                carry = v > 9;
                                if (carry) { v -= 10; }
                
                                return v;
                            }
                        );

                        // If there's a final carry value, prepend that to the sum
                        if (carry) { sum.push_front(1); }

                        // Transfer the sum making it the next number to be processed
                        //   (i.e., reversed, summed, and checked if it's a
                        //   palindrome)
                        n = sum;
                    }

                    /*
                    * Update our records.  First, determine if we have a new
                    *   maximum number of iterations that isn't the control limit
                    *   (MaxIterations) for a particular number.  If we're less
                    *   tha the current maximum (maxIter) or we've exceeded the number
                    *   of permissible iterations, ignore the current result and move
                    *   onto the next number.
                    */
                    if (iter < maxIters[id] || iter == MaxIterations) { continue; }

                    // Otherwise update our records, which possibly means discarding
                    //   our current maximum and rebuilding our records list.
                    
                    Record record{number, n};
                    if (iter > maxIters[id]) {    
                        t_records[id].clear();
                        maxIters[id] = iter;
                    }
                    t_records[id].push_back(record);
                }
                batchSize = (--batchSize == 0) ? 1 : batchSize;
            }

            barrier.arrive_and_wait();
        }};

        (id < lastID) ? t.detach() : t.join();

    }

    // Process the list of each threads records
    size_t maxIter = *max_element(maxIters.begin(), maxIters.end());
    std::cout << "\nmaximum number of iterations = " << maxIter << "\n";
    for (auto i = 0; i < MaxThreads; ++i) {
        if (maxIters[i] == maxIter) {
            for (auto& [number, palindrome] : t_records[i]) {
                std::cout 
                    << "\t" << number 
                    << " : [" << palindrome.size() << "] "
                    << palindrome << "\n";
            }
        }
    }

    // Output our final results
    // std::cout << "\nmaximum number of iterations = " << maxIter << "\n";
    // for (auto& [number, palindrome] : records) {
    //     std::cout 
    //         << "\t" << number 
    //         << " : [" << palindrome.size() << "] "
    //         << palindrome << "\n";
    // }
}
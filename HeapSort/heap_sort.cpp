#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <iterator>
#include <chrono>


using namespace std::chrono;

template< typename RandomIt, typename Compare >
void heap_sort(RandomIt first, RandomIt last, Compare comp) {

  
  // used to test the time as my function was not working
  //std::make_heap(first,last, comp);
  //std::sort_heap(first,last,comp);

  //Your Heap Sort implementation goes here
  RandomIt current = first;
  RandomIt temp = first;

  if((*first) == NULL) {
    return;
  }

  RandomIt large = first;

  while(std::distance(current, last) > 0) {
    do {
      // dont know how to multiply current by 2 and add 1 or 2 for left and right child
      RandomIt leftChild = (current++);
      RandomIt rightChild = (current++);

      if(std::distance(leftChild, last) < 0) {
        if(std::distance(rightChild, last) < 0) {
          break;
        }
        else {
          large = rightChild;
        }
      }
      else if(std::distance(rightChild, last) < 0) {
        large = leftChild;
      }
      else {
        if(comp(*leftChild, *rightChild)) {
          large = (rightChild);
        }
        else {
          large = (leftChild);
        }
      }

      if(comp((*current),(*large))) {
        *temp = *large;
        *large = *current;
        *current = *large;
      }
    }
    while(std::distance(current, last) > 0);
    
  current++;
  }
  
  while(std::distance(current, last) > 0) {
    std::cout << *current << std::endl;
    current++;
  } 
  

  // hint, use std::distance
  size_t dist = std::distance(first, last);
  std::cout << "dist = " << dist << std::endl;
  std::cout << "*(first + 5) = " << *(first + 5) << std::endl; // like heap[5]
  
}

int main(int argc, char **argv) {

  const size_t N = 100000;

  //
  // Generate random numbers for input
  std::vector<size_t> the_input;
  std::mt19937 mt(0);
  std::uniform_int_distribution<size_t> dist(
      0, std::numeric_limits<size_t>::max());
  for (size_t i = 0; i < N; ++i) {
    the_input.push_back(dist(mt));
  }
  

  auto start = high_resolution_clock::now();
  //
  // Call std::sort
  //std::sort(the_input.begin(), the_input.end(), std::less<size_t>());
  heap_sort(the_input.begin(), the_input.end(), std::less<size_t>());

  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << std::endl;
  //
  // Check if sorted
  assert(std::is_sorted(the_input.begin(), the_input.end(), std::less<size_t>()));

  

  return 0;
}
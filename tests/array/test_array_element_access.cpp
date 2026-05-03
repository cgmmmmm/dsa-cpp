#include <iostream>
#include <cstddef>
#include <cassert>
#include <type_traits>
#include <stdexcept>
#include "../../include/data_structures/cgm_array.hpp"

template <typename ArrayType>
void test1(ArrayType& array, std::size_t index)
{	
	try {
		if constexpr (std::is_const_v<ArrayType>)
		{
			std::cout << "Read-only array value at index " << index << ": " << array.at(index) << " (Should return " << array[index] << " (operator[] ret))" << std::endl;
		}
		else
		{
			std::cout << "Modifiable array value at index " << index << ": " << array.at(index) << " (Should return " << array[index] << " (operator[] ret))" << std::endl;
		}
	}
	catch (const std::out_of_range& e)
	{
		if constexpr (std::is_const_v<ArrayType>)
		{
			std::cout << "Read-only array value at index " << index << ": " << e.what() << std::endl;
		}
		else
		{
			std::cout << "Modifiable array value at index " << index << ": " << e.what() << std::endl;
		}
	}
}

int main()
{
	cgm::array<int, 0> empty;
	const cgm::array<int, 0> r_empty;

	cgm::array<int, 4> arr{3, 1, 4, 1};
	const cgm::array<int, 4> r_arr{9, 8, 7, 6};
	
	std::cout << "Modifiable Array : " << arr[0] << "," << arr[1] << "," << arr[2] << "," << arr[3] << std::endl;
	std::cout << "Read-only Array  : " << r_arr[0] << "," << r_arr[1] << "," << r_arr[2] << "," << r_arr[3] << std::endl;
	
	std::cout << std::endl;
	std::cout << "====  testing cgm::array::at AND cgm::array::operator[]  ====" << std::endl;
	// 1. modifiable array
	// N within bounds
	test1(arr, 3);
	// N not within bounds
	test1(arr, 11);
	// 2. read-only array
	// N within bounds
	test1(r_arr, 1);
	// N not within bounds
	test1(r_arr, 7);

	std::cout << std::endl;
	std::cout << "====  testing cgm::array::front  ====" << std::endl;
	// 1. modifiable array
	std::cout << "Modifiable array value .front(): " << arr.front() << " (Should return 3)" << std::endl;
	// 2. read-only array
	std::cout << "Read-only array value .front(): " << r_arr.front() << " (Should return 9)" << std::endl;
	std::cout << "TESTED: seg fault occurs when N = 0 or array.empty() is true" << std::endl;

	std::cout << std::endl;
	std::cout << "==== testing cgm::array::back  ====" << std::endl;
	// 1. modifiable array
	std::cout << "Modifiable array value .back(): " << arr.back() << " (Should return 1)" << std::endl;
	// 2. read-only array
	std::cout << "Read-only array value .back(): " << r_arr.back() << " (Should return 6)" << std::endl;
	std::cout << "TESTED: seg fault occurs when N = 0 or array.empty() is true" << std::endl;

	std::cout << std::endl;
	std::cout << "====  testing cgm::array::data  ====" << std::endl;
	std::cout << "Modifiable array first element raw pointer: " << arr.data() << std::endl;
	std::cout << "EMPTY Modifiable array first element raw pointer: " <<  empty.data() << std::endl;
	std::cout << "Read-only array first element raw pointer: " << r_arr.data() << std::endl;
	std::cout << "EMPTY Read-only array first element raw pointer: " << r_empty.data() << std::endl;

	std::cout << std::endl;
	std::cout << "ALL ELEMENT ACCESS DEFINITIONS PASSED" << std::endl;

	return 0;
}

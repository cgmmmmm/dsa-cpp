#include <iostream>
#include <cassert>
#include "../../include/data_structures/cgm_array.hpp"

int main()
{	
	std::cout << std::endl;

	std::cout << "====================================" << std::endl;
	std::cout << "1. Testing cgm::array::empty" << std::endl;
	std::cout << "====================================" << std::endl;
	
	using empty_arr_traits = cgm::detail::array_traits<int, 0>;
	using cgm_empty_arr = cgm::array<int, 0>;
	
	// 1. test internal memory layout type directly
	empty_arr_traits::storage_type rawStorageEmptyArr;
	std::cout << "Raw storage size for N=0: " << sizeof(rawStorageEmptyArr) << " byte(s)" << std::endl;

	// 2. test the actual array capacity implementation
	cgm_empty_arr emptyArray;
	if (emptyArray.empty())
	{
		std::cout << "emptyArray is empty." << std::endl;
	}
	else
	{
		std::cerr << "emptyArray is not empty." << std::endl;
		return 1;
	}

	assert(emptyArray.size() == 0);
	assert(emptyArray.max_size() == 0);

	std::cout << "Capacity tests for N=0 passes." << std::endl;

	std::cout << std::endl;


	std::cout << "==================================================" << std::endl;
	std::cout << "2. Testing cgm::array::size & cgm::array::max_size" << std::endl;
	std::cout << "==================================================" << std::endl;
	
	using size5Array = cgm::detail::array_traits<double, 5>;
	using cgm_array = cgm::array<double, 5>;

	// 1. test internal memory layout directly
	size5Array::storage_type rawStorageArray5;
	std::cout << "Raw storage size for N=5 (double): " << sizeof(rawStorageArray5) << " byte(s)" << std::endl;
	
	// 2. test the actual array capacity implementation
	cgm_array size5Arr;
	if (size5Arr.empty())
	{
		std::cout << "size5Arr is empty." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "size5Arr is not empty." << std::endl;
	}

	assert(size5Arr.size() == 5);
	assert(size5Arr.max_size() == 5);

	std::cout << "Capacity tests for N>0 passes." << std::endl;

	std::cout << std::endl;


	std::cout << "==========================================================================" << std::endl;
	std::cout << "3. Testing cgm::array::size & cgm::array::max_size with values initialized" << std::endl;
	std::cout << "==========================================================================" << std::endl; 
	
	using charArray = cgm::detail::array_traits<char, 10>;

	// 1. test internal memory layout directly
	charArray::storage_type rawStorageCharArray = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	std::cout << "Raw storage size for N=10 (char): " << sizeof(rawStorageCharArray) << " byte(s)" <<  std::endl;

	// 2. test the actual array capacity implementation
	cgm::array<char, 10> abc = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	if (abc.empty())
	{
		std::cout << "char_array is empty." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "char_array is not empty." << std::endl;
	}

	assert(abc.size() > 0);
	assert(abc.size() == 10);
	assert(abc.max_size() == 10);
	
	char* ptr = reinterpret_cast<char*>(&abc);
	std::cout << "---------------- Memory Addresses -----------------" << std::endl;
	std::cout << "          Base Address: " << (void*)ptr << std::endl;
	for (int i=0; i<10; ++i)
	{
		std::cout << "Index [" << i << "] | Address: " << (void*)(ptr + i) << " | Value: '" << *(ptr + i) << "'" << std::endl;
	}
	std::cout << "--------------------------------------------------" << std::endl;

	std::cout << "Capacity test for N>0 initialized with values passes." << std::endl;


	std::cout << std::endl;
	
	return 0;
}

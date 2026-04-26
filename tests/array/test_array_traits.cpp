#include <iostream>
#include "../../include/data_structures/cgm_array.hpp"

int main()
{
	std::cout << std::endl;

	std::cout << "====================================" << std::endl;
	std::cout << "1. Testing cgm::detail::array_traits" << std::endl;
	std::cout << "====================================" << std::endl;

	using int_traits = cgm::detail::array_traits<int, 3>;

	int_traits::storage_type myData = {10, 20, 30};

	// 1. test cgm::detail::array_traits::ref
	int& middle = int_traits::ref(myData, 1);
	std::cout << "Original middle: " << middle << std::endl;

	// 2. testing const_cast
	middle = 999;

	std::cout << "New middle: " << middle << std::endl;

	// 3. test cgm::detail::array_traits::ptr
	int* first = int_traits::ptr(myData);
	std::cout << "First item via pointer: " << *first << std::endl;

	std::cout << "Final array: [" << myData[0] << "," << myData[1] << "," << myData[2] << "]" << std::endl;

	std::cout << std::endl;


	std::cout << "==================================================" << std::endl;
	std::cout << "2. Testing cgm::detail::array_traits (Empty array)" << std::endl;
	std::cout << "==================================================" << std::endl;
			
	using empty_traits = cgm::detail::array_traits<int, 0>;

	empty_traits::storage_type emptyData;

	// 1. test ptr() for empty array
	int* p = empty_traits::ptr(emptyData);
	if (p == nullptr)
	{
		std::cout << "ptr() correctly returned nullptr." << std::endl;
	}

	// 2. test ref() for empty array
	int* p_from_ref = &empty_traits::ref(emptyData, 0);

	std::cout << "Address of ref(emptyData, 0): " << p_from_ref << std::endl;

	if (p_from_ref == nullptr)
	{
		std::cout << "ref() correctly points to address 0 (nullptr)." << std::endl;
	}


	std::cout << std::endl;

	return 0;
}

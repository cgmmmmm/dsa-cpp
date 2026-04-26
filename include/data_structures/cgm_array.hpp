#ifndef CGM_ARRAY_HPP
#define CGM_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

#endif

namespace cgm
{
	// =======================================
	//	Internal Memory Layout Traits
	// ======================================= 
	namespace detail
	{
		// (N > 0) case
		template<typename T, std::size_t N>
		struct array_traits 
		{
			using storage_type = T [N]; // creates an actual array that occupies space
			
			static constexpr T& ref(const storage_type& t, std::size_t n) noexcept
			{
				return const_cast<T&>(t[n]); // returns a referrence (the element itself)
			}

			static constexpr T* ptr(const storage_type& t) noexcept
			{
				return const_cast<T*>(t); // returns a pointer (hex value in memory of the start of the array)
			}

		};
		
		// (N = 0) case
		template<typename T>
		struct array_traits<T, 0> // a raw array cannot have zero size, (T[0] is illegal)
		{
			struct storage_type { }; // defines an empty struct, allocate at least 1 byte, rather than allocating space for T
			
			static constexpr T& ref(const storage_type&, std::size_t) noexcept
			{
				return *static_cast<T*>(nullptr); // cpp semantics: nullptr evaluates to address 0
			}

			static constexpr T* ptr(const storage_type&) noexcept
			{
				return nullptr; // ptr to empty array should always return nullptr
			}
		};
	}


	// =================================
	//	cgm::array Definitions
	// =================================
	template <typename T, std::size_t N>
	struct array
	{
		// Data Member
		typename detail::array_traits<T, N>::storage_type _M_elems;

		// Standard Types
		using size_type			= std::size_t;

		// Capacity
		[[nodiscard]] constexpr bool empty() const noexcept { return N==0; };
		[[nodiscard]] constexpr size_type size() const noexcept { return N; };
		[[nodiscard]] constexpr size_type max_size() const noexcept { return N; };
	};
}

#ifndef CGM_ARRAY_HPP
#define CGM_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

#endif

namespace cgm
{
	namespace detail
	{
		template<typename T, std::size_t N>
		struct array_traits 
		{
			using storage_type = T [N];
			
			static constexpr T& ref(const storage_type& t, std::size_t n) noexcept
			{
				return const_cast<T&>(t[n]);
			}

			static constexpr T* ptr(const storage_type& t) noexcept
			{
				return const_cast<T*>(t);
			}

		};

		template<typename T>
		struct array_traits<T, 0> // handles edge-case for empty array (N = 0)
		{
			struct storage_type { }; // defines an empty struct, allocate at least 1 byte, rather than allocating space for T
			
			static constexpr T& ref(const storage_type&, std::size_t) noexcept
			{
				return *static_cast<T*>(nullptr);
			}

			static constexpr T* ptr(const storage_type&) noexcept
			{
				return nullptr;
			}
		};


	}
}

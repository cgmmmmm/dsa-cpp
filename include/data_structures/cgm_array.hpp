#ifndef CGM_ARRAY_HPP
#define CGM_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <iterator>

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

		// Member Types
		using size_type			= std::size_t;
		using value_type		= T;
		using reference			= value_type&;
		using const_reference		= const value_type&;
		using pointer			= value_type*;
		using const_pointer		= const value_type*;
		using iterator			= T*;
		using const_iterator		= const T*;
		using reverse_iterator		= std::reverse_iterator<iterator>;
		using const_reverse_iterator	= const std::reverse_iterator<iterator>;

		// Capacity
		[[nodiscard]] constexpr bool empty() const noexcept { return N==0; };
		[[nodiscard]] constexpr size_type size() const noexcept { return N; };
		[[nodiscard]] constexpr size_type max_size() const noexcept { return N; };

		// Element access
		constexpr reference at(size_type position)
		{
			if (position >= N) 
			{
				throw std::out_of_range("cgm::array::at: Index out of bounds");
			}
			return detail::array_traits<T, N>::ref(_M_elems, position);
		}
		constexpr const_reference at(size_type position) const
		{
			if (position >= N)
			{
				throw std::out_of_range("cgm::array::at: Index out of bounds");
			}
			return detail::array_traits<T, N>::ref(_M_elems, position);
		}
		
		[[nodiscard]] constexpr reference operator[](size_type position) noexcept
		{
			return detail::array_traits<T, N>::ref(_M_elems, position);
		}

		[[nodiscard]] constexpr const_reference operator[](size_type position) const noexcept
		{
			return detail::array_traits<T, N>::ref(_M_elems, position);
		}

		[[nodiscard]] constexpr reference front() noexcept
		{
			return detail::array_traits<T, N>::ref(_M_elems, 0);
		}
		[[nodiscard]] constexpr const_reference front() const noexcept
		{
			return detail::array_traits<T, N>::ref(_M_elems, 0);
		}

		[[nodiscard]] constexpr reference back() noexcept
		{
			return detail::array_traits<T, N>::ref(_M_elems, N>0 ? N-1 : 0);
		}
		[[nodiscard]] constexpr const_reference back() const noexcept
		{
			return detail::array_traits<T, N>::ref(_M_elems, N>0 ? N-1 : 0);
		}

		[[nodiscard]] constexpr pointer data() noexcept
		{
			return detail::array_traits<T, N>::ptr(_M_elems);
		}
		[[nodiscard]] constexpr const_pointer data() const noexcept
		{
			return detail::array_traits<T, N>::ptr(_M_elems);
		}

		// Iterators
		[[nodiscard]] constexpr iterator begin() noexcept { return iterator(data()); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return const_iterator(data()); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator end() noexcept { return iterator(data() + N); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return const_iterator(data() + N); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return rend(); }

	};
}

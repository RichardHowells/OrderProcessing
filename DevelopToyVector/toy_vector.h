#if !defined TOY_VECTOR_H
#define TOY_VECTOR_H

#include <memory>

template <typename T, typename allocator = std::allocator<T>>
class toy_vector
{
	allocator allocator;
	T* data_start;
	T* first_available;
	T* limit;

public:
	using iterator = T*;
	using const_iterator = const T*;

	toy_vector& operator=(const toy_vector& rhs) = delete;

	// Careful - initializers with dependencies...  What's the order of initialization?
	toy_vector() : data_start{ allocator.allocate(20) }, first_available{ data_start }, limit{ data_start + 20 } {}

	toy_vector(const toy_vector& other) : allocator{ other.allocator }, data_start { allocator.allocate(20) }, first_available{ data_start }, limit{ data_start + 20 }
	{
		std::uninitialized_copy(other.data_start, other.data_start + other.size(), first_available);
		first_available += other.size();
	}

	~toy_vector() {
		allocator.deallocate(data_start, limit - data_start);
	}

	size_t size() const { return first_available - data_start; }

	void push_back(const T& newValue)
	{
		std::uninitialized_fill(first_available, first_available + 1, newValue);
		++first_available;
	}

	T& back() {
		return *(first_available - 1);
	}

	const_iterator begin() const {
		return data_start;
	}

	iterator begin() {
		return data_start;
	}

	const_iterator end() const {
		return first_available;
	}

	iterator end() {
		return first_available;
	}
};

#endif

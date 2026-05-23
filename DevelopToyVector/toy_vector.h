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

	// Careful - initializers with dependencies...  What's the order of initialization?
	toy_vector() : data_start{ allocator.allocate(20) }, first_available{ data_start }, limit{ data_start + 20 } {}

	toy_vector(const toy_vector& other) : allocator{ other.allocator }, data_start{ allocator.allocate(20) }, first_available{ data_start }, limit{ data_start + 20 }
	{
		std::uninitialized_copy(other.data_start, other.data_start + other.size(), first_available);
		first_available += other.size();
	}

	toy_vector(toy_vector&& other) : allocator{ std::move(other.allocator) }, data_start{ other.data_start }, first_available { other.first_available }, limit{ other.limit }
	{
		// Leave the other object safe for deletion - it needs memory to delete, but no objects in that memory
		other.data_start = other.allocator.allocate(20);
		other.first_available = other.data_start;
		other.limit = other.data_start + 20;
	}

	toy_vector& operator=(const toy_vector& rhs) 
	{
		auto new_allocator = rhs.allocator;
		auto new_data_start = allocator.allocate(20);
		std::uninitialized_copy(rhs.data_start, rhs.data_start + rhs.size(), new_data_start);
		auto new_first_available = new_data_start + rhs.size();
		auto new_limit = new_data_start + 20;

		// Potentially throwing operations completed - well except for the allocator
		// Ignore that for the moment

		// Nuke the existing data.  First destroy the objects
		// then use the existing allocator to release the memory
		for (auto p = begin(); p != end(); ++p)
			p->~T();
		allocator.deallocate(data_start, size());

		// Now swap in the new attribute values
		allocator = new_allocator;		// This is suspect.  For all we know it might throw
		data_start = new_data_start;
		first_available = new_first_available;
		limit = new_limit;

		return *this;
	}


	~toy_vector() {
		for (auto p = begin(); p != end(); ++p)
			p->~T();
		allocator.deallocate(data_start, 20);
	}

	size_t size() const { return first_available - data_start; }

	void push_back(const T& newValue)
	{
		// construct_at is C++20 - previously used allocator.construct
		std::construct_at(first_available, newValue);
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

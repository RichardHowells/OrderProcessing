#if !defined TOY_VECTOR_H
#define TOY_VECTOR_H

template <typename T>
class toy_vector
{
	static const size_t limit = 20;
	T* data_start;
	T* first_available;

public:
	using iterator = T*;
	using const_iterator = const T*;

	toy_vector(const toy_vector& other) = delete;
	toy_vector& operator=(const toy_vector& rhs) = delete;

	// Careful - initializers with dependencies...  What's the order of initialization?
	toy_vector() : data_start{ new T[limit] }, first_available{ data_start } {}

	~toy_vector() {
		delete[] data_start;
	}

	void push_back(const T& newValue)
	{
		*first_available = newValue;
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

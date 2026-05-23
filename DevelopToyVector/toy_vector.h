#if !defined TOY_VECTOR_H
#define TOY_VECTOR_H

template <typename T>
class toy_vector
{
	static const size_t limit = 20;
	T data[limit];
	int first_available = 0;

public:
	using iterator = T*;
	using const_iterator = const T*;

	void push_back(const T& newValue)
	{
		data[first_available] = newValue;
		++first_available;
	}

	T& back() {
		return data[first_available - 1];
	}

	const_iterator begin() const {
		return &data[0];
	}

	iterator begin() {
		return &data[0];
	}

	const_iterator end() const {
		return &data[first_available];
	}

	iterator end() {
		return &data[first_available];
	}
};

#endif

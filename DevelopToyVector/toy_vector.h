#if !defined TOY_VECTOR_H
#define TOY_VECTOR_H

template <typename T>
class toy_vector
{
	static const size_t limit = 20;
	T data[limit];
	int first_available = 0;

public:
	void push_back(const T& newValue)
	{
		data[first_available] = newValue;
		++first_available;
	}

	T& back() {
		return data[first_available - 1];
	}
};

#endif

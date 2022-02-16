#include "Vector.h"

namespace Core {
	template<size_t n, typename T>
	Core::Vector<n, T>::Vector(std::array<T, n> value)
	{
		contents = value;
	}
}
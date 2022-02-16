#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <array>

namespace Core {

	template<size_t n, typename T>
	class Vector {
	public:
		Vector(std::array<T, n> value);
		//Add(Vector<size_t n, typename T>);

	private:
		std::array<T, n> contents;
	};

}
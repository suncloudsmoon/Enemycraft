/*
 * Copyright (c) 2021, suncloudsmoon and the Enemycraft contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * Arr2D.hpp
 *
 *  Created on: Oct 6, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_ARR2D_HPP_
#define INCLUDE_ARR2D_HPP_

template<class T, class S>
class Arr2D {
public:
	Arr2D(S numRows, S numColumns) :
			rows(numRows), columns(numColumns) {
		arr = new T[numRows * numColumns]();
	}
	~Arr2D() {
		delete[] arr;
	}
	T& get(S x, S y) {
		if (x >= rows || y >= columns) {
			std::string err = "X or Y is out of range: (X: " + std::to_string(x)
					+ ", Y: " + std::to_string(y) + "), (" + "Row: "
					+ std::to_string(rows) + ", Col: " + std::to_string(columns)
					+ ")";
			throw std::out_of_range(err);
		}
		return arr[y * rows + x];
	}

	T& operator()(S x, S y) {
		return get(x, y);
	}
	void clear() {
		std::fill_n(arr, rows * columns, 0);
	}
private:
	T *arr;
	S rows, columns;
};

#endif /* INCLUDE_ARR2D_HPP_ */

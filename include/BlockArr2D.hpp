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
 * BlockArr2D.hpp
 *
 *  Created on: Oct 9, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_BLOCKARR2D_HPP_
#define INCLUDE_BLOCKARR2D_HPP_

#include <string>

#include <Block.hpp>
#include <Point.hpp>

/**
 * Custom class specifically made to handle block pointers
 */
template<class T, class S>
class BlockArr2D {
public:
	/**
	 * numRows = number of rows in each chunk
	 * numColumns = number of columns in each chunk
	 * bSize = block size
	 */
	BlockArr2D(S numRows, S numColumns, S bSize) :
			rows(numRows), columns(numColumns), arraySize(numRows * numColumns), blockSize(
					bSize) {
		arr = new Block<T>*[numRows * numColumns]();
	}
	~BlockArr2D() {
		for (auto *b : arr) {
			if (b != NULL)
				delete b;
		}
		if (arr != NULL)
			delete[] arr;
	}

	void clear() {
		for (auto *b : arr) {
			if (b != NULL)
				delete b;
		}
		std::fill_n(arr, rows * columns, 0);
	}

	void set(Point<T> &p, Block<T> *block) {
		set(p.x, p.y, block);
	}

	void set(T x, T y, Block<T> *block) {
		S newX = (S) (x / blockSize);
		S newY = (S) (y / blockSize);
		if (newX < 0 || newY < 0 || newX >= rows || newY >= columns) {
			std::string err = "X or Y is out of range: (X: "
					+ std::to_string(newX) + ", Y: " + std::to_string(newY)
					+ "), (" + "Row: " + std::to_string(rows) + ", Col: "
					+ std::to_string(columns) + ")";
			throw std::out_of_range(err);
		}
		arr[newY * rows + newX] = block;
	}

	void remove(Point<T> &p) {
		remove(p.x, p.y);
	}

	void remove(T x, T y) {
		S newX = (S) (x / blockSize);
		S newY = (S) (y / blockSize);
		if (arr[newY * rows + newX] != nullptr) {
			delete arr[newY * rows + newX];
			arr[newY * rows + newX] = nullptr;
		}
	}

	Block<T>* get(Point<T> &p) {
		return get(p.x, p.y);
	}

	Block<T>* get(T x, T y) {
		S newX = (S) (x / blockSize);
		S newY = (S) (y / blockSize);
		// Bounds checking
		if (newX < 0 || newY < 0 || newX >= rows || newY >= columns) {
			std::string err = "X or Y is out of range: (X: "
					+ std::to_string(newX) + ", Y: " + std::to_string(newY)
					+ "), (" + "Row: " + std::to_string(rows) + ", Col: "
					+ std::to_string(columns) + ")";
			throw std::out_of_range(err);
		}

		return arr[newY * rows + newX];
	}

	Block<T>* operator()(T x, T y) {
		return get(x, y);
	}

	S getSize() {
		return arraySize;
	}

	Block<T>**& getArr() {
		return arr;
	}

	void setArr(Block<T> **&arr) {
		this->arr = arr;
	}

	S getColumns() const {
		return columns;
	}

	S getRows() const {
		return rows;
	}

private:
	Block<T> **arr;
	S rows, columns;
	S arraySize;
	S blockSize;
};

#endif /* INCLUDE_BLOCKARR2D_HPP_ */

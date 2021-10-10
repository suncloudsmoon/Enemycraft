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
 * Point.hpp
 *
 *  Created on: Oct 4, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_POINT_HPP_
#define INCLUDE_POINT_HPP_

template<class T>
class Point {
public:
	Point() :
			x(0), y(0) {
	}
	Point(T xCoord, T yCoord) :
			x(xCoord), y(yCoord) {
	}
	bool operator==(const Point<T> &p) const {
		return x == p.x && y == p.y;
	}
	bool operator!=(const Point<T> &p) const {
		return x != p.x || y != p.y;
	}
	bool operator<(const Point<T> &p) const {
		if (y < p.y) {
			return true;
		} else if (y == p.y) {
			return x < p.x;
		}
		return false;
	}
	bool operator>(const Point<T> &p) const {
		if (y > p.y) {
			return true;
		} else if (y == p.y) {
			return x > p.x;
		}
		return false;
	}

	bool operator<=(const Point<T> &p) const {
		return y <= p.y;
	}

	bool operator>=(const Point<T> &p) const {
		return y >= p.y;
	}

	T operator[](T item) const {
		return (item == 1) ? y : x;
	}

	Point<T> operator+(const Point<T> &p) const {
		return Point<T>(x + p.x, y + p.y);
	}
	Point<T> operator-(const Point<T> &p) const {
		return Point<T>(x - p.x, y - p.y);
	}
	Point<T> operator*(const Point<T> &p) const {
		return Point<T>(x * p.x, y * p.y);
	}
	Point<T> operator/(const Point<T> &p) const {
		return Point<T>(x / p.x, y / p.y);
	}
	Point<T> operator%(const Point<T> &p) const {
		return Point<T>(x % p.x, y % p.y);
	}
	Point<T>& operator+=(const Point<T> &p) const {
		x += p.x;
		y += p.y;
		return *this;
	}
	Point<T>& operator-=(const Point<T> &p) const {
		x -= p.x;
		y -= p.y;
		return *this;
	}
	Point<T>& operator*=(const Point<T> &p) const {
		x *= p.x;
		y *= p.y;
		return *this;
	}
	Point<T>& operator/=(const Point<T> &p) const {
		x /= p.x;
		y /= p.y;
		return *this;
	}
	Point<T>& operator%=(const Point<T> &p) const {
		x %= p.x;
		y %= p.y;
		return *this;
	}

	T x, y;
};

template<class T>
struct std::hash<Point<T>> {
	std::size_t operator()(const Point<T> &p) const {
		return p.x ^ (p.y << 1);
	}
};

#endif /* INCLUDE_POINT_HPP_ */

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
 * ForceTable.hpp
 *
 *  Created on: Oct 4, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_FORCETABLE_HPP_
#define INCLUDE_FORCETABLE_HPP_

#include <cstdlib>
#include <string>
#include <sstream>
#include <array>
#include "Arr2D.hpp"

// G - general data points, P - precision data points
template<class G, class P>
class ForceTable {
public:
	ForceTable(G width, G height, G bSize) :
			w(width), h(height), blockSize(bSize) {
		fx = new Arr2D<P, G>(width, height);
		fy = new Arr2D<P, G>(width, height);
	}
	~ForceTable() {
		delete fx;
		delete fy;
	}
	/*
	 * fx, fy is negative/positive
	 */
	void addForce(G x, G y, P forceX, P forceY) {
		x = x / blockSize;
		y = y / blockSize;
		if (x < 0 || x >= w || y < 0 || y >= h) {
			return;
		}
		if (fx > 0) {
			for (G i = x + 1; i < w; i++) {
				fx->get(i, y) += forceX;
			}
		} else if (fx < 0) {
			for (G i = x - 1; i >= 0; i--) {
				fx->get(i, y) += forceX;
			}
		}

		if (fy > 0) {
			for (G i = y + 1; i < h; i++) {
				fy->get(x, i) += forceY;
			}
		} else if (fy < 0) {
			for (G i = y - 1; i >= 0; i--) {
				fy->get(x, i) += forceY;
			}
		}
	}

	void removeForce(G x, G y, P forceX, P forceY) {
		addForce(x, y, -forceX, -forceY);
	}

	void clearAllForces() {
		if (w > 0 && h > 0) {
			fx->clear();
			fy->clear();
		} else {
			throw -10;
		}
	}

	Point<P> getForce(G x, G y) {
		G accessX = x / blockSize, accessY = y / blockSize;
		if (accessX < w && accessY < h) {
			return Point<P> { fx->get(accessX, accessY), fy->get(accessX, accessY) };
		} else {
			return Point<P>();
		}

	}

	void serialize(std::string &dest) {
		dest += w + " " + h + "\n";
		for (G row = 0; row < h; row++) {
			for (G col = 0; col < w; col++) {
				dest += std::to_string(fx(row, col)) + " "
						+ std::to_string(fy(row, col));
			}
			dest += "\n";
		}
	}

private:
	Arr2D<P, G> *fx;
	Arr2D<P, G> *fy;
	G w, h;
	G blockSize;
};

#endif /* INCLUDE_FORCETABLE_HPP_ */

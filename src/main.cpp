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
 * main.cpp
 *
 *  Created on: Oct 2, 2021
 *      Author: suncloudsmoon
 */

#include <iostream>

#include <Game.hpp>
#include <Point.hpp>

const Point<unsigned int> fullHD(1920, 1080);

int main() {
//	try {
//		Game g("Enemycraft - Just Imagine", fullHD);
//		g.startGameLoop();
//	} catch (std::exception &e) {
//		std::cerr << "Oops, an exception: " << e.what() << std::endl;
//	} catch (...) {
//		std::cerr << "An Unknown Exception Occurred!" << std::endl;
//	}
	Game g("Enemycraft - Just Imagine", fullHD);
	g.startGameLoop();
}


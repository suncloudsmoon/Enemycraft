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
 * Block.hpp
 *
 *  Created on: Oct 2, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_BLOCK_HPP_
#define INCLUDE_BLOCK_HPP_

#include <SFML/Graphics.hpp>

/*
 * There are four states of a block: 0,1-4
 * 0 - no magnetic charge
 * 1 - North charge (up facing icon)
 * 2 - East charge (right facing icon)
 * 3 - South charge (bottom facing icon)
 * 4 - West charge (left facing icon)
 * Any block can be magnetic, but like real life, some blocks are more magnetic in general than others (need to define the magnetic constants)
 * By right clicking on a block, you can change the charge? (change the thing in survival where the player loses a magnetic health point for it)
 */
template<class T>
class Block: public sf::Sprite {
public:
	Block(T len, T m, T velocityX, T velocityY, sf::Texture &texture) :
		sf::Sprite(texture), length(len), mass(m), vx(
					velocityX), vy(velocityY) {
		magnetFacingDirection = 0; // default
	}

	T getLength() const {
		return length;
	}

	void setLength(T length) {
		this->length = length;
	}

	int getMagnetFacingDirection() const {
		return magnetFacingDirection;
	}

	void setMagnetFacingDirection(int magnetFacingDirection) {
		this->magnetFacingDirection = magnetFacingDirection;
	}

	T getMass() const {
		return mass;
	}

	void setMass(T mass) {
		this->mass = mass;
	}

	T getVx() const {
		return vx;
	}

	void setVx(T vx) {
		this->vx = vx;
	}

	T getVy() const {
		return vy;
	}

	void setVy(T vy) {
		this->vy = vy;
	}

private:
	T length;
	T mass; // in kg
	T vx, vy;
	int magnetFacingDirection;
};

#endif /* INCLUDE_BLOCK_HPP_ */

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

#include <vector>
#include <SFML/Graphics.hpp>

#include "Point.hpp"
#include "TextureManager.hpp"

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
	Block(T len, T m, T velocityX, T velocityY, float muConstant,
			TextureManager &manager) :
			sf::Sprite(manager.getNormalBlock()), length(len), mass(m), vx(
					velocityX), vy(velocityY), mu(muConstant), textureManager(
					manager) {
		magnetFacingDirection = 0; // default
	}

	void moveWithStats(T x, T y) {
		previousCoord.x = getPosition().x;
		previousCoord.y = getPosition().y;
		setPosition(getPosition().x + (float) x, getPosition().y + (float) y);
	}

	void setPosWithStats(T x, T y) {
		previousCoord.x = getPosition().x;
		previousCoord.y = getPosition().y;
		setPosition((float) x, (float) y);
	}

	bool isMagnetic() {
		return magnetFacingDirection >= 1 && magnetFacingDirection <= 4;
	}

	bool operator==(const Block<T> &b) const {
		sf::Vector2f &aPos = getPosition();
		sf::Vector2f &bPos = getPosition();
		return (((aPos.x / length) * length) == ((bPos.x / length) * length))
				&& (((aPos.y / length) * length) == ((bPos.y / length) * length));
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
		switch (magnetFacingDirection) {
		case 0:
			setTexture(textureManager.getNormalBlock());
			break;
		case 1:
			setTexture(textureManager.getMagnetUpBlock());
			break;
		case 2:
			setTexture(textureManager.getMagnetDownBlock());
			break;
		case 3:
			setTexture(textureManager.getMagnetLeftBlock());
			break;
		case 4:
			setTexture(textureManager.getMagnetRightBlock());
			break;
		default:
			setTexture(textureManager.getNormalBlock());
			break;
		}
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

	const Point<T>& getPreviousCoord() const {
		return previousCoord;
	}

	void setPreviousCoord(const Point<T> &previousCoord) {
		this->previousCoord = previousCoord;
	}

	float getMu() const {
		return mu;
	}

	void setMu(float mu) {
		this->mu = mu;
	}

private:
	T length;
	T mass; // in kg

	T vx, vy;

	float mu; // between 0 and 1
	TextureManager &textureManager;

	int magnetFacingDirection;
	Point<T> previousCoord;
};

#endif /* INCLUDE_BLOCK_HPP_ */

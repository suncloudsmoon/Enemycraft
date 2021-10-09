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
 * BlockManager.hpp
 *
 *  Created on: Oct 2, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_BLOCKMANAGER_HPP_
#define INCLUDE_BLOCKMANAGER_HPP_

#include <string>
#include <vector>
#include <random>
#include <map>

#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "TextureManager.hpp"
#include "Point.hpp"
#include "ForceTable.hpp"

template<class P, class T>
class BlockManager {
public:
	BlockManager(P bSize, P bMass, T w, T h, TextureManager &manager,
			std::mt19937 &device) :
			blockSize(bSize), blockMass(bMass), width(w), height(h), textureManager(
					manager), randDevice(device) {
		forceTable = new ForceTable<T, P>(width / blockSize, height / blockSize,
				blockSize);
		magnetForce = 100; // in Newtons (N)
	}

	void add(Block<P> block) {
		// Learned: you cannot insert the same object twice
		Point<T> coords = getBlockyCoordinates(block.getPosition().x,
				block.getPosition().y);
		addMagneticForce(coords, block);
		blockMap.insert( { coords, block });
	}

	void addMagneticForce(const Point<T> &coords, const Block<P> &block) const {
		switch (block.getMagnetFacingDirection()) {
		// Up
		case 1:
			forceTable->addForce(coords.x, coords.y, 0, block.getMass());
			break;
			// Down
		case 2:
			forceTable->addForce(coords.x, coords.y, 0, -block.getMass());
			break;
			// Left
		case 3:
			forceTable->addForce(coords.x, coords.y, -block.getMass(), 0);
			break;
			// Right
		case 4:
			forceTable->addForce(coords.x, coords.y, block.getMass(), 0);
			break;
		default:
			break;
		}
	}

	void removeMagneticForce(const Point<T> &p, const Block<P> &block) const {
		switch (block.getMagnetFacingDirection()) {
		// Up
		case 1:
			forceTable->removeForce(p.x, p.y, 0, block.getMass());
			break;
			// Down
		case 2:
			forceTable->removeForce(p.x, p.y, 0, -block.getMass());
			break;
			// Left
		case 3:
			forceTable->removeForce(p.x, p.y, -block.getMass(), 0);
			break;
			// Right
		case 4:
			forceTable->removeForce(p.x, p.y, block.getMass(), 0);
			break;
		default:
			break;
		}
	}

	void remove(Point<T> p) {
		// TODO: remove the force too here
		auto &key = blockMap.at(p);
		removeMagneticForce(p, key);
		blockMap.erase(p);
	}

	void generateAll() {
		std::uniform_int_distribution<T> randsBlocks(0, blockSize);
		std::uniform_int_distribution<T> randsX(0, width - blockSize);
		std::uniform_int_distribution<T> randsY(0, height - blockSize);
		std::uniform_int_distribution<T> randMagnetism(0, 4);

		T numBlocks = randsBlocks(randDevice);
		for (T i = 0; i < numBlocks; i++) {
			Block<P> block(blockSize, blockMass, 0, 0, textureManager);
			block.setMagnetFacingDirection(randMagnetism(randDevice));
			T x = (T) (randsX(randDevice) / blockSize) * blockSize;
			T y = (T) (randsY(randDevice) / blockSize) * blockSize;
			block.setPosition(x, y);
			add(block);
		}
	}

	Point<T> getBlockyCoordinates(P x, P y) {
		T newX = (T) (x / blockSize) * blockSize;
		T newY = (T) (y / blockSize) * blockSize;
		return Point<T>(newX, newY);
	}

	Point<T> getBlockyCoordinates(Point<P> p) {
		T newX = (T) (p.x / blockSize) * blockSize;
		T newY = (T) (p.y / blockSize) * blockSize;
		return Point<T>(newX, newY);
	}

	T getBlockMass() const {
		return blockMass;
	}

	void setBlockMass(T blockMass) {
		this->blockMass = blockMass;
	}

	T getBlockSize() const {
		return blockSize;
	}

	void setBlockSize(T blockSize) {
		this->blockSize = blockSize;
	}

	T getHeight() const {
		return height;
	}

	void setHeight(T height) {
		this->height = height;
	}

	T getWidth() const {
		return width;
	}

	void setWidth(T width) {
		this->width = width;
	}

	// Need to be careful with getters and setters; they can introduce bugs into code!
	std::map<Point<T>, Block<P> >& getBlockMap() {
		return blockMap;
	}

	void setBlockMap(std::map<Point<T>, Block<P> > &blockMap) {
		this->blockMap = blockMap;
	}

	ForceTable<T, P>*& getForceTable() {
		return forceTable;
	}

	void setForceTable(ForceTable<T, P> *&forceTable) {
		this->forceTable = forceTable;
	}

private:
	std::map<Point<T>, Block<P>> blockMap;
	ForceTable<T, P> *forceTable;

	T blockSize;
	T blockMass;
	T width, height;
	TextureManager &textureManager;
	std::mt19937 &randDevice;

	T magnetForce; // assumed to be positive
};

#endif /* INCLUDE_BLOCKMANAGER_HPP_ */

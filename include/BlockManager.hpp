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

#include <SFML/Graphics.hpp>
#include <Block.hpp>
#include <TextureManager.hpp>
#include <Point.hpp>
#include <ForceTable.hpp>
#include <BlockArr2D.hpp>

template<class P, class T>
class BlockManager {
public:
	BlockManager(P bSize, P bMass, T w, T h, float defaultMuConstant,
			TextureManager &manager, std::mt19937 &device) :
			blockSize(bSize), blockMass(bMass), width(w / bSize), height(
					h / bSize), defaultMu(defaultMuConstant), textureManager(
					manager), randDevice(device) {
		blockMap = new BlockArr2D<P, T>(width, height, blockSize);
		forceTable = new ForceTable<T, P>(width, height, blockSize);
		magnetForce = 100;

		// Debug Messages
		std::cout << "BlockManager width: " << width << ", height: " << height
				<< std::endl;
	}

	void add(Block<P> *block) {
		// Learned: you cannot insert the same object twice
		Point<P> blockCoord(block->getPosition().x, block->getPosition().y);
		addMagneticForce(blockCoord, block);
		blockMap->set(blockCoord, block);
	}

	void remove(Point<P> &p) {
		remove(p.x, p.y);
	}

	void remove(P x, P y) {
		Block<P> *block = blockMap->get(x, y);
		removeMagneticForce(x, y, block);
		blockMap->remove(x, y);
	}

	void addMagneticForce(const Point<P> &coords, const Block<P> *block) const {
		addMagneticForce(coords.x, coords.y, block);
	}

	void addMagneticForce(P x, P y, const Block<P> *block) const {
		switch (block->getMagnetFacingDirection()) {
		// Up
		case 1:
			forceTable->addForce(x, y, 0, block->getMass());
			break;
			// Down
		case 2:
			forceTable->addForce(x, y, 0, -block->getMass());
			break;
			// Left
		case 3:
			forceTable->addForce(x, y, -block->getMass(), 0);
			break;
			// Right
		case 4:
			forceTable->addForce(x, y, block->getMass(), 0);
			break;
		default:
			break;
		}
	}

	void removeMagneticForce(const Point<P> &p, const Block<P> *block) const {
		removeMagneticForce(p.x, p.y, block);
	}

	void removeMagneticForce(P x, P y, const Block<P> *block) const {
		switch (block->getMagnetFacingDirection()) {
		// Up
		case 1:
			forceTable->removeForce(x, y, 0, block->getMass());
			break;
			// Down
		case 2:
			forceTable->removeForce(x, y, 0, -block->getMass());
			break;
			// Left
		case 3:
			forceTable->removeForce(x, y, -block->getMass(), 0);
			break;
			// Right
		case 4:
			forceTable->removeForce(x, y, block->getMass(), 0);
			break;
		default:
			break;
		}
	}

	void generateAll() {
		std::uniform_int_distribution<T> randsBlocks(0, blockSize);
		std::uniform_int_distribution<T> randsX(1, width-1);
		std::uniform_int_distribution<T> randsY(1, height-1);
		std::uniform_int_distribution<T> randMagnetism(0, 4);

		T numBlocks = randsBlocks(randDevice);
		for (T i = 0; i < numBlocks; i++) {
			Block<P> *block = new Block<P>(blockSize, blockMass, 0, 0,
					defaultMu, textureManager);
			block->setMagnetFacingDirection(randMagnetism(randDevice));
			T x = (T) (randsX(randDevice) * blockSize);
			T y = (T) (randsY(randDevice) * blockSize);
			block->setPosition(x, y);
			add(block);
		}
	}

	Point<T> getBlockyCoordinates(Point<P> &p) {
		return getBlockyCoordinates(p.x, p.y);
	}

	Point<T> getBlockyCoordinates(P x, P y) {
		T newX = (T) (x / blockSize) * blockSize;
		T newY = (T) (y / blockSize) * blockSize;
		return Point<T>(newX, newY);
	}

	// LEARNED: Need to be careful with getters and setters; they can introduce bugs into code!
	// Getters and Setters

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

	ForceTable<T, P>*& getForceTable() {
		return forceTable;
	}

	void setForceTable(ForceTable<T, P> *&forceTable) {
		this->forceTable = forceTable;
	}

	BlockArr2D<P, T>*& getBlockMap() {
		return blockMap;
	}

	void setBlockMap(BlockArr2D<P, T> *&blockMap) {
		this->blockMap = blockMap;
	}

private:
	BlockArr2D<P, T> *blockMap;
	ForceTable<T, P> *forceTable;

	T blockSize;
	T blockMass;
	T width, height;
	float defaultMu;

	TextureManager &textureManager;
	std::mt19937 &randDevice;

	T magnetForce; // ASSUMPTION: magnetForce >= 0 Newtons
};

#endif /* INCLUDE_BLOCKMANAGER_HPP_ */

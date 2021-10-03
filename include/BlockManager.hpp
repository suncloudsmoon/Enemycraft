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
#include "Block.hpp"

template<class P, class T>
class BlockManager {
public:
	BlockManager(P bSize, P bMass, T w, T h, sf::Texture &bTexture, std::mt19937 &device) :
			blockSize(bSize), blockMass(bMass), width(w), height(h), blockTexture(bTexture), randDevice(
					device) {
	}

	void add(Block<P> block) {
		blocks.push_back(block);
	}

	void generateAll() {
		std::uniform_int_distribution<T> randsBlocks(0, blockSize);
		std::uniform_int_distribution<T> randsX(0, width - blockSize);
		std::uniform_int_distribution<T> randsY(0, height - blockSize);

		T numBlocks = randsBlocks(randDevice);
		for (T i = 0; i < numBlocks; i++) {
			Block<P> block(blockSize, blockMass, 0, 0, blockTexture);
			P x = (int) (randsX(randDevice) / blockSize) * blockSize;
			P y = (int) (randsY(randDevice) / blockSize) * blockSize;
			block.setPosition(x, y);
			blocks.push_back(block);
		}
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
	std::vector<Block<P> >& getBlocks() {
		return blocks;
	}

	void setBlocks(const std::vector<Block<P> > &blocks) {
		this->blocks = blocks;
	}

private:
	T blockSize;
	T blockMass;
	T width, height;
	sf::Texture &blockTexture;
	std::mt19937 &randDevice;
	std::vector<Block<P>> blocks;
};

#endif /* INCLUDE_BLOCKMANAGER_HPP_ */

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
 * TextureManager.hpp
 *
 *  Created on: Oct 3, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_TEXTUREMANAGER_HPP_
#define INCLUDE_TEXTUREMANAGER_HPP_

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class TextureManager {
public:
	bool loadNormalBlock(std::string path);
	bool loadMagnetUpBlock(std::string path);
	bool loadMagnetDownBlock(std::string path);
	bool loadMagnetLeftBlock(std::string path);
	bool loadMagnetRightBlock(std::string path);

	sf::Texture& getMagnetDownBlock() {
		return magnetDownBlock;
	}

	void setMagnetDownBlock(sf::Texture &magnetDownBlock) {
		this->magnetDownBlock = magnetDownBlock;
	}

	sf::Texture& getMagnetLeftBlock() {
		return magnetLeftBlock;
	}

	void setMagnetLeftBlock(sf::Texture &magnetLeftBlock) {
		this->magnetLeftBlock = magnetLeftBlock;
	}

	sf::Texture& getMagnetRightBlock() {
		return magnetRightBlock;
	}

	void setMagnetRightBlock(sf::Texture &magnetRightBlock) {
		this->magnetRightBlock = magnetRightBlock;
	}

	sf::Texture& getMagnetUpBlock() {
		return magnetUpBlock;
	}

	void setMagnetUpBlock(sf::Texture &magnetUpBlock) {
		this->magnetUpBlock = magnetUpBlock;
	}

	sf::Texture& getNormalBlock() {
		return normalBlock;
	}

	void setNormalBlock(sf::Texture &normalBlock) {
		this->normalBlock = normalBlock;
	}

private:
	sf::Texture normalBlock, magnetUpBlock, magnetDownBlock, magnetLeftBlock,
			magnetRightBlock;
};

#endif /* INCLUDE_TEXTUREMANAGER_HPP_ */

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
 * TextureManager.cpp
 *
 *  Created on: Oct 3, 2021
 *      Author: suncloudsmoon
 */

#include <string>
#include <SFML/Graphics.hpp>

#include <TextureManager.hpp>

bool TextureManager::loadNormalBlock(std::string path) {
	return normalBlock.loadFromFile(path);
}

bool TextureManager::loadMagnetUpBlock(std::string path) {
	return magnetUpBlock.loadFromFile(path);
}

bool TextureManager::loadMagnetDownBlock(std::string path) {
	return magnetDownBlock.loadFromFile(path);
}

bool TextureManager::loadMagnetLeftBlock(std::string path) {
	return magnetLeftBlock.loadFromFile(path);
}

bool TextureManager::loadMagnetRightBlock(std::string path) {
	return magnetRightBlock.loadFromFile(path);
}

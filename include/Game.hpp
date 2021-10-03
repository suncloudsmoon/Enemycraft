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
 * Game.hpp
 *
 *  Created on: Oct 2, 2021
 *      Author: suncloudsmoon
 */

#ifndef INCLUDE_GAME_HPP_
#define INCLUDE_GAME_HPP_

#include <string>
#include <thread>
#include <random>

#include "../include/SFML/Graphics.hpp"
#include "../include/BlockManager.hpp"
#include "../include/TextureManager.hpp"

class Game {
public:
	Game(std::string windowTitle, unsigned int width, unsigned int height);
	~Game();

	void startGameLoop();

	void handleAllUserInteractions(sf::Event &event, sf::RenderWindow &window);
	void handleMousePresses(sf::Event &event);
	void handleKeyPresses(sf::Event &event);

	void drawAllBlocks(sf::RenderWindow &window);

	// Calculations
	void updateBlockPositions();

protected:
private:
	TextureManager textureManager;

	std::mt19937 randDevice;
	BlockManager<float, int> *blockManager;

	sf::Time deltaTime;
	std::string title;
	unsigned int w, h;
};



#endif /* INCLUDE_GAME_HPP_ */

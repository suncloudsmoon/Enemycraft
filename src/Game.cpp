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
 * Game.cpp
 *
 *  Created on: Oct 2, 2021
 *      Author: suncloudsmoon
 */

#include <string>
#include <thread>
#include <ctime>

#include <unistd.h>

#include <iostream>

#include "../include/Game.hpp"

Game::Game(std::string windowTitle, unsigned int width, unsigned int height) :
		title(windowTitle), w(width), h(height) {
	deltaTime = sf::Time::Zero;
	randDevice.seed(time(NULL));

	// Loading textures from image files in res folder
	if (!textureManager.loadBlockTexture("res/Block.png")) {
		throw -999;
	}

	if (!textureManager.loadMagnetBlockTextures("res/Magnet Block Up.png")
			|| !textureManager.loadMagnetBlockTextures(
					"res/Magnet Block Down.png")
			|| !textureManager.loadMagnetBlockTextures(
					"res/Magnet Block Left.png")
			|| !textureManager.loadMagnetBlockTextures(
					"res/Magnet Block Right.png")) {
		throw -999;
	}

	blockManager = new BlockManager<float, int>(50.f, 50.f, width, height,
			textureManager, randDevice);
}

Game::~Game() {
	delete blockManager;
}

void Game::startGameLoop() {
	sf::RenderWindow window(sf::VideoMode(w, h), title);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	blockManager->generateAll();

	sf::Clock clock;
	while (window.isOpen()) {
		deltaTime = clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			handleAllUserInteractions(event, window);
		}
		// Calculations
		updateBlockPositions();

		window.clear(sf::Color::Black);
		drawAllBlocks(window);
		window.display();
	}
}
void Game::handleAllUserInteractions(sf::Event &event,
		sf::RenderWindow &window) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		handleMousePresses(event);
		break;
	case sf::Event::KeyPressed:
		handleKeyPresses(event);
		break;
	case sf::Event::Closed:
		window.close();
		break;
	default:
		break;
	}
}

void Game::handleMousePresses(sf::Event &event) {
	switch (event.mouseButton.button) {
	case sf::Mouse::Left: {
		Block<float> block(blockManager->getBlockSize(),
				blockManager->getBlockMass(), 0, 0,
				textureManager.getBlockTexture());
		float x = (int) (event.mouseButton.x / blockManager->getBlockSize())
				* blockManager->getBlockSize();
		float y = (int) (event.mouseButton.y / blockManager->getBlockSize())
				* blockManager->getBlockSize();
		block.setPosition(x, y);
		blockManager->add(block);
		break;
	}
	case sf::Mouse::Right:
		break;
	default:
		break;
	}
}

void Game::handleKeyPresses(sf::Event &event) {
	switch (event.key.code) {
	case sf::Keyboard::W:
		break;
	case sf::Keyboard::A:
		break;
	case sf::Keyboard::S:
		break;
	case sf::Keyboard::D:
		break;
	default:
		break;
	}
}

void Game::drawAllBlocks(sf::RenderWindow &window) {
	for (sf::Sprite &sprite : blockManager->getBlocks()) {
		window.draw(sprite);
	}
}

// Calculate block position based on velocity
void Game::updateBlockPositions() {
	for (Block<float> &block : blockManager->getBlocks()) {
		block.move(block.getVx() * deltaTime.asSeconds(),
				block.getVy() * deltaTime.asSeconds());
		std::cout << "X: " << block.getPosition().x << ", Y: "
				<< block.getPosition().y << std::endl;
	}
}


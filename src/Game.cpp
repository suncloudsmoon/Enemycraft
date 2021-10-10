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
#include <span>

// Debug Libraries to import
#include <unistd.h>
#include <iostream>

#include <Game.hpp>
#include <TMath.hpp>
#include <Point.hpp>

Game::Game(std::string windowTitle, const Point<unsigned int> &dimensions) :
		Game(windowTitle, dimensions.x, dimensions.y) {

}
Game::Game(std::string windowTitle, unsigned int width, unsigned int height) :
		title(windowTitle), w(width), h(height) {
	randDevice.seed(time(NULL));
	deltaTime = sf::Time::Zero;
	defaultMu = 0.5;
	defaultBlockSize = 50.f;

	// Loading textures from image files in res folder
	if (!textureManager.loadNormalBlock("res/Block.png")
			|| !textureManager.loadMagnetUpBlock("res/Magnet_Block_Up.png")
			|| !textureManager.loadMagnetDownBlock("res/Magnet_Block_Down.png")
			|| !textureManager.loadMagnetLeftBlock("res/Magnet_Block_Left.png")
			|| !textureManager.loadMagnetRightBlock(
					"res/Magnet_Block_Right.png")) {
		std::cerr << "err loading textures!" << std::endl;
		throw -999;
	}

	blockManager = new BlockManager<accur, gen>(defaultBlockSize, 5.f, width,
			height, defaultMu, textureManager, randDevice);
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
//		updateBlockForces();
//		updateBlockVelocity();
//		enforceBoxBounds();
//		updateBlockPositions();

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
		Point<accur> coord(
				(event.mouseButton.x / blockManager->getBlockSize())
						* blockManager->getBlockSize(),
				(event.mouseButton.y / blockManager->getBlockSize())
						* blockManager->getBlockSize());

		auto *block = blockManager->getBlockMap()->get(coord);
		if (block == nullptr) {
			Block<accur> *newBlock = new Block<accur>(
					blockManager->getBlockSize(), blockManager->getBlockMass(),
					0, 0, defaultMu, textureManager);
			newBlock->setPosition(coord.x, coord.y);
			blockManager->add(newBlock);
			std::cout << "Added block!" << std::endl;
		} else {
			blockManager->remove(coord);
			std::cout << "Removed block!" << std::endl;
		}

		break;
	}
	case sf::Mouse::Right: {
		Point<accur> coord(event.mouseButton.x, event.mouseButton.y);
		auto *block = blockManager->getBlockMap()->get(coord);
		if (block != NULL) {
			int magnetFacingDirection = block->getMagnetFacingDirection();
			// When the magnet's direction is already 4 (the last one), it should go back to 0
			block->setMagnetFacingDirection(
					(magnetFacingDirection >= 4) ?
							0 : magnetFacingDirection + 1);
		}
		break;
	}
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
	for (gen i = 0; i < blockManager->getBlockMap()->getSize(); i++) {
		Block<accur> *block = blockManager->getBlockMap()->getArr()[i];
		if (block != NULL) {
			window.draw(*block);
		}
	}
}

void Game::updateBlockForces() {
	for (gen i = 0; i < blockManager->getBlockMap()->getSize(); i++) {
		Block<accur> *block = blockManager->getBlockMap()->getArr()[i];
		if (block == NULL) {
			continue;
		}
		// TODO: make it not calculate unnecessarily if the magnetic block isn't moving
		if (block->isMagnetic()) {
			Point<accur> blockPos { block->getPosition().x,
					block->getPosition().y };
			blockManager->removeMagneticForce(block->getPreviousCoord(), block);
			blockManager->addMagneticForce(blockPos.x, blockPos.y, block);
			Point<accur> force = blockManager->getForceTable()->getForce(
					block->getPosition().x, block->getPosition().y);
			blockManager->getForceTable()->addForce(blockPos.x, blockPos.y,
					-(force.x * block->getMu()), -(force.y * block->getMu()));
		}
	}
}

// Calculate block position based on velocity

// A = F/M
void Game::updateBlockVelocity() {
	for (gen i = 0; i < blockManager->getBlockMap()->getSize(); i++) {
		Block<accur> *block = blockManager->getBlockMap()->getArr()[i];
		if (block == NULL) {
			continue;
		}
		Point<gen> pos(block->getPosition().x, block->getPosition().y);
		Point<accur> f = blockManager->getForceTable()->getForce(pos.x, pos.y);
		block->setVx(block->getVx() + (f.x / block->getMass()));
		block->setVy(block->getVy() + (f.y / block->getMass()));

		// Debug Messages
		std::cout << "fx: " << f.x << ", fy: " << f.y << std::endl;
	}
}

void Game::enforceBoxBounds() {
	for (gen i = 0; i < blockManager->getBlockMap()->getSize(); i++) {
		Block<accur> *block = blockManager->getBlockMap()->getArr()[i];
		if (block == NULL) {
			continue;
		}
		const sf::Vector2f &pos = block->getPosition();
		if (pos.x < 0) {
			// Set velocity greater than zero
			block->setVx(tma::abs(block->getVx()));
		} else if (pos.x > w) {
			block->setVx(block->getVx() < 0 ? block->getVx() : -block->getVx());
		}

		if (pos.y < 0) {
			block->setVy(tma::abs(block->getVy()));
		} else if (pos.y > w) {
			block->setVy(block->getVy() < 0 ? block->getVy() : -block->getVy());
		}
	}
}

void Game::updateBlockPositions() {
	for (gen i = 0; i < blockManager->getBlockMap()->getSize(); i++) {
		Block<accur> *block = blockManager->getBlockMap()->getArr()[i];
		if (block == NULL) {
			continue;
		}
		accur deltaX = block->getVx() * deltaTime.asSeconds();
		accur deltaY = block->getVy() * deltaTime.asSeconds();
		block->moveWithStats(deltaX, deltaY);

		// Debug Messages
		std::cout << "Vx: " << block->getVx() << ", Vy: " << block->getVy()
				<< std::endl;
	}
}

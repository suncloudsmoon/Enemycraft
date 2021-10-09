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
#include "../include/TMath.hpp"

Game::Game(std::string windowTitle, unsigned int width, unsigned int height) :
		title(windowTitle), w(width), h(height) {
	randDevice.seed(time(NULL));
	deltaTime = sf::Time::Zero;

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

	blockManager = new BlockManager<accur, gen>(50.f, 5.f, width, height,
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
		updateBlockForces();
		updateBlockVelocity();
		updateBlockPositions();
		enforceBoxBounds();

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
		Point<gen> gridCoord;
		gridCoord.x = (gen) (event.mouseButton.x / blockManager->getBlockSize())
				* blockManager->getBlockSize();
		gridCoord.y = (gen) (event.mouseButton.y / blockManager->getBlockSize())
				* blockManager->getBlockSize();

		auto &map = blockManager->getBlockMap();
		if (map.find(gridCoord) == map.end()) {
			Block<accur> block(blockManager->getBlockSize(),
					blockManager->getBlockMass(), 0, 0, textureManager);
			block.setPosition(gridCoord.x, gridCoord.y);
			blockManager->add(block);
		} else {
			blockManager->remove(gridCoord);
		}

		break;
	}
	case sf::Mouse::Right: {
		const Point<gen> coords = blockManager->getBlockyCoordinates(
				event.mouseButton.x, event.mouseButton.y);
		auto &map = blockManager->getBlockMap();
		if (map.find(coords) != map.end()) {
			auto &key = map.at(coords);
			size_t magnetFacingDirection = key.getMagnetFacingDirection();
			key.setMagnetFacingDirection(
					(magnetFacingDirection > 4) ?
							1 : magnetFacingDirection + 1);
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
	for (auto& [key, val] : blockManager->getBlockMap()) {
		window.draw(val);
	}
}

void Game::updateBlockForces() {
	for (auto& [key, val] : blockManager->getBlockMap()) {
		// TODO: make it not calculate unnecessarily if the magnetic block isn't moving
		if (val.isMagnetic()) {
			Point<gen> previousCoord = blockManager->getBlockyCoordinates(
					val.getPreviousCoord());
			blockManager->removeMagneticForce(previousCoord, val);
			blockManager->addMagneticForce(
					Point<gen>(val.getPosition().x, val.getPosition().y), val);
		}
	}
}

// Calculate block position based on velocity

// A = F/M
void Game::updateBlockVelocity() {
	for (auto& [key, val] : blockManager->getBlockMap()) {
		Point<gen> coord = blockManager->getBlockyCoordinates(
				val.getPosition().x, val.getPosition().y);
		Point<accur> f = blockManager->getForceTable()->getForce(coord.x,
				coord.y);
		val.setVx(val.getVx() + (f.x / val.getMass()));
		val.setVy(val.getVy() + (f.y / val.getMass()));
		std::cout << "fx: " << f.x << ", fy: " << f.y << std::endl;
	}
}

void Game::updateBlockPositions() {
	for (auto& [key, val] : blockManager->getBlockMap()) {
		val.move(val.getVx() * deltaTime.asSeconds(),
				val.getVy() * deltaTime.asSeconds());
		// Debug
		std::cout << "Vx: " << val.getVx() << ", Vy: " << val.getVy()
				<< std::endl;
	}
}

void Game::enforceBoxBounds() {
	for (auto& [key, val] : blockManager->getBlockMap()) {
		const sf::Vector2f &pos = val.getPosition();
		if (pos.x < 0) {
			// Set velocity greater than zero
			val.setVx(tma::abs(val.getVx()));
		} else if (pos.x > w) {
			val.setVx(val.getVx() < 0 ? val.getVx() : -val.getVx());
		}

		if (pos.y < 0) {
			val.setVy(tma::abs(val.getVy()));
		} else if (pos.y > w) {
			val.setVy(val.getVy() < 0 ? val.getVy() : -val.getVy());
		}
	}
}

#pragma once

#include <stdint.h>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"

namespace ResWolf
{
	/** A wall in the level */
	class Wall
	{
	public:

		/** statically caches the wall shader for easy use without lookup multiple times per frame */
		static Shader* shader;
		/** statically caches the wall model for easy use without lookup multiple times per frame */
		static Model* model;

		/** initializes the static variables for the wall */
		static void init();

		/** Constructs a wall */
		Wall(uint16_t x, uint16_t y, uint16_t floorCode, uint16_t wallCode, uint16_t ceilingCode, bool isDoor, uint8_t lockType, char* message, bool solid);
		~Wall();

		/** The texture for the floor tile. If none is specified, will load the floor tile at (0, 0) */
		Texture* floorTexture;
		/** The texture for the wall */
		Texture* wallTexture;
		/** The texture for the ceiling tile. If none is specified, will load the ceiling tile at (0, 0) */
		Texture* ceilingTexture;

		/** The position of the wall */
		glm::vec3 pos;
		/** Is this a door */
		bool isDoor;
		/** What kind of key unlocks this door (if it's a door). 0 -> no key, it's always unlocked */
		uint8_t lockType;
		/** Message associated with the wall. Generally used for signs */
		char* message;

		/** Is this solid? */
		bool solid;

		/** Tracks the movement of the door */ // TODO: Use some nice easing animations for this
		float openProgress;

		/** Is the door open? If so, don't collide */
		bool isOpen;

		/** Draw the wall */
		void draw();
		/** Update the wall (check open progress) */
		void update();
		/** Try to open this wall, given the player's keys.
		  * If the player doesn't have the right key, return false and don't open.
		  * Otherwise, open and return true. */
		bool tryOpen(uint8_t playerKeys);

		/** Opens the door unconditionally */
		void open();
	};
}
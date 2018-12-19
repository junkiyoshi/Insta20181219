#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	~Particle();

	void update(vector<unique_ptr<Particle>>& particles);
	void draw();
	glm::vec2 separate(vector<unique_ptr<Particle>>& particles);
	glm::vec2 align(vector<unique_ptr<Particle>>& particles);
	glm::vec2 cohesion(vector<unique_ptr<Particle>>& particles);
	glm::vec2 seek(glm::vec2 target);
	void applyForce(glm::vec2 force);
	glm::vec2 getLocation();
	glm::vec2 getVelocity();
	glm::vec2 getAcceleration();

private:
	glm::vec2 location;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::vec2 prev_acceleration;

	float range;
	float max_force;
	float max_speed;
	int wall;
};

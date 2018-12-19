#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	this->shader.load("shader/shader.vert", "shader/shader.frag");

	this->number_of_particle = 50;
	for (int i = 0; i < this->number_of_particle; i++) {

		auto particle = make_unique<Particle>();
		this->particles.push_back(move(particle));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& particle : this->particles) {
		
		particle->update(this->particles);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> targets;
	vector<float> force;
	for (auto& particle : this->particles) {
		
		targets.push_back(particle->getLocation());
		force.push_back(std::min(ofMap(glm::length(particle->getAcceleration()), 0, 2, 0.2, 1), 1.f));
	}

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &targets[0].x, this->number_of_particle);
	this->shader.setUniform1fv("force", &force[0], this->number_of_particle);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
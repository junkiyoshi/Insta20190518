#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);

	this->radius = 40;
	for (auto i = 0; i < 30; i++) {

		auto location = glm::vec2(ofRandom(ofGetWidth() * 0.5 - this->radius * 2, ofGetWidth() * 0.5 + this->radius * 2), ofGetHeight() - this->radius * 0.5);
		auto direction = glm::vec2(ofRandom(-1.2, 1.2), ofRandom(-3, -6));
		auto particle = make_pair(location, direction);
		this->particles.push_back(particle);
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	for (auto& particle : this->particles) {

		particle.first += particle.second;

		if (particle.first.y < -this->radius) {

			particle.first = glm::vec2(ofRandom(ofGetWidth() * 0.5 - this->radius * 2, ofGetWidth() * 0.5 + this->radius * 2), ofGetHeight() - this->radius * 0.5);
			particle.second = glm::vec2(ofRandom(-1.2, 1.2), ofRandom(-1, -5));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& particle : this->particles) {

		ofNoFill();
		ofDrawCircle(particle.first, this->radius);

		for (auto& other : this->particles) {

			if (particle == other) { continue; }

			double theta, a;
			if (this->calculate_angle(particle.first, this->radius, other.first, this->radius, theta, a)) {
				
				auto point_1 = particle.first + glm::vec2(this->radius * cos(theta + a), this->radius * sin(theta + a));
				auto point_2 = particle.first + glm::vec2(this->radius * cos(theta - a), this->radius * sin(theta - a));

				ofFill();
				ofDrawCircle(point_1, 8);
				ofDrawCircle(point_2, 8);
			}
			
		}
	}
}

//--------------------------------------------------------------
bool ofApp::calculate_angle(glm::vec2 location_1, float radius_1, glm::vec2 location_2, float radius_2, double& theta, double& a) {

	auto distance = glm::distance(location_1, location_2);
	if (distance > radius_1 + radius_2 || distance < radius_1 - radius_2) { return false; }

	theta = atan2(location_2.y - location_1.y, location_2.x - location_1.x);
	auto cos_a = (pow(distance, 2) + pow(radius_1, 2) - pow(radius_2, 2)) / (2 * distance * radius_1);
	a = acos(cos_a);
	return true;
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
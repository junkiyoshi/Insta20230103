#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	ofColor color;
	this->base_color_list.push_back(ofColor(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int len = 8;
	ofColor color;
	for (int base_x = -270; base_x <= 270; base_x += 180) {

		color.setHsb(ofMap(base_x, -270, 450, 0, 255), 200, 255);

		for (int radius = 0; radius < 80; radius += 5) {

			ofMesh face, line;
			line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

			int start_deg = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0025), 0, 1, -360, 360);
			int deg_len = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -180, 360);

			for (int deg = start_deg; deg <= start_deg + deg_len; deg++) {

				face.addVertex(glm::vec3(base_x + radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
				face.addVertex(glm::vec3(base_x + radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));
				face.addVertex(glm::vec3(base_x + (radius + len) * cos((deg + 1) * DEG_TO_RAD), (radius + len) * sin((deg + 1) * DEG_TO_RAD), 0));
				face.addVertex(glm::vec3(base_x + (radius + len) * cos(deg * DEG_TO_RAD), (radius + len) * sin(deg * DEG_TO_RAD), 0));

				for (int i = 0; i < 4; i++) {

					face.addColor(ofColor(color, 128));
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addVertex(glm::vec3(base_x + radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
				line.addVertex(glm::vec3(base_x + radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));
				line.addVertex(glm::vec3(base_x + (radius + len) * cos((deg + 1) * DEG_TO_RAD), (radius + len) * sin((deg + 1) * DEG_TO_RAD), 0));
				line.addVertex(glm::vec3(base_x + (radius + len) * cos(deg * DEG_TO_RAD), (radius + len) * sin(deg * DEG_TO_RAD), 0));

				for (int i = 0; i < 4; i++) {

					line.addColor(color);
				}

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

				if (deg == start_deg) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				}

				if (deg == start_deg + deg_len) {

					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
				}
			}

			face.draw();
			line.draw();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}

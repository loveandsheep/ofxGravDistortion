//
//  distortManager.cpp
//  boidDistort
//
//  Created by Ovis aries on 2014/02/05.
//
//

#include "ofxGravDistortion.h"

void ofxGravDistortion::setup(ofFbo* buf){
	buffer = buf;
	mDis.setup(buf);
	bMot.setup(50);

	setThinning(false);
	setThinDepth(2);
}

void ofxGravDistortion::update(bool mouseFollow){

	setRadius(1.0);
	if (mouseFollow){
		
		mDis.clearPoint();
		mDis.addPoint(ofVec2f(ofGetMouseX(),ofGetMouseY()));

		setDirection(sin(ofGetElapsedTimef()*3.0)*0.98);
		mDis.update();

	}

}

void ofxGravDistortion::setForce(int frc){
	mDis.setForce(frc);
}

void ofxGravDistortion::setRadius(float radius){
	mDis.setRadius(radius);
}

void ofxGravDistortion::addPoint(ofVec2f pt){
	mDis.addPoint(pt);
}

void ofxGravDistortion::clearPoint(){
	mDis.clearPoint();
}

void ofxGravDistortion::setThinning(bool thin){
	mDis.setThinning(thin);
}

void ofxGravDistortion::setThinDepth(int num){
	mDis.setThinDepth(num);
}

void ofxGravDistortion::setDirection(float dir){
	mDis.setDirection(dir);
}
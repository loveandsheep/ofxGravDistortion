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
	setDirection(1.0);

	meshDis.setup(buf);

	enableMeshDist = true;
}

void ofxGravDistortion::update(bool mouseFollow){

	if (mouseFollow){
		setRadius(1.0);

		clearPoint();
		addPoint(ofVec2f(ofGetMouseX(),ofGetMouseY()),
				 sin(ofGetElapsedTimef()/1.4)*200.0+200.0,
				 sin(ofGetElapsedTimef())*1.0+1.0, false);

		addPoint(ofVec2f(ofGetWidth()  - ofGetMouseX(),
						 ofGetHeight() - ofGetMouseY()),
				 sin(ofGetElapsedTimef()/1.4)*200.0+200.0,
				 sin(ofGetElapsedTimef())*1.0+1.0, true);
	}

	if (enableMeshDist){
		meshDis.update();
	}else{
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
	if (enableMeshDist){
		meshDis.clearPoint();
	}else{
		mDis.clearPoint();
	}
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

void ofxGravDistortion::addPoint(ofVec2f pt, float rad, float force,bool invert){
	if (enableMeshDist){
		meshDis.addPoint(pt, rad, force, invert);
	}else{
		mDis.addPoint(pt, rad, force,invert);
	}
}
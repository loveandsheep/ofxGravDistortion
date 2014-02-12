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
}

void ofxGravDistortion::update(){

	bMot.setAttract(ofVec2f(ofGetMouseX(),ofGetMouseY()));

	bMot.update();

	mDis.clearPoint();
	for (int i = 0;i < bMot.Pts.size();i++){
		mDis.addPoint(bMot.Pts[i]);
	}
	
	mDis.update();
}

void ofxGravDistortion::setForce(int frc){
	mDis.setForce(frc);
}

void ofxGravDistortion::setRadius(float radius){
	mDis.setRadius(radius);
}
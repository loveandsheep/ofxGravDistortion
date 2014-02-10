//
//  boidMotioner.cpp
//  boidDistort
//
//  Created by Ovis aries on 2014/02/04.
//
//

#include "boidMotioner.h"

void boidMotioner::setup(int numPts){
	for (int i = 0;i < numPts;i++){
		Pts.push_back(ofVec2f(ofRandomf()*100.0,
							  ofRandomf()*100.0));
		Accs.push_back(ofVec2f(0.0,0.0));
	}
	attract.set(0.0, 0.0);
	seed = ofRandomuf();
}

void boidMotioner::update(){
	for (int i = 0;i < Pts.size();i++){
		ofVec2f dst = attract - Pts[i];

		/*万有引力*/
		Accs[i] += (dst.normalized() * 1000000.0 * (seed*0.0+0.5) / dst.lengthSquared()).limit(0.4);
		Accs[i].limit(20.0);
		Pts[i] += Accs[i];

		/*反比例*/
//		Pts[i] += (attract - Pts[i])/10.0*(seed*0.7+0.3);
	}
}

void boidMotioner::draw(){
	ofSetColor(255, 255, 0);
	for (int i = 0;i < Pts.size();i++){
//		ofCircle(Pts[i], 5);
	}
	ofSetColor(255);
}

void boidMotioner::setAttract(ofVec2f pos){
	attract = pos;
}
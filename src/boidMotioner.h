//
//  boidMotioner.h
//  boidDistort
//
//  Created by Ovis aries on 2014/02/04.
//
//

#ifndef __boidDistort__boidMotioner__
#define __boidDistort__boidMotioner__

#include "ofMain.h"

class boidMotioner{
public:
	void setup(int numPts);
	void update();
	void draw();

	void setAttract(ofVec2f pos);



	ofVec2f			attract;
	vector<ofVec2f> Pts;
	vector<ofVec2f> Accs;
	float			seed;
};

#endif /* defined(__boidDistort__boidMotioner__) */

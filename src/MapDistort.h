//
//  MapDistort.h
//  boidDistort
//
//  Created by Ovis aries on 2014/02/03.
//
//

#ifndef __boidDistort__MapDistort__
#define __boidDistort__MapDistort__

#include "ofMain.h"

class mapDistort{
public:

	void setup(ofFbo* buf);
	void update();

	void addPoint(ofPoint pt);
	void clearPoint();

	void drawMap(int x,int y,int w,int h);
	void setForce(int frc);
	void setRadius(float rad);
private:

	ofFbo*		buffer;
	ofFbo		ShadingBuffer;
	ofFbo		distortionMap;

	ofFbo		Distcircle;

	ofVec2f		buffer_size;

	ofShader	distShader;

	vector<ofPoint> pts;

	int force;
	float radius;

};

#endif /* defined(__boidDistort__MapDistort__) */

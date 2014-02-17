//
//  MeshDistort.h
//  boidDistort
//
//  Created by Ovis aries on 2014/02/16.
//
//

#ifndef __boidDistort__MeshDistort__
#define __boidDistort__MeshDistort__

#include "ofMain.h"

struct gravPoint{
	ofVec2f pos;
	float force;
	float radius;
	bool direction;
};

class MeshDistort{
public:
	void setup(ofFbo* buffer);
	void update();
	void drawTest();

	void clearPoint();
	void addPoint(ofVec2f pt,float rad,float force,bool invert);

	vector<ofVec3f> pts;
	vector<ofVec3f> mov;
	vector<ofVec2f> tex;
	vector<ofIndexType> ids;

	vector<gravPoint> gravPts;

protected:
	ofVbo vbo;
	ofFbo* buf;
	ofFbo backBuffer;

	static const int slice = 4;
};

#endif /* defined(__boidDistort__MeshDistort__) */

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
#define MAP_RESO 512.0

class mapDistort{
public:

	void setup(ofFbo* buf);
	void update();

	void addPoint(ofPoint pt);
	void addPoint(ofPoint pt,float radius_,float force_,bool invert_);

	void clearPoint();

	void drawMap(int x,int y,int w,int h);
	void setForce(int frc);
	void setRadius(float rad);

	void setThinning(bool isThin);
	void setThinDepth(int num);

	void setDirection(float direction_);
private:

	void genDistMap(bool usePng);

	ofFbo*		buffer;
	ofFbo		ShadingBuffer;
	ofFbo		distortionMap;

	ofFbo		Distcircle;
	ofFbo		DistcircleInv;

	ofVec2f		buffer_size;

	ofShader	distShader;
	ofShader	thinShader;

	vector<ofPoint> pts;
	vector<float> rads;
	vector<float> forces;
	vector<bool> isInvert;

	int force;
	float radius;
	float direction;//1.0f ~ -1.0f

	bool thinning;
	int thinCount;
};

#endif /* defined(__boidDistort__MapDistort__) */

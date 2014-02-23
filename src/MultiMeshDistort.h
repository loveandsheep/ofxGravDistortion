//
//  MultiMeshDistort.h
//  boidDistort
//
//  Created by Ovis aries on 2014/02/21.
//
//

#ifndef __boidDistort__MultiMeshDistort__
#define __boidDistort__MultiMeshDistort__

#include "ofMain.h"
#include "MeshDistort.h"
//struct gravPoint{
//	ofVec2f pos;
//	float force;
//	float radius;
//	bool direction;
//};

class MultiMeshDistort{
public:
	void setup();
	void update(bool mouseFollow = true);

	/*---　重力場を追加します　---*/
	void addPoint(ofVec2f pt,float rad,float force,bool invert);

	/*---　重力場を初期化します　---*/
	void clearPoint();

	/*---　任意の座標で歪みを取得します　---*/
	ofVec2f getPoint(ofVec2f pt);

private:
	vector<gravPoint> gravPts;
};

#endif /* defined(__boidDistort__MultiMeshDistort__) */

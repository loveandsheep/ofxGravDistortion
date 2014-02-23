//
//  MultiMeshDistort.cpp
//  boidDistort
//
//  Created by Ovis aries on 2014/02/21.
//
//

#include "MultiMeshDistort.h"

void MultiMeshDistort::setup(){
	clearPoint();
}

void MultiMeshDistort::update(bool mouseFollow){
	if (mouseFollow){
		clearPoint();
		addPoint(ofVec2f(ofGetMouseX(),ofGetMouseY()),
				 200.0,
				 sin(ofGetElapsedTimef())*50.0+50.0, false);

		addPoint(ofVec2f(ofGetWidth()  - ofGetMouseX(),
						 ofGetHeight() - ofGetMouseY()),
				 200.0,
				 sin(ofGetElapsedTimef())*50.0+50.0, true);
	}
}


ofVec2f MultiMeshDistort::getPoint(ofVec2f pt){
	ofVec2f mov = pt;

	for (int j = 0;j < gravPts.size(); j++){

		//適用する距離を制限
		if (pt.distanceSquared(gravPts[j].pos) < pow(gravPts[j].radius, 2.0f)){

			//重力との差分ベクトル
			ofVec2f v  = pt - gravPts[j].pos;
			ofVec2f va = pt - gravPts[j].pos;
			ofVec2f vc;

			//差分の単位ベクトル
			ofVec2f vn = va.normalized();
			ofVec2f vb,vo;

			//歪曲を適用
			vb = gravPts[j].force * vn * cos((va.length() / gravPts[j].radius) * HALF_PI);

			vo = va + vb;

			if (gravPts[j].direction){
				vo *= -1.0;
				v  *= -1.0;

				ofVec2f vv = v - vo;
				vv.limit(v.length());
				mov -= vv;
			}else{
				mov = vo + gravPts[j].pos;
			}
		}
	}

	return mov;
}

void MultiMeshDistort::clearPoint(){
	gravPts.clear();
}

void MultiMeshDistort::addPoint(ofVec2f pt, float rad, float force, bool invert){

	gravPoint p;
	p.pos = pt;
	p.force = force * 1.0;
	p.radius = rad;
	p.direction = invert;

	gravPts.push_back(p);
}
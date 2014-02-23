//
//  MeshDistort.cpp
//  boidDistort
//
//  Created by Ovis aries on 2014/02/16.
//
//

#include "MeshDistort.h"

void MeshDistort::setup(ofFbo* buffer){
	buf = buffer;

	for (int j = 0;j < buffer->getHeight()+slice;j+=slice){
		for (int i = 0;i < buffer->getWidth()+slice;i+=slice){
			pts.push_back(ofVec2f(i,j));
			mov.push_back(ofVec2f(i,j));
			tex.push_back(ofVec2f(i,j));
		}
	}

	int w_count = buffer->getWidth()/slice+1;
	int h_count = buffer->getHeight()/slice+1;

	int stp = 16;
	for (int j = 0;j < h_count-stp;j+=stp){
		for (int i = 0;i < w_count-stp;i++){
			ids.push_back(ofIndexType( j    * w_count + i));
			ids.push_back(ofIndexType( j    * w_count + i+1));

//			ids.push_back(ofIndexType( j    * w_count + i));
//			ids.push_back(ofIndexType( j    * w_count + i + 1));
//			ids.push_back(ofIndexType((j+1) * w_count + i));
//
//			ids.push_back(ofIndexType((j+1) * w_count + i));
//			ids.push_back(ofIndexType( j    * w_count + i + 1));
//			ids.push_back(ofIndexType((j+1) * w_count + i + 1));

		}
	}

	for (int j = 0;j < h_count-stp;j++){
		for (int i = 0;i < w_count-stp;i+=stp){
			ids.push_back(ofIndexType((j+1) * w_count + i));
			ids.push_back(ofIndexType((j    ) * w_count + i));
		}
	}

	vbo.setVertexData	(&mov[0], pts.size(), GL_DYNAMIC_DRAW);
	vbo.setTexCoordData	(&tex[0], pts.size(), GL_DYNAMIC_DRAW);
	vbo.setIndexData	(&ids[0], ids.size(), GL_DYNAMIC_DRAW);

	backBuffer.allocate(buf->getWidth(), buf->getHeight());
}

void MeshDistort::update(){
	for (int i = 0; i < pts.size(); i++) {
		mov[i] = pts[i];
	}
	for (int i = 0; i < pts.size(); i++) {

		for (int j = 0; j < gravPts.size(); j++) {

			//歪める
			if (pts[i].distanceSquared(gravPts[j].pos) <
				pow(gravPts[j].radius,2.0f)){
				ofVec2f v   = pts[i] - gravPts[j].pos;
				ofVec2f va  = pts[i] - gravPts[j].pos;
				if (va.length() > 0.00001){
					ofVec2f vn = va.normalized();
					ofVec2f vb,vo;

					if (va.length() <= cbrt(2.0*pow(gravPts[j].radius, 2.0f)*gravPts[j].force)){
						va = vn * cbrt(2.0*pow(gravPts[j].radius, 2.0f)*gravPts[j].force);
					}

					vb = gravPts[j].force * vn * pow(gravPts[j].radius,2.0f) / va.lengthSquared();
					vo = va + vb;

					if (gravPts[j].direction)
					{
						vo *= -1.0;
						v  *= -1.0;

						ofVec2f vv = v - vo;
						vv.limit(v.length());
						mov[i] -= vv;
					}else{

						mov[i] = mov[i] - v + vo;

					}
				}
			}

		}

	}
	vbo.updateVertexData(&mov[0], mov.size());

	backBuffer.begin();

	ofDisableAntiAliasing();
	buf->getTextureReference().bind();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	vbo.drawElements(GL_TRIANGLES, ids.size());
	buf->getTextureReference().unbind();
	ofEnableAntiAliasing();

	ofSetCircleResolution(40);
	for (int i = 0;i < gravPts.size();i++){
		if (!gravPts[i].direction){
			ofFill();
//			ofSetColor(0, 0, 0);
//			ofCircle(gravPts[i].pos,
//					 cbrt(2.0*pow(gravPts[i].radius, 2.0f)*gravPts[i].force) +
//					 gravPts[i].force * pow(gravPts[i].radius,2.0f) / pow(cbrt(2.0*pow(gravPts[i].radius, 2.0f)*gravPts[i].force),2.0));
//			ofSetColor(255);
//			ofNoFill();
//			ofCircle(gravPts[i].pos,
//					 cbrt(2.0*pow(gravPts[i].radius, 2.0f)*gravPts[i].force) +
//					 gravPts[i].force * pow(gravPts[i].radius,2.0f) / pow(cbrt(2.0*pow(gravPts[i].radius, 2.0f)*gravPts[i].force),2.0));
			ofFill();
		}
	}
	backBuffer.end();

	buf->begin();
	ofClear(0, 0, 0);
	backBuffer.draw(0, 0);
	buf->end();
}

void MeshDistort::drawTest(){
	ofDisableAntiAliasing();
	vbo.drawElements(GL_LINES, ids.size());
	ofEnableAntiAliasing();
}

void MeshDistort::clearPoint(){
	gravPts.clear();
}

void MeshDistort::addPoint(ofVec2f pt, float rad, float force, bool invert){

	gravPoint p;
	p.pos = pt;
	p.force = force * 1.0;
	p.radius = rad;
	p.direction = invert;

	gravPts.push_back(p);
}
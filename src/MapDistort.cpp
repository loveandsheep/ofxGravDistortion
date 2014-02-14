//
//  MapDistort.cpp
//  boidDistort
//
//  Created by Ovis aries on 2014/02/03.
//
//

#include "MapDistort.h"

void mapDistort::setup(ofFbo *buf){
	buffer = buf;
	force = 255;
	radius = 1.0;

	buffer_size.set(buf->getWidth(), buf->getHeight());
	ShadingBuffer.allocate(buffer_size.x, buffer_size.y);
	distortionMap.allocate(buffer_size.x, buffer_size.y);

	distShader.load("","shader/convergence.frag");
	thinShader.load("","shader/thinning.frag");


	/*歪みマップ用のサークル*/
	Distcircle.allocate		(MAP_RESO, MAP_RESO);
	DistcircleInv.allocate	(MAP_RESO, MAP_RESO);
	genDistMap(true);


//	ofPixels pix;
//	pix.allocate(512, 512, 4);
//	Distcircle.readToPixels(pix);
//	ofSaveImage(pix, "map.png");
//
//	ofPixels pixI;
//	pixI.allocate(512, 512, 4);
//	DistcircleInv.readToPixels(pixI);
//	ofSaveImage(pixI, "map_inv.png");
}

void mapDistort::update(){

	distortionMap.begin();
	ofClear(127, 127, 0,255);

	glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE);

	for (int i = 0;i < pts.size();i++){
		ofSetColor(255,forces[i]);
		int scl = MAP_RESO*rads[i];

		if (isInvert[i])	DistcircleInv.draw(pts[i].x-scl/2,pts[i].y-scl/2,scl,scl);
		else				Distcircle.draw(pts[i].x-scl/2,pts[i].y-scl/2,scl,scl);
	}


	distortionMap.end();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);

	/*ディストーションシェーディング処理*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	distShader.begin();
	distShader.setUniformTexture("dMap" , distortionMap,1);
	distShader.setUniformTexture("image", *buffer, 0);
	distShader.setUniform1f		("direction", 1.0);
	distShader.setUniform1f		("rand"	, ofGetMouseX()/(float)ofGetWidth());
	distShader.setUniform1f		("radius", 255);

	ShadingBuffer.begin();
	ofDisableAntiAliasing();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	buffer->draw(0, 0, buffer_size.x, buffer_size.y);
	ShadingBuffer.end();

	distShader.end();


	/*元のバッファに還元*/

	int num = MAX(0,thinCount-1)*2+1;//奇数
	if (!thinning) num = 1;

	for (int i = 0;i < num;i++)
	{
		if (i % 2 == 0) buffer->begin();
		else			ShadingBuffer.begin();

		ofClear(0.0, 0.0, 0.0, 255.0);
//		if (thinning) thinShader.begin();
//		thinShader.setUniformTexture("image", ShadingBuffer, 0);
//		thinShader.setUniform1f("rand", ofRandom(1.0));

		if (i % 2 == 0) ShadingBuffer.draw(0, 0,buffer_size.x,buffer_size.y);
		else			buffer->draw(0, 0, buffer_size.x, buffer_size.y);

//		if (thinning) thinShader.end();
		if (i % 2 == 0) buffer->end();
		else			ShadingBuffer.end();

	}

}

void mapDistort::addPoint(ofPoint pt){
	ofPoint p = pt;
	float rd = radius;
	float fc = force;
	bool iv = (direction < 0.0);

	pts		.push_back(p);
	rads	.push_back(rd);
	forces	.push_back(fc);
	isInvert.push_back(iv);

}

void mapDistort::addPoint(ofPoint pt,float radius_,float force_,bool invert_){
	ofPoint p = pt;
	float rd = radius_;
	float fc = force_;
	bool iv = invert_;

	pts		.push_back(p);
	rads	.push_back(rd);
	forces	.push_back(fc);
	isInvert.push_back(iv);

}

void mapDistort::clearPoint(){
	pts		.clear();
	rads	.clear();
	forces	.clear();
	isInvert.clear();
}

void mapDistort::drawMap(int x,int y,int w,int h){
	distortionMap.draw(x,y,w,h);
}

void mapDistort::setForce(int frc){
	force = frc;
}

void mapDistort::setRadius(float rad){
	radius = rad;
}

void mapDistort::setThinning(bool isThin){
	thinning = isThin;
}

void mapDistort::setThinDepth(int num){
	thinCount = num;
}

void mapDistort::setDirection(float direction_){
	direction = direction_;
}

void mapDistort::genDistMap(bool usePng){

	/*膨張マップ*/
	Distcircle.begin();
	ofClear(127, 127, 0,0);

	if (usePng){

		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofClear(127, 127, 0,0);
		ofImage im;
		ofSetColor(255);
		im.loadImage("image/map.png");
		im.draw(0,0, MAP_RESO, MAP_RESO);

	}else{

		glBegin(GL_POINTS);
		for (int i = -MAP_RESO/2;i < MAP_RESO/2;i++){
			for (int j = -MAP_RESO/2;j < MAP_RESO/2;j++){
				ofPoint dst = ofPoint(-i,-j);

				dst *= 128 / ofPoint(-i,-j).length();
//				bool flg = false;
//				if (abs(dst.x) > abs(i)){
//					dst.x = i;
//					flg = true;
//				}
//				if (abs(dst.y) > abs(j)){
//					dst.y = j;
//					flg = true;
//				}

				ofSetColor(dst.x * (512.0 / MAP_RESO) + 128,
						   dst.y * (512.0 / MAP_RESO) + 128, 0,
						   255 - (ofPoint(-i,-j).length()));

				glVertex2f(i+MAP_RESO/2, j+MAP_RESO/2);
			}
		}
		glEnd();

	}

	Distcircle.end();

	/*縮小マップ*/
	DistcircleInv.begin();
	ofClear(127, 127, 0, 0);

	if (usePng){

		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofClear(127, 127, 0,0);
		ofImage im;
		ofSetColor(255);
		im.loadImage("image/map_inv.png");
		im.draw(0,0, MAP_RESO, MAP_RESO);

	}else{

		glBegin(GL_POINTS);
		for (int i = -MAP_RESO/2;i < MAP_RESO/2;i++){
			for (int j = -MAP_RESO/2;j < MAP_RESO/2;j++){
				ofPoint dst = ofPoint(-i,-j);

				dst *= 128 / ofPoint(-i,-j).length();

				ofSetColor(-dst.x * (512.0 / MAP_RESO) + 128,
						   -dst.y * (512.0 / MAP_RESO) + 128, 0,
						   255 - ofPoint(-i,-j).length());

				glVertex2f(i+MAP_RESO/2, j+MAP_RESO/2);
			}
		}
		glEnd();

	}

	DistcircleInv.end();
}
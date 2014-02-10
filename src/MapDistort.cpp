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

	buffer_size.set(buf->getWidth(), buf->getHeight());
	ShadingBuffer.allocate(buffer_size.x, buffer_size.y);
	distortionMap.allocate(buffer_size.x, buffer_size.y);

	distShader.load("","shader/convergence.frag");

	/*歪みマップ用のサークル*/
	Distcircle.allocate(512, 512);
	Distcircle.begin();
	ofClear(127, 127, 0,0);

	glBegin(GL_POINTS);
	for (int i = -256;i < 256;i++){
		for (int j = -256;j < 256;j++){
			ofPoint dst = ofPoint(-i,-j);

			dst *= MIN(1.0,128.0 / ofPoint(-i,-j).length());

			ofSetColor(dst.x+128, dst.y+128, 0,
					   255.0 - ofPoint(-i,-j).length());
			glVertex2f(i+256, j+256);
		}
	}
	glEnd();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofClear(127, 127, 0,0);
	ofImage im;
	ofSetColor(255);
	im.loadImage("image/map.png");
	im.draw(0,0, 512, 512);

	Distcircle.end();

//	ofPixels pix;
//	pix.allocate(512, 512, 4);
//	Distcircle.readToPixels(pix);
//	ofImage img;
//	img.setFromPixels(pix);
//	img.saveImage("map.png");
}

void mapDistort::update(){

	distortionMap.begin();
	ofClear(127, 127, 0,255);

	glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE);

	ofSetColor(255,force);
	int scl = 512;
	for (int i = 0;i < pts.size();i++){
		Distcircle.draw(pts[i].x-scl/2,pts[i].y-scl/2,scl,scl);
	}
	
	distortionMap.end();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);


	/*シェーディング処理*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	distShader.begin();
	distShader.setUniformTexture("dMap" , distortionMap,1);
	distShader.setUniformTexture("image", *buffer, 0);
	distShader.setUniform1f		("rand"	, ofGetMouseX()/(float)ofGetWidth());

	ShadingBuffer.begin();
	ofDisableAntiAliasing();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	buffer->draw(0, 0, buffer_size.x, buffer_size.y);
	ShadingBuffer.end();

	distShader.end();


	/*元のバッファに還元*/
	buffer->begin();
	ofClear(0.0, 0.0, 0.0, 255.0);
	ShadingBuffer.draw(0, 0,buffer_size.x,buffer_size.y);
	buffer->end();

}

void mapDistort::addPoint(ofPoint pt){
	ofPoint p = pt;
	pts.push_back(p);
}

void mapDistort::clearPoint(){
	pts.clear();
}

void mapDistort::drawMap(int x,int y,int w,int h){
	distortionMap.draw(x,y,w,h);
}

void mapDistort::setForce(int frc){
	force = frc;
}
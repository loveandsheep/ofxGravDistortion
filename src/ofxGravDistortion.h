//
//  distortManager.h
//  boidDistort
//
//  Created by Ovis aries on 2014/02/05.
//
//

#ifndef __boidDistort__distortManager__
#define __boidDistort__distortManager__

#include "ofMain.h"
#include "MapDistort.h"
#include "boidMotioner.h"

class ofxGravDistortion{
public:

	/*初期化処理。Fboのアロケーションを終えた後に、ポインタを渡す形で呼び出してください。*/
	void setup(ofFbo* buf);

	/*更新処理。Fboの描画処理を終えた後に呼び出してください*/
	void update();

	/*歪みのかかり具合を調整します。0-255の範囲で設定できます*/
	void setForce(int frc);

	/*歪みの半径を設定します1.0fがデフォルトのサイズ*/
	void setRadius(float radius);

private:
	ofFbo* buffer;
	mapDistort mDis;
	boidMotioner bMot;

};


#endif /* defined(__boidDistort__distortManager__) */

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
	void update(bool mouseFollow = true);


	/*===================== 歪み処理関係 =======================*/
	/*歪みのかかり具合を調整します。0-255の範囲で設定できます*/
	void setForce(int frc);

	/*歪みの半径を設定します1.0fがデフォルトのサイズ*/
	void setRadius(float radius);


	/*====================== 歪み座標関係 =========================*/
	/*新規にポイントを追加します*/
	void addPoint(ofVec2f pt);

	/*ポイントをリセットします*/
	void clearPoint();

	/*====================== 細線化関係 =========================*/
	/*細線化処理を実行するかどうか決めます*/
	void setThinning(bool thin);

	/*細線化の回数を決めます（処理量・効果的に0~5くらいの間を指定してください。1か2が効果的だと思います。太い時はあまりかけないほうが吉？）*/
	void setThinDepth(int num);


private:
	ofFbo* buffer;
	mapDistort mDis;
	boidMotioner bMot;

};


#endif /* defined(__boidDistort__distortManager__) */

uniform sampler2DRect image;
uniform sampler2DRect dMap;
uniform float rand;
vec4 table[9];

bool check1();
bool check2();
bool common_Check();

void main (void)
{
    vec2 texCoord = gl_TexCoord[0].st;

	vec4 col = texture2DRect(image,texCoord);

	table[0] = texture2DRect(image,texCoord+vec2(-1,-1));
	table[1] = texture2DRect(image,texCoord+vec2( 0,-1));
	table[2] = texture2DRect(image,texCoord+vec2( 1,-1));
	table[3] = texture2DRect(image,texCoord+vec2(-1, 0));
	table[4] = texture2DRect(image,texCoord+vec2( 0, 0));
	table[5] = texture2DRect(image,texCoord+vec2( 1, 0));
	table[6] = texture2DRect(image,texCoord+vec2(-1, 1));
	table[7] = texture2DRect(image,texCoord+vec2( 0, 1));
	table[8] = texture2DRect(image,texCoord+vec2( 1, 1));

	bool endFlg = true;

	if (check1()){
		col.rgba = vec4(0.0,0.0,0.0,1.0);
		if (check2()){
			col.rgba = vec4(0.0,0.0,0.0,1.0);
		}else{
			endFlg = false;
		}
	}else{
		endFlg = false;
	}




    gl_FragColor.rgba = col.rgba;
}

bool check1(){
	if (table[4].r > 0.5){

		/*除去しないパターンの絞込*/
		if (table[2].r < 0.5 && table[5].r > 0.5 &&
			table[7].r > 0.5 && table[8].r < 0.5) return false;//1_1

		if (table[0].r < 0.5 && table[1].r > 0.5 &&
			table[3].r > 0.5 && table[5].r < 0.5) return false;//1_2

		if (common_Check()){
			return false;
		}else{

			/*除去するパターンに該当*/
			if (table[1].r < 0.5 || table[5].r < 0.5) return true;

		}

	}

	return false;
}

bool check2(){
	if (table[4].r > 0.5){

		/*除去しないパターンの絞込*/
		if (table[0].r < 0.5 && table[1].r > 0.5 &&
			table[3].r > 0.5 && table[7].r < 0.5) return false;//1_1

		if (table[3].r < 0.5 && table[5].r > 0.5 &&
			table[7].r > 0.5 && table[8].r < 0.5) return false;//1_2

		if (common_Check()){
			return false;
		}else{

			/*除去するパターンに該当*/
			if (table[6].r < 0.5 || table[3].r < 0.5) return true;

		}

	}

	return false;
}

bool common_Check(){
	if (table[4].r > 0.5){
		if (table[3].r < 0.5 && table[5].r < 0.5 &&
			table[7].r > 0.5) return true;//1

		if (table[1].r < 0.5 && table[3].r > 0.5 &&
			table[7].r < 0.5) return true;//2

		if (table[1].r > 0.5 && table[3].r < 0.5 &&
			table[5].r < 0.5) return true;//3

		if (table[1].r < 0.5 && table[5].r > 0.5 &&
			table[7].r < 0.5) return true;//4

		if (table[3].r < 0.5 && table[6].r > 0.5 &&
			table[7].r < 0.5) return true;//5

		if (table[0].r > 0.5 && table[1].r < 0.5 &&
			table[3].r < 0.5) return true;//6

		if (table[1].r < 0.5 && table[2].r > 0.5 &&
			table[5].r < 0.5) return true;//7

		if (table[5].r < 0.5 && table[7].r < 0.5 &&
			table[8].r > 0.5) return true;//8

		if (table[0].r < 0.5 && table[1].r > 0.5 &&
			table[2].r < 0.5 && table[3].r > 0.5 &&
			table[5].r > 0.5 && table[6].r < 0.5 &&
			table[8].r < 0.5) return true;//9

		if (table[0].r < 0.5 && table[1].r > 0.5 &&
			table[2].r < 0.5 && table[5].r > 0.5 &&
			table[6].r < 0.5 && table[7].r > 0.5 &&
			table[8].r < 0.5) return true;//10

		if (table[0].r < 0.5 && table[2].r < 0.5 &&
			table[3].r > 0.5 && table[5].r > 0.5 &&
			table[6].r < 0.5 && table[7].r > 0.5 &&
			table[8].r < 0.5) return true;//11

		if (table[0].r < 0.5 && table[1].r > 0.5 &&
			table[2].r < 0.5 && table[3].r > 0.5 &&
			table[6].r < 0.5 && table[7].r > 0.5 &&
			table[8].r < 0.5) return true;//12

		return false;
	}
	return false;
}
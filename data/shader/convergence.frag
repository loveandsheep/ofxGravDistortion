uniform sampler2DRect image;
uniform sampler2DRect dMap;
uniform float rand;

void main (void)
{
    vec2 texCoord = gl_TexCoord[0].st;
	vec2 dPos;

	dPos.x = texCoord.x + (texture2DRect(dMap,texCoord).r - 0.5)*256.0;
	dPos.y = texCoord.y + (texture2DRect(dMap,texCoord).g - 0.5)*256.0;

    vec4 col = texture2DRect(image,dPos);

//	if (abs(texture2DRect(dMap,texCoord).r - 0.5) > 0.01 &&
//		abs(texture2DRect(dMap,texCoord).g - 0.5) > 0.01){
//		col.rgb = vec3(0.0,0.0,0.0);
//	}
	if (col.r > 0.5 &&
		col.g > 0.5 &&
		col.b > 0.5){
		col.rgb = vec3(1.0,1.0,1.0);
	}

    gl_FragColor.rgba = col.rgba;
}
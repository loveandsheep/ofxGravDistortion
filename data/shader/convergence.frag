uniform sampler2DRect image;
uniform sampler2DRect dMap;
uniform float rand;
uniform float direction;

void main (void)
{
    vec2 texCoord = gl_TexCoord[0].st;
	vec2 dPos;

	dPos.x = texCoord.x + (texture2DRect(dMap,texCoord).r - 0.5)*255.0*direction;
	dPos.y = texCoord.y + (texture2DRect(dMap,texCoord).g - 0.5)*255.0*direction;

    vec4 col = texture2DRect(image,dPos);

	if (col.r > 0.5 &&
		col.g > 0.5 &&
		col.b > 0.5){
		col.rgba = vec4(1.0,1.0,1.0,1.0);
	}else{
		col.rgba = vec4(0.0,0.0,0.0,1.0);
	}

    gl_FragColor.rgba = col.rgba;
}
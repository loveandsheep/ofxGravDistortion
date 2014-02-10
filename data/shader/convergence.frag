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

	if ((texture2DRect(dMap,texCoord).r > 0.9)&&
		(texture2DRect(dMap,texCoord).g > 0.9)){
		col.rgb = vec3(0.0,0.0,0.0);
	}

    gl_FragColor.rgba = col.rgba;
}
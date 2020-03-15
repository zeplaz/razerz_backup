#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

		// 坐标

		vec2 p =(gl_FragCoord.xy *2.0 -resolution) / min(resolution.x,resolution.y);



		// 赤セット
		vec3 rColor =vec3(1.0,0.0,0.3);
	        // 青セット
	        vec3 bColor =vec3(0.0,0.2,1.0);
	        // 緑セット
	        vec3 gColor =vec3(0.0,0.9,0.3);

	        // 黄色
	        vec3 yColor =vec3(0.9,0.9,0.3);



		// y軸曲げる
		float x = sin(p.y * 2.0  * 2.0);
	        float bx = cos(p.x * 1.0 +  2.0);
	        float gx = sin(p.x * 0.4 + time * 1.5);
	        float yx = sin(p.y * 2.0 + 3.0);

		float tx = tan(x);
		float txp = pow(x,time);
		float txppxp = txp* pow(time,txp);
		gColor = gColor*txppxp;
		bColor = cos( tan (txppxp)*time)*bColor;
		yColor = cos( tan (txppxp)*time)*bColor;
		rColor= tan(bColor*time+rColor);
	// x軸の設定（yをたす）？
		float y = 0.1 / abs(p.x + x);
	         // x軸の設定（yをたす）？
		float by = 0.1 / abs(p.y + bx);
	        float gy = 0.05 / abs(p.y + gx);
	        float yy = 0.1 / abs(p.x + yx);


		// どうやら 乗算 すると白に色がつく
		vec3 destColor = rColor * y ;

	        vec3 destColor2 = bColor * by inversesqrt(rColor);

	       vec3 destColor3 = gColor * gy *txppxp;

	        vec3 destColor4 = yColor * yy ;

		gl_FragColor =vec4(destColor  +destColor2 + destColor3 + destColor4,1.0);

}

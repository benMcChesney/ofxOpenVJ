
// ported from https://www.shadertoy.com/view/lslGWr
// Added some stars: Thanks to http://glsl.heroku.com/e#6904.0
// Modified for use
#version 120  
#ifdef GL_ES
precision mediump float;
#endif


uniform float time;
uniform vec2 resolution;
uniform float low ; 
uniform float medium ; 
uniform float high ; 
uniform float beat ; 
uniform float tunnelSpeed ; 
uniform float maxBrightness ; 
uniform float lowBrightnessFactor; 
uniform float beatJumpOffset ;

void main( void ) 
{
	vec3 light_color = vec3(1.2,0.8,0.6);
	
	float t = time*20.0;
	vec2 position = ( gl_FragCoord.xy -  resolution.xy*.5 ) / resolution.x;

	// 256 angle steps
	float angle = atan(position.y,position.x)/(2.*3.14159265359);
	angle -= floor(angle);
	float rad = length(position);
	
	float color = 0.0;
	float brightness = maxBrightness+ ( low * lowBrightnessFactor );
	float speed = tunnelSpeed ; 
	
	for (int i = 0; i < 6; i++) {
		float angleRnd = floor(angle*64.)+1.;
		float angleRnd1 = fract(angleRnd*fract(angleRnd*.7235)*45.1);
		float angleRnd2 = fract(angleRnd*fract(angleRnd*.82657)*13.724);
		float t = t*speed  - ( beat * beatJumpOffset) + angleRnd1*30.;
		float radDist = sqrt(angleRnd2+float(i));
		
		float adist = radDist/rad*.1;
		float dist = (t*.1+adist);
		dist = abs(fract(dist)-.5);
		color +=  (1.0 / (dist))*cos(0.7*(sin(t)))*adist/radDist * brightness;
		angle = fract(angle+.61  );
	}
	
	
	gl_FragColor = vec4(color,color,color,1.0)*vec4(light_color,1.0);
}
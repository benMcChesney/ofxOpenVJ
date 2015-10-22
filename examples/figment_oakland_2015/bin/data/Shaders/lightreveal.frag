#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;
uniform float low ; 
uniform float medium ; 
uniform float high ; 
uniform float beat ; 
uniform float beatSin2 ; 
uniform float beatSin4 ; 
uniform float beatSin8 ; 
uniform float intensity ; 
float metaball(vec2 uv,vec2 center,float size)
{
	vec2 d = uv - center;
	return size/length(d);
}
void main( void ) 
{
	float reso = max(resolution.x,resolution.y );
	vec2 center = vec2(0.5 , 0.25);
	vec2 uv = gl_FragCoord.xy / reso;
	float t = time * 0.2; //time * 0.1;
	float Freq = 20.0 ; // +  beatSin4  ; 
	float m = 0.0;
	
	m +=metaball(uv,vec2(0.5 , 0.25 + beatSin8 * ( 0.01 * ( 1.0 - intensity ) ) ) , 0.07 * ( 1.0f + (low * 0.2) ) * ( intensity + 0.05 * sin(time * Freq * 0.5 )));
	
	//uv.x  = uv.x + sin(time * 2.0) * 0.02;
	uv.x  = 0.5 + uv.x * 0.0009 + fract( beat ) / Freq;
	
	m += metaball(uv,center , 0.01 + low * 0.02  );
	
	m = pow(m,2.0 - (low * 0.2 ));
	
	float w = m * intensity ;

	//gl_FragColor = vec4( vec3(1.0,1.8,1.0) * w, 1.0 );
	//gl_FragColor = vec4( vec3(.4,0.6,1.2) * w , 1.0 );
	gl_FragColor = vec4( vec3( beatSin4 * 0.2 + .8 ,beatSin2 * .2 + 0.5 ,0.8 * beatSin8  + .6 ) * w , 1.0 );
}

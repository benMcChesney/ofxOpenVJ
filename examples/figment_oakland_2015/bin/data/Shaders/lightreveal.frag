#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;
uniform float low ; 
uniform float medium ; 
uniform float high ; 
uniform float beat ; 

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
	float t = beat * 0.1; //time * 0.1;
	float Freq = 20.0 ; 
	float m = 0.0;
	
	m +=metaball(uv,vec2(0.5 , 0.25) , 0.07 * (1.0 + 0.05 * sin(time * Freq * 0.5)));
	
	//uv.x  = uv.x + sin(time * 2.0) * 0.02;
	uv.x  = 0.5 + uv.x * 0.0009 + fract(t * Freq) / Freq;
	
	m += metaball(uv,center , 0.02);
	
	m = pow(m,2.0);
	
	float w = m;

	gl_FragColor = vec4( vec3(1.0,1.8,1.0) * w, 1.0 );
	gl_FragColor = vec4( vec3(.4,0.6,1.2) * w , 1.0 );
	gl_FragColor = vec4( vec3(1.3,0.4,1.3) * w , 1.0 );
}

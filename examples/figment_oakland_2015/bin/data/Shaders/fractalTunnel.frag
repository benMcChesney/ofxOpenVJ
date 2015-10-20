
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
#ifdef GL_ES
precision highp float;
#endif

uniform vec2 mouse;
varying vec3 positionSurface;
varying vec3 positionSize;

vec3   iResolution = vec3(resolution, 1.0);
//float  iGlobalTime = time-60.;
//vec4   iMouse = vec4(mouse, 0.0, 1.0);
//uniform sampler2D iChannel0,iChannel1;

const int MAX_ITER = 30; // 

vec2 rotate(in vec2 v, in float a) {
	return vec2(cos(a)*v.x + sin(a)*v.y, -sin(a)*v.x + cos(a)*v.y);
}

float torus(in vec3 p, in vec2 t)
{
	vec2 q = abs(vec2(max(abs(p.x), abs(p.z))-t.x, p.y));
	return max(q.x, q.y)-t.y;
}

// These are all equally interesting, but I could only pick one :(
float trap(in vec3 p)
{
	#define var1 abs(max(abs(p.z)-0.1, abs(p.x)-0.1))-0.01
	#define var2 length(max(abs(p.xy) - 0.05, 0.0))
	#define var3 length(p)-0.5
	#define var4 length(max(abs(p) - 0.35, 0.0))
	#define var5 abs(length(p.xz)-0.2)-0.01
	#define var6 abs(min(torus(vec3(p.x, mod(p.y,0.4)-0.2, p.z), vec2(0.1, 0.05)), max(abs(p.z)-0.05, abs(p.x)-0.05)))-0.005
	#define var7 abs(min(torus(p, vec2(0.3, 0.05)), max(abs(p.z)-0.05, abs(p.x)-0.05)))-0.005
	#define var8 min(length(p.xz), min(length(p.yz), length(p.xy))) - 0.05
	
	return  abs(max(abs(p.z)-0.1, abs(p.x)-0.1))-0.01;
	
}

float map(in vec3 p)
{
	float cutout = dot(abs(p.yz),vec2(0.5))-0.035;
	
	vec3 z = abs(1.0-mod(p,2.0));
	z.yz = rotate(z.yz, time*0.05);

	float d = 999.0;
	float s = 1.0;
	for (float i = 0.0; i < 3.0; i++) {
		z.xz = rotate(z.xz, radians(i*10.0+time));
		z.zy = rotate(z.yz, radians((i+1.0)*20.0+time*1.1234));
		z = abs(1.0-mod(z+i/3.0,2.0));
		
		z = z*2.0 - 0.3;
		s *= 0.5;
		d = min(d, trap(z) * s);
	}
	return min(max(d, -cutout), 1.0);
}

vec3 hsv(in float h, in float s, in float v) {
	return mix(vec3(1.0), clamp((abs(fract(h + vec3(3, 2, 1) / 3.0) * 6.0 - 3.0) - 1.0), 0.0 , 1.0), s) * v;
}

vec3 intersect(in vec3 rayOrigin, in vec3 rayDir)
{
	float total_dist = 0.0;
	vec3 p = rayOrigin;
	float d = 1.0;
	float iter = 0.0;
	float mind = 3.14159+sin(time*0.1)*0.2;
	
	for (int i = 0; i < MAX_ITER; i++)
	{		
		if (d < 0.001) continue;
		
		d = map(p);
		p += d*vec3(rayDir.x, rotate(rayDir.yz, sin(mind)));
		mind = min(mind, d);
		total_dist += d;
		iter++;
	}

	vec3 color = vec3(0.0);
	if (d < 0.001) {
		float x = (iter/float(MAX_ITER));
		float y = (d-0.01)/0.01/(float(MAX_ITER));
		float z = (0.01-d)/0.01/float(MAX_ITER);
		if (max(abs(p.y-0.025), abs(p.z)-0.50)< (beat)) { // Road
			float w = smoothstep(mod(p.x*50.0, 4.0), 2.0, 2.02);
			w -= 1.0-smoothstep(mod(p.x*50.0+2.0, 8. * low  ), 2.0, 1.9 - low );
			w = fract(w+0.0001);
			float a = fract(smoothstep(abs(p.z), 0.0025, 0.0026));
			color = vec3((1.0-x-y*2.)*mix(vec3(0.8, 0.1, 0), vec3(0.1), 1.0-(1.0-w)*(1.0-a)));
		} else {
			float q = 1.0-x-y*2.+z;
			color = hsv(q*0.2+0.85, 1.0-q*0.2 , q);
		}
	} else
		color = hsv(d, 1.0, 1.0)*mind*45.0; // Background
	return color;
}

void main()
{	
	float a = pow(10.0,5.0*mouse.x);
	vec3 upDirection = vec3(0, -1, 0);
	vec3 cameraDir = vec3(1,0,0);
	vec3 cameraOrigin = vec3(a*time*0.551, 0, 0);
	
	vec3 u = normalize(cross(upDirection, cameraOrigin));
	vec3 v = normalize(cross(cameraDir, u));
	vec2 screenPos = -1.0 + 2.0 * gl_FragCoord.xy / iResolution.xy;
	screenPos.x *= iResolution.x / iResolution.y;
	vec3 rayDir = normalize(u * screenPos.x + v * screenPos.y + cameraDir*(1.0-length(screenPos)*0.5)) * ( 1.0 + (beat*0.5  )) ;
	
	gl_FragColor = vec4(intersect(cameraOrigin, rayDir), 10.0);
	gl_FragColor = vec4(gl_FragColor.xxx,1.0);
} 
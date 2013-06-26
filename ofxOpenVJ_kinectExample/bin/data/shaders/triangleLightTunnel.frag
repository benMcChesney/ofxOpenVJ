
 
 //Thanks to glsl.heroku.com for the shader inspiration !
 //http://glsl.heroku.com/e#6808.0
 
 


#ifdef GL_ES
precision highp float;
#endif

uniform vec2 resolution;
uniform float time;
uniform float low ;
uniform float mid ;
uniform float high ;

// a raymarching experiment by kabuto
// fork by s1e

const int MAXITER = 44;

vec3 field(vec3 p) {
	p *= 0.1;
	float f = .1;
	for (int i = 0; i < 6; i++) {
		//p = p.yzx;
		p = p.yzx * mat3(.7,.5,0,-.6,0.8,0,0,0,1);
		p += vec3(.3,.5 + sin ( time ) * 0.2 * ( low + .0001 ) ,.7 )*float(i);
		p = abs(fract(p)-.5);
        //Mirroring 
		p *= 2.0 + ( low * 0.2 ) ;
		f *= 2.0 ;
	}
	p *= p ;
	return sqrt(p+p.yzx)/f-0.0001;
}

void main( void ) {
	vec3 dir = normalize(vec3((gl_FragCoord.xy-resolution*.5)/resolution.x,1.0));
	vec3 pos = vec3(0, 0, time/8.0 * ( low + 0.01 ));
	vec3 color = vec3(0);
	float condition = sin(time*3.)*cos(time)*0.5+0.5;
	for (int i = 0; i < MAXITER; i++) {
		vec3 f2 = field(pos);
		float f = min(min(f2.x,f2.y),f2.z);
		
		pos += dir*f;
		if (condition > float(i)/ ( 64.0 + (( mid + 0.01 ) * 64.0 )) || condition < float(i)/64.0 - 0.3) color += float(MAXITER-i)/f2;
	}
	vec3 color3 = vec3(1.-1./(1.+color*(4.0/float(MAXITER*MAXITER*MAXITER))));
	color3 *= color3;
	gl_FragColor = vec4(vec3(color3.r/color3.g*color3.b),0.5);
	//gl_FragColor = vec4(color3, 1.0);
}
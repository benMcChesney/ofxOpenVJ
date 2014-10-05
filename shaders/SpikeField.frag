/* 
 
 Thanks to glsl.heroku.com for the shader inspiration !
 http://glsl.heroku.com/e#2915.0
 
 */
#ifdef GL_ES
precision mediump float;
#endif

uniform float low ;
uniform float mid ;
uniform float high ;
uniform vec2 resolution;
uniform float time;

//another oldie that started with riffing on the clod.-george toledo


float f(vec3 o){
	float a=(cos(o.x)+o.y*2.0 * ( low + 0.01 ) )*.05;
	o=vec3(sin(a)*o.x*sin(a)*o.y,sin(a)*o.x-sin(a)*o.y,o.z+(sin(a)-tan(a)*.5 ));
	return dot(cos(o)*cos(o),vec3(1.5))-1.5;
}

vec3 s(vec3 o,vec3 d){
	float t=0.,a,b;
	for(int i=0;i<150;i++){
		if(f(o+d*t)<.1){
			a=t+1.0;
			b=t;
			for(int i=0; i<1;i++){
				t=((a+b)*.5);
				if(f(o+d*t)<0.)b=t;
				else a=t;
			}
			vec3 e=vec3(1.4,1.0,.0),p=o+d/t,n=-normalize(vec3(f(p+e),f(p+e.yxy),f(p+e.yyx))-vec3((cos(p*1.14)))+1.0 );
			return vec3(mix( ((max(-dot(n,vec3(.2)),-10.) / 10.0*max(-dot(n,vec3(-1.0,-.1,0)),0.)))*(mod(length(p.xy)*.5,0.5)<1.0?vec3(.3,1.2,.5):vec3(.0,.5,1.0)),vec3(.05,.06,.06),vec3(pow(t/20.,1.0))));
		}
		t+=3.8
        ;
	}
	return vec3(1.0,1.0,1.0);
}

void main(){
    
	float t=dot(gl_FragColor.xyz,vec3(1.0,0.0,1.0))*1.0;
	gl_FragColor=vec4(s(vec3(cos(time*.1)*.1,cos(time)*1.0,time),
                        normalize(vec3((2.*gl_FragCoord.xy-vec2(resolution.x,resolution.y))/vec2(resolution.x),1.0))),1);
}
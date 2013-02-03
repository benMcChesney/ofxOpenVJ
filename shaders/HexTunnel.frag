

uniform float low ;
uniform float mid ;
uniform float high ;
uniform float time ;
uniform vec2 resolution;

vec3 rotXY(vec3 p, vec2 rad) {
	vec2 s = sin(rad);
	vec2 c = cos(rad);
	
	mat3 m = mat3(
                  c.y, 0.0, -s.y,
                  -s.x * s.y, c.x, -s.x * c.y,
                  c.x * s.y, s.x, c.x * c.y
                  );
	return m * p;
}

vec2 repeat(vec2 p, float n) {
	vec2 np = p * n;
	vec2 npfrct = fract(np);
	vec2 npreal = np - npfrct;
	np.x += fract(npreal.y * 0.5);
	
	return fract(np) * 2.0 - 1.0;
}

float hexDistance(vec2 ip) {
	const float SQRT3 = 1.732050807568877;
	const vec2 TRIG30 = vec2(0.25, 0.866025403784439); //x:sine, y:cos
	
	vec2 p = abs(ip * vec2(SQRT3 * 0.5, 0.5+sin(time)*0.5));
	float d = dot(p, vec2(-TRIG30.x, TRIG30.y)) - SQRT3 * 0.125;
	
	return (d > 0.0)? min(d, (SQRT3 * 0.5 - p.x)) : min(-d, p.x);
}

float smoothEdge(float edge, float margin, float x) {
	return smoothstep(edge - margin, edge + margin, x);
}

void main(void) {
	const float PI = 3.1415926535;
	vec3 rgb;

	vec2 nsc = (gl_FragCoord.xy - resolution * 0.5) / resolution.yy * 2.0;
	vec3 dir = normalize(vec3(nsc, -2.0));
	//dir = rotXY(dir, vec2((mouse.yx - 0.5) * PI * 0.35));
	dir = rotXY(dir, vec2(( 0.0) * PI * 5.0 ));
  //  dir = rotXY(dir, vec2(( 0.0) * PI * 0.35 * clap ));
	vec2 uv = vec2(atan(dir.y, dir.x) / (PI * 2.0) , dir.z / length(dir.xy));
	
	float t= time*0.25;
	vec2 pos = uv * vec2(1.0, low + 0.1 ) - vec2(t * 0.05, t * 0.5);
	
    float re = pow ( 16.0 , ( 0.9 + mid ) ) ;
	vec2 p = repeat(pos, re )  ;
	
	float d = hexDistance(p);
	float dist = dir.z/length(dir.xy);
	d/=-dist;
	float fade = 1.0 / pow(1.0 / length(dir.xy) * 0.3, 1.0);
	fade = clamp(fade, 0.0, 1.0);
	rgb  = mix(vec3(0.15)*fade, vec3(0.0), smoothEdge(0.03, 0.01, d));
	rgb += mix(vec3(1.0, 0.6 + low , pow( 3.0 , high ) )*fade, vec3(0.0), smoothEdge(0.03, 0.5, d)) * 0.5;
	rgb += mix(vec3(0.1, cos ( time ) * 0.7 , 0.0)*fade, vec3(0.0), smoothEdge(0.03, 1.0, d)) * ( 0.15 + pow ( 1.0 , low )) ;
	
	rgb = mix(rgb, vec3(0.2 + low * 0.25 + sin( time ) * 0.6 ,0.6 + sin( time ) * .2 ,0.99), tan( time ) * dir.y );
	gl_FragData[0] = vec4(rgb, 1.0);
	
}

/*
void main (void)
{
	//sample both textures
    vec2 texPos = gl_TexCoord[0].st ; 
    texPos.x += tan( time ) * globalSound * soundMultiplier ; 
    texPos.y += cos( time * cos ( texPos.x ))  * globalSound * soundMultiplier ; 
	vec4 source = texture2DRect(Tex0, texPos );

	//use the color from the image, but use the r channel of the mask as the alpha channel of our output
	gl_FragData[0] = vec4( source.r + rOffset , source.g + gOffset , source.b + bOffset , source.a ) ; //vec4(image.rgb,composite.r);  

}*/
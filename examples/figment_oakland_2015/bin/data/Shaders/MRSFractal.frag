
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

void main( void ) {

    vec2 uv = .5 * gl_FragCoord.xy / resolution.y;
    float t = time*.03, k = cos(t), l = sin(t);        
    
    float s = .5;
	float scale = beat * 0.005 ; 
    for(int i=0; i<64   ; ++i) {
        uv  = abs(uv) - s;    // Mirror
        uv *= mat2(k,-l,l,k); // Rotate
        s  *= (.95156 + scale);         // Scale
    }
    
    float x = .5 + cos( (6.28318 + low * 0.1 )*(40.*length(uv)));
    gl_FragColor = vec4(vec3(x),1);
}
#version 120  


uniform float time;
uniform vec2 resolution;
uniform float low ; 
uniform float medium ; 
uniform float high ; 
uniform float beat ; 
uniform float minFractalTime ; 
uniform float maxFractalTime ; 
uniform float beatSin2 ; 
uniform float beatSin4 ; 
uniform float beatSin8 ; 
uniform float complexity ; 

void main(void)
{
	//this is a default vertex shader all it does is this...
   // vec3 p = ftransform() ; 
   // p.x = sin( time ) * 50.0 + p.x ;
	gl_Position = ftransform();
	//.. and passes the multi texture coordinates along to the fragment shader
	gl_TexCoord[0] = gl_MultiTexCoord0;
    
}
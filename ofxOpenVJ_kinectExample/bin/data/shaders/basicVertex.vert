
uniform float time;
uniform vec2 resolution;

void main(void)
{
	//this is a default vertex shader all it does is this...
   // vec3 p = ftransform() ; 
   // p.x = sin( time ) * 50.0 + p.x ;
	gl_Position = ftransform();
	//.. and passes the multi texture coordinates along to the fragment shader
	gl_TexCoord[0] = gl_MultiTexCoord0;
    
}

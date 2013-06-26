uniform float time ;
uniform float var1;
uniform float var2;
uniform float var3;
uniform float var4;

void main() {
	// a fragment shader HAS to write gl_FragColor -> this determines the pixel color
	// gl_Color is a value that is set by OpenGL commands, to specifiy the object color
    //this is the fragment shader
	//this is where the pixel level drawing happens
	//gl_FragCoord gives us the x and y of the current pixel its drawing
	
	//we grab the x and y and store them in an int
	float xVal = gl_FragCoord.x;
	float yVal = gl_FragCoord.y;
	
	gl_FragColor = gl_Color;
	
    
	//we use the mod function to only draw pixels if they are every 2 in x or every 4 in y
	//if( mod(xVal, 2.0) == 0.5 && mod(yVal, 2.0) == 0.5 ){
//		gl_FragColor = gl_Color;
 //   }else{
//		gl_FragColor.a = 0.85;//
//      }

    
}
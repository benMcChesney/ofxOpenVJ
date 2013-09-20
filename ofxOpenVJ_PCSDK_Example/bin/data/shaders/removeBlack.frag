#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src_tex_unit0;
   
void main (void) {
	vec2 st = gl_TexCoord[0].st;
	
	vec4 outColor = texture2DRect(src_tex_unit0, st);
	
	if(outColor.r + outColor.g + outColor.b <= 0.0) {
		outColor.w = 0.0;
	}
	
	gl_FragColor = outColor;
}
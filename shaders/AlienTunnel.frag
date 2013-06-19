#ifdef GL_ES
precision highp float;
#endif

uniform vec2 resolution;
uniform float time;
uniform float low ;
uniform float mid ;
uniform float high ;

//Object A (tunnel)
float oa(vec3 q)
{
    //return cos(q.x)+cos(q.y*q.x*1.5 * handDistance )+cos(q.z)+cos(q.y*20.)* bass ;
    return cos(q.x)+cos(q.y*q.x * 2.5 * (mid+0.15) )+cos(q.z)+cos(q.y*15.) + ( low * 1.25) ;
}

//Object B (ribbon)
float ob(vec3 q)
{
    return length(max(abs(q-vec3(cos(q.z*1.5)*.3,-.5+cos(q.z)*.2,.0))-vec3(.125,.02,3.),vec3(.0)));
}

//Scene
float o(vec3 q)
{
    // return min(oa(q),ob(q)) * handDistance ;
    return min(oa(q),ob(q)) + 0.5 +sin ( time * .75 ) * 0.1 ;
}

//Get Normal
vec3 gn(vec3 q)
{
    vec3 f=vec3(.01,0,0);
    return normalize(vec3(o(q+f.xyy),o(q+f.yxy),o(q+f.yyx)));
}

//MainLoop
void main(void)
{
    vec2 p = gl_FragCoord.xy / resolution.xy;
    p -= 0.5;
    
    // Fisheye madness!
    p.x *= resolution.x/resolution.y;
    float theta = atan(p.y, p.x );
    float rad = length(p);
    rad = pow(rad, 0.6 + 0.3 ) ; //* sin(time * 0.29857473));
    theta +=time * 0.15 ; 
    p.x = rad*cos(theta);
    p.y = rad*sin(theta);
    
    vec4 c=vec4(1.0);
    //mouse.xy-gt
    vec3 org=vec3(sin(time)*.5,cos(time)*.5,1.0),dir=normalize(vec3((p.x),p.y,1.0)),q=org,pp;
    float d=.0;
    
    //First raymarching
    for(int i=0;i<16;i++)
    {
        d=o(q);
        q+=d*dir ;
    }
    pp=q;
    float f=length(q-org)*0.02;
    
    //Second raymarching (reflection)
    dir=reflect(dir,gn(q));
    q+=dir;
    /*
    for(int i=0;i<32;i++)
    {
        d=o(q);
        q+=d*dir;
    }
     */
    c=max(dot(gn(q),vec3(.12,.1,.0)),.0)+vec4(cos(time*-.5)*.5+.85,sin(time*.5)*.5+.85,sin ( time ) * .5+.25,1.)*min(length(q-org)*.04,1.);
    
    //Ribbon Color
    if(oa(pp)>ob(pp))c=mix(c,vec4(sin(time*.3)*.5+.5,cos(time*.2)*.5+.5,sin(time)*.5,1.),.9);
    
    //Final Color
    vec4 fcolor = ((c+vec4(f))+(1.-min(pp.y+1.9,1.))*vec4(1.,sin(time) * .8, cos(time) *.8,1.))*min(time*.5,1.);
    gl_FragColor= c ; //vec4(fcolor.xyz,1.0);
}

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
uniform float cellScale ; 
uniform float colorMin ; 

vec2 hash(vec2 p)
{
    mat2 m = mat2(  1.85, 47.77,
                    99.41, 188.48
                );

    return fract(sin(m*p) * 46738.29);
}

float voronoi(vec2 p)
{
    vec2 g = floor(p);
    vec2 f = fract(p);

    float distanceToClosestFeaturePoint = 1.0;
    for(int y = -1; y <= 1; y++)
    {
        for(int x = -1; x <= 1; x++)
        {
            vec2 latticePoint = vec2(x, y);
            float currentDistance = distance(latticePoint + hash(g+latticePoint), f);
            distanceToClosestFeaturePoint = min(distanceToClosestFeaturePoint, currentDistance);
        }
    }

    return distanceToClosestFeaturePoint;
}

void main( void )
{
    vec2 uv = ( gl_FragCoord.xy / resolution.xy ) * 2.0 - 1.0;
    uv.x *= resolution.x / resolution.y;

    float offset = voronoi(uv*cellScale + vec2(time));			   
    float t = 1.0/abs(((uv.x + sin(uv.y + time)) + offset) * 30.0 * low );

    float r = voronoi( uv * 8.0 ) * 10.0 * low ;
    vec3 finalColor = vec3(low + 10.0 * uv.y, 2.0, 1.0 * r) * (t+0.01);
    
    gl_FragColor = vec4(finalColor * ( beat + colorMin ) , 1.0 );
}

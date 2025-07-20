#version 330

// Input uniform values from Raylib
uniform vec2 iResolution; // Viewport resolution (pixels)
uniform float iTime;      // Shader playback time (seconds)

// Output fragment color
out vec4 fragColor;

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = (fragCoord - 0.5 * iResolution.xy) / min(iResolution.x,iResolution.y);
    
    //distorted,inspired by https://www.shadertoy.com/view/3fKGRd
    float theta = atan(uv.y, uv.x);
    float r = length(uv);
    theta += 2.0/(r+0.1);
    vec2 distorted = r * vec2(cos(theta), sin(theta));
    
    //pattern
    float pattern = sin(distorted.x*20.0 + iTime*2.0) * 
                   cos(distorted.y*20.0 + iTime*2.0) * 
                   (1.0 - smoothstep(0.0, 0.8, r));
    
    //color
    vec3 col = vec3(0.0);
    col += vec3(0.5,0.2,0.7) * (pattern); 
    col += vec3(0.8,0.5,1.0) * abs(pattern); 
    col += vec3(0.3,0.1,0.5) * (0.3 + 0.7*smoothstep(0.4,0.2, r)); 
    
    fragColor = vec4(col, 1.0);
}

void main() {
    mainImage(fragColor, gl_FragCoord.xy);
}
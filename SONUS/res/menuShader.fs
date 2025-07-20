#version 330 core

// Uniforms que Raylib rellenará automáticamente:
uniform vec2 iResolution; // (anchura, altura) de la ventana
uniform float iTime;      // tiempo en segundos desde que comenzó el programa

in vec2 fragTexCoord;
out vec4 fragColor;

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    // Center the coordinates and adjust aspect ratio
    vec2 p = (2.0 * fragCoord - iResolution.xy) / min(iResolution.x, iResolution.y);
    
    // Convert to polar coordinates for the tunnel effect
    float r = length(p);
    float a = atan(p.y, p.x);
    
    // Create the tunnel effect with warping based on time
    float tunnel = 1.0 / (r + 0.5);
    
    // Animate the tunnel movement
    float z = fract(tunnel + iTime * 0.5);
    
    // Create grid lines for the tunnel
    float numLines = 20.0;
    float lineThickness = 0.03;
    
    // Radial lines
    float radialLines = abs(fract(a / 3.14159 * numLines * 0.5) - 0.5);
    radialLines = smoothstep(0.0, lineThickness, radialLines);
    
    // Circular lines
    float circLines = abs(fract(z * numLines) - 0.5);
    circLines = smoothstep(0.0, lineThickness, circLines);
    
    // Combine the lines
    float lines = min(radialLines, circLines);
    
    // Color mapping - synthwave palette
    vec3 col = mix(
        vec3(0.8, 0.0, 0.8),  // Hot pink
        vec3(0.0, 0.6, 0.9),  // Cyan
        sin(a + iTime) * 0.5 + 0.5
    );
    
    // Add a sun/horizon effect
    float horizon = smoothstep(0.5, 0.8, 1.0 - p.y * 0.5);
    vec3 sunCol = mix(
        vec3(1.0, 0.2, 0.6),  // Pink
        vec3(1.0, 0.8, 0.0),  // Yellow/orange
        horizon
    );
    
    // Mix the tunnel and sun colors based on distance
    float sunMix = smoothstep(0.4, 0.0, r - 0.2 * sin(iTime * 0.5));
    col = mix(col, sunCol, sunMix * horizon);
    
    // Apply the lines effect with glow
    float glow = (1.0 - lines) * z * 2.0;
    col += vec3(1.0, 1.0, 1.0) * glow;
    
    // Add some noise for texture
    float noise = fract(sin(dot(uv, vec2(12.9898, 78.233)) * 43758.5453));
    col += noise * 0.03;
    
    // Apply scanlines for retro effect
    float scanline = sin(uv.y * iResolution.y * 0.8) * 0.05 + 0.95;
    col *= scanline;
    
    // Vignette effect
    float vignette = 1.0 - r * 0.5;
    col *= vignette;
    
    // Background color gradient
    vec3 bgCol = mix(
        vec3(0.0, 0.0, 0.2),  // Dark blue
        vec3(0.1, 0.0, 0.1),  // Dark purple
        uv.y
    );
    
    // Mix with the background based on tunnel distance
    col = mix(bgCol, col, min(1.0, z * 1.5));
    
    // Output to screen
    fragColor = vec4(col, 1.0);
}

void main()
{
    // Usamos la coordenada de píxel real:
    vec2 fragCoord = gl_FragCoord.xy;
    mainImage(fragColor, fragCoord);
}
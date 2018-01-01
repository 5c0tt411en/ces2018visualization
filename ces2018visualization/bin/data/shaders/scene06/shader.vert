#version 120

#pragma include "noise4D.frag"

varying vec4 globalColor;

// the time value is passed into the shader by the OF app.
uniform float time;
uniform float noiseX;
uniform float speedY;
uniform float dHeight;
uniform float nFreq;

float rand(float n){return fract(sin(n) * 43758.5453123);}

float noise(float p){
    float fl = floor(p);
    float fc = fract(p);
    return mix(rand(fl), rand(fl + 1.0), fc);
}

void main()
{
    vec4 position = ftransform();

    float displacementHeight = 10 + dHeight;

    float displacementX = 0;
    float displacementY = snoise(vec4((1 + speedY) * time + (1 + nFreq) * position.x / 1000, (1 + speedY) * time + (1 + nFreq) * position.y / 1000, 0, 0.1352 * 1 * 1)) * displacementHeight;
    
    vec4 modifiedPosition = position;
	modifiedPosition.x += displacementX;
    modifiedPosition.y += displacementY;
	gl_Position = modifiedPosition;
    
    globalColor = gl_Color;
}

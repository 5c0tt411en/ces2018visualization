//#version 120
//#extension GL_ARB_texture_rectangle : enable

uniform sampler2D sparkTex;

void main() {
    
    gl_FragColor = texture2D(sparkTex, gl_TexCoord[0].st) * gl_Color;
}

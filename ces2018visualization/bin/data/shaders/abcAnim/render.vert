#version 120
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_rectangle : enable

#pragma include "util.frag"
#pragma include "noise4D.frag"

uniform float size;
uniform sampler2DRect u_posAndAgeTex;
uniform float resolution;
uniform vec2 screen;
uniform float u_time;
uniform float u_timestep;
uniform float u_scale;
uniform int  u_startShape;

void main() {
    if (u_startShape == 0) {
        vec2 verPos = gl_MultiTexCoord0.xy;
        vec3 pos = texture2DRect( u_posAndAgeTex, verPos ).xyz;
        
        gl_TexCoord[0] = gl_MultiTexCoord0;
        vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;
        float dist = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
        float att     = 600.0 / dist;
        eyeCoord.x += pos.x + 70. * snoise(
                              vec4(
                                   eyeCoord.x * 0.02,
                                   eyeCoord.y * 0.02,
                                   eyeCoord.z * 0.02,
                                   0.001 * u_time
                                   )
                              );
        eyeCoord.y += pos.y + 70. * snoise(
                        vec4(
                             eyeCoord.x * 0.02,
                             eyeCoord.y * 0.02,
                             eyeCoord.z * 0.02,
                             0.001 * u_time
                             )
                        );
        eyeCoord.z += pos.z + 70. * snoise(
                        vec4(
                             eyeCoord.x * 0.02,
                             eyeCoord.y * 0.02,
                             eyeCoord.z * 0.02,
                             0.001 * u_time
                             )
                        );
        gl_Position = gl_ProjectionMatrix * eyeCoord;
//        gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
        gl_PointSize = 3. + size + 20. * snoise(
                                           vec4(
                                                eyeCoord.x * 0.005,
                                                eyeCoord.y * 0.005,
                                                eyeCoord.z * 0.005,
                                                0.001 * u_time
                                                )
                                           );
    gl_FrontColor = gl_Color;
    }
    else {
//         use the texture coordinates as an index into the position texture
        vec2 verPos = gl_MultiTexCoord0.xy;

        // read position data from texture
        vec3 pos = texture2DRect( u_posAndAgeTex, verPos ).xyz;
        gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);


        gl_PointSize = size + 20. * snoise(
                                           vec4(
                                                pos.x * 0.001,
                                                pos.y * 0.001,
                                                pos.z * 0.001,
                                                0.001 * u_time
                                                )
                                           );
        gl_FrontColor = gl_Color;
    }

}

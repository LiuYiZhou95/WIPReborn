#version 300 es
#extension GL_ARB_texture_rectangle : enable
precision mediump float;
in vec2 v_texCoord;
uniform sampler2D s_baseMap; 
uniform sampler2D s_lightMap;  
void main()                                      
{                                                 
 
gl_FragColor = vec4 ( 0.0, 0.32, 0.32, 0.7 );
    
}                       
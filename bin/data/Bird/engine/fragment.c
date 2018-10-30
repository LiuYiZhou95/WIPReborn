#version 300 es
#extension GL_ARB_texture_rectangle : enable
precision mediump float;
in vec2 v_texCoord;
out vec4 outColor;
uniform sampler2D s_baseMap; 
uniform sampler2D s_lightMap;  
void main()                                      
{                                                 
 vec4 baseColor;                                 
vec4 lightColor;                                  
baseColor = texture2D( s_baseMap, v_texCoord );   
lightColor = texture2D( s_lightMap, v_texCoord );   
    outColor = baseColor;
}                                               
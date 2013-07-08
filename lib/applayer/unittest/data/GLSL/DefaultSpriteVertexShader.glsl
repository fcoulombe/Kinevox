uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform int CurrentFrame;
attribute vec4 InPosition;     
attribute vec2 InTexCoord; 
varying vec2 texcoord;  
varying vec4 color;  
void main()          
{                    
#if ENABLE_FIX_PIPELINE 
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex; 
	gl_TexCoord[0] = gl_MultiTexCoord0; 
#else 
   gl_Position = ProjectionMatrix * ModelViewMatrix * InPosition; 
	texcoord = InTexCoord.xy;
#endif 
	color = InNormal; //vec4(InTexCoord.x,InTexCoord.y, 0.0,1.0); 
}                           
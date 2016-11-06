#version 330                                                                  
                                                                                    
layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;  
layout (location = 3) in vec3 Color;
layout (location = 4) in ivec4 BoneIndices;
layout (location = 5) in vec4 BoneWeights;                                           

uniform mat4 gWVP;
uniform mat4 gWorld;
uniform mat4 gBones[DEFINE_MAX_BONES];
                                        
out vec2 TexCoord0;                                                                 
out vec3 Normal0;                                                                   
out vec3 WorldPos0;                                                                 

void main()
{       
	if(BoneWeights[0] + BoneWeights[1] + BoneWeights[2] + BoneWeights[3] != 0) {
		mat4 boneTransform = gBones[BoneIndices[0]] * BoneWeights[0];
		boneTransform += gBones[BoneIndices[1]] * BoneWeights[1];
		boneTransform += gBones[BoneIndices[2]] * BoneWeights[2];
		boneTransform += gBones[BoneIndices[3]] * BoneWeights[3];

		gl_Position = gWVP * boneTransform * vec4(Position, 1.0);
		Normal0 = (gWorld * boneTransform * vec4(Normal, 0.0)).xyz;   
		WorldPos0 = (gWorld * boneTransform * vec4(Position, 1.0)).xyz;
	} else {
		gl_Position = gWVP * vec4(Position, 1.0);
		Normal0 = (gWorld * vec4(Normal, 0.0)).xyz;   
		WorldPos0 = (gWorld * vec4(Position, 1.0)).xyz;
	}

    TexCoord0 = TexCoord;                  

}
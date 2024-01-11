#version 330 core

layout (triangles) in;
layout (line_strip,max_vertices = 6) out;

out vec3 CurrentPosition;
out vec3 Normal;
out vec3 Color;
out vec2 TexCord;

in DATA
{
	vec3 CurrentPosition;
	vec3 Normal;
	vec3 Color;
	vec2 TexCord;
	mat4 CameraMatrix;
	float T;
} data_in[];


void main(){
	

	gl_Position = data_in[0].CameraMatrix * (gl_in[0].gl_Position);
	EmitVertex();
	gl_Position = data_in[0].CameraMatrix * (gl_in[0].gl_Position + 0.01f * vec4(data_in[0].Normal,0.0f));
	EmitVertex();
	EndPrimitive();

	gl_Position = data_in[1].CameraMatrix * (gl_in[1].gl_Position);
	EmitVertex();
	gl_Position = data_in[1].CameraMatrix * (gl_in[1].gl_Position + 0.01f * vec4(data_in[1].Normal,0.0f));
	EmitVertex();
	EndPrimitive();

	gl_Position = data_in[2].CameraMatrix * (gl_in[2].gl_Position);
	EmitVertex();
	gl_Position = data_in[2].CameraMatrix * (gl_in[2].gl_Position + 0.01f * vec4(data_in[2].Normal,0.0f));
	EmitVertex();
	EndPrimitive();

}



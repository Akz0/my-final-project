#version 330 core

out vec4 FragColor;

in vec3 Color;
in vec2 TexCord;
in vec3 Normal;
in vec3 CurrentPosition;
in vec4 FragPositionLight;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;
uniform sampler2D shadowMap;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 CameraPosition;


vec4 PointLight(float power){
	
	vec3 LightVector = lightPosition - CurrentPosition;
	float distance = length(LightVector);

	float a = 3.1f;
	float b = 1.2f;

	float intensity = 1.0f / (a*distance*distance + b*distance + 1.0f);
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - CurrentPosition);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	diffuse = max(diffuse,0.0);

	float SpecularLight = 0.5f;
	vec3 ViewDirection = normalize(CameraPosition - CurrentPosition);
	vec3 ReflectionDirection = reflect(-lightDirection, normal);

	vec3 halfway = normalize(ViewDirection + lightDirection);

	float SpecularAmount = pow(max(dot(normal,halfway),0.0f),16);
	float specular = SpecularAmount * SpecularLight;

	float ambient = 0.20f;

	return ((texture(diffuse0, TexCord) * (diffuse + ambient + intensity) + texture(specular0, TexCord).r * specular) * lightColor) * power;
}

vec4 SpotLight(float power){
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	
	vec3 normal = normalize(texture(normal0, TexCord).xyz * 2.0f - 1.0f);
	vec3 lightDirection = normalize(lightPosition - CurrentPosition);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float SpecularLight = 0.5f;
	vec3 ViewDirection = normalize(CameraPosition - CurrentPosition);
	vec3 ReflectionDirection = reflect(-lightDirection, normal);

	vec3 halfway = normalize(ViewDirection + lightDirection);

	float SpecularAmount = pow(max(dot(normal,halfway),0.0f),16);
	float specular = SpecularAmount * SpecularLight;

	float ambient = 0.20f;

	float angle = dot(vec3(0.0f,-1.0f,0.0f),-lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone),0.0f,1.0f);


	//Calculating Shadows

	float shadow = 0.0f;
	vec3 lightCords = FragPositionLight.xyz / FragPositionLight.w;
	if( lightCords.z <= 1.0f ){

		lightCords = (lightCords + 1.0f)/2.0f;
		float currentDepth = lightCords.z;
		float bias = max(0.00025f * (1.0f - dot(normal,lightDirection)),0.00005f);
		

		//Softening of Shadows

		int sampleSize = 2;
		vec2 pixels = 1.0 / textureSize(shadowMap,0);

		for (int y = -sampleSize;y<=sampleSize;y++){
			for (int x = -sampleSize;x<=sampleSize;x++){
				float depth = texture(shadowMap,lightCords.xy + vec2(x,y) * pixels).r;
				if(currentDepth > depth){
					shadow+=1.0f;
				}
			}
		}

		shadow /= pow((sampleSize * 2 + 1), 2);

	}


	return ((texture(diffuse0, TexCord) * (diffuse*(1.0f - shadow) + ambient + intensity) + texture(specular0, TexCord).r * specular *(1.0f - shadow) *intensity) * lightColor) * power;
}

vec4 DirectionLight(float power){
	
	//Calculation of Diffuse Light
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f,1.0f,0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//Calculation of Specular Light
	float SpecularLight = 0.5f;
	vec3 ViewDirection = normalize(CameraPosition - CurrentPosition);
	vec3 ReflectionDirection = reflect(-lightDirection, normal);

	//Without Halfway Vector, it would be normal phong illumination
	vec3 halfway = normalize(ViewDirection + lightDirection);

	float SpecularAmount = pow(max(dot(normal,halfway),0.0f),16);
	float specular = SpecularAmount * SpecularLight;

	float ambient = 0.20f;


	//Calculating Shadows

	float shadow = 0.0f;
	vec3 lightCords = FragPositionLight.xyz / FragPositionLight.w;
	if( lightCords.z <= 1.0f ){

		lightCords = (lightCords + 1.0f)/2.0f;
		float currentDepth = lightCords.z;
		float bias = max(0.025f * (1.0f - dot(normal,lightDirection)),0.005f);
		

		//Softening of Shadows

		int sampleSize = 2;
		vec2 pixels = 1.0 / textureSize(shadowMap,0);

		for (int y = -sampleSize;y<=sampleSize;y++){
			for (int x = -sampleSize;x<=sampleSize;x++){
				float depth = texture(shadowMap,lightCords.xy + vec2(x,y) * pixels).r;
				if(currentDepth > depth){
					shadow+=1.0f;
				}
			}
		}

		shadow /= pow((sampleSize * 2 + 1), 2);

	}


	return ((texture(diffuse0, TexCord) * (diffuse *(1.0f - shadow) + ambient ) + texture(specular0, TexCord).r * specular *(1.0f - shadow) ) * lightColor) * power;
}

void main()
{
	FragColor = SpotLight(1.0);
}
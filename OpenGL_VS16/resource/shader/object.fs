#version 330 core

struct Matertial {
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
out vec4 fragColor;

uniform Matertial material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 ourNormal;
in vec2 ourTexCoord;
uniform sampler2D texture_diffuse0;

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	// properties
	vec3 norm = normalize(ourNormal);
	vec3 viewDir = normalize(viewPos - fragPos);
	
	// direction light
	vec3 result = calculateDirLight(dirLight, norm, viewDir);
	// point light
	for (int i = 0; i < NR_POINT_LIGHTS; ++i)
		result += calculatePointLight(pointLight[i], norm, fragPos, viewDir);
	// spot light
	result += calculateSpotLight(spotLight, norm, fragPos, viewDir);

	fragColor = vec4(result, 1.0f);
}

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir),0.0f),material.shininess);
	// combine
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, ourTexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, ourTexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, ourTexCoord));

	return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir),0.0f),material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// combine
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, ourTexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, ourTexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, ourTexCoord));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir),0.0f),material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * distance * distance));
	// spotlight intesity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
	// combine
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, ourTexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, ourTexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, ourTexCoord));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity ;

	return (ambient + diffuse + specular);
}
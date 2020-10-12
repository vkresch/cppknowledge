#version 330 core

layout(location = 0) out vec4 f_color;

in vec3 v_normal;
in vec3 v_position;
in vec2 v_tex_coord;

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
};

struct PointLight {
    vec3 position;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    // Required to model the intensity of the light
    float linear;
    float quadratic;
};

struct SpotLight {

    vec3 position;
    vec3 direction; // Must be normalized

    float innerCone;
    float outerCone;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
};

uniform Material u_material;
uniform DirectionalLight u_directional_light;
uniform PointLight u_point_light;
uniform SpotLight u_spot_light;
uniform sampler2D u_diffuse_map;

void main()
{
    // Vector from fragment to camera (camera always at 0,0,0)
    vec3 view = normalize(-v_position);
    vec3 normal = normalize(v_normal);

    vec4 diffuseColor = texture(u_diffuse_map, v_tex_coord);

    vec3 light = normalize(-u_directional_light.direction);
    vec3 reflection = reflect(u_directional_light.direction, normal);

    vec3 ambient = u_directional_light.ambient * diffuseColor.xyz;
    vec3 diffuse = u_directional_light.diffuse * max(dot(normal, light), 0.0f) * diffuseColor.xyz;
    vec3 specular = u_directional_light.specular * pow(max(dot(reflection, view), 0.0001f), u_material.shininess) * u_material.specular;

    light = normalize(u_point_light.position - v_position);
    reflection = reflect(-light, normal);

    float distance = length(u_point_light.position - v_position);
    float attenuation = 1.0f / (1.0f + (u_point_light.linear * distance)) + (u_point_light.quadratic * distance * distance);

    ambient += attenuation * u_point_light.ambient * diffuseColor.xyz;
    diffuse += attenuation * u_point_light.diffuse * diffuseColor.xyz * max(dot(normal, light), 0.0f);
    specular += attenuation * u_point_light.specular * u_material.specular * pow(max(dot(reflection, view), 0.0001f), u_material.shininess);

    light = normalize(u_spot_light.position - v_position);
    reflection = reflect(-light, normal);
    float theta = dot(light, u_spot_light.direction);
    float epsilon = u_spot_light.innerCone - u_spot_light.outerCone;
    float intensity = clamp((theta - u_spot_light.outerCone)/epsilon, 0.0f, 1.0f);
    if(theta > u_spot_light.outerCone){
        ambient += u_spot_light.ambient * diffuseColor.xyz;
        diffuse += intensity * u_spot_light.diffuse * diffuseColor.xyz * max(dot(normal, light), 0.0f);
        specular += intensity * u_spot_light.specular * u_material.specular * pow(max(dot(reflection, view), 0.0001f), u_material.shininess);
    } else {
        ambient += u_spot_light.ambient * diffuseColor.xyz;
    }

    f_color = vec4(ambient + diffuse + specular + u_material.emissive, 1.0f);
}
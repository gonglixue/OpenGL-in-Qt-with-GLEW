#version 400

in vec3 o_normal;
in vec3 o_lightVector;
in vec3 o_viewVector;

uniform vec3 u_objectColor;  // diffuse color of object
uniform vec3 u_coolColor;  // cool color of gooch
uniform vec3 u_warmColor;  //
uniform float u_alpha;
uniform float u_beta;

out vec4 Color;

void main()
{
    vec3 normalVector = normalize(o_normal);
    vec3 lightVector = normalize(o_lightVector);

    float diffuseLighting = dot(lightVector, normalVector);
    diffuseLighting = (1.0 + diffuseLighting)/2;

    vec3 coolColorMod = u_coolColor + u_objectColor * u_alpha;
    vec3 warmColorMod = u_warmColor + u_objectColor * u_beta;
    vec3 colorOut = mix(coolColorMod, warmColorMod, diffuseLighting);

    Color.rgb = colorOut;
    Color.a = 1.0;
}

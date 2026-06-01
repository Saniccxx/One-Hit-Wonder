#version 330 core

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 resolution;

#define MAX_LIGHTS 100

uniform vec3 lights[MAX_LIGHTS]; // x, y, radius
uniform vec4 light_colors[MAX_LIGHTS];
uniform int num_lights;
uniform float ambient; // 0.0 (black) .. 1.0 (no darkness)

out vec4 finalColor;

void main() {
    vec4 base_color = texture(texture0, fragTexCoord);
    if (base_color.a == 0.0) {
        discard;
    }

    vec3 light_accum = vec3(0.0);
    vec2 frag_pos_screen = gl_FragCoord.xy;

    for (int i = 0; i < num_lights; i++) {
        float dist = distance(lights[i].xy, frag_pos_screen);
        float radius = lights[i].z;
        if (dist < radius) {
            float attenuation = 1.0 - (dist / radius);
            light_accum += light_colors[i].rgb * attenuation;
        }
    }

    // Multiplicative lighting with ambient term to keep some darkness
    vec3 light_factor = clamp(vec3(ambient) + light_accum, 0.0, 1.0);
    vec3 lit_rgb = base_color.rgb * light_factor;

    finalColor = vec4(lit_rgb, base_color.a);
}
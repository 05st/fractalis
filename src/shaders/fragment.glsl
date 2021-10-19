#version 460 core

in vec4 gl_FragCoord;
out vec4 FragColor;

uniform vec2 windowSize;

int max_iters = 2000;

void main() {
    int iters = 0;

    double c_r = ((gl_FragCoord.x / windowSize.x) - 0.5) * windowSize.x / 320.0;
    double c_i = ((gl_FragCoord.y / windowSize.y) - 0.5) * windowSize.y / 320.0;

    double r = 0.0;
    double i = 0.0;
    double r_2 = 0.0;
    double i_2 = 0.0;
    
    double q = (c_r - 0.25) * (c_r - 0.25) + c_i * c_i;
    bool cardoidCheck = (q * (q + (c_r - 0.25)) <= (c_i * c_i) / 4.0);

    if (cardoidCheck) {
        iters = max_iters;
    } else {
        while (r_2 + i_2 <= 4 && iters < max_iters) {
            i = 2 * r * i + c_i;
            r = r_2 - i_2 + c_r;

            r_2 = r * r;
            i_2 = i * i;

            iters++;
        }
    }

    if (iters == max_iters) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    } else {
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

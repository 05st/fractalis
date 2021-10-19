#version 460 core

in vec4 gl_FragCoord;
out vec4 FragColor;

uniform vec2 windowSize;

int max_iters = 10000;
bool mandelbrot = true;

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    int iters = 0;

    double c_r = ((gl_FragCoord.x / windowSize.x) - 0.5) * windowSize.x / 320.0;
    double c_i = ((gl_FragCoord.y / windowSize.y) - 0.5) * windowSize.y / 320.0;

    double r = 0.0;
    double i = 0.0;
    double r_2 = 0.0;
    double i_2 = 0.0;

    if (mandelbrot) {
        double q = (c_r - 0.25) * (c_r - 0.25) + c_i * c_i;
        bool cardoidCheck = (q * (q + (c_r - 0.25)) <= (c_i * c_i) / 4.0);
        bool circleCheck = (((c_r + 1.0) * (c_r + 1.0) + c_i * c_i) <= 0.0625);

        if (cardoidCheck || circleCheck) {
            iters = max_iters;
        } else {
            while (r_2 + i_2 <= 5 && iters < max_iters) {
                i = 2 * r * i + c_i;
                r = r_2 - i_2 + c_r;

                r_2 = r * r;
                i_2 = i * i;

                iters++;
            }
        }
    } else {
        c_r = -0.512511498387847167;
        c_i = 0.521295573094847167;

        r = ((gl_FragCoord.x / windowSize.x) - 0.5) * windowSize.x / 320.0;
        i = ((gl_FragCoord.y / windowSize.y) - 0.5) * windowSize.y / 320.0;

        while (r*r + i*i <= 5 && iters < max_iters) {
            double r_ = r;
            r = r * r - i * i + c_r;
            i = 2 * r_ * i + c_i;
            iters++;
        }
    }

    if (iters == max_iters) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    } else {
        if (mandelbrot) {
            i = 2 * r * i + c_i;
            r = r_2 - i_2 + c_r;
            r_2 = r * r;
            i_2 = i * i;
            iters++;

            float color = float(iters) + 1.0f - (log(log(sqrt(float(r_2 + i_2)))))/(log(2.0f));
            FragColor = vec4(hsv2rgb(vec3(color / 256.0, 1.0f, 1.0f)), 1.0f);
        } else {
            float color = float(iters) + 1.0f - (log(log(sqrt(float(r * r + i * i)))))/(log(2.0f));
            FragColor = vec4(hsv2rgb(vec3(color / 256.0, 1.0f, 1.0f)), 1.0f);
        }
    }
}

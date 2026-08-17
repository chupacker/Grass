#version 460 core
out vec4 FragColor;


void main(){
    float r = 70.0 / 255.0;
    float g = 194.0 / 255.0;
    float b = 43.0 / 255.0;
    FragColor = vec4(r, g, b, 1.0);
}

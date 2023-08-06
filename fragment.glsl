#version 400 core
out vec4 FragColor;
in vec2 FragCoord;
uniform float Time;
uniform double ScrRatio;
uniform int iterations;
uniform double zoom;
uniform dvec2 camera;
double pi = 2*acos(0);
void main()
{
    dvec2 c = 2*(camera + dvec2(FragCoord.x*ScrRatio,FragCoord.y)/zoom);

    dvec2 z = dvec2(0);

    double iterCount = double(iterations);

    double i = 0;
    while(i < iterCount && z.x*z.x+z.y*z.y < 4)
    {
        dvec2 newZ;
        newZ.x = z.x*z.x - z.y*z.y + c.x;
        newZ.y = 2*z.x*z.y + c.y;
        z = newZ;
        i++;
    }

    float col = float((i/iterCount)*10);
    FragColor = vec4(cos(col),sin(col),-sin(col), 1.0);

}

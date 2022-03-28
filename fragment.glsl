#version 330 core
out vec4 FragColor;
in vec2 FragCoord;
uniform float Time;
uniform float ScrRatio;
uniform float zoom;
uniform vec2 camera;
float pi = 2*acos(0);
void main()
{
    vec2 c = 2*(camera + vec2(FragCoord.x*ScrRatio,FragCoord.y)/zoom);

    vec2 z = vec2(0);

    float iterCount = abs(64+zoom);
    if (iterCount > 5000){iterCount = 5000;}

    float i = 0;
    while(i < iterCount && z.x*z.x+z.y*z.y < 4)
    {
        vec2 newZ;
        newZ.x = z.x*z.x - z.y*z.y + c.x;
        newZ.y = 2*z.x*z.y + c.y;
        z = newZ;
        i++;
    }

    float col = (i/iterCount)*10;
    FragColor = vec4(cos(col),sin(col),-sin(col), 1.0);

}


class Tank
{
public:
    float x;
    float y;

    float speedX;
    float speedY;
    
    float size;

    float *color;

    Tank(float xPos, float yPos, float size, float *color);
    Tank();
    void Move();
};
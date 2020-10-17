
class Tank
{
public:
    float x;
    float y;

    // Speed Direction
    float speed = 0;
    float speedX;
    float speedY;

    float power;

    bool engineState = false;

    float angle;
    float rotateSpeed;

    float size;

    float *color;

    Tank(float xPos, float yPos, float size, float *color, float angle, float rotSp, float pw);
    Tank();
    void Move();
    void Rotate(int dir);
};
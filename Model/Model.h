
struct TankModel
{
    unsigned cvBody;
    unsigned cvTower;
    unsigned countParams;
    float offsetBodyX;
    float offsetBodyY;
    float *vertices;
};

struct GunShellModel
{
    unsigned cv;
    unsigned countParams;
    float *vertices;
};

class Model
{
public:
    static TankModel readTankModel(const char* path);
    static GunShellModel readGunShellModel(const char* path);
};
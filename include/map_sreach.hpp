#include <vector>
#include <ctime>
#include <cstdlib>

struct Point{
    int x;
    int y;
    float value;
    Point(int x,int y,float value) : x(x),y(y),value(value){}
};

class Map{
public:
    int width;
    int height;
    float size;
    Map(int x,int y,float s){
        width = x;
        height = y;
        size = s;
        std::vector<int> temp;
        for (size_t i = 0; i < y; i++){
            temp.push_back(0);
        }
        for (size_t i = 0; i < x; i++){
            map.push_back(temp);
        }
    }

    std::vector<std::vector<int>> getMap(){
        return map;
    }

    void summonMaze(int start_x, int start_y, int end_x, int end_y){
        // 初始化随机数种子
        static bool seeded = false;
        if (!seeded) {
            srand(time(NULL));
            seeded = true;
        }
        
        // 先全部填充为墙(1)
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                map[i][j] = 1;
            }
        }
        
        // 递归生成迷宫(从起点开始)
        map[start_x][start_y] = 0;
        carvePath(start_x, start_y);
        
        // 确保终点可达
        map[end_x][end_y] = 0;
    }


    
private:
    std::vector<std::vector<int>> map;

    void carvePath(int x, int y) {
        // 四个方向: 上下左右(每次移动2格以保持墙厚度为1)
        int dirs[4][2] = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
        
        // 随机打乱方向
        for (int i = 0; i < 4; i++) {
            int r = rand() % 4;
            std::swap(dirs[i][0], dirs[r][0]);
            std::swap(dirs[i][1], dirs[r][1]);
        }
        
        // 尝试四个方向
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            
            // 检查新位置是否在边界内且未访问
            if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && map[nx][ny] == 1) {
                // 打通当前格子和新格子之间的墙
                map[x + dirs[i][0] / 2][y + dirs[i][1] / 2] = 0;
                map[nx][ny] = 0;
                
                // 递归访问新格子
                carvePath(nx, ny);
            }
        }
    }
};
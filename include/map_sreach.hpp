#include <vector>
#include <ctime>
#include <cstdlib>
#include <unordered_set>
#include "queue.hpp"

struct Point{
    int x;
    int y;
    float dis;
    Point* parent;
    Point(int x,int y) : x(x),y(y),dis(0.0f),parent(nullptr){}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    struct Hash{
        size_t operator()(const Point& n) const {
            return std::hash<int>()(n.x) ^ std::hash<int>()(n.y);
        }
    };
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

    void summonMaze(int start_x, int start_y, int end_x, int end_y,
                    int minSize, int maxSize, int count){
        // 初始化随机数种子
        static bool seeded = false;
        if (!seeded) {
            srand(time(NULL));
            seeded = true;
        }

        // 全部清空为可走(0)
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                map[i][j] = 0;
            }
        }

        // 参数保护
        if (minSize < 1) minSize = 1;
        if (maxSize < minSize) maxSize = minSize;

        int placed = 0;
        int guard = 0;
        const int maxGuard = count * 50 + 100; // 防止死循环

        while (placed < count && guard < maxGuard) {
            guard++;

            int size = minSize + (rand() % (maxSize - minSize + 1));
            if (size > width || size > height) continue;

            int x0 = rand() % (width - size + 1);
            int y0 = rand() % (height - size + 1);

            // 检查是否覆盖起点/终点
            bool coversStart = (start_x >= x0 && start_x < x0 + size &&
                                start_y >= y0 && start_y < y0 + size);
            bool coversEnd = (end_x >= x0 && end_x < x0 + size &&
                              end_y >= y0 && end_y < y0 + size);
            if (coversStart || coversEnd) continue;

            // 放置障碍物(1)
            for (int x = x0; x < x0 + size; x++) {
                for (int y = y0; y < y0 + size; y++) {
                    map[x][y] = 1;
                }
            }

            placed++;
        }

        // 确保起点终点可走
        map[start_x][start_y] = 0;
        map[end_x][end_y] = 0;
    }


    //BFS寻路
    std::vector<std::pair<int,int>> bfsSreach(std::pair<int,int> start,std::pair<int,int> end){
        // openQueue存放将要访问的节点，clostList用来记录已经访问过的节点
        // allocated记录点内存，，用于结束搜索后的释放
        Queue<Point*> openQueue;
        std::unordered_set<Point,Point::Hash> clostList;
        std::vector<Point*> allocated;
        Point* start_point = new Point(start.first,start.second);
        start_point->dis = 0;

        // 基本初始化 起始节点入队
        allocated.push_back(start_point);

        clostList.insert(*start_point);
        openQueue.push(start_point);

        while (!openQueue.isEmpty()){

            // 开放队列出队，第一个为起始节点
            Point* current = openQueue.top();
            openQueue.pop();

            // 如果遍历到了终点，终止循环，回溯路径并返回
            if (current->x == end.first && current->y == end.second){
                std::vector<std::pair<int,int>> path;
                while (current){
                    path.push_back({current->x,current->y});
                    current = current->parent;
                }
                // 释放openList
                for (Point* p : allocated){
                    delete p;
                }
                return path;
            }
            
            // 定义方向，上下左右
            std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto& d : directions){
                // 定义一个新节点用来标记访问的邻点
                int newX = current->x + d.first;
                int newY = current->y + d.second;

                // 确保在边界内，且无障碍物
                if (newX >= 0 && newY >= 0 && 
                    newX < width && newY < height && 
                    map[newX][newY] == 0){

                    // 确保没有访问过，如果已经访问过了，就直接跳过这个点，例如第一次遍历，以起始点右边的点为当前点，上下左右遍历到左的时候
                    // 左边是起点，已经访问过了，所以就跳过，
                    // 定义一个临时点，然后在闭合队列里查重，没找到就是没访问过
                    // find函数会返回对应元素的迭代器，如果没有那就是end()
                    // if中为没找到，迭代器不为end() true
                    Point probe(newX,newY);
                    if(clostList.find(probe) != clostList.end()){
                        continue;
                    }

                    // 闭合列表中没有重复，那就记录下dis和parent，入队openQueue和clostlist，以及记录数组
                    Point* newPoint = new Point(newX,newY);
                    newPoint->dis = current->dis + 1;
                    newPoint->parent = current;
                    allocated.push_back(newPoint);

                    clostList.insert(*newPoint);
                    openQueue.push(newPoint);
                }  
            }
        }

        //没找到，清理队列退出
        for (Point* p : allocated){
            delete p;
        }
        return {};
    }


    
private:
    std::vector<std::vector<int>> map;
};
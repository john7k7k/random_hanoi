#define TOWER_HEIGHT 4
#include <cstdio>
#include <cstdlib>
#include <random>
//#define PRINT_TOWERS() printTower(sources[0], TOWER_HEIGHT);printTower(sources[1], TOWER_HEIGHT);printTower(destination, TOWER_HEIGHT);printf("========\n")

void printTowers();
int** genarateRandomTwoSource();
int getSlayBlock(int *, int);
int randomTwoSourceHanoiMove(int *, int *, int *);

#include "hanoi.hpp"

int **sources = genarateRandomTwoSource();
int destination[TOWER_HEIGHT] = {0};

int main(int argc, char *argv[]){
    if(argc > 1){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++){
                sources[i][j] = argv[i+1][j] - '0';
            }
        }
    }
    printTowers();
    randomTwoSourceHanoiMove(sources[0], sources[1], destination);
    printf("finish\n");
    printTowers();
    free(sources[0]);
    free(sources[1]);
    free(sources);
    return 0;
}

void printTowers(){
    printTower(sources[0], TOWER_HEIGHT);
    printTower(sources[1], TOWER_HEIGHT);
    printTower(destination, TOWER_HEIGHT);
    printf("========\n");
}

int** genarateRandomTwoSource(){
    int **_sources = (int **)calloc(2, sizeof(int *));
    _sources[0] = (int *)calloc(TOWER_HEIGHT, sizeof(int));
    _sources[1] = (int *)calloc(TOWER_HEIGHT, sizeof(int));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,1);
    for(int i = 0; i < TOWER_HEIGHT; i++){
        int random_number = dis(gen);
        for(int j = 0; j < TOWER_HEIGHT; j++){
            if(_sources[random_number][j] > 0) continue;
            _sources[random_number][j] = TOWER_HEIGHT - i;
            break;
        }
    }
    return _sources;
}

int getSlayBlock(int *tower, int height){
    for(int i = 0; i < height; i++){
        if(tower[i] > 0) continue;
        if(i == 0) return 0;
        return tower[i - 1];
    }
    return tower[height - 1];
}

int randomTwoSourceHanoiMove(int *_source1, int *_source2, int *_destination){
    int slay1 = getSlayBlock(_source1, TOWER_HEIGHT), slay2 = getSlayBlock(_source2, TOWER_HEIGHT);
    /*狀況一*/
    if(slay1 == 0) hanoiMove(TOWER_HEIGHT, _source2, _source1, _destination);
    else if(slay2 == 0) hanoiMove(TOWER_HEIGHT, _source1, _source2, _destination);
    /*狀況二*/
    else if(slay1 == 4){
        move(_source1, _destination);
        hanoiMove(3, _source2, _source1, _destination);
    }
    else if(slay2 == 4){
        move(_source2, _destination);
        hanoiMove(3, _source1, _source2, _destination);
    }
    /*狀況三跟四*/
    else if(slay1 == 3){
        hanoiMove(2, _source2, _destination, _source1);
        if(getSlayBlock(_source2, TOWER_HEIGHT) == 4){
            move(_source2, _destination);
            hanoiMove(3, _source1, _source2, _destination);
        }
        else{
            hanoiMove(4, _source1, _source2, _destination);
        }
    }
    else if(slay2 == 3){
        hanoiMove(2, _source1, _destination, _source2);
        if(getSlayBlock(_source1, TOWER_HEIGHT) == 4){
            move(_source1, _destination);
            hanoiMove(3, _source2, _source1, _destination);
        }
        else{
            hanoiMove(4, _source2, _source1, _destination);
        }
    }
    /*狀況五六七八*/
    else if(slay1 == 2){
        move(_source2, _source1);
        slay2 = getSlayBlock(_source2, TOWER_HEIGHT);
        if(slay2 == 0) hanoiMove(4, _source1, _source2, _destination);
        else if(slay2 == 4){
            move(_source2, _destination);
            hanoiMove(3, _source1, _source2,_destination);
        }
        else{
            hanoiMove(2, _source1, _destination, _source2);
            slay1 = getSlayBlock(_source1, TOWER_HEIGHT);
            if(slay1 == 4){
                move(_source1, _destination);
                hanoiMove(3, _source2, _source1, _destination);
            }
            else if(slay1 == 0) hanoiMove(4, _source2, _source1, _destination);
            else return -1; //錯誤
        }
    }
    else if(slay2 == 2){
        move(_source1, _source2);
        slay1 = getSlayBlock(_source1, TOWER_HEIGHT);
        if(slay1 == 0) hanoiMove(4, _source2, _source1, _destination);
        else if(slay1 == 4){
            move(_source1, _destination);
            hanoiMove(3, _source2, _source1,_destination);
        }
        else{
            hanoiMove(2, _source2, _destination, _source1);
            slay2 = getSlayBlock(_source2, TOWER_HEIGHT);
            if(slay2 == 4){
                move(_source2, _destination);
                hanoiMove(3, _source1, _source2, _destination);
            }
            else if(slay2 == 0) hanoiMove(4, _source1, _source2, _destination);
            else return -1; //錯誤
        }
    }
    return 0;
}

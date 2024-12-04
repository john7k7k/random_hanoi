# include <cstdio>

int move(int *, int *);
int printTower(int *, int);
int hanoiMove(int, int *, int *, int *);

int hanoiMove(int amount, int *_source, int *_temp, int *_destination){
    if(amount == 1) {
        if(move(_source, _destination) < 0) return -1;
        return 1;
    }
    if(hanoiMove(amount - 1, _source, _destination, _temp) < 0) return -1;
    if(move(_source, _destination) < 1) return -1;
    if(hanoiMove(amount - 1, _temp, _source, _destination) < 0) return -1;
    return 1;
}

int move(int *_source, int *_destination){
    if(_source[0] == 0) return -1; //來源沒有物品可以搬運
    for(int i = 0; i < TOWER_HEIGHT; i++){
        if(i < TOWER_HEIGHT - 1 && _source[i] > 0) continue;
        if(i == TOWER_HEIGHT - 1  && _source[i] != 0) i = TOWER_HEIGHT;
        for(int j = 0; j < TOWER_HEIGHT; j++){
            if(_destination[j] > 0) continue;
            if(j > 0 && _destination[j - 1] < _source[i - 1]) return -2; //目的地物品無法承受來源物品重量
            _destination[j] =  _source[i - 1];
            _source[i - 1] = 0;
            break;
        }
        break;
    }
    printTowers();
    return 1; //搬運完成
}

int printTower(int *tower, int size){
    for(int i = 0; i < size; i++){
        printf("%d", tower[i]);
        if(i < size - 1) printf(",");
    }
    printf("\n");
    return 0;
}
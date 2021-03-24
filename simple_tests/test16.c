int f(int x, int y){
    do{
        x = x + y;
    } while (x < 2* y);
    return x;
}
int f(int a, int b){
    int x = 0;

    for(int i = 0; i < 10; i+=1){
        if(i==5){
            break;
        }

        x += a*b;
    }

    return x;
}
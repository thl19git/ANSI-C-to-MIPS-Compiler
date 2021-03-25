int f(int a){
    int b = 100;
    for(int i = 0; i < 10; i+=1){
        if(i==6){
            continue;
        }
        b-=a;
    }
    return b;
}

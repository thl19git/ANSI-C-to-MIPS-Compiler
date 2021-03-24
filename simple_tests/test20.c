int f(int z){
    int x = 7;
    while(z<5){
        z+=1;
        if(z==2){
            continue;
        }
        x += 1;
    }
    return x;
}
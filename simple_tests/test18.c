int f(int a, int b, int c, int d, int e){
    
    int x = 1;
    
    x += a;
    
    if(b){
        b = 5;
    } else {
        b = 2;
    }

    c += a * b;

    for(int i = 0; i < 10; i+=1){
        d += c;
    }
 
    while(e>0){
        int y = 0x1;
        x += d;
        e -= y;
    }
    
    return x;
}
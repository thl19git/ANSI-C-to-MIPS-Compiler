int f(int a){
    int i = 0;

    while(i<7){
        if(i==4){
            break;
        }
        i+=1;
    }

    return i+a;
}
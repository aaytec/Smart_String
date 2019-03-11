#include <stdlib.h>
#include <stdio.h>

#include "../../smart_string.h"

int main(int argc, char** argv){
    smart_zstring str = new_zstring("bcvggahk,  qbjrwvzfhsfifly,    bz,gaspdar\nusjitqrmhizqkmofmw,qcjtolcdddeoht\neyjgbdcrzs,  jcpivvnziprpziokrxkvjt\nlfamwhyw,lojdhya,ncpcdvkgvcmgxjmae\nyynakdsfykrciey,rjibtevi,elpqxuwvh\n");
    size_t count;
    smart_zstring* tokens = tokenize_zstring(str, ',', &count);
    printf("count = %ld\n", count);
    for(size_t i = 0; i < count; i++){
        printf("token[%ld] = %s\n", i, tokens[i]);
    }
}
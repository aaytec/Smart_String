#include <stdlib.h>
#include <stdio.h>

#include "../../src/smart_parse.h"

int main(int argc, char** argv){
    smart_str str = new_ss("bcvggahk,  qbjrwvzfhsfifly,    bz,gaspdar\n\nusjitqrmhizqkmofmw,,qcjtolcdddeoht\neyjgbdcrzs,  jcpivvnziprpziokrxkvjt\nlfamwhyw,lojdhya,ncpcdvkgvcmgxjmae\nyynakdsfykrciey,rjibtevi,elpqxuwvh\n");
    size_t count;
    smart_tok tokens = tokenize_ss(str, ',', &count);
    printf("count = %ld\n", count);
    for(size_t i = 0; i < count; i++){
        printf("token[%ld] = %s\n", i, tokens[i]);
    }

    delete_st(tokens);
    delete_ss(str);
}

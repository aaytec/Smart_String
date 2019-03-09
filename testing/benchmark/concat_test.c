#include <stdio.h>
#include <string.h>
#include "../../smart_string.h"


int main(int argc, char** argv){
	if(argc < 2){
		return 0;
	}

	smart_zstring buf = new_zstring("The Following is being concatinated: ");
	smart_zstring buf2 = new_zstring("x");

	// printf("Before concat:\n");
	// printf("buf = %s, size = %lu\n", buf, getlen_zstring(buf));	
	// printf("buf2 = %s, size = %lu\n", buf2, getlen_zstring(buf2));
	
	for(int i = 0; i < atoi(argv[1]); i++){
		buf = concat_zstring(buf, buf2);
	}

	// printf("buf = %s, size = %lu\n", buf, getlen_zstring(buf));
	// printf("buf2 = %s, size = %lu\n", buf2, getlen_zstring(buf2));

	delete_zstring(buf);
	delete_zstring(buf2);
        return 0;
}    

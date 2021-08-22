#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../src/smart_string.h"
//#include "catch.hpp"

int main(int argc, char** argv){
	if(argc < 2){
		printf("Usage : ./concat_test <num>\n");
		return 0;
	}

	smart_str buf = new_ss("The Following is being concatinated: ");
	smart_str buf2 = new_ss("x");

	printf("Before concat:\n");
	printf("buf size = %lu\n", getlen_ss(buf));
	// printf("buf2 = %s, size = %lu\n", buf2, getlen_ss(buf2));


	for(int i = 0; i < atoi(argv[1]); i++){
	
		// printf("start %d\n", i);
	
		buf = concat_ss(buf, buf2);
	
		// printf("end %d\n", i);
	}

	printf("After concat:\n");
	printf("buf size = %lu\n", getlen_ss(buf));
	// printf("buf2 = %s, size = %lu\n", buf2, getlen_ss(buf2));

	delete_ss(buf);
	delete_ss(buf2);
	return 0;
}

make
time ./concat_test 30000000
time ./concat_test2 30000000
valgrind ./concat_test 30000
valgrind ./concat_test2 30000

#!/bin/bash

###############################################################
#															  #
# copy tester directory in the root of your project directory #
#															  #
# cd into tester directory									  #
#															  #
# run with													  #
#	./test.sh n					  							  #
#	or														  #
#	bash test.s n				  							  #
# where n is the number of times you want to run the tests	  #
# if no n is given, all tests will be run once				  #
#															  #
# assumes the executable of your project is named philosphers #
#	if different change on									  #
#		line 11 in test.should.die.sh						  #
#		and													  #
#		line 12 in test_should_eat.sh						  #
#															  #
###############################################################

filename1="should_eat.txt"
filename2="should_die.txt"

echo "Recompiling your project..."
make re -C ..
echo

while read line2;
	do
	./test_should_die.sh $line2 $1
done < $filename2

while read line;
	do
	./test_should_eat.sh $line $1
done < $filename1

echo "Cleaning up..."
make fclean -C ..

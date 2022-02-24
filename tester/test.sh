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

filename1="should_die.txt"
filename2="should_eat.txt"

echo "Recompiling your project..."
make re -C .. > /dev/null
echo

while read line1;
	do
	./test_should_die.sh $line1 $1
done < $filename1

ret_value=$?
if [ $ret_value == 0 ];
	then
		echo -e "\033[32;1;4mPASSED FIRST TEST\033[0m\n"
	else
		echo -e "\033[31;1;4mFAILED\033[0m\n"
fi

while read line2;
	do
	./test_should_eat.sh $line2 $1
done < $filename2

ret_value=$?
if [ $ret_value == 0 ];
	then
		echo -e "\033[32;1;4mPASSED SECOND TEST\033[0m\n"
	else
		echo -e "\033[31;1;4mFAILED\033[0m\n"
fi

echo "Cleaning up..."
make fclean -C .. > /dev/null

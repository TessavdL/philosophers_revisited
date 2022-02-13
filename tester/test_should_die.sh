#!/bin/bash

function execute_tester() {
result=0
local numberof_meals_eaten
local number_of_philosophers=$1
local time_until_death=$2
local time_to_eat=$3
local time_to_sleep=$4
local number_of_meals=$5
../philosophers $number_of_philosophers $time_until_death $time_to_eat $time_to_sleep $number_of_meals > output2
local str=$(grep < output2 " has died")
if [ "$str" ];
	then
	echo "$str - OK!"
	else
	echo "NO"
	result=1
fi
}

if [ $6 ]
	then
		n=$6
	else
		n=1
fi

echo "Testing "$1" "$2" "$3" "$4" "$5""
for ((count=1; count<=$n; count++))
	do
	execute_tester "$1" "$2" "$3" "$4" "$5"
done

rm -f output2

if [ $result -eq 0 ];
	then
		echo -e "ALL OK!\n"
	else
		echo -e "You fucking lobster\n"
		exit 1
fi

exit 0

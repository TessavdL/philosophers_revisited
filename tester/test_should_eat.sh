#!/bin/bash

function execute_tester() {
result=0
local str
local numberof_meals_eaten
local number_of_philosophers=$1
local time_until_death=$2
local time_to_eat=$3
local time_to_sleep=$4
local number_of_meals=$5
../philosophers $number_of_philosophers $time_until_death $time_to_eat $time_to_sleep $number_of_meals > output
for ((i=1; i<=number_of_philosophers; i++))
	do
	str=$i" is eating"
	number_of_meals_eaten=$(grep < output "$str" | wc -l)
	if [ $number_of_meals_eaten -eq $number_of_meals ];
		then
			echo "Philosopher $i has eaten $number_of_meals times - OK!"
		else
			echo "NO"
			result=1
			break
	fi
done
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

if [ $result -eq 0 ];
	then
		echo "ALL OK!"
	else
		echo "You fucking lobster"

fi

rm -f output

echo

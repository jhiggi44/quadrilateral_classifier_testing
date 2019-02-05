#!/bin/bash
export set PATH=$PATH:~/fuzz
for i in `seq 0 999`;
do
    ./detectShape < "automated_testing/test_files/test$i.txt" > "automated_testing/output_files/output$i.txt"
done
COUNTER=0
for i in `seq 0 399`;
do
    ./detectShape < "automated_testing/modified_files/modified$i.txt" > "automated_testing/oracle_files/oracle$i.txt"
    diff automated_testing/output_files/output$i.txt automated_testing/oracle_files/oracle$i.txt >> "automated_testing/results/negative.txt"
    error=$?
    if [ $error -eq 0 ]
    then
    echo "test $i passed" >> "automated_testing/results/positive.txt"
    elif [ $error -eq 1 ]
    then
    COUNTER=$[$COUNTER +1]
    echo "test $i failed" >> "automated_testing/results/negative.txt"
    else
    echo "test $i didn't run properly"
    fi
done
for i in `seq 400 549`;
do
    diff automated_testing/output_files/output$i.txt automated_testing/err_keys/err1.txt >> "automated_testing/results/negative.txt"
    error=$?
    if [ $error -eq 0 ]
    then
    echo "test $i passed" >> "automated_testing/results/positive.txt"
    elif [ $error -eq 1 ]
    then
    COUNTER=$[$COUNTER +1]
    echo "test $i failed" >> "automated_testing/results/negative.txt"
    else
    echo "test $i didn't run properly"
    fi
done
for i in `seq 550 699`;
do
    diff automated_testing/output_files/output$i.txt automated_testing/err_keys/err2.txt >> "automated_testing/results/negative.txt"
    error=$?
    if [ $error -eq 0 ]
    then
    echo "test $i passed" >> "automated_testing/results/positive.txt"
    elif [ $error -eq 1 ]
    then
    COUNTER=$[$COUNTER +1]
    echo "test $i failed" >> "automated_testing/results/negative.txt"
    else
    echo "test $i didn't run properly"
    fi
done
for i in `seq 700 849`;
do
    diff automated_testing/output_files/output$i.txt automated_testing/err_keys/err3.txt >> "automated_testing/results/negative.txt"
    error=$?
    if [ $error -eq 0 ]
    then
    echo "test $i passed" >> "automated_testing/results/positive.txt"
    elif [ $error -eq 1 ]
    then
    COUNTER=$[$COUNTER +1]
    echo "test $i failed" >> "automated_testing/results/negative.txt"
    else
    echo "test $i didn't run properly"
    fi
done
for i in `seq 850 999`;
do
    diff automated_testing/output_files/output$i.txt automated_testing/err_keys/err4.txt >> "automated_testing/results/negative.txt"
    error=$?
    if [ $error -eq 0 ]
    then
    echo "test $i passed" >> "automated_testing/results/positive.txt"
    elif [ $error -eq 1 ]
    then
    COUNTER=$[$COUNTER +1]
    echo "test $i failed" >> "automated_testing/results/negative.txt"
    else
    echo "test $i didn't run properly"
    fi
done
if [[ $COUNTER -gt 0 ]]
then
echo "Error"
exit 1
elif [[ $COUNTER -eq 0 ]]
then
echo "OK"
exit 0
fi


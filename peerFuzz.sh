#!/bin/bash
COUNTER=0
for i in `seq 0 4999`;
do
    ./detectShape < "automated_testing/test_files/test$i.txt" > "automated_testing/output_files/output$i.txt"
    ./detectShapePeer < "automated_testing/test_files/test$i.txt" > "automated_testing/peer_output/output$i.txt"
    diff automated_testing/output_files/output$i.txt automated_testing/peer_output/output$i.txt >> "automated_testing/results/negative.txt"
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


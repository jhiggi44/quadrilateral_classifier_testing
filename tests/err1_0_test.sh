./detectShape < test_suite/err1_0.txt > test_output/err1_0_output.txt
diff test_output/err1_0_output.txt test_answers/err1_key.txt
error=$?
if [ $error -eq 0 ]
then
echo "test passed"
elif [ $error -eq 1 ]
then
echo "test failed"
exit 1
else
echo "test didn't run properly"
exit 1
fi

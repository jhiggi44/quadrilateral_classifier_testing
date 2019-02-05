./detectShape < coverage_testing/test_suite/err1_1.txt > coverage_testing/test_output/err1_1_output.txt
diff coverage_testing/test_output/err1_1_output.txt coverage_testing/test_answers/err1_key.txt
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

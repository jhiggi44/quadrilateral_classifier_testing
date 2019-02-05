./detectShape < coverage_testing/test_suite/err3_0.txt > coverage_testing/test_output/err3_0_output.txt
diff coverage_testing/test_output/err3_0_output.txt coverage_testing/test_answers/err3_key.txt
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

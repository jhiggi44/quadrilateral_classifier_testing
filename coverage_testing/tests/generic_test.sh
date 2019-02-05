./detectShape < coverage_testing/test_suite/generic_tests.txt > coverage_testing/test_output/generic_output.txt
diff coverage_testing/test_output/generic_output.txt coverage_testing/test_answers/generic_expected.txt
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

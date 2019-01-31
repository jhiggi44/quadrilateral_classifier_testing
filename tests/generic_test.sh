./detectShape < test_suite/generic_tests.txt > test_output/generic_output.txt
diff test_output/generic_output.txt test_answers/generic_expected.txt
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

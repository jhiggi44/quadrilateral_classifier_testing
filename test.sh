./detectShape < input.txt > output.txt
diff output.txt expected.txt
error=$?
if [ $error -eq 0 ]
then
echo "test passed"
elif [ $error -eq 1 ]
then
echo "test failed"
else
echo "test didn't run properly"
fi

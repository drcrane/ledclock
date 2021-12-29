#!/bin/busybox ash
echo "Running unit tests:"

echo "X" > testsrc/tests.log

VALGRIND=valgrind

for i in testsrc/*_tests
do
	if test -f $i
	then
		if $VALGRIND ./$i 2>> testsrc/tests.log
		then
			echo $i PASS
		else
			echo "ERROR in test $i: here's testsrc/tests.log"
			echo "------"
			tail testsrc/tests.log
			exit 1
		fi
	fi
done

echo ""


#!/usr/bin/env python
import subprocess

passed = 0

n_tests = 7;

# Run a for loop of tests.
for i in range(1,n_tests+1):
    print "Running test " + str(i) + "... "
    # Run case i, redirect output into $.out
    subprocess.call("./test_driver " + str(i) + " > " + str(i) + ".out",shell=True)
    # Compare output to the ground truth.
    rt = subprocess.call("diff -b " + str(i) + ".out " + str(i) + ".gt > /dev/null",shell=True);
    subprocess.call("rm " + str(i) + ".out",shell=True)
    if rt == 0:
        passed += 1
        print "passed"
    else:
        print "failed"




print "Passed " + str(passed) + " of " + str(n_tests) + " tests"

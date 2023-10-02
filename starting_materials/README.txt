In this directory, you should write the program `scheduler.c` and compile it into the binary `scheduler` (e.g., `gcc -o scheduler scheduler.c -Wall -Werror`). You should do it inside the Ubuntu machine you have setup, as grading will be done so inside the Ubuntu.

After doing so, you can run the tests from this directory by running the
`./run_tests.sh` script. If all goes well, you will see standard output that indicate that all tests are passed.

Note that the test cases are expecting exact matches in string formatting and whitespace. To confirm if that is the cause of any mismatch, you can change the run_tests.sh program to use "--ignore-all-space" on the lines with the diff command to see if they then pass. If so, you probably have an extra space somewhere, perhaps before the newline character.

Passing all tests are not sufficient to obtain all points for this assignment. As an example, any assignment in which hardcodes the expected output to pass the test case will lead to point deductions.





-run learner-
$ make learn

-run jumper with current best torques produced by the learner-
$ make jump

-standing animation-
$ make sample1

-quick jumping animation-
$ make sample2

-jumping and landing animation-
$ make sample3


NOTE:
When the learner is running, it frequently updates the file "output.txt" with the best list of torques found. You can run "make jump", which reads in the "output.txt" as input torques, anytime while the learner is running, or whenever an "output.txt" file exists.

#!/bin/bash

InhDir=data/Phase5/Inherited
InhInpDir=data/Phase5/Inherited/Inherited-InputSet
InhAnsDir=data/Phase5/Inherited/Inherited-AnswerSet
NewDir=data/Phase5/New
NewInpDir=data/Phase5/New/New-InputSet
NewAnsDir=data/Phase5/New/New-AnswerSet

for source in `ls $InhDir/*.c`; do
  echo $source
  a=$(basename $source)
  b=${a%.c}
  cp $source test.c
  ./translate < test.c > test.s
  echo $?
    cp $InhAnsDir/$b.ans test.ans
    ts=$InhInpDir/$b.in
    if [ -f $ts ]; then
      spim -stat_file spimstat -file test.s < $ts 1>spimout 2>quiet
    else
      spim -stat_file spimstat -file test.s 1>spimout 2>quiet
    fi
    diff spimout test.ans
    if [ $? -ne 0 ]; then
      result=1
    fi
  echo $result
  
done


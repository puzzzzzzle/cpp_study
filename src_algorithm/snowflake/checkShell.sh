#!/bin/bash

EXEC_PARA="./algorithm_snowflake"

rm -rvf *.log
for ((i=0;i<100;++i));
do
  echo no run at $i
  ${EXEC_PARA} >> run_log.log
  if [[  $? -ne 0 ]]
  then
    echo "one error happened at " $i |tee -a error.log
  fi
done

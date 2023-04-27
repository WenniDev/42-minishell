#!/bin/bash

MINISHELL=../minishell

LOG_FILE=./log.txt
ERROR_FILE=./error.txt

SAVE_FILE=./pid.txt

INPUT_FILE=bridge.fifo

function get_diff
{
  if [[ "$1" == "$2" ]]
  then
    echo "Test pass"
  else
    echo "Test not pass"
  fi
}

function exec_cmd
{
  echo "$1" > $INPUT_FILE
  sleep 1
  if [[ "$2" == "OK" ]]; then
    get_diff "$(tail -1 $LOG_FILE)" "spash: command not found: $1"
  fi
  if [[ "$2" == "KO" ]]; then
    get_diff "$(tail -1 $ERROR_FILE)" "spash: command not found: $1"
  fi
}

rm -f $INPUT_FILE
rm -f $SAVE_FILE
mkfifo $INPUT_FILE
cat > $INPUT_FILE &
echo $! > $SAVE_FILE
echo "Minishell init finish"

$MINISHELL 1> $LOG_FILE 2>$ERROR_FILE < $INPUT_FILE &
echo "Minishell started"

exec_cmd "pwd" "KO"

echo "Minishell killed"

rm -rf $INPUT_FILE $SAVE_FILE
#! /usr/bin/env bash

MINISHELL=../minishell
TEST_FILE=./minitest.csv
LOG_FILE=./log.txt

INPUT_FILE=bridge.fifo

exec_cmd()
{
  command=$1
  expected=$2

  echo "$command" > $INPUT_FILE
  result=$(cat $LOG_FILE | tail -n2 | head -1)
  echo "$result = $expected"
  if [ "$result" = "$expected" ]
  then
    echo "Test pass"
  else
    echo "Test not pass"
  fi
  
}

killCmd() {
    kill "$1"
}

rm -f $INPUT_FILE
mkfifo $INPUT_FILE
while true; do cat; done >$INPUT_FILE &
PID=$!
echo "Minishell init finish"

$MINISHELL > $LOG_FILE < $INPUT_FILE &
echo "Minishell started"


while read -r line || [ -n "$line" ]
do
    # Séparer les éléments de la ligne en utilisant le délimiteur ';'
    newline_string=$(echo "$line" | tr ',' '\n')
    readarray -t elements <<<"$newline_string"

    # Stocker chaque élément dans une variable séparée
    test_name=${elements[0]}
    command=${elements[1]}
    expected_result=${elements[2]}

    # Faire quelque chose avec chaque élément séparé
    echo " ---- $test_name ---- "
    exec_cmd "$command" "$expected_result"
    sleep 1
done < $TEST_FILE

killCmd $PID &

echo "Minishell killed"

rm -rf $INPUT_FILE
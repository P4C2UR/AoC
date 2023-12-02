#!/bin/env bash
priority() {
  if [[ $1 -ge 97 ]]; then
    echo "$(($1-97+1))"
  else
    echo "$(($1-65+27))"
  fi
}
sum=0
ssum=0
j=0
comb=""
first=""
second=""
for i in $(cat "$1"); do
  lines="$(echo "$i" | sed -E 's/(.)/\1\n/g')"

  n="$(((${#lines}+1)/4))"
  fhalf="$(echo "$lines" | head -n "$n" | sort | uniq)"
  shalf="$(echo "$lines" | tail -n "$n" | sort | uniq)"
  val=$(priority $(printf "%d\n" "'$(echo -e "$shalf\n$fhalf" | sort | uniq -d)"))
  sum=$(($sum+$val))

  if [[ $j -eq 2 ]]; then
    second="$(echo "$lines" | sort | uniq)"
    ssum=$(($ssum+$(priority $(printf "%d\n" "'$(echo -e "$first\n$second" | sort | uniq -d)"))))
    j=0
  elif [[ $j -eq 1 ]]; then
    second="$lines"
    first="$(echo -e "$(echo "$second" | sort | uniq)\n$(echo "$first" | sort | uniq)" | sort | uniq -d)"
    j=2
  else
    first="$lines"
    j=1
  fi
done
echo "First half:"
echo "$sum"
echo "Second half:"
echo "$ssum"


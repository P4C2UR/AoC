#!/bin/env -S awk -f
{
	split($0,pair,",")
	split(pair[1],first,"-")
	split(pair[2],second,"-")
	if(first[2]>=second[1]&&first[1]<=second[2]) {
		ssum+=1
		if((first[1]<=second[1]&&first[2]>=second[2])||(second[1]<=first[1]&&second[2]>=first[2]))
			sum+=1
	}
}
END {
	printf("First half:\n%d\nSecond half:\n%d\n",sum,ssum)
}

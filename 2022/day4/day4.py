import sys
ssum=0
sum=0
for line in open(sys.argv[1]):
	a=line[:line.find(",")]
	b=line[line.find(",")+1:]
	r1=[int(a[:a.find("-")]),int(a[a.find("-")+1:])]
	r2=[int(b[:b.find("-")]),int(b[b.find("-")+1:])]
	if(r1[1]>=r2[0] and r1[0]<=r2[1]):
	    ssum+=1
	    if((r1[0]<=r2[0] and r1[1]>=r2[1]) or (r2[0]<=r1[0] and r2[1]>=r1[1])):
	        sum+=1
print(sum)
print(ssum)

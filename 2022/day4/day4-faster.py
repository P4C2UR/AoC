import time
import sys

def subtonum(str, i):
  c2=ord(str[i+1])-ord('0')
  if c2>=0:
    return (ord(str[i])-ord('0'))*10+c2
  else:
    return ord(str[i])-ord('0')

times = []

for _ in range(5):
  lines = open(sys.argv[1])
  ssum=0
  fsum=0
  start = time.time()


  for line in lines:
    after=line.find(',',3)+1
    f1=subtonum(line, 0)
    f2=subtonum(line,line.find("-",1)+1)
    s1=subtonum(line, after)
    s2=subtonum(line,line.find("-", after)+1)
    if(f2>=s1 and f1<=s2):
        ssum+=1
        if((f1<=s1 and f2>=s2) or (s1<=f1 and s2>=f2)):
          fsum+=1
  end=time.time()
  times.append(end-start)

print(f"ans: {ssum}")
print("Times:")
for num, time in enumerate(times):
    print(f"{num}: {time}")
print(f"Min: {min(times)}\n"
      f"Mean: {sum(times)/len(times)}\n"
      f"Max: {max(times)}")


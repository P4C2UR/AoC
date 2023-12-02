const fs = require('fs');
const readline = require('readline');

if(process.argv.length<3) {
  console.log("Pass path to data file as argument");
  return 1;
}
var rd = readline.createInterface({
  input: fs.createReadStream(argv[2]),
});
let acc = 0
rd.on('line',
  line => {
    const labeled = line.split(": ")
    const number = parseInt(labeled[0].split(" ")[1])
    const games = labeled[1].split("; ")
    const takes = games.map(x=>x.split(", ").map(y=>y.split(" "))).flat()
    .map(x=>[parseInt(x[0]),x[1]])
    .reduce((acc,tuple)=>(
      (tuple[1][0]=='r')
      ?(tuple[0]>acc[0])?[tuple[0],acc[1],acc[2]]:acc
      :(tuple[1][0]=='g')
        ?(tuple[0]>acc[1])?[acc[0],tuple[0],acc[2]]:acc
        :(tuple[0]>acc[2])?[acc[0],acc[1],tuple[0]]:acc),[0,0,0])
    const power = takes[0]*takes[1]*takes[2]
    acc += power
  })
rd.on('close',
  ()=>console.log(acc))

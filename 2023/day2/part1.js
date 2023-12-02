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
    const takes = games.map(x=>x.split(", ").map(y=>y.split(" "))
    .map(tuple=>(tuple[1][0]=='r')?tuple[0]<=12:(tuple[1][0]=='g')?tuple[0]<=13:tuple[0]<=14)
    .reduce((acc,x)=>acc&&x,true))
    .reduce((acc,x)=>acc&&x,true)
    if(takes) acc += number;
  })
rd.on('close',
  ()=>console.log(acc))

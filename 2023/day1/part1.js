#!/bin/env node
const fs = require('fs');
const readline = require('readline');

function asDigit(x) {
  return x.charCodeAt(0)-'0'.charCodeAt(0)
}
if(process.argv.length<3) {
  console.log("Pass path to data file as argument");
  return 1;
}
var rd = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});
var acc = 0;
rd.on('line',
  line => {
    const chars = Array.from(line).filter(char=>char>='0'&&char<='9');
    acc += asDigit(chars[0])*10+asDigit(chars[chars.length-1])
  })
rd.on('close', ()=>console.log(acc))

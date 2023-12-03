#!/bin/env node
const fs = require('fs');
const readline = require('readline');

if(process.argv.length<3) {
  console.log("Pass path to data file as argument");
  return 1;
}
var rd = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});
let prev = ""
let curr = ""

function isDigit(x) { return x>='0'&&x<='9' }
function parseNumber(arr, i) {
  console.log(arr.charAt(i))
}

rd.on('line',
  line => {
    if(prev=="") {
      prev = line
      return
    } else if(curr=="") {
      curr = line
      return
    }
    for(let i=0;i<line.length;i++) {
      if(!isDigit(line[i]) && line[i]!='.') {
        if(i>0) {
          if(isDigit(prev.charAt(i-1)))
            parseNumber(prev, i-1)
          if(isDigit(curr.charAt(i-1)))
            parseNumber(curr, i-1)
          if(isDigit(line.charAt(i-1)))
            parseNumber(line, i-1)
        }
        if(isDigit(prev.charAt(i)))
          parseNumber(prev, i)
        if(isDigit(line.charAt(i)))
          parseNumber(line, i)
        if(i+1<line.length) {
          if(isDigit(prev.charAt(i+1)))
            parseNumber(prev, i+1)
          if(isDigit(curr.charAt(i+1)))
            parseNumber(curr, i+1)
          if(isDigit(line.charAt(i+1)))
            parseNumber(line, i+1)
        }
      }
    }
  })

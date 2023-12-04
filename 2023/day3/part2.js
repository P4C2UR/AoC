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
let acc = 0;
let num;
let numbers = []

function isDigit(x) { return x>='0'&&x<='9' }
function parseNumber(arr, i) {
  let ret = 0;
  while(isDigit(arr[i])) {
    i--
    if(i==-1) break;
  }
  i++;
  while(isDigit(arr[i])) {
    ret*=10;
    ret+=arr[i]-'0';
    arr[i] = '.';
    i++;
  }
  return ret
}

rd.on('line',
  line => {
    line = Array.from(line)
    if(prev=="") {
      prev = line
      return
    } else if(curr=="") {
      curr = line
      return
    }
    for(let i=0;i<line.length;i++) {
      num = 0
      if(curr[i]=='*') {
        if(i>0) {
          if(isDigit(prev[i-1]))
            numbers[num++] = parseNumber(prev, i-1)
          if(isDigit(curr[i-1]))
            numbers[num++] = parseNumber(curr, i-1)
          if(isDigit(line[i-1]))
            numbers[num++] = parseNumber(line, i-1)
        }
        if(isDigit(prev[i]))
          numbers[num++] = parseNumber(prev, i)
        if(isDigit(line[i]))
          numbers[num++] = parseNumber(line, i)
        if(i+1<line.length) {
          if(isDigit(prev[i+1]))
            numbers[num++] = parseNumber(prev, i+1)
          if(isDigit(curr[i+1]))
            numbers[num++] = parseNumber(curr, i+1)
          if(isDigit(line[i+1]))
            numbers[num++] = parseNumber(line, i+1)
        }
      }
      if(num == 2)
        acc += numbers[0]*numbers[1]
    }
    prev = curr;
    curr = line;
  })

rd.on('close', ()=> {
  num = 0
  for(let i=0;i<curr.length;i++) {
    if(curr[i]=='*') {
      if(i>0) {
        if(isDigit(prev[i-1]))
          numbers[num++] = parseNumber(prev, i-1)
        if(isDigit(curr[i-1]))
          numbers[num++] = parseNumber(curr, i-1)
      }
      if(isDigit(prev[i]))
        numbers[num++] = parseNumber(prev, i)
      if(i+1<curr.length) {
        if(isDigit(prev[i+1]))
          numbers[num++] = parseNumber(prev, i+1)
        if(isDigit(curr[i+1]))
          numbers[num++] = parseNumber(curr, i+1)
      }
    }
  }
  if(num == 2)
    acc += numbers[0]*numbers[1]
  console.log(acc)
})

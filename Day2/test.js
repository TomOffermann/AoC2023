const fs = require("fs");

let input = fs.readFileSync("./input.txt").toString();
input = input.split("\n");
input = input.map((e) => e.split(":")[1].split(";"));
input = input.map((e) => e.map((f) => f.split(",")));
input = input.map((e) => e.map((f) => f.map((g) => g.trim().split(" "))));

let isValid = (set) => {
  return set["red"] <= 12 && set["green"] <= 13 && set["blue"] <= 14;
};

let power = (set) => {
  return set["red"] * set["blue"] * set["green"];
}

let result1 = 0;
let result2 = 0;

for (let i = 0; i < input.length; i++) {
  let fset = {
    red: 0,
    green: 0,
    blue: 0,
  };
  for (let set = 0; set < input[i].length; set++) {
    for (let element = 0; element < input[i][set].length; element++) {
      switch (input[i][set][element][1]) {
        case "red":
          fset["red"] = Math.max(fset["red"], parseInt(input[i][set][element][0]));
          break;
        case "green":
          fset["green"] = Math.max(fset["green"], parseInt(input[i][set][element][0]));
          break;
        case "blue":
          fset["blue"] = Math.max(fset["blue"], parseInt(input[i][set][element][0]));
          break;
      }
    }
  }
  if (isValid(fset)) {
    result1 += i + 1;
  }
  result2 += power(fset);
}

console.log(result1, result2);

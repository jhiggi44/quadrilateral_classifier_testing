#!/usr/bin/env node
const fs = require('fs');

function generateAllTests() {
    generateErrKeys();
    generateValidTests(400, 0);
    generateErr1Tests(150, 400);
    generateErr2Tests(150, 550);
    generateErr3Tests(150, 700);
    generateErr4Tests(150, 850);
}

//generates test files with valid quads, scales it down, and generates an oracle.txt to compare
function generateValidTests(numOfFiles, index) { 
    for (let i = index; i < index + numOfFiles; i++) {
        let variationOfSquare = makeVariationOfASquare();
        fs.writeFile(`automated_testing/test_files/test${i}.txt`, variationOfSquare, (err) => {
            if (err) throw err;
            let oracle = scaleDown(variationOfSquare);
            fs.writeFile(`automated_testing/modified_files/modified${i}.txt`, oracle, (err) => {
                if (err) throw err;
            });
        });
    }
}

// generates the keys to check errors against
function generateErrKeys() {
    for (let i = 1; i < 5; i++) {
        fs.writeFile(`automated_testing/err_keys/err${i}.txt`, `error ${i}\n`, (err) => {
            if (err) throw err;
        });
    }
}

function generateErr1Tests(numOfFiles, index) {
    for (let i = index; i < index + numOfFiles; i++) {
        fs.writeFile(`automated_testing/test_files/test${i}.txt`, generateGibberish(), (err) => {
            if (err) throw err;
        });
    }
}

function generateErr2Tests(numOfFiles, index) {
    for (let i = index; i < index + numOfFiles; i++) {
        fs.writeFile(`automated_testing/test_files/test${i}.txt`, plotCoinciding(), (err) => {
            if (err) throw err;
        });
    }
}

function generateErr3Tests(numOfFiles, index) {
    for (let i = index; i < index + numOfFiles; i++) {
        fs.writeFile(`automated_testing/test_files/test${i}.txt`, plotCrossing(), (err) => {
            if (err) throw err;
        });
    }
}

function generateErr4Tests(numOfFiles, index) {
    for (let i = index; i < index + numOfFiles; i++) {
        fs.writeFile(`automated_testing/test_files/test${i}.txt`, plotColinear(), (err) => {
            if (err) throw err;
        });
    }
}

// used to make a smaller version of a quad. Used as an oracle for testing
function scaleDown(line) {
    let cords = line.split(" ");
    let newLine = "";
    cords[0] -= 10;
    cords[2] -= 10;
    cords[3] -= 10;
    cords[5] -= 10;
    for (let i = 0; i < cords.length - 1; i++) {
        newLine += `${cords[i]} `;
    }
    newLine += `${cords[cords.length-1]}\n`;
    return newLine;
}

//will trigger error 4
function plotColinear() {
    let x1 = getRandomNumBetween(1, 5);
    let y1 = x1;
    let x2 = x1 + x1;
    let y2 = x2;
    let x3 = x2 + x1;
    let y3 = x3;
    return `${x1} ${y1} ${x2} ${y2} ${x3} ${y3}\n`
}

// trigger error 2
function plotCoinciding() {
    let p1 = getRandomNumBetween(0, 100);
    let p2 = getRandomNumBetween(0, 100);
    if (p1 % 3 == 0) {
        return `${p1} ${p2} ${p1} ${p2} ${getRandomNumBetween(0, 80)} ${getRandomNumBetween(0, 80)}\n`;
    } else if (p1 % 2 ==0) {
        return `${p1} ${p2} ${getRandomNumBetween(0, 80)} ${getRandomNumBetween(0, 80)} ${p1} ${p2} \n`;
    } else {
        return `${getRandomNumBetween(0, 80)} ${getRandomNumBetween(0, 80)} ${p1} ${p2} ${p1} ${p2} \n`;
    }
}

// trigger error 3
function plotCrossing() {
    let x1 = getRandomNumBetween(70, 100);
    let y1 = getRandomNumBetween(50, 100);
    let x2, y2, x3, y3;
    if (y1 > 75) {
        x2 = getRandomNumBetween(0, 50);
        y2 = getRandomNumBetween(76, 100);
        x3 = getRandomNumBetween(70, x1);
        y3 = getRandomNumBetween(0, 40);
    } else {
        x2 = getRandomNumBetween(70, x1);
        y2 = getRandomNumBetween(0, 40);
        x3 = getRandomNumBetween(0, 50);
        y3 = getRandomNumBetween(76, 100);
    }
    return `${x1} ${y1} ${x2} ${y2} ${x3} ${y3}\n`;
}

// this will make quads, traps, squares, rectangles, rhombus and kites.
function makeVariationOfASquare() {
    let x1 = getRandomNumBetween(20, 90);
    let y1 = 0;
    let x2 = x1;
    let y2 = x1;
    let x3 = 0;
    let y3 = x1;
    let moveX = getRandomNumBetween(-20, 20);
    let moveY = getRandomNumBetween(-20, 20);
    if (moveX > 5) {
        x1 += getRandomNumBetween(0, 8);
        x2 += getRandomNumBetween(0, 8);
        x3 += getRandomNumBetween(0, 8);
    } else if (moveX < -5) {
        x1 -= getRandomNumBetween(0, 8);
        x2 -= getRandomNumBetween(0, 8);
    } 
    if (moveY > 5) {
        y1 += getRandomNumBetween(0, 8);
        y2 += getRandomNumBetween(0, 8);
        y3 += getRandomNumBetween(0, 8);
    } else if (moveX < -5) {
        y2 -= getRandomNumBetween(0, 8);
        y3 -= getRandomNumBetween(0, 8);
    } 
    return `${x1} ${y1} ${x2} ${y2} ${x3} ${y3}\n`;
}

// will trigger mostly error 1
function generateGibberish() {
    let cords = "";
    for (let i = 0; i < getRandomNumBetween(1, 7); i++) {
        cords += String.fromCharCode(getRandomNumBetween(31, 127)) + " ";
    }
    return cords += String.fromCharCode(getRandomNumBetween(31, 127)) + "\n";
}

let getRandomNumBetween = function(begin, end) {
    return Math.floor((Math.random() * (end - begin)) + begin);
}

generateAllTests();

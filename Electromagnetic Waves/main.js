const width = 600;
const height = 600;

// Determines wavelength, lamba = 1 / SCALE
const SCALE = 5;

// y level where 'detector' is, amplitudes graphed from this level
const Y_BASE = 30;
const BAR_HEIGHT = 40;
const dx = 2;
let dt = 0;

let x1;
let y1;
let x2;
let y2;

let t = 0;

function setup() {
    createCanvas(width, height);
    pixelDensity(1);
    rectMode(CENTER);
    x1 = 250;
    y1 = height;
    x2 = x1 + (SCALE * TWO_PI) * 2;
    y2 = height;
    dt = PI / 8;
    frameRate(10);
    textSize(16);
}

function draw() {
    strokeWeight(.5);
    fill(100, 100, 255);

    loadPixels();

    for (let i = 0; i < width; i++) {
        for (let j = 0; j < height; j++) {
            let col1 = cos(dist(x1, y1, i, j) / SCALE - t);
            let col2 = cos(dist(x2, y2, i, j) / SCALE - t);
            let col = map(col1 + col2, -2, 2, 100, 150);
            setPixel(i, j, col, col, col, 255);
        }
    }
    
    updatePixels();

    plotCurrentAmp(Y_BASE);
    plotInterferenceAmp(Y_BASE);

    stroke(0, 255, 0);
    line(0, Y_BASE, width, Y_BASE);
    stroke(200, 200, 0, 200);
    line(0, Y_BASE + 10, width, Y_BASE + 10);
    line(0, Y_BASE - 10, width, Y_BASE - 10);
    stroke(0);

    writeCaptions();
    t += dt;
}

function setPixel(x, y, r, g, b, a) {

    let index = (x + y * width) * 4;
    pixels[index] = r;
    pixels[index+1] = g;
    pixels[index+2] = b;
    pixels[index+3] = a;
}

function getPixel(x, y) {

    // Return R, G, B values for pixel (x, y)
    let index = (x + y * width) * 4;
    return createVector(pixels[index], pixels[index+1], pixels[index+2])
}

function plotInterferenceAmp (yLevel) {
    const eps = 0.05;

    for (let i = 0; i < width; i += dx) {
        let r2 = dist(i, yLevel, x2, y2);
        let r1 = dist(i, yLevel, x1, y1);
        let phi = (1 / SCALE) * abs(r2 - r1);
        let E = 2 * abs(cos(phi / 2));
        fill(250, 50, 50, 80);
        rect(i, yLevel + 50, 2, map(E, 0, 2, 0, BAR_HEIGHT));
        if (E < eps)
            stroke(200, 200, 0, 100);
            line(i, 0, i, height);
            stroke(0);
    }
}

function plotCurrentAmp(yLevel) {
    for (let i = 0; i < width; i += dx) {
        fill(50, 50, 255, 100);
        rect(i, yLevel, 2, map(getPixel(i, yLevel).x, 100, 150, 0, BAR_HEIGHT));
    }
}

function keyPressed() {
    let increment = (1 / SCALE) * 50;
    switch (keyCode) {
        case RIGHT_ARROW: 
            x2 += increment;
            break;
        case LEFT_ARROW: 
            x2 -= increment;
            break;
        case 65: // 'a'
            x1 -= increment;
            break;
        case 68: // 'd'
            x1 += increment;
            break;
    }
}

function writeCaptions() {
    fill(255);
    text("Click anywhere to set focus", width - 200, height - 10);
    text("A and D move left source", 10, height - 30);
    text("← and → move right source", 10, height - 10);
    text("Blue graph shows amplitude at y=30", 10, 150);
    text("Red graph shows amplitude of interference at y = 30", 10, 170);
}
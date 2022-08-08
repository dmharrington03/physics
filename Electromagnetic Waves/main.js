const width = 600;
const height = 600;

const SCALE = 8;

function setup() {
    createCanvas(width, height);
    pixelDensity(1)
}

function draw() {
    background(0);
    fill(100);
    ellipse(width / 2, height / 2, 20);

    let x1 = 100;
    let y1 = height;
    let x2 = 500;
    let y2 = height;
    loadPixels();

    let topAmps = [];

    for (let i = 0; i < width; i++) {
        for (let j = 0; j < height; j++) {
            let col1 = sin(dist(x1, y1, i, j) / SCALE);
            let col2 = sin(dist(x2, y2, i, j) / SCALE);
            let col = map(col1 + col2, -2, 2, 100, 150);
            setPixel(i, j, col, col, col, 255);
        }
    }
    



    updatePixels();
}

function setPixel(x, y, r, g, b, a) {

    let index = (x + y * width) * 4;
    pixels[index] = r;
    pixels[index+1] = g;
    pixels[index+2] = b;
    pixels[index+3] = a;
}
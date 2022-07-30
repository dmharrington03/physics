const width = 600;
const height = 600;

// E Field Proportionality constant, equal to 1 / (4 * pi * epsilon_0)
const K = 1;

// Define point charge class
class PointCharge {
    // All calculations done in center-origin coordinates
    pos = createVector(0, 0);
    charge = 0;
    radius = 30;
    linesPerCharge = 6;
    startPoints = [];
    target;

    constructor(x, y, charge, target) {
        this.pos.x = x
        this.pos.y = y
        this.charge = charge;
        this.target = target; // p5 Vector
        //TODO convert target to center-origin
    }

    createStartPoints() {
        // Create start points for the field lines, in polar coordinates
        let n_lines = this.charge * this.linesPerCharge;
        let angle = TWO_PI / n_lines;

        for (let i = 0; i < n_lines; i++) {
            // Push cartesian coordinates to startPoints array
            this.startPoints.push(p5.Vector.mult(createVector(cos(angle), sin(angle)), this.radius));
        }
    }

    drawLines() {
        //  Loop through each start point:
        /*  Loop until off-screen or at end region
            Calculate E field normal vector 
            Move dR * Ehat and make new vertex */
    }

    isInBounds(positionVector) {
        // param positionVector: p5 Vector
        
        // Check off-screen
        let onScreen = (abs(positionVector.x) >= width / 2) || (abs(positionVector.y) >= height / 2);

        // Check if in range of target
        let displacement = p5.Vector.sub(this.target, positionVector);
        let inRange = displacement.mag() < this.radius;
        return onScreen || inRange;
    }

    dispay() {
        // Draw to the canvas
        fill(250, 50, 50);
        ellipse(this.pos.x, this.pos.y, this.radius, this.radius);
    }

    static toCornerOrigin(a, b) {
        // Given a point in center-origin coordinates, convert to upper-corner center
        return createVector(a + width / 2, height / 2 - b);
    }
}



function setup() {
    createCanvas(width, height);
}

function draw() {
    // Set origin to center of screen
    // translate(width/2, height/2); 
    // scale(1, -1);

    var source = new PointCharge(200, 200, 3);
    background(220);
    noStroke();
    fill(250, 50, 50);
    // ellipse(width / 2, height / 2, 30, 30);
    source.dispay();
    
}

function getEField(charge) {
    // param point: p5.Vector
    // param charge: float
    const displacement = createVector(mouseX, mouseY); // Assumes charge at (0, 0)
    displacement.div(1000);
    let EField = charge / pow(displacement.mag(), 2);
    return EField;
}
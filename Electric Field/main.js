const width = 600;
const height = 600;

// E Field Proportionality constant, equal to 1 / (4 * pi * epsilon_0)
const K = 1;

// Define point charge class
class PointCharge {
    // All calculations done in center-origin coordinates
    pos = createVector(0, 0);
    charge = 0;
    radius = 10;
    linesPerCharge = 3;
    startPoints = [];
    target;
    dR = 5;

    constructor(x, y, charge, target) {
        // all parameters should be center-origin
        this.pos.x = x
        this.pos.y = y
        this.charge = charge;
        this.target = target; // p5 Vector
        this.createStartPoints();
    }

    createStartPoints() {
        // Create start points for the field lines, in polar coordinates
        let n_lines = this.charge * this.linesPerCharge;
        let angle = TWO_PI / n_lines;

        for (let i = 0; i < n_lines; i++) {
            // Push cartesian coordinates to startPoints array
            let theta = angle * i;
            this.startPoints.push(p5.Vector.mult(createVector(cos(theta), sin(theta)), this.radius));
        }
        console.log(this.startPoints);
    }

    getEField(displacement) {
        // param displacement: p5.Vector
        // returns p5.Vector

        let EFieldMag = 10000 * this.charge / pow(displacement.mag(), 2);
        return p5.Vector.mult(displacement.normalize(), EFieldMag);
    }

    drawLines() {
        //  Loop through each start point:
        /*  Loop until off-screen or at end region
            Calculate E field normal vector 
            Move dR * Ehat and make new vertex */
        //TODO fix
        for (let i = 0; i < this.startPoints.length; i++) {
            
            let pt = createVector(this.startPoints[i].x, this.startPoints[i].y);
            console.log("pt" + i + " " + pt);
            for (let i = 0; i < 10; i++) {
                let EFieldUnit = this.getEField(p5.Vector.sub(pt, this.pos));
                let newPt = p5.Vector.add(pt, p5.Vector.mult(EFieldUnit, this.dR));

                let cPt = PointCharge.toCornerOrigin(pt);
                let cNewPt = PointCharge.toCornerOrigin(newPt);
                line(cPt.x, cPt.y, cNewPt.x, cNewPt.y);
                // ellipse(cPt.x, cPt.y, 5, 5);
                pt = newPt;
            }
            console.log("done")
        }
    }

    isInBounds(positionVector) {
        // param positionVector: p5 Vector
        
        // Check on-screen
        let onScreen = (abs(positionVector.x) <= width / 2) || (abs(positionVector.y) <= height / 2);

        // Check if not in range of target
        // let displacement = p5.Vector.sub(this.target, positionVector);
        // let notInRange = displacement.mag() > this.radius + 1;
        return onScreen;
    }

    dispay() {
        // Draw to the canvas
        fill(250, 50, 50);
        let cPos = PointCharge.toCornerOrigin(this.pos);
        ellipse(cPos.x, cPos.y, this.radius * 2);
    }

    static toCornerOrigin(a) {
        // Given a point in center-origin coordinates, convert to upper-corner center
        // param a: p5.Vector
        return createVector(a.x + width / 2, height / 2 - a.y);
    }
}


let source;

function setup() {
    createCanvas(width, height);
    source = new PointCharge(0, 0, 2, createVector(500, 500));
    noLoop();
}

function draw() {

    // Set origin to center of screen
    // translate(width/2, height/2); 
    // scale(1, -1);

    background(220);
    // noStroke();
    strokeWeight(2);
    fill(250, 50, 50);
    // ellipse(width / 2, height / 2, 30, 30);
    source.drawLines();
    source.dispay();
    
}


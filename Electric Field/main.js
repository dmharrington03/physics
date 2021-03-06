const width = 600;
const height = 600;

// E Field Proportionality constant, equal to 1 / (4 * pi * epsilon_0)
const K = 20000;


// Define point charge class
class PointCharge {
    // All calculations done in center-origin coordinates
    pos = createVector(0, 0);
    charge = 0;
    radius = 10;
    linesPerCharge = 4;
    startPoints = [];
    target = null;
    doDraw;
    dR = 5;

    constructor(x, y, charge, target) {
        // all parameters should be center-origin
        this.pos.x = x
        this.pos.y = y
        this.charge = charge;
        // if (target instanceof PointCharge)
        this.target = target;
        // throw "target not a PointCharge";
        this.createStartPoints();
    }

    update(movement=true) {
        // Run every frame
        if (movement && mousePressedInWindow())
            this.pos = PointCharge.toCenterOrigin(createVector(mouseX, mouseY));;
        this.startPoints = [];
        this.createStartPoints();
        /* If + always draw
        If 0 never draw
        If - only draw if other is - or 0 */
        this.doDraw = false;
        if (this.charge > 0)
            this.doDraw = true;
        else if (this.charge === 0)
            this.doDraw = false;
        else if (this.target.charge <= 0) // else this.charge < 0
            this.doDraw = true;

        if (this.doDraw)
            this.drawLines();
        this.dispay();
    }

    createStartPoints() {
        // Create start points for the field lines, in polar coordinates
        let n_lines = abs(this.charge) * this.linesPerCharge;
        let angle = TWO_PI / n_lines;

        for (let i = 0; i < n_lines; i++) {
            // Push cartesian coordinates to startPoints array
            let theta = angle * i;
            this.startPoints.push(
                p5.Vector.add(
                    p5.Vector.mult(createVector(cos(theta), sin(theta)), this.radius),
                    this.pos
                )
            );
        }
    }

    getEField(pt, otherCharge=null) {
        // param pt: p5.Vector
        // param otherCharge: PointCharge
        // returns p5.Vector
        let displacementSelf = p5.Vector.sub(pt, this.pos);

        let EFieldMagSelf = K * this.charge / pow(displacementSelf.mag(), 2);
        if (!otherCharge) {
            return p5.Vector.mult(displacementSelf.normalize(), EFieldMagSelf);
        } else {
            let displacementOther = p5.Vector.sub(pt, otherCharge.pos);
            let EFieldSelf = p5.Vector.mult(displacementSelf.normalize(), EFieldMagSelf);
            let EFieldMagOther = K * otherCharge.charge / pow(displacementOther.mag(), 2);
            let EFieldOther = p5.Vector.mult(displacementOther.normalize(), EFieldMagOther);
            return p5.Vector.add(EFieldOther, EFieldSelf);
        }
    }

    drawLines() {
        //  Loop through each start point:
        /*  Loop until off-screen or at end region
            Calculate E field normal vector 
            Move dR * Ehat and make new vertex */
        
        for (let i = 0; i < this.startPoints.length; i++) {
            
            let pt = createVector(this.startPoints[i].x, this.startPoints[i].y);
            let j = 0;

            while (!this.outOfBounds(pt)) {
                
                let EFieldUnit = this.getEField(pt, this.target).normalize();
                let newPt;

                /* Reverse if both are negative or one is negative and the other is zero */
                let reverseDir = this.target.charge <= 0 && this.charge < 0;
                if (reverseDir)
                    EFieldUnit.mult(-1);

                // Edge case EFieldUnit == 0, no movement will happen:
                if (EFieldUnit.mag() <= 0.01)
                    newPt = p5.Vector.add(pt, p5.Vector.mult(createVector(2, 1), this.dR));
                else
                    newPt = p5.Vector.add(pt, p5.Vector.mult(EFieldUnit, this.dR));

                let cPt = PointCharge.toCornerOrigin(pt);
                let cNewPt = PointCharge.toCornerOrigin(newPt);
                stroke(4)
                line(cPt.x, cPt.y, cNewPt.x, cNewPt.y);
                
                // Calculate points to construct triangle arrow
                let cPtNormal1 = PointCharge.toCornerOrigin(
                    p5.Vector.add(p5.Vector.rotate(p5.Vector.sub(newPt, pt), - PI/2), pt)
                );
                let cPtNormal2 = PointCharge.toCornerOrigin(
                    p5.Vector.add(p5.Vector.rotate(p5.Vector.sub(newPt, pt), PI/2), pt)
                );
                let cLagPt =  PointCharge.toCornerOrigin(
                    p5.Vector.add(p5.Vector.rotate(p5.Vector.sub(newPt, pt), PI), pt)
                );
                
                // Draw every 20 dR, offset so it doesn't draw on top of charge circle body
                noStroke();
                fill(0);
                if (j % 20 === 15) {
                    if (reverseDir) {
                        triangle(
                            cPtNormal1.x, cPtNormal1.y,
                            cLagPt.x, cLagPt.y,
                            cPtNormal2.x, cPtNormal2.y
                        );
                    } else {
                        triangle(
                            cPtNormal1.x, cPtNormal1.y,
                            cNewPt.x, cNewPt.y,
                            cPtNormal2.x, cPtNormal2.y
                        );
                    }
                }

                // Check for cycles, occurs if same charge field lines meet colinearly
                if (j++ > 10 * width / this.dR)
                    break

                pt = newPt;
            }
        }
    }

    outOfBounds(positionVector) {
        // param positionVector: p5 Vector
        
        let inBounds = (abs(positionVector.x) <= width / 2 + 300) && (abs(positionVector.y) <= height / 2 + 300);
        let isAtTarget = p5.Vector.dist(positionVector, this.target.pos) < this.target.radius;
        return (!inBounds || isAtTarget);
    }

    dispay() {
        // Draw to the canvas
        if (this.charge > 0)
            fill(250, 50, 50);
        else if (this.charge < 0)
            fill(50, 50, 250);
        else
            fill(50);
        let cPos = PointCharge.toCornerOrigin(this.pos);
        noStroke();
        ellipse(cPos.x, cPos.y, this.radius * 2);
    }

    static toCornerOrigin(a) {
        // Given a point in center-origin coordinates, convert to upper-corner center
        // param a: p5.Vector
        return createVector(a.x + width / 2, height / 2 - a.y);
    }

    static toCenterOrigin(a) {
        // Given a point in corner-origin coordinates, convert to center origin
        // param a: p5.Vector
        return createVector(a.x - width / 2, height / 2 - a.y);
    }
}

function mousePressedInWindow() {
    return (
        mouseIsPressed && (mouseX <= width && mouseY <= height)
    );
}


let source1;
let source2;
let mousePos;

function setup() {
    createCanvas(width, height);
    source2 = new PointCharge(-150, 0, 4);
    source1 = new PointCharge(0, 20, -2, source2);
    source2.target = source1;
    stroke(100);
    slider1 = createSlider(-5, 5, 3, 1);
    slider2 = createSlider(-5, 5, -2, 1);
    // slider1.position(20, height - 20);
    // slider2.position(160, height - 20);
    textSize(16);
}

function draw() {

    background(240);
    strokeWeight(2);
    fill(250, 50, 50);
    source1.charge = slider1.value();
    source2.charge = slider2.value();
    fill(0);
    text(`Charge 1: ${source1.charge}`, 20, height - 10);
    text(`Charge 2: ${source2.charge}`, 140, height - 10);
    source1.update();
    source2.update(movement=false);
}


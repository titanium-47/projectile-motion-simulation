let time;
let resolultion;
let velocity;
let angle;
let area;
let drag_coefficient;
let mass;
let xPosition;
let yPosition;
let shift;
let maxLength;
const height = window.innerHeight-200;
const width = window.innerWidth;
let instance;
const element = document.getElementById('circle');
let start, previousTimeStamp;
let done = false

function submit() {
    done = false;
    start = undefined;
    previousTimeStamp = undefined;

    time = parseFloat(document.getElementById("time").value);
    resolultion = parseInt(document.getElementById("resolution").value);
    velocity = parseFloat(document.getElementById("velocity").value);
    angle = parseFloat(document.getElementById("angle").value);
    area = parseFloat(document.getElementById("area").value);
    drag_coefficient = parseFloat(document.getElementById("drag_coefficient").value);
    mass = parseFloat(document.getElementById("mass").value);

    instance = new Module.Simulator(time, resolultion, velocity, angle, area, drag_coefficient, mass);
    console.log(instance.getMaxHieght());
    console.log(instance.getMaxLength());
    shift = Math.min(height/instance.getMaxHieght(), width/instance.getMaxLength()); 
    maxLength = instance.getMaxLength();
    window.requestAnimationFrame(simulate);
    console.log("finished");
}

function simulate(timestamp) {
    if (start === undefined) {
        start = timestamp;
        }
    const elapsed = timestamp - start;

    if (previousTimeStamp !== timestamp) {
        xPosition = instance.getX(parseInt(elapsed/1000.0*60))*shift;
        yPosition = instance.getY(parseInt(elapsed/1000.0*60))*shift;
        element.style.transform = 'translate(' + xPosition + 'px, ' + '-'+yPosition + 'px)';
        if (maxLength*shift - xPosition == 0 || yPosition<0) {
            instance.delete();
            console.log("done");
            done = true;
        }
    }

    if (elapsed < time*1000) {
        previousTimeStamp = timestamp
        !done && window.requestAnimationFrame(simulate);
    }
}
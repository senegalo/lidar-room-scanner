//Stepper Shaft

shaftHeight = 1.2;
shaftDiameter = 0.8;
shaftThickness = 0.3;

difference(){
    cylinder(h=shaftHeight,d=shaftDiameter,center=false,$fn=50);
    cylinder(h=shaftHeight,d=shaftDiameter-shaftThickness,center=false,$fn=50);
}

//the Plate
plate = [4,5,0.5];
translate([0,0,shaftHeight]) cube(plate, center=true);

//translate([4,0,0]) servo();

//Servo
module servo() {
    servoBody = [3.54,4.136,2.05];
    servoHead = [0.24,0.7,1.89];
    servoHeadXShift = 0.6;

    servoHead1Shift = [servoBody.x/2 - servoHeadXShift - servoHead.x/2 , 
                      servoBody.y/2 + servoHead.y/2, 0];
    servoHead2Shift = [servoHead1Shift.x , -servoHead1Shift.y, servoHead1Shift.z];

   
        cube(servoBody,center=true);
        translate(servoHead1Shift) servoHead();
        translate(servoHead2Shift) servoHead();
    


    module servoHead() {
        servoHeadHoleDiameter = 0.4;
        
        servoHeadHole1Shift =[-servoHead.x/2,0.05,((servoHead.z/2)-servoHeadHoleDiameter)/2];
        servoHeadHole2Shift =[-servoHead.x/2,0.05,-((servoHead.z/2)-servoHeadHoleDiameter)/2];
        
        difference(){
            cube(servoHead, center=true);
            translate(servoHeadHole1Shift) rotate([0,90,0]) cylinder(h=servoHead.x,d=servoHeadHoleDiameter,$fn=50);
            translate(servoHeadHole2Shift) rotate([0,90,0]) cylinder(h=servoHead.x,d=servoHeadHoleDiameter,$fn=50);
        }
    }
}
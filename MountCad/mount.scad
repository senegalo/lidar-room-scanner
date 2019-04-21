//Stepper Shaft

shaftHeight = 12;
shaftDiameter = 8;
shaftThickness = 3;

plateShift = [-shaftDiameter/2,-shaftDiameter/2-20,shaftHeight];
plate = [40+abs(plateShift.x),50+abs(plateShift.y),5];

servoBody = [35.4,41.36,20.5];
servoHead = [2.4,7,18.9];
servoHeadXShift = 6;
servoShaftDiameter = 6.8;
servoShaftHeight = 7.2;

union(){ 
    difference(){
        cylinder(h=shaftHeight,d=shaftDiameter,center=false,$fn=50);
        cylinder(h=shaftHeight,d=shaftDiameter-shaftThickness,center=false,$fn=50);
    }

    //the Plate
    translate(plateShift) cube(plate, center=false);
}

rotate([0,0,180]) translate([-13.5,0,shaftHeight+plate.z+servoBody.z/2]) servo();

//Servo
module servo() {

    servoHead1Shift = [servoBody.x/2 - servoHeadXShift - servoHead.x/2 , 
                      servoBody.y/2 + servoHead.y/2, 0];
    servoHead2Shift = [servoHead1Shift.x , -servoHead1Shift.y, servoHead1Shift.z];
    
    servoShaftShift = [servoBody.x/2+servoShaftHeight/2,servoBody.y/2-10,0];

   union() {
        cube(servoBody,center=true);
        translate(servoShaftShift) rotate([0,90,0]) cylinder(h=servoShaftHeight,d=servoShaftDiameter,center=true,$fn=30);
        translate(servoHead1Shift) servoHead();
        translate(servoHead2Shift) servoHead();
   }


    module servoHead() {
        servoHeadHoleDiameter = 4;
        
        servoHeadHole1Shift =[-servoHead.x/2,0.05,((servoHead.z/2)-servoHeadHoleDiameter)/2];
        servoHeadHole2Shift =[-servoHead.x/2,0.05,-((servoHead.z/2)-servoHeadHoleDiameter)/2];
        
        difference(){
            cube(servoHead, center=true);
            translate(servoHeadHole1Shift) rotate([0,90,0]) cylinder(h=servoHead.x,d=servoHeadHoleDiameter,$fn=50);
            translate(servoHeadHole2Shift) rotate([0,90,0]) cylinder(h=servoHead.x,d=servoHeadHoleDiameter,$fn=50);
        }
    }
}
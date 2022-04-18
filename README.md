# CollsionDetection

Hardware Used:<br/>
Keypad<br/>
VGA port<br/>
Monitor<br/>
DE1-SoC<br/>

The algorithm creates a bounding circle around an object by creating the smallest possible circle around an object given its center. In order to detect if any two objects are colliding, one must only check if the distance between the two objects is less than the sum of the radi of the two objects. One of the main benefits of this algorithm is that the bounding circle of an object never changes even when it is rotating as the bounding circle was still stay the same. The bounding circle will only change when the object moves or is scaled but even then, it is still easy to implement. The main con about this algorithm is that it is not a great representation of some shapes.

import java.util.LinkedList;

/* ************************************************************************
 * I am using the LinkedList data structure from the Java standard library
 * since it implements the Queue ADT from the Java SL.
 * ************************************************************************/

public class FlightSimulator {
    Queue<Airplane> takingOff;
    Queue<Airplane> landing;
    
    public FlightSimulator() {
        takingOff = new LinkedList<Airplane>()
        landing = new LinkedList<Airplane>();
    }
    public Airplane takeOff() {
        // returns null in case of the takingoff queue is empty

        if( landing.peek() == null ) {
            return takingOff.poll();
        } else {
            return null;
        }
    }

    public Airplane land() {
        // returns null if landing queue is empty
        return landing.poll();
    }
    
    // Unclear what these methods do
    // No detailed specifications
    public Airplane requestTakeOff() {
        // Uses the takeOff() method to make a plane takeoff.
        // if The landing queue is not empty it empties it first
        // then makes a plane takeoff
        Airplane a;
        if (takingOff.peek() == null) return null;
        while(true) {
            if((a = landing.peek()) == null) {
                return takeOff();
            }
        }
    }

    public void requestLand(Airplane newPlane) {
        // Adds a new plane in the landing queue
        landing.offer(newPlane)
    }

}

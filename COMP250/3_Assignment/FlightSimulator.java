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
    

    public void requestTakeOff(Airplane newPlane) {
        takingOff.offer(newPlane);
    }

    public void requestLand(Airplane newPlane) {
        landing.offer(newPlane)
    }

}

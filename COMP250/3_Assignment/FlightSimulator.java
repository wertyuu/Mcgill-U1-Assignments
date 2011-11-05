import java.util.LinkedList;

/* ************************************************************************
 * I am using the LinkedList data structure from the Java standard library
 * since it implements the Queue ADT from the Java SL.
 * ************************************************************************/

public class FlightSimulator {
    LinkedList<Airplane> takingoff = new LinkedList<Airplane>();
    LinkedList<Airplane> landing = new LinkedList<Airplane>();
    
    public Airplane takeOff() {
        // returns null in case of the takingoff queue is empty

        if( landing.peek() == null ) {
            return takingoff.poll();
        } else {
            // not correctly implemented ASK FOR CLARIFICATION
            return null;
        }
    }

    public Airplane land() {
        // returns null if landing queue is empty
        return landing.poll();
    }
    

    // CLARIFICATION REQUIRED ON WHAT THOSE METHODS DO
    public void requestTakeOff() {
    
    }

    public void requestLand() {
    
    }

}

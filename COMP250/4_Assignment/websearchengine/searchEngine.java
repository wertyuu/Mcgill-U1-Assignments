import java.util.*;
import java.io.*;

// This class implements a google-like search engine
public class searchEngine {

	public HashMap wordIndex;                  // this will contain a set of pairs (String, LinkedList of Strings)	
	public directedGraph internet;             // this is our internet graph
	public static double DAMPING_FACTOR = 0.5;	// this value is suggested by the authors of Google   
	
	
	// Constructor initializes everything to empty data structures
	// It also sets the location of the internet files
	searchEngine() {
		// Below is the directory that contains all the internet files. 07
		htmlParsing.internetFilesLocation = "internetFiles";
		wordIndex = new HashMap();		
		internet = new directedGraph();				
	} // end of constructor
	
	
    // Returns a String description of a searchEngine
	public String toString () {
		return "wordIndex:\n" + wordIndex + "\ninternet:\n" + internet;
	}


	// This does a graph traversal of the internet, starting at the given url.
	// For each new vertex seen, it updates the wordIndex, the internet graph,
	// and the set of visited vertices.
	
	void traverseInternet(String url) throws Exception {
		/* WRITE SOME CODE HERE */

	} // end of traverseInternet




	/* This computes the pageRanks for every vertex in the internet graph.
	   It will only be called after the internet graph has been constructed using 
	   traverseInternet.
	   Use the iterative procedure described in the text of the assignment to
	   compute the pageRanks for every vertices in the graph. 
	   	   
	   This method will probably fit in about 30 lines.
	   */
	void computePageRanks() {
		/* WRITE YOUR CODE HERE */
		
	} // end of computePageRanks
		


	
	/* Returns the URL of the page with the high page-rank containing the query word
	   Returns the String "" if no web site contains the query.
	   This method can only be called after the computePageRanks method has been executed.
	   Start by obtaining the list of URLs containing the query word. Then return the URL 
	   with the highest pageRank.
	   This method should take about 25 lines of code.
	*/
	String getBestURL(String query) {
		/* WRITE YOUR CODE HERE */
	    return "";
	} // end of getBestURL
	

	
	public static void main(String args[]) throws Exception{		
		searchEngine google = new searchEngine();
		// to debug your program, start with.
	       google.traverseInternet("http://www.mcb.mcgill.ca/~blanchem/250/a.html");

	       // When your program is working on the small example, move on to
	       //  google.traverseInternet("http://www.mcb.mcgill.ca");
	       
		// this is just for debugging purposes
		System.out.println(google);

		google.computePageRanks();

		// this is just for debugging purposes
		System.out.println(google);
		
		BufferedReader stndin = new BufferedReader(new InputStreamReader(System.in));
		String query;
		do {
			System.out.print("Enter query: ");
			query = stndin.readLine();
			if ( query != null && query.length() > 0 ) {
				System.out.println("Best site = " + google.getBestURL(query));
			}
		} while (query!=null && query.length()>0);				
	} // end of main
}

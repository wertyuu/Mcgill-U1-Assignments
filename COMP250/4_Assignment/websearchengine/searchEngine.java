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

                if ( !internet.getVisited( url ) ) {
                        internet.setVisited(url,true);
                        LinkedList<String> wordsInPage = htmlParsing.getContent( url );
                        for ( String word : wordsInPage ) {
                                // add the url to the word index with key word if it already 
                                // exists. Otherwise create a new LinkedList to store the 
                                // url
                                if ( wordIndex.containsKey( word ) ) {
                                        // The url is added to the url LinkedList only
                                        // if it is not already in it
                                        LinkedList<String> urlList = (LinkedList<String>)wordIndex.get( word );
                                        if ( !urlList.contains( url ) ) {
                                            urlList.add( url );
                                        }
                                } else {
                                        LinkedList<String> urlsWithWord = new LinkedList<String>();
                                        urlsWithWord.addLast(url);
                                        wordIndex.put( word, urlsWithWord );
                                }
                        }
                // Traverse &
                // Build the directed graph
                //if ( !htmlParsing.queriedURL_links.containsKey( url ) ) {
                        LinkedList<String> links = htmlParsing.getLinks( url );
                        // add the current url to directed graph
                        internet.addVertex(url);
                        for ( String nextUrl : links ) {
                                // Add edge connecting the current vertex to the next
                                internet.addEdge( url, nextUrl );
                                this.traverseInternet( nextUrl );
                        }
                }
                return;
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
                // set everything to 1.0 first 
                for ( String vertex : (LinkedList<String>)internet.getVertices() ) {
                        internet.setPageRank( vertex, 1.0 );
                }

                // repeat 100 iterations
                for ( int i = 0; i < 100; i++ ) {
                        // for each vertex v do PR(v) = (1 - d) + ( d * ( PR(w1)/C(w1) + ... + PR(wn)/C(wn) ) ) 
                        // let d = 0.5

                        for ( String vertex : (LinkedList<String>)internet.getVertices() ) {
                            
                                double sumOfPR = 0;
                                for ( String vertex2 : (LinkedList<String>)internet.getEdgesInto( vertex )) {
                                        sumOfPR += internet.getPageRank( vertex2 ) / internet.getOutDegree( vertex2 );
                                }

                                double pageRankV = (1 - DAMPING_FACTOR) + DAMPING_FACTOR * sumOfPR;

                                internet.setPageRank( vertex, pageRankV);

                        }
                }
                return;
                
	} // end of computePageRanks
		


	
	/* Returns the URL of the page with the high page-rank containing the query word
	   Returns the String "" if no web site contains the query.
	   This method can only be called after the computePageRanks method has been executed.
	   Start by obtaining the list of URLs containing the query word. Then return the URL 
	   with the highest pageRank.
	   This method should take about 25 lines of code.
	*/
	String getBestURL(String query) {
                String bestSite = "";
                double bestRank = 0;
                if ( wordIndex.containsKey(query) ){
                        // Finds the site with max PageRank from the ones containing the query
                        for ( String current : (LinkedList<String>)wordIndex.get(query) ) {
                                if ( internet.getPageRank(current) > bestRank ) {
                                    bestRank = internet.getPageRank(current);
                                    bestSite = current;
                                }
                        }
                }
                return bestSite;
	} // end of getBestURL
	

	
	public static void main(String args[]) throws Exception{		
		searchEngine google = new searchEngine();
		// to debug your program, start with.
	       //google.traverseInternet("http://www.cs.mcgill.ca/~dprecup/courses/IntroCS/Assignments/hw4PageRank/a.html");

	       // When your program is working on the small example, move on to
	         google.traverseInternet("http://www.cs.mcgill.ca");
	       
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

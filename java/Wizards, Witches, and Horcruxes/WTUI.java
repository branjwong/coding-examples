/*****************************************************************************  
 *  WTUI   Authors: Brandon Wong, Layla Trummer
 *  Wizards and witches game
 *
 *  CMPT 125 2012-1, Final Project 
 *
 *****************************************************************************
 *
 * Wizards and witches game Text User Interaction and top level:   
 *
 */
 

import java.util.Scanner;

public class WTUI
{

 // INSTANCE AND AUXILIARY VARIABLES 
 
 // The game, the two players and the board are DECLARED here 
 // (as instance / global variables in WTUI)
 // and instances will be created (new) here in TUI 
 // also after the user provides the necessary data.
 
 // NOTICE: these variables need to be initialized (in null) otherwise
 // there will be a compilation error indicating that the variable
 // may be not initialized 
 public	Scanner scan = new Scanner (System.in); 
	
 //private WGame game  = null;
 
 //  +++++++ for Players
 
 public WBoard b;
// private WDrawing panel = null; 
 
 // ++++++++++++++++++++++
 
 // variables to capture values that the user will provide to create the game 
 int maxTurnsToPlay = 0;
 
 // variables to capture values that the user will provide to create the board 
 protected int size = 0;
 int minE = 0;
 int maxE = 0;
 int minD =0;
 int maxD =0;
 final int TOTALHOR = 7;
 
 int numberOfPlayers = 2; 
 
 public WPlayer P1;
 public WPlayer P2;
 
 private String Pname = "";
 private String Ptype = "";
 private double Plives; 
   
 protected WGame game; 

 
 //MAIN AS STARTER
 public static void main(String[] args)
 {
    
   WTUI wt = new WTUI();
   wt.topLevel();

 }
 
 // CONSTRUCTOR
 public WTUI()
 {
 	
	 // the top level could have been directly here in the
 	// constructor instead of a separate method
 }
 
 
 // TOP LEVEL
 public void topLevel()
 {
	intro();
	
	while (wantPlay())
	{
		
		//1. Create the board
		inputDataBoardAndCreate();
		
		
		
		System.out.print("\nThere are two players in this game: ");
		
		System.out.print("\nEnter the maximum number of turns each player will have: ");
		maxTurnsToPlay = scan.nextInt();
		
		//2. Create the players
		inputDataPlayersAndCreate();
		
		//display the players
		System.out.println("\nInitial status of players: ");
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(P1.toString() + "\n");
		System.out.println(P2.toString());
		
		
		//DISPLAYBOARD
		//System.out.println("\nThis is what the board looks like: ");
		//System.out.println("---------------------------------------------------------------------------");
		//printBoard(); 
		
		//PLAY
		game = new WGame(P1, P2, maxTurnsToPlay, b);
		
		game.play(); 
		
		reportEndResults();
      
      	System.out.println("\nIt was a fun game! Maybe you want to play again?");
		}	
 System.out.println ("\nGood bye!");   
 
}
 

 public void intro(){
	 System.out.println("Wizards and Witches Game\nCoded by Brandon Wong & Layla Trummer\n=====================================\n\n");
 }
 
 public boolean wantPlay()
 {
	 	boolean result = true;
	 	System.out.print("Would you like to play? (y/n): ");
		String wantPlay = scan.next();
		if (wantPlay.equalsIgnoreCase("n")) {
			System.out.println("\nThat's too bad!");
			result = false;
		}
		if (wantPlay.equalsIgnoreCase("y")){
			result = true;
		}
		//catch invalid input -- never trust the user!!
		if (!(wantPlay.equalsIgnoreCase("n"))){
			if (!(wantPlay.equalsIgnoreCase("y")))
			System.out.println("You're input was not valid, but I know you want to play!");
		}
		return result;
 }
 
 // INPUT VALUES FROM USER AND CREATION OF BOARD------------------------------- 
 
 private void inputDataBoardAndCreate()
 {
	 	
	 	System.out.print("\nEnter the size for the board: ");
		size = scan.nextInt(); 
	 	
		
		System.out.print("Enter minimum number of dementors in each cell: ");
		minD = scan.nextInt();
		
		
		System.out.print("Enter maximum number of dementors in each cell: ");
		maxD = scan.nextInt();
		
		
		System.out.print("Enter minimum number of elves in each cell: ");
		minE = scan.nextInt();
		
		
		System.out.print("Enter maximum number of elves in each cell: ");
		maxE = scan.nextInt();
		
		
		b = new WBoard(size, minD, maxD, minE, maxE);
		
 }
 

     
 
 // INPUT VALUES FROM USER AND CREATION OF 2 PLAYERS ------------------------------- 
 
 private void inputDataPlayersAndCreate()
 {  
	getDataPlayer(1);
	
	if (Ptype.equalsIgnoreCase("n"))
		P1 = new WNaivePlayer(Pname, Plives, maxTurnsToPlay, size);
	if (Ptype.equalsIgnoreCase("h"))
		P1 = new WHelpfulPlayer(Pname, Plives, maxTurnsToPlay, size);
	if (Ptype.equalsIgnoreCase("u")) {
		//System.out.print("As a user player, what behaivior do you want to have when you arrive to a cell? (n-naive, h-helpful, e-evil): ");
		//String type = scan.next(); 
		P1 = new WUserPlayer(Pname, Plives, maxTurnsToPlay, size);
	}
	if (Ptype.equalsIgnoreCase("e"))
		P1 = new WEvilPlayer(Pname, Plives, maxTurnsToPlay, size);
		
 	
	getDataPlayer(2);
	
	if (Ptype.equalsIgnoreCase("n"))
		P2 = new WNaivePlayer(Pname, Plives, maxTurnsToPlay, size);
	if (Ptype.equalsIgnoreCase("h"))
		P2 = new WHelpfulPlayer(Pname, Plives, maxTurnsToPlay, size);
	if (Ptype.equalsIgnoreCase("u")) {
		//System.out.print("As a user player, what behaivior do you want to have when you arrive to a cell? (n-naive, h-helpful, e-evil): ");
		//String type = scan.next(); 
		P2 = new WUserPlayer(Pname, Plives, maxTurnsToPlay, size);
	}
	if (Ptype.equalsIgnoreCase("e"))
		P2 = new WEvilPlayer(Pname, Plives, maxTurnsToPlay, size);
		
  }
       		
       		
 // gets name, type of player and life points from user
 private void getDataPlayer(int numPlayer)
 {
	// data from user
	  	System.out.print("Enter a name for player #" + numPlayer + ": ");
		Pname = scan.next(); 
		
		System.out.print("Enter type of player #" + numPlayer + ", (n- naive, h- helpful, e-evil, u-user): ");
		Ptype = scan.next(); 
		
		//System.out.print("\n\n");
		Plives = 0; 
		while (Plives <= 0 || Plives >= 20) {
			System.out.print("Enter life points for player #" + numPlayer + " (number life points < 20): ");
			Plives = scan.nextDouble(); 
		} 
	 
	 
    }
   
  
  // REPORTING - TEXT OUTPUT
  
 
 public void printBoard()
  {
		System.out.println(b.toString());
     	 		
  }
 
   
  private void reportEndResults() //final status, final board, winners if any
  {
	  game.displayResults();
  }
  
  
  
  // SOME GETTERS
 
  
  // this getter can be of use  in the class  WDrawing
  public WBoard getB()
  {
  	return b;
  }
  
  
  // the following static methods are used from various classes just to display 
  // to or ask values from the user from various classes just to place these 
  // in the TUI class, simulating that all the user interaction takes place in this 
  // class
  
  	
  //public static void specialMessg(String s)
  //{
  //	System.out.println(s);
  //}
  
  //  ++++++++++++++++++++++++
                                
}


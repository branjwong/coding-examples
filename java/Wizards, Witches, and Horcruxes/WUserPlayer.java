import java.util.Scanner;

/*****************************************************************************  
 *  WUserPlayer   Author:  Brandon Wong, Layla Trummer
 *
 * 	Wizards and witches game
 *
 *
 *****************************************************************************
 */
 
 /*   
  *
  * this class extends WPlayer,
  */ 
 



public class WUserPlayer extends WPlayer
{ 
	public Scanner scan = new Scanner (System.in);
	
	String player_type;
	
	public WUserPlayer(String name, double lives, int turns, int SIZE)
	{
		System.out.print("As a user player, what behaivior do you want to have when you arrive to a cell? (n-naive, h-helpful, e-evil): ");
		player_type = scan.next();
		currentPosition = 0; 
		
		player(name, lives, turns, SIZE);
	}
	

	public void player(String name, double lives, int turns, int SIZE)
	{	
		//System.out.println("\nFOR TESTING: THE ABOVE PLAYER IS:" + whoAmI()); 
		
		
		super.player(name, lives, turns, SIZE);
		
		
	}
	
	
	public void takeTurn(int turnNumber)
	{
		System.out.print("\n");
		System.out.print("Which cell number would you like to go to next? ");
		int goHere = scan.nextInt(); 
		currentPosition = goHere;
		while (currentPosition >= (size))
			currentPosition -= (size); 
		
		//go to cell of that number~~~
		
		//update path data:
		//AddToPlayerPath(turnNumber, currentPosition);
		
		//if (player_type.equalsIgnoreCase("n"))
		//if (player_type.equalsIgnoreCase("h"))
		//if (player_type.equalsIgnoreCase("e"))
		
		//interact within cell
		
		
		
		
	}
	public int getPos(){
		return currentPosition;
	}
	
	public void doneTurn() {
		System.out.println("\nThe last player to play was " + name + ", who is currently in cell #" + currentPosition);
		turnsLeft--; 
	}

	public String toString()
	{
		String s = new String(""); 
		s += "Player ("+ whoAmI() +"), " + name;
		s += "\nTotal turns left: " + turnsLeft; 
		s += "\nTotal lifepoints left: " + lifepoints;
		s += "\nTotal horcruxes in box: " + horcEarned;
		s += path();
		
		return s; 
	}
   
    public String whoAmI()
    {
    
   	String s = new String("User: " + actLike());
   	
   	return s;
    }

    public String actLike() {
    	String whatType = "";
        if (player_type.equalsIgnoreCase("n"))
        	whatType = "naive";
        if (player_type.equalsIgnoreCase("e"))
        	whatType = "evil";
        if (player_type.equalsIgnoreCase("h"))
        	whatType = "helpful";
        return whatType;
    }
    

		
}
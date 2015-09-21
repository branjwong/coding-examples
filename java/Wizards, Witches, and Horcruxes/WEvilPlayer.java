/*****************************************************************************  
 *  WEvilPlayer   Author:  Brandon Wong, Layla Trummer
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
 



public class WEvilPlayer extends WPlayer
{ 
	public WEvilPlayer(String name, double lives, int turns, int SIZE)
	{
		currentPosition = 0; 
		
		player(name, lives, turns, SIZE);
	}
	

	public void player(String name, double lives, int turns, int SIZE)
	{	
		//System.out.println("FOR TESTING: THE ABOVE PLAYER IS:" + whoAmI() + "\n"); 
		
		
		super.player(name, lives, turns, SIZE);
		
		
	}
	
	
	public void takeTurn(int turnNumber)
	{
		die.roll(); 
		System.out.println("\nThis player just rolled the die. The face value is: " + die.getFaceValue());
		currentPosition += die.getFaceValue(); 
		while (currentPosition >= (size))
			currentPosition -= (size); 
		
		//update path data:
		//AddToPlayerPath(turnNumber, currentPosition);
		
		
		
	
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
		s += "Player (NPC: "+ whoAmI() +"), " + name + ", is in cell #" + currentPosition;
		s += "\nTotal turns left: " + turnsLeft; 
		s += "\nTotal lifepoints left: " + lifepoints;
		s += "\nTotal horcruxes in box: " + horcEarned;
		s += path();
		
		return s; 
	}
   
    public String whoAmI()
    {
   	String s = new String("evil");
   	return s;
    }
    
    public String actLike()
    {
    return whoAmI(); 	
    }
    
    }

		

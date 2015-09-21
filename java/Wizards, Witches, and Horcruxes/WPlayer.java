/*****************************************************************************  
 *  WPlayerInit   Author: Layla Trummer, Brandon Wong
 *
 *  Wizards and witches game
 *
 * THIS IS AN INCOMPLETE VERSION
 *
 * HINTS FOR ASPECTS THAT YOU NEED TO FURTHER CONSIDER 
 * ARE INDICATED WITH COMMENTS PRECEDED BY ++++++++
 *
 * YOU MAY DECIDE THAT YOU NEED TO ADD FURTHER CODE THAN WHAT IS SUGGESTED
 *
 * 
 *
 *  CMPT 125 2012-1, Final Project 
 *
 *****************************************************************************
 */
 
 /**
  * 
  *  THE DESIGN SUGGESTED IS THAT YOU HAVE PLAYER AS AN ABSTRACT CLASS 
  *  AND "CONCRETE" CLASSES FOR THE CHILDREN (i.e. specific types of players)
  *  
  *  
  *  either type of player will: 
  *      travel in the board form cell to cell 
  *      be exposed to the creatures in each cell
  *      interact with the other player if they meet in the same cell 
  *  
  *  as the player moves it will keep track of the path that it has travelled already
  *
  *  abstract methods recommended: 
  *     whoAmI - 
  *     takeTurnSpecific    
  *
  */
 
  // import ++++++++++++++++++++++

public abstract class WPlayer
{
	protected final int TOTALHORCRS = 7;
	
	protected String name;
	protected double lifepoints; 
	protected int horcEarned = 0; 
	public Die die; 
	public int size;
	public int maxTurnsToPlay;
   //  ++++++++++++++ may  include information to be able to access the other player
   //  ++++++++++++++ may  include information to be able to access the board (the
   // same board that the other player is using!)

	// +++++++++ protected  variables with the information associated to a player
	
	
	// ++++++++++++++ other variables needed
	public int currentPosition; 
	public int[] path;
	public int turnsLeft; 
	
	
	
	public void player(String name, double lives, int turns, int SIZE)
	{
		this.name = name;
		this.size = SIZE;
		this.maxTurnsToPlay = turns;
		this.lifepoints = lives; 
		
		turnsLeft = turns; 
		
		path = new int[(maxTurnsToPlay + 1)];
		path[0] = 0; 
		for (int i = 1; i < (maxTurnsToPlay + 1); i++)
			path[i] = -1; //this way if position was negative it means it was not this players turn
	
		die = new Die(); 
		
		//currentPosition = 0; 
		
	}
	
	public String nameToString()
	{
		return name; 
	}
	
	
	
	
	//keep track of where the player has been
		public void AddToPlayerPath(int turnNumber, int cellNumber)
		{
		path[turnNumber] = cellNumber;
		
		}
		
	public String path()
	{
		String s = new String("\nPath so far: \n");
		s += "\tStart in cell #0\n";
		
		for (int i = 1; i < path.length; i++) {
			if (path[i] >= 0)
				s += "\tTurn #" + i + ": In cell #" + path[i] + "\n";
		}
		return s; 
			
	}
	
	public void addHorc(int h)
	{
		horcEarned += h;
	}
	
	
	public int horcEarned()
	{
		return horcEarned; 
	}
	
	public void zeroHorc() {
		horcEarned = 0;
	}
	
	public boolean isWinner()
	{
		if (horcEarned >= 7)
			return true;
		else
			return false;
	}
	public int turnsLeft(){
		return turnsLeft; 
	}
	
	public boolean isAlive(){
		if (lifepoints > 0)
			return true;
		else
			return false;
	}
	
	public void addLifepoints(double points){
		lifepoints += points;
		
	}
	public void addLifepoints(int points){
		lifepoints += points;
		
	}
	
	public void removeLifepoints(int points){
		lifepoints -= points;
	}
	public void removeLifepoints(double points){
		lifepoints -= points;
	}
	
	public void halfLifepoints(){
		lifepoints = lifepoints/2.0; 
	}
	
	public void replaceLifepoints(double points){
		lifepoints = points; 
	}
	
	public double getLifepoints() {
		return lifepoints;
	}
	
	public void kill(){
		lifepoints = 0;
	}
	
	public void displayWinner(){
		if (isWinner()) {
			if (isAlive()) {
				System.out.println("And the winner is: " + name + " ("+ whoAmI() + ")!!");
			}
		}
	}

    // ++++++ getters and setters and various methods to 
    // porvide action and also information 
    
    // for example, some method to empty the box when the 
    // horcruxes were robbed by the otehr player (this requires to inform the 
    // number of horcruxes this player had, and also to change the
    // number of horcruxes to 0)  
	
	
    /* 
     * ============ TAKE TURN (one player) =================
	 *
	 */
	
	public abstract void takeTurn(int turnNumber);
	
		
		// move to the next cell
		// differnt types of players will move differntly
		 
		 // update the path followed so far

		 //  fights with the creatures  in the cell
		 // life points are updated
		 
		 	   
		 /// interaction with the other player depending on this 
		 // player and /or the other being alive
		 
	
	
	
	
	
	
		
	//public abstract String toStringWithStatus();
	
	
		
	
	public abstract String toString();
	
	
	
	public abstract String whoAmI();
	
	public abstract String actLike();
	
	public abstract int getPos();
	
	public abstract void doneTurn();
   
   	
}
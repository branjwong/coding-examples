/*****************************************************************************  
 *  WGame  Authors: Layla Trummer, Brandon Wong
 *
 *  Wizards and witches game
 *****************************************************************************
 *
 */
 

import java.util.Random;
 
 
public class WGame
{
 protected WBoard b;  
 	
 protected WPlayer P1;
 protected WPlayer P2;
 
 private int turns; //per player

 public Random r = new Random();
      
 public WGame(WPlayer P1, WPlayer P2, int maxTurnsToPlay, WBoard board) 
 {
    this.P1 = P1;
    this.P2 = P2;
    
    b = board; 
    
    turns = maxTurnsToPlay; 
   
    
 }
 
 public void play(){
	 System.out.println("Let's begin the game!\nPlayer #1, " + P1.nameToString() + ", will move first.");
	 
	 while (!gameOver()){
	 for (int i = 1; i <= turns; i++){
		 	
			 if (P2.isAlive() && !P2.isWinner() && !P1.isWinner() && P1.isAlive() )
			 {
				 //display board
				 printBoard();
				 
		// P1 rolls dice/decides which cell to move to	 
		System.out.print("\nIt is Player #1's turn: ");
		 P1.takeTurn(i);
		 if ((P1.actLike()).equalsIgnoreCase("evil") && P1.whoAmI().charAt(0) != 'U'){
			if (P1.getPos() != P2.getPos()) {
				System.out.println("\nThis player is evil, and they did not land in a cell with another player, so they want to roll again!");
				P1.takeTurn(i);
			}	
		 }
	 	
		 
		 //1. is voldemort there??? but no dumbl?
		 if (!(b.checkDumblAt((P1.getPos())))) {
			 if (b.checkVoldAt((P1.getPos()))){
				 System.out.println("\nOh no! Voldemort is in this cell!! Dumbledore isn't there to stop him!!");
				 P1.kill();
				 P1.AddToPlayerPath(i, (P1.getPos()));
				 P1.doneTurn();
				 System.out.println("Voldemort just killed " + P1.nameToString() + "!!");
			 }
		 }
		 
		 
		 //2. If Voldemort is in that cell but Dumbledore is also there, then neither Voldemort nor
		 //					Dumbledore affect the player.  
		 //3. If there are domestic elves in the cell then the player gains life points, as many points
		 //          as there are elves (i.e. 1 point per elf)
		 if (P1.isAlive() && b.getElvesAt(P1.getPos()) > 0){
		 	
		 	P1.addLifepoints((b.getElvesAt(P1.getPos())));
		 	System.out.println("This player gained " + b.getElvesAt(P1.getPos()) + " lifepoints thanks to the nearby elves.");
		 	
		 }
		 
		 
		 
		 //4. If there are dementors in the cell then the player looses life points Ð as many points as
		 //there are dementors Since the player had a fight with the dementors, after the player was deducted the
		// points because of dementors, the cell will have one less dementor.
		 if (P1.isAlive() && b.getDementsAt((P1.getPos())) > 0){
		 P1.removeLifepoints(b.getDementsAt((P1.getPos())));
		 System.out.println("This player fought with dementors and lost " + b.getDementsAt((P1.getPos())) + " lifepoints. One dementor ran away.");
		 b.subtDementsAt((P1.getPos()));
		 }
		 
		 //5. If the other player was already in the same cell when this player
		 //arrived the interaction with the other player will depend on the type of players this player is
		  if (P1.isAlive())
		 interact(P1, P2);
		 
		 //6. then the player collects the horcrux/es. (also empty horcruxes at this cell)
		 if (P1.isAlive() && b.getHorcAt((P1.getPos())) > 0){
			 P1.addHorc(b.getHorcAt((P1.getPos())));
			 System.out.println("This player found " + b.getHorcAt((P1.getPos())) + " horcrux/es!");
		 	b.emptyHorcAt((P1.getPos()));
		 }
			 
	 	if (P1.isAlive()) {
		P1.AddToPlayerPath(i, (P1.getPos()));
	 	P1.doneTurn();
	 	}
	 	
	 	if (P1.isAlive()) {
	 	System.out.println("\nThe two players so far:");
		 System.out.println(P1.toString());
		 System.out.println(P2.toString());
	 	}
		 
		}
			 
	 	//==============================================================================================================
	 	
	 	
	 	//P2 rolls dice/decides which cell to move to
		if (P2.isAlive() && !P2.isWinner() && !P1.isWinner() && P1.isAlive() ){
			
			// display board
			printBoard();
			
	 	System.out.print("\nIt is Player #2's turn: ");
	 	P2.takeTurn(i); 
	 	
	 	if ((P2.actLike()).equalsIgnoreCase("evil") && P2.whoAmI().charAt(0) != 'U'){
			if (P2.getPos() != P1.getPos()) {
				System.out.println("\nThis player is evil, and they did not land in a cell with another player, so they want to roll again!");
				P2.takeTurn(i);
			}	
	 	}
	 	
	 	//1.is voldemort there??? but no dumbl?
	 	if (b.checkDumblAt((P2.getPos())) == false) {
	 		if (b.checkVoldAt((P2.getPos()))) {
	 			System.out.println("\nOh no! Voldemort is in this cell!! Dumbledore isn't there to stop him!!");
	 			P2.kill();
	 			P2.AddToPlayerPath(i, (P2.getPos()));
	 		 	P2.doneTurn();
	 			System.out.println("Voldemort just killed " + P2.nameToString() + "!!");
	 		}
	 	}
	 	
	 	//2. If Voldemort is in that cell but Dumbledore is also there, then neither Voldemort nor
		 //					Dumbledore affect the player.  
	 	//3. If there are domestic elves in the cell then the player gains life points, as many points
		 //          as there are elves (i.e. 1 point per elf)
	 	if (P2.isAlive() && b.getElvesAt(P2.getPos()) > 0){
		 	
		 	P2.addLifepoints((b.getElvesAt(P2.getPos())));
		 	System.out.println("This player gained " + b.getElvesAt(P2.getPos()) + " lifepoints thanks to the nearby elves.");
		 	
		 } 
		 
		//4. If there are dementors in the cell then the player looses life points Ð as many points as
		 //there are dementors Since the player had a fight with the dementors, after the player was deducted the
		// points because of dementors, the cell will have one less dementor.
	 	if (P2.isAlive() && b.getDementsAt((P2.getPos())) > 0){
		 P2.removeLifepoints(b.getDementsAt((P2.getPos())));
		 System.out.println("This player fought with dementors and lost " + b.getDementsAt((P2.getPos())) + " lifepoints. One dementor ran away.");
		 b.subtDementsAt((P2.getPos()));
		 }
		 
		//5. If the other player was already in the same cell when this player
		 //arrived the interaction with the other player will depend on the type of players this player is
		 //System.out.println("\nI, P2, am interacting with other players if they are in this cell as well");
	 	if (P2.isAlive())
	 		interact(P2, P1); 
		 
		//6. then the player collects the horcrux/es. (also empty horcruxes at this cell)
	 	if (P2.isAlive() && b.getHorcAt((P2.getPos())) > 0){
			 P2.addHorc(b.getHorcAt((P2.getPos())));
			 System.out.println("This player found " + b.getHorcAt((P2.getPos())) + " horcrux/ex!");
		 	b.emptyHorcAt((P2.getPos()));
		 }
		 
		 
	 	if (P2.isAlive()) {
	 	P2.AddToPlayerPath(i, (P2.getPos()));
	 	P2.doneTurn();
	 	}
	 	
	 	if (P2.isAlive()) {
	 	System.out.println("\nThe two players so far:");
		 System.out.println(P1.toString());
		 System.out.println(P2.toString());
	 	}
		
		
		}
	 	
	 	}
	 
		 
	 	
		 
		if (gameOver()){
			System.out.println("\n\tGAME OVER!\n");
		 
		} 
	 }
 }
     
 
 public void interact(WPlayer A, WPlayer B){
	 if (A.getPos() == B.getPos()) {
	 if ((A.actLike()).equalsIgnoreCase("helpful")){
		 double newPoints = 0; 
		 newPoints += A.getLifepoints() + B.getLifepoints();
		 newPoints = newPoints/2.0;
		 A.replaceLifepoints(newPoints);
		 B.replaceLifepoints(newPoints); 
		 System.out.println(A.nameToString() + " just redistributed the lifepoints of both players!");
	 }
	 
	 if ((A.actLike()).equalsIgnoreCase("evil")){
		 //the evil player will take all the horcruxes from the other player 
		 //and will also take half the life points from the other player to his own benefit!
		 B.halfLifepoints();
		 A.addLifepoints((B.getLifepoints()));
		 System.out.println(A.nameToString() + " just robbed " + B.getLifepoints() + " lifepoints from " + B.nameToString());
		 if (B.horcEarned() > 0) {
			 System.out.println(A.nameToString() + " also stole all " + B.horcEarned() + " horcruxes from " + B.nameToString());
	 	}
		 A.addHorc(B.horcEarned());
		 B.zeroHorc(); 
		 }
	 
	//I, p1, user evil just robbed half life points (5.0) from the other player!
	 //Oh no! p0(user helpful) says: " someone emptied my box with horcruxes!!!"  
 
	 
	
	 }
 }
 

 // DETERMINING WINNER ------------------------------------------------

   
   public boolean playerWins() {
	boolean result = false; 
	if (P1.isWinner())
		result = true; 
	if (P2.isWinner())
		result = true; 
	
	return result;
   }
  
  public void displayResults() {
	  
	  System.out.println("The final status of the players:");
	  System.out.println("--------------------------------");
	  System.out.println(P1.toString());
	  System.out.println(P2.toString());
	  System.out.println("The board at the end looks like: ");
	  System.out.println("---------------------------------");
	  System.out.println(b.toString()); 
	  
	  if (playerWins()){
		  P1.displayWinner();
		  P2.displayWinner();
	  }
	  else
		  System.out.println("There was no winner this time.");
  }
  
  
  public boolean gameOver() {
	 
	  boolean result = false; 
	  
	 if (playerWins()){
		 result = true;
	 }
    if (P1.getLifepoints() <= 0 || P2.getLifepoints() <= 0) {
    	result = true;
    }
    if (P1.turnsLeft() == 0){
    	if (P2.turnsLeft() == 0)
    		result = true; 
    }
    return result; 
    
    }
  
  
  public void printBoard()
  {
	  	System.out.println("\nThis is what the board looks like: ");
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(b.toString());
     	 		
  }
    
  }

  
  
 
  

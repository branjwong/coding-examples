 
import java.util.Random;


public class WBoard
{
	
	private WCell[] cell;
	private final int MAX_HORCRS = 7;
	private int SIZE;
    //  +++++++++++++++++  you would like to have an array or 
    //                      an arraylist of cells
    
    // +++++++ you may need other instance variables
	
	public Random random = new Random();
	

	public WBoard(int size, int minD, int maxD, int minE, int maxE)  
	{

		createCells(size, minD, maxD, minE, maxE);
		SIZE = size;
		addHorcrsVoldDumbl(); 
		                                  

		
	}
	
	//==========================================
	// create arraylist with all cells
	//==========================================
	
	private void createCells(int size, int minD, int maxD, int minE, int maxE)
	{
		cell = new WCell[size];
		cell[0] = new WCell(0, 0, 0, 0);
		for (int i = 1; i < size; i++){
			cell[i] = new WCell(minD, maxD, minE, maxE);
		}
	}
	
	
	private void addHorcrsVoldDumbl()
	{
		int cellNum;
		
		
		//for each horcr, find a random cell to place it in.
		for(int i = 0; i < MAX_HORCRS; i++){
			//int num1 = random.nextInt(SIZE) + 1;
			cellNum = random.nextInt((SIZE - 1)) + 1;
			cell[cellNum].addHorcr();
		}
		
		//for vold, find a random cell to place him in.
		//cellNum = (int)(Math.random(SIZE-1) + 1);
		cellNum = random.nextInt((SIZE - 1)) + 1;
		cell[cellNum].setVoldTrue();
		
		//for dumbl, find a random cell to place him in.
		//cellNum = (int)(Math.random*SIZE);
		cellNum = random.nextInt((SIZE - 1)) + 1;
		cell[cellNum].setDumblTrue();
	}
	
	
   
	
	//==========================================
	// getters and setters of  cells contents, but in this class
	// it's done to the board as a whole, so that  a parameter 
	// indicates the cell number and therefore the cell in that 
	// position of the board is the one where the getting or setting
	//  takes place
	//==========================================
    
	
	public int getDementsAt(int cellNum)
	{
		int result;
		result = cell[cellNum].getDements();
		return result;
	}
	
	public void subtDementsAt(int cellNum)
	{
		cell[cellNum].subtDement();
	}
	
	public int getElvesAt(int cellNum)
	{
		return cell[cellNum].getElves();
	}
	
	public boolean checkDumblAt(int cellNum){
		return cell[cellNum].checkDumbl();
	}
	
	public boolean checkVoldAt(int cellNum){
		return cell[cellNum].checkVold();
	}
	
	//  -------------------------------------------------------------------------
	//  -------------------------------------------------------------------------
	//  Layla tries to code
	//  -------------------------------------------------------------------------
	//  -------------------------------------------------------------------------
	public int getHorcAt(int cellNum){
		return cell[cellNum].getHorc();
		
	}
	public void emptyHorcAt(int cellNum){
		cell[cellNum].emptyAllHorcrs();
	}
	
	
	
	
	
	//i.e. Cell 1: 2 horcruxes, 1 dementors, 2 elves,
    //			Vold is here!!  Dumbl is here!!
	public String toString()
	{
		String result = "";
		for (int i = 0; i < SIZE; i++){
			result += "Cell " + i + ": " + cell[i].toString() + "\n";
		}
		return result;
	}
	
	
	
	//public static void main(String[] args)
	//{
		// minor testing
	   
		//WBoard b = new WBoard(10,0,2,0,2);
		//System.out.println(b);
	//}	
		
}
import java.util.Random;

public class WCell
{
	private int _horcrs;
	private int _dements;
	private int _elves;
	private boolean _vold; 
	private boolean _dumbl;   
	
	Random gen = new Random();

  

   //--------------------------------------------------------------------------
   // Constructor: constructs the cell with dementors and elves random values 
   // between min and max
   // 
   // ++++++  horcruxes, Vold and Dumbledore need to be placed also, 
   //                    but this could be done after the cell has been constructed
   //                    and only in some cells
   // 
   //--------------------------------------------------------------------------
   
	public WCell(int minD, int maxD, int minE, int maxE)
   	{
   		_dements = randomGenRange(minD, maxD);
		_elves = randomGenRange(minE, maxE);
		_horcrs = 0;
		_vold = false;
		_dumbl = false;
   }
   
	private int randomGenRange(int min, int max)
	{
		int result;
		result = gen.nextInt(max-min+1)+min;
		return result;
	}

  
//-----------------------------------------------------------------
   // methods that will be used often as when initializing the cell
   //
   //++++++++++++++ You may want to include setters, getters
   //                  and /or more specialized methods which not only
   //                  change the cell contents,  but also return values
   //-----------------------------------------------------------------
   
   
	public void addHorcr()  
	{
		_horcrs++;
	}
	
	//used when player gets attacked by dement
	public void subtDement()
	{
		if (_dements > 0)
			_dements--;
	}
	
	public void setVoldTrue()
	{
		_vold = true;
	}
	
	public void setDumblTrue()
	{
		_dumbl = true;
	}
	
	public int getDements()
	{
		return _dements;
	}
	
	public int getElves()
	{
		return _elves;
	}
	
	public boolean checkDumbl()
	{
		boolean result;
		if (_dumbl)
			result = true;
		else
			result = false;
		return result;	
	}
	
	public boolean checkVold()
	{
		boolean result;
		if (_vold)
			result = true;
		else
			result = false;
		return result;	
	}


 
   

   //-----------------------------------------------------------------
   //  methods that will be used often as the game unfolds, 
   //  needing to change the cell contents 
   //
   //
   //   ++++++++++++++ You may want to include setters, getters
   //                  and /or more specialized methods which not only
   //                  change the cell contents,  but also return values
   //-----------------------------------------------------------------
   
   
   
	public void emptyAllHorcrs()
	{
		_horcrs = 0;
	}

	public String toString()
	{
		String result;
		result = _horcrs + " horcruxes, " + _dements + " dementors, " + _elves + " elves." + "\n";
		if(checkDumbl() || checkVold())
			{
				if(checkDumbl())
					result += "\t Dumbl is here!!";
				if(checkVold())
					result += "\t Vold is here!!";
				result += "\n";
			}
		return result;
	}
   
//  -------------------------------------------------------------------------
	//  -------------------------------------------------------------------------
	//  Layla tries to code
	//  -------------------------------------------------------------------------
	//  -------------------------------------------------------------------------
	
	public int getHorc(){
		return _horcrs;
	}
	
	public void oneLessDem(){
		if (_dements > 0)
			_dements--;
	}
	
	
	
   
	//public static void main(String[] args)
	//{
		// minor testing
	//	WCell c = new WCell(0,2,0,2);
	//	c.setVoldTrue();
	//	System.out.println(c);
	//}
}
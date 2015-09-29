using UnityEngine;
using System.Collections;


public class PlayerController : MonoBehaviour {


	// Panel Axis Coordinates
	/*
	 *	+ A  B  C  x
	 *	a[1][2][3]
	 *	b[4][5][6]
	 *	c[7][8][9]
	 *	y
	 */

	// horizontal coordinates
	public const float Px_A = -.06f;		
	public const float Px_B = .34f;		
	public const float Px_C = .74f;
	// vertical coordinates
	public const float Py_C = .20f;		
	public const float Py_B = .43f;
	public const float Py_A = .66f;

	// Player has 9 panels.
	// Top Left: Panel #1, Middle: Panel #5, Bottom Right: Panel #9
	public const int PCentre = 5;

	private float panel_x;
	private float panel_y;
	public int panel_num = PCentre;
	public bool move = true;

	private Transform trans;			// Reference to the player's transform component.
	private Animator anim;				// Reference to the player's animator component.
	private Blaster blaster;			// Reference to the player's blaster script.



	// Use this for initialization
	void Start () {
		// Setting up references.
		anim = GetComponent<Animator> ();
		trans = GetComponent<Transform> ();
		blaster = transform.root.GetComponent<Blaster>();

		// initiate Player
		Relocate (panel_num);
	}
	
	// Update is called once per frame
	void Update () {
		InputToMove ();
	}
	

	// Relocate Player to Panel p_dest
	// Top Left = Panel: AA, Centre: Panel: BB, Bottom Right: CC (Think Chess Board)
	void Relocate(int p_dest){

		// Player has 9 panels.
		// Top Left: Panel #1, Middle: Panel #5, Bottom Right: Panel #9
		if (p_dest == 1){
			//put Player on panel 1
			trans.position = new Vector3(Px_A, Py_A, trans.position.z);
		}
		else if (p_dest == 2){
			//put Player on panel 2
			trans.position = new Vector3(Px_B, Py_A, trans.position.z);
		}
		else if (p_dest == 3){
			//put Player on panel 3
			trans.position = new Vector3(Px_C, Py_A, trans.position.z);
		}
		else if (p_dest == 4){
			//put Player on panel 4
			trans.position = new Vector3(Px_A, Py_B, trans.position.z);
		}
		else if (p_dest == 5){
			//put Player on panel 5
			trans.position = new Vector3(Px_B, Py_B, trans.position.z);
		}
		else if (p_dest == 6){
			//put Player on panel 6
			trans.position = new Vector3(Px_C ,Py_B, trans.position.z);
		}
		else if (p_dest == 7){
			//put Player on panel 7
			trans.position = new Vector3(Px_A, Py_C, trans.position.z);
		}
		else if (p_dest == 8){
			//put Player on panel 8
			trans.position = new Vector3(Px_B, Py_C, trans.position.z);
		}
		else if (p_dest == 9){
			//put Player on panel 9
			trans.position = new Vector3(Px_C, Py_C, trans.position.z);
		}
		else {
			Debug.Log ("Player: Invalid Panel Placement");
//			panel_num = PCentre;
			return;
		}
		panel_x = trans.position.x;
		panel_y = trans.position.y;
		Debug.Log ("Relocate: "+ panel_x + ", " + panel_y);
	}

//	// Relocate Player to panel p_dest
//	void RelocateCheck (int p_dest){
//		// check if next panel location is valid
//		if (panel_num >= PTopLeft && panel_num <= PBtmRight)
//			Relocate(p_dest);
////			Shift ();
//		else
//		{
//
//		}		
//	}

	// DirectionButtons -> Move Player
	void InputToMove() {
//		float x = Input.GetAxis ("Horizontal");
//		float y = Input.GetAxis ("Vertical");

		bool Wdown = Input.GetKeyDown(KeyCode.W);
		bool Adown = Input.GetKeyDown(KeyCode.A);
		bool Sdown = Input.GetKeyDown(KeyCode.S);
		bool Ddown = Input.GetKeyDown(KeyCode.D);

		if (move){
			if (Wdown){
				if (panel_y != Py_A){
					Debug.Log("Move: Up");
					panel_num -= 3;
					anim.Play("Move1");
					move = false;
//					blaster.shoot = false; 
				}
				else {
					Debug.Log("Move: Denied Movement");
				}
			}
			else if (Adown){
				if (panel_x != Px_A){
					Debug.Log("Move: Left");
					panel_num -= 1;
					anim.Play("Move1");
					move = false;
//					blaster.shoot = false; 
				}
				else {
					Debug.Log("Move: Denied Movement");
				}
			}
			else if (Sdown){
				if (panel_y != Py_C){
					Debug.Log("Move: Down");
					panel_num += 3;
					anim.Play("Move1");
					move = false;
//					blaster.shoot = false; 
				}
				else {
					Debug.Log("Move: Denied Movement");
				}

			}
			else if (Ddown){
				if (panel_x != Px_C){
					Debug.Log("Move: Right");
					panel_num += 1;
					anim.Play("Move1");
					move = false;
//					blaster.shoot = false; 
				}
				else {
					Debug.Log("Move: Denied Movement");
				}
			}
		}
	}

//	IEnumerator MoveTransition (){
//		anim.Play("Move1");
//		move = false;
//		yield return new WaitForSeconds (0.1f);
//		Relocate (panel_num);
////	anim.Play ("Move2");
////	yield return new WaitForSeconds (0.1f);
//		move = true;
//	}

	void AnimationToRelocate(){
		Relocate(panel_num);
	}



}




using UnityEngine;
using System.Collections;

public class Boss1 : MonoBehaviour {

	// horizontal coordinates
	public const float Px_E = 1.9f;		
	public const float Px_F = 2.12f;		
	public const float Px_G = 2.5f;
	// vertical coordinates
	public const float Py_C = .20f;		
	public const float Py_B = .43f;
	public const float Py_A = .66f;

	private const int PCentre = 5;
	private const int actionCount = 9;
	private const float waitTime = 0.2f;

//	private bool dead = false;
	private TextMesh hp_text;
	private Transform trans;			// Reference to the boss's transform component.
	private Animator anim;				// Reference to the boss's animator component.

	public int hitPoints = 1000;
	public int panel_num = PCentre;




	// Use this for initialization
	void Start () {
		hp_text = GameObject.Find ("Health").GetComponent<TextMesh> ();
		anim = GetComponent<Animator> ();
	}
	
	// Update is called once per frame
	void Update () {
		hp_text.text = "" + hitPoints;
		Action (waitTime);
	}

	public void Hurt(int dmg){
		hitPoints = hitPoints - dmg;
	}

	// Relocate Boss1 to Panel p_dest
	// Top Left = Panel: EA, Centre: Panel: FB, Bottom Right: GC (Think Chess Board)
	void Relocate(int p_dest){
		
		// Boss1 has 9 panels.
		// Top Left: Panel #1, Middle: Panel #5, Bottom Right: Panel #9
		if (p_dest == 1){
			//put Boss1 on panel 1
			trans.position = new Vector3(Px_E, Py_A, trans.position.z);
		}
		else if (p_dest == 2){
			//put Boss1 on panel 2
			trans.position = new Vector3(Px_F, Py_A, trans.position.z);
		}
		else if (p_dest == 3){
			//put Boss1 on panel 3
			trans.position = new Vector3(Px_G, Py_A, trans.position.z);
		}
		else if (p_dest == 4){
			//put Boss1 on panel 4
			trans.position = new Vector3(Px_E, Py_B, trans.position.z);
		}
		else if (p_dest == 5){
			//put Boss1 on panel 5
			trans.position = new Vector3(Px_F, Py_B, trans.position.z);
		}
		else if (p_dest == 6){
			//put Boss1 on panel 6
			trans.position = new Vector3(Px_G ,Py_B, trans.position.z);
		}
		else if (p_dest == 7){
			//put Boss1 on panel 7
			trans.position = new Vector3(Px_E, Py_C, trans.position.z);
		}
		else if (p_dest == 8){
			//put Boss1 on panel 8
			trans.position = new Vector3(Px_F, Py_C, trans.position.z);
		}
		else if (p_dest == 9){
			//put Boss1 on panel 9
			trans.position = new Vector3(Px_G, Py_C, trans.position.z);
		}
		else {
			Debug.Log ("Boss1: Invalid Panel Placement");
//			panel_num = PCentre;
			return;
		}
	}

	void AnimationToRelocate(){
		Relocate(panel_num);
	}

	IEnumerator Action (float waitTime){
		Debug.Log ("Boss1: Action");
		yield return new WaitForSeconds (waitTime);
		int actionSelect = Mathf.RoundToInt(Random.Range(0, 9));
		if (actionSelect <= 9)
		{
			panel_num = actionSelect;
			anim.Play("Boss1_Move1");
		}
	}
	

}


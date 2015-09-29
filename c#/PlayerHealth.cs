using UnityEngine;
using System.Collections;

public class PlayerHealth : MonoBehaviour {

	public int hitPoints = 100;						// The player's health.
	public float repeatDamagePeriod = 2f;			// How frequently the player can be damaged.

	private float lastHitTime;						// The time at which the player was last hit.
	private PlayerController playerCtrl;			// Reference to the PlayerController script.
	private TextMesh health;						// Reference to the Health gameobject on the player.
//	private Animator anim;							// Reference to the Animator on the player.


	// Use this for initialization
	void Start () {
		// Setting up references.
		playerCtrl = GetComponent<PlayerController>();
		health = GetComponent<TextMesh>();
//		anim = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
		health.text = "" + hitPoints;
	}

	public void Hurt(int dmg){
		hitPoints = hitPoints - dmg;
	}

	public void Heal(int healvalue){
		hitPoints = hitPoints + healvalue;
	}
}

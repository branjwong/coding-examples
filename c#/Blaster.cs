using UnityEngine;
using System.Collections;

public class Blaster : MonoBehaviour {

	public Rigidbody2D projectile;			// Prefab of the projectile.
	public float speed = 15f;				// The speed the blaster will fire at.
	public bool shoot = true;				// 

	private PlayerController playerCtrl;	// Reference to the PlayerControl script.
	private Animator anim;					// Reference to the Animator component.

	// Use this for initialization
	void Start () {
		anim = transform.root.gameObject.GetComponent<Animator>();
		playerCtrl = transform.root.GetComponent<PlayerController>();
	
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetButtonDown("Buster") && shoot){
			anim.Play("Shoot");
			Debug.Log("Shoot");
			Rigidbody2D projectileInstance = Instantiate(projectile, transform.position, Quaternion.Euler(new Vector3(0,0,-1))) as Rigidbody2D;
//			projectileInstance.drag = 0f;
			projectileInstance.velocity = new Vector2(speed, 0);
//			projectileInstance.AddForce(new Vector2(0,50f));
		}
	}


}

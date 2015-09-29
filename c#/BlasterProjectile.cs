using UnityEngine;
using System.Collections;

public class BlasterProjectile : MonoBehaviour {

	// Use this for initialization
	void Start () {
		// Destroy the rocket after 1 seconds if it doesn't get destroyed before then.
		Destroy(gameObject, 1);
	}
	
	void OnTriggerEnter2D (Collider2D col) 
	{
		// If it hits an Boss1...
		if(col.tag == "Boss")
		{
			// ... find the Boss1 script and call the Hurt function.
			col.gameObject.GetComponent<Boss1>().Hurt(10);
			
			// Destroy the rocket.
			Destroy (gameObject);
		}
	}
}

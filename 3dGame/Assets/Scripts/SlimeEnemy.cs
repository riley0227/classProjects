using UnityEngine;

public class SlimeEnemy : BaseEnemy
{
    public float jumpForce = 5f; //vertical jump force
    public float jumpCooldown = 2f; //time between jumps
    public float forwardJumpForce = 5f; //force towards the player

    private bool isJumping = false;

    protected override void Start()
    {
        base.Start();
        player = GameObject.FindGameObjectWithTag("Player").transform;
        StartCoroutine(JumpRoutine());
    }


    private System.Collections.IEnumerator JumpRoutine()
    {
        while (true)
        {
            if (!isJumping && player != null)
            {
                isJumping = true;

                //jump towards player
                Vector3 directionToPlayer = (player.position - transform.position).normalized;
                Vector3 jumpDirection = new Vector3(directionToPlayer.x, 1f, directionToPlayer.z).normalized;

                rb.AddForce(jumpDirection * forwardJumpForce + Vector3.up * jumpForce, ForceMode.Impulse);

                yield return new WaitForSeconds(0.5f);
                isJumping = false;
            }

            yield return new WaitForSeconds(jumpCooldown);
        }
    }

    private void OnCollisionEnter(Collision collision)
{
    if (collision.collider.CompareTag("Player"))
    {
        //deal damage using playerhealth script
        PlayerHealth playerHealth = collision.collider.GetComponent<PlayerHealth>();
        if (playerHealth != null)
        {
            playerHealth.TakeDamage(1f); //half heart
        }
    }
}

    protected override void Die()
    {
        base.Die();
    }
}

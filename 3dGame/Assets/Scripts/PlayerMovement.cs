using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerMovement : MonoBehaviour
{
    public CharacterController controller;

    public float speed = 12f;
    public float sprintSpeed = 18f;
    public float crouchSpeed = 6f;
    public float jumpHeight = 3f;
    public float gravity = -9.81f;

    public Transform groundCheck;
    public float groundDistance = 0.4f;
    public LayerMask groundMask;

    public float maxStamina = 100f;
    public float stamina = 100f;
    public float staminaDrain = 15f; //per second
    public float staminaRegen = 10f; //per second
    public float cooldownDuration = 3f; //stamina cooldown duration
    public Slider staminaBar;

    private Vector3 velocity;
    private bool isGrounded;

    private float originalHeight;
    public float crouchHeight = 1f;

    private bool isCooldown = false; //tracks if the cooldown is active
    private float cooldownTimer = 0f;

    void Start()
    {
        originalHeight = controller.height; //original height
        staminaBar.maxValue = maxStamina;
        staminaBar.value = stamina;
    }

    void Update()
    {
        //player is grounded check
        isGrounded = Physics.CheckSphere(groundCheck.position, groundDistance, groundMask);

        if (isGrounded && velocity.y < 0)
        {
            velocity.y = -2f; //reset downward velocity when grounded
        }

        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");

        //change for Sprinting and Crouching
        float currentSpeed = speed;

        // Handle cooldown after stamina depletion
        if (isCooldown)
        {
            cooldownTimer += Time.deltaTime;

            if (cooldownTimer >= cooldownDuration)
            {
                isCooldown = false; // End cooldown
                cooldownTimer = 0f; // Reset timer
            }
            else
            {
                currentSpeed = speed / 2f; // Slow movement during cooldown
            }
        }
        else if (Input.GetKey(KeyCode.LeftShift) && stamina > 0) // Sprint
        {
            currentSpeed = sprintSpeed;
            stamina -= staminaDrain * Time.deltaTime;

            if (stamina <= 0)
            {
                stamina = 0; // Clamp stamina to 0
                isCooldown = true; // Start cooldown
            }
        }
        else if (Input.GetKey(KeyCode.LeftControl)) // Crouch
        {
            currentSpeed = crouchSpeed;
            controller.height = crouchHeight; //lower the player's height
        }
        else
        {
            controller.height = originalHeight; //reset height when not crouching
        }

        //regen
        if (!Input.GetKey(KeyCode.LeftShift) || isCooldown)
        {
            stamina += staminaRegen * Time.deltaTime;
        }

        //max stamina
        stamina = Mathf.Clamp(stamina, 0, maxStamina);

        //stamina bar
        staminaBar.value = stamina;

        //move the player
        Vector3 move = transform.right * x + transform.forward * z;
        controller.Move(move * currentSpeed * Time.deltaTime);

        //jumping
        if (Input.GetButtonDown("Jump") && isGrounded)
        {
            velocity.y = Mathf.Sqrt(jumpHeight * -2f * gravity);
        }
        //gravity
        velocity.y += gravity * Time.deltaTime;
        controller.Move(velocity * Time.deltaTime);
    }
}


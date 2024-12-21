using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance; 
    public TextMeshProUGUI enemiesLeftText; 
    public TextMeshProUGUI coinsText;       
    public GameObject roomPrefab;          
    public Transform player;              
    public GameObject room0;               //say it with me! We love room0 (starting room/great for debugging)

    private GameObject currentRoomInstance; //active room instance
    private int roomNumber = 0;             
    private int totalCoins = 0;             
    public TextMeshProUGUI roomNumberText;

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject); //persist manager across scenes
        }
        else
        {
            Destroy(gameObject); 
        }
    }

    //start us in room0. Remeber, we love it
    private void Start()
    {
        UpdateCoinsUI();

        if (room0 != null)
        {
            currentRoomInstance = room0;
            Transform playerSpawnPoint = room0.transform.Find("PlayerSpawnPoint");
            if (playerSpawnPoint != null)
            {
                player.position = playerSpawnPoint.position;
            }
            else
            {
                player.position = Vector3.zero; 
            }
        }
        else
        {
            SpawnNextRoom();
        }
    }

    public void SpawnNextRoom()
    {
        roomNumber++;

        UpdateRoomNumberUI();
        SpawnRoom();

        //open a shop every 4 rooms
        if (roomNumber % 4 == 0)
        {
            OpenShopAfterRoom();
        }
    }

    private void SpawnRoom()
    {
        if (currentRoomInstance != null && currentRoomInstance != room0)
        {
            Destroy(currentRoomInstance);
        }

        Vector3 roomSpawnPosition = new Vector3(0, 5.0f, 0);
        currentRoomInstance = Instantiate(roomPrefab, roomSpawnPosition, Quaternion.identity);

        EnemySpawner spawner = currentRoomInstance.GetComponentInChildren<EnemySpawner>();
        if (spawner != null)
        {
            spawner.roomNumber = roomNumber;
        }

        TransportPlayerToSpawnPoint();
    }

    private void OpenShopAfterRoom()
    {
        StartCoroutine(DelayShopOpening());
    }

    private IEnumerator DelayShopOpening()
    {
        yield return new WaitForEndOfFrame(); //wait for player to be ready

        ShopManager shopManager = FindObjectOfType<ShopManager>();
        if (shopManager != null)
        {
            shopManager.OpenShop();
        }
    }

    //going through the doors, temp disable controller
    private void TransportPlayerToSpawnPoint()
    {
        Transform playerSpawnPoint = currentRoomInstance.transform.Find("PlayerSpawnPoint");
        if (playerSpawnPoint != null)
        {
            CharacterController controller = player.GetComponent<CharacterController>();
            if (controller != null)
            {
                controller.enabled = false; 
                player.position = playerSpawnPoint.position;
                player.rotation = playerSpawnPoint.rotation; 
                controller.enabled = true;
            }
            else
            {
                player.position = playerSpawnPoint.position;
                player.rotation = playerSpawnPoint.rotation;
            }
        }
        else
        {
            player.position = Vector3.zero; //fallback position
        }
    }

    public void AddCoins(int amount)
    {
        totalCoins += amount; 
        UpdateCoinsUI();      
    }

    private void UpdateCoinsUI()
    {
        if (coinsText != null)
        {
            coinsText.text = $"Coins: {totalCoins}";
        }
    }

    public int GetTotalCoins()
    {
        return totalCoins;
    }

    public void SpendCoins(int amount)
    {
        if (totalCoins >= amount)
        {
            totalCoins -= amount;
            UpdateCoinsUI();
        }
        else
        {
            Debug.LogWarning("Not enough coins to spend!");
        }
    }
    private void UpdateRoomNumberUI()
{
    if (roomNumberText != null)
    {
        roomNumberText.text = $"Room: {roomNumber}";
    }
}

}

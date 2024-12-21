using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class EnemySpawner : MonoBehaviour
{
    public List<GameObject> enemyPrefabs; //list of enemy prefabs to spawn
    public Transform roomBounds;          //room's bounds for random placement
    public GameObject doorPrefab;         
    public Transform doorSpawnPoint;      

    public int roomNumber = 1;            //room number (to scale difficulty and track for future features)
    public int maxEnemiesPerRoom = 10;    //hardcoding this for now so things dont get TOO crazy
    public float spawnDelay = 0.5f;       //delay between each spawn

    public TextMeshProUGUI enemiesLeftText; 

    private int enemiesToSpawn;           
    private List<GameObject> spawnedEnemies = new List<GameObject>(); 
    private int enemiesLeft;              

    private void Start()
    {
        if (GameManager.Instance != null)
        {
            enemiesLeftText = GameManager.Instance.enemiesLeftText;
        }

        //how many enemies to spawn for the current room
        enemiesToSpawn = Mathf.Min(roomNumber, maxEnemiesPerRoom);
        enemiesLeft = enemiesToSpawn;
        UpdateEnemiesLeftUI();
        StartCoroutine(SpawnEnemies());
    }

    private void UpdateEnemyCount()
{
    
    enemiesToSpawn = Mathf.Min(roomNumber, maxEnemiesPerRoom); 
    enemiesLeft = enemiesToSpawn; 
    UpdateEnemiesLeftUI(); 
}

public IEnumerator SpawnEnemies()
{
    UpdateEnemyCount(); //update enemy count is for the current room

    for (int i = 0; i < enemiesToSpawn; i++)
    {
        SpawnRandomEnemy();
        yield return new WaitForSeconds(spawnDelay);
    }
}

    private void SpawnRandomEnemy()
    {
        if (enemyPrefabs.Count == 0) return; 

        GameObject enemyPrefab = enemyPrefabs[Random.Range(0, enemyPrefabs.Count)];
        Vector3 randomPosition = GetRandomPositionWithinBounds();

        GameObject enemy = Instantiate(enemyPrefab, randomPosition, Quaternion.identity);
        spawnedEnemies.Add(enemy);

        BaseEnemy baseEnemy = enemy.GetComponent<BaseEnemy>();
        if (baseEnemy != null)
        {
            baseEnemy.OnDeath += HandleEnemyDeath;
        }
    }

    private Vector3 GetRandomPositionWithinBounds()
    {
        if (roomBounds == null)
        {
            return Vector3.zero;
        }

        Bounds bounds = roomBounds.GetComponent<Collider>().bounds;

        float offset = 2.0f; 
        float randomX = Random.Range(bounds.min.x + offset, bounds.max.x - offset);
        float randomZ = Random.Range(bounds.min.z + offset, bounds.max.z - offset);
        float yPosition = bounds.min.y + 2.0f;

        return new Vector3(randomX, yPosition, randomZ);
    }

    private void HandleEnemyDeath()
    {
        enemiesLeft--;
        UpdateEnemiesLeftUI();

        if (enemiesLeft <= 0)
        {
            SpawnDoor();
        }
    }

    private void SpawnDoor()
    {
        if (doorPrefab != null && doorSpawnPoint != null)
        {
            GameObject door = Instantiate(doorPrefab, doorSpawnPoint.position, Quaternion.identity);
            door.transform.rotation = Quaternion.Euler(0, 90, 0);
            door.transform.localScale = new Vector3(3, 3, 3);
        }
    }

    private void UpdateEnemiesLeftUI()
    {
        enemiesLeftText.text = $"Enemies Left: {enemiesLeft}";
    }

    public void ClearEnemies()
    {
        foreach (GameObject enemy in spawnedEnemies)
        {
            if (enemy != null)
            {
                Destroy(enemy);
            }
        }

        spawnedEnemies.Clear();
    }
}

using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class SceneController : MonoBehaviour
{
    public static SceneController Instance;
    public Transform player;
    public TextMeshProUGUI enemiesLeftText;
    public TextMeshProUGUI coinsText;
    public TextMeshProUGUI roomNumberText;
    public GameObject deathScreen;
    public TextMeshProUGUI roomReachedText; 
    public TextMeshProUGUI highScoreText;
    private void Awake()
{
    if (Instance == null)
    {
        Instance = this;
        DontDestroyOnLoad(gameObject);

        GameObject existingDeathScreen = GameObject.Find("DeathScreen");
        if (existingDeathScreen != null && existingDeathScreen != deathScreen)
        {
            deathScreen = existingDeathScreen;
        }
        else if (deathScreen != null)
        {
            DontDestroyOnLoad(deathScreen);
        }

        SceneManager.sceneLoaded += OnSceneLoaded;
    }
    else
    {
        Destroy(gameObject);
    }
}


   private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
{
    ReassignSceneReferences();
    deathScreen.SetActive(false); 

    if (scene.name != "MainMenu" && GameManager.Instance != null)
    {
        GameManager.Instance.RestartToRoom0();
    }
}


    private void ReassignSceneReferences()
{
    //assign references if something goes wrong
    GameObject existingDeathScreen = GameObject.Find("DeathScreen");

    if (deathScreen == null && existingDeathScreen != null)
    {
        deathScreen = existingDeathScreen;

        if (!deathScreen.scene.name.Equals("DontDestroyOnLoad"))
        {
            DontDestroyOnLoad(deathScreen); 
        }
    }

    player = GameObject.FindWithTag("Player")?.transform;
    enemiesLeftText = GameObject.Find("EnemiesLeftText")?.GetComponent<TextMeshProUGUI>();
    coinsText = GameObject.Find("CoinsText")?.GetComponent<TextMeshProUGUI>();
    roomNumberText = GameObject.Find("RoomNumberText")?.GetComponent<TextMeshProUGUI>();
}


    public void LoadScene(string sceneName)
    {
        Time.timeScale = 1; 
        SceneManager.LoadScene(sceneName);
    }

    public void RestartCurrentScene()
{
    Time.timeScale = 1; 
    deathScreen.SetActive(false); 
    SceneManager.LoadScene(SceneManager.GetActiveScene().name); 
}


    public void ShowDeathScreen()
{
        Time.timeScale = 0; 
        deathScreen.SetActive(true); 
        int currentRoom = GameManager.Instance != null ? GameManager.Instance.GetCurrentRoomNumber() : 0;
        int highScore = GameManager.Instance != null ? GameManager.Instance.GetHighScore() : 0;
        if(currentRoom > highScore) {
            highScore = currentRoom;
            highScoreText.text = $"New High Score!";
        }
        else {
            highScoreText.text = $"High Score: Room {highScore}";
        }
        roomReachedText.text = $"You made it to Room {currentRoom}";

}


    public void GoToMainMenu()
{
    Time.timeScale = 1; 
    deathScreen.SetActive(false);
    SceneManager.LoadScene("MainMenu"); 
}

}

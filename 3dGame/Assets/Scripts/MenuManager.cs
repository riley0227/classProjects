using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

public class MenuManager : MonoBehaviour
{
    public GameObject controlsPanel; 
    public TextMeshProUGUI highScoreText;
    public Toggle startingItemsToggle;

    private void Update()
{
    if (Input.GetKeyDown(KeyCode.Escape) || Input.GetKeyDown(KeyCode.Backspace))
    {
        if (controlsPanel.activeSelf) 
        {
            controlsPanel.SetActive(false); 
        }
    }
}
    private void Start()
    {
        controlsPanel.SetActive(false); 
        int highScore = PlayerPrefs.GetInt("HighScore", 0);
        highScoreText.text = $"High Score: Room {highScore}";
        startingItemsToggle.isOn = PlayerPrefs.GetInt("StartWithEverything", 0) == 1;
    }

    public void PlayGame()
    {
        PlayerPrefs.SetInt("StartWithEverything", startingItemsToggle.isOn ? 1 : 0);
        PlayerPrefs.Save();
        SceneManager.LoadScene("SampleScene"); 
    }

    public void QuitGame()
    {
        Debug.Log("Quit Game");
        Application.Quit();
    }

    public void ShowControls()
    {
        controlsPanel.SetActive(true);
    }

    public void HideControls()
    {
        controlsPanel.SetActive(false);
    }
}


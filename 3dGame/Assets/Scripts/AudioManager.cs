using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Sound
{
    public string name;               
    public AudioClip clip;            
    [Range(0f, 1f)] public float volume = 1f;   
    [Range(0.1f, 3f)] public float pitch = 1f; 

    public bool loop;                 

    [HideInInspector] public AudioSource source; 
}

public class AudioManager : MonoBehaviour
{
    public static AudioManager Instance; 
    public AudioSource debugSource; 

    public List<Sound> sounds; 
    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject); 
        }
        else
        {
            Destroy(gameObject);
            return;
        }

        foreach (Sound sound in sounds)
        {
            sound.source = gameObject.AddComponent<AudioSource>();
            sound.source.clip = sound.clip;
            sound.source.volume = sound.volume;
            sound.source.pitch = sound.pitch;
            sound.source.loop = sound.loop;
        }
    }

    public void PlaySound(string name)
{
    Sound sound = sounds.Find(s => s.name == name);
    if (sound == null)
    {
        Debug.LogError($"Sound '{name}' not found in AudioManager!");
        return;
    }

    sound.source.volume = sound.volume; 
    sound.source.pitch = sound.pitch; 
    sound.source.Play();
}



    public void StopSound(string name)
    {
        Sound sound = sounds.Find(s => s.name == name);
        if (sound != null && sound.source.isPlaying)
        {
            sound.source.Stop();
        }
    }
}

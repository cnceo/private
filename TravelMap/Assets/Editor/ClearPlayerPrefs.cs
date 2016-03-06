using UnityEngine;
using UnityEditor;

public class ClearPlayerPrefs {
	[MenuItem("Assets/ClearPlayerPrefs")]
	static void ClearPlayerPrefsCache () {
		PlayerPrefs.DeleteAll();
	}
}

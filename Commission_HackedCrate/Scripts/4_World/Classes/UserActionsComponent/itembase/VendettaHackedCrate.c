class HCLocation {
    string Position;
    string Rotation;

    void HCLocation(string position = "", string rotation = "") {
        Position = position;
        Rotation = rotation;
    }

    vector GetPosition() {
        return Position.ToVector();
    }

    vector GetRotation() {
        return Rotation.ToVector();
    }
}


class CrateSettings {
    bool StaticSpawns;
    int ActiveCrateCount;
    bool AutoRefresh;
    int RefreshInterval;
    string CrateType;
    bool UseCrateNotifications;
    string CrateSpawnNotification;
    string CrateStartNotification;
    string CrateEndNotification;
    int CountdownTime;
    bool UseBasicMarkers;
    bool UseMarkersDuringCountdownOnly;
    ref array<ref HCLocation> CrateLocations;

    void CrateSettings() {
        CrateLocations = new array<ref HCLocation>;
    }

    void LoadSettings(string filePath) {
        if (FileExist(filePath)) {
           // HC_Log.GetInstance().HC_Write("Loading settings from " + filePath);
            JsonFileLoader<CrateSettings>.JsonLoadFile(filePath, this);
        } else {
           // HC_Log.GetInstance().HC_Write("Settings file does not exist: " + filePath);
        }
    }

    void SaveSettings(string filePath) {
        JsonFileLoader<CrateSettings>.JsonSaveFile(filePath, this);
       // HC_Log.GetInstance().HC_Write("Settings saved to " + filePath);
    }
}

class CrateManagement {
    ref array<ref CrateSettings> CrateConfigs;
    int ServerStartGracePeriod;
    
    void CrateManagement() {
        CrateConfigs = new array<ref CrateSettings>;
    }

    void LoadSettings(string filePath) {
        if (FileExist(filePath)) {
            JsonFileLoader<CrateManagement>.JsonLoadFile(filePath, this);
         //   HC_Log.GetInstance().HC_Write("Settings loaded from " + filePath);
        } else {
            SaveDefaultSettings(filePath);
        }
    }

    void SaveSettings(string filePath) {
        JsonFileLoader<CrateManagement>.JsonSaveFile(filePath, this);
       // HC_Log.GetInstance().HC_Write("Settings saved to " + filePath);
    }

    void SaveDefaultSettings(string filePath) {
        ServerStartGracePeriod = 5;
        // Default settings for Hacked_Crate
        CrateConfigs.Insert(CreateDefaultCrateSettings(
            false, 2, true, 2, "Hacked_Crate", true, "A Crate has spawned! Come and hack it!", "Hacked Crate Timer Started!",
            "Hacked Crate unlocked!", 1, 60, 3, 6, false, false,
            CreateCrateLocations1()));

        SaveSettings(filePath);
       // HC_Log.GetInstance().HC_Write("Default settings saved to " + filePath);
    }

    CrateSettings CreateDefaultCrateSettings(
        bool staticSpawns, int activeCrateCount, bool autoRefresh, int refreshInterval, string crateType,
        bool useCrateNotifications, string crateSpawnNotification, string crateStartNotification,
        string crateEndNotification, int countdownTime, bool useBasicMarkers, bool useMarkersDuringCountdownOnly,
         array<ref HCLocation> locations) {
        
        ref CrateSettings settings = new CrateSettings();
        settings.StaticSpawns = staticSpawns;
        settings.ActiveCrateCount = activeCrateCount;
        settings.AutoRefresh = autoRefresh;
        settings.RefreshInterval = refreshInterval;
        settings.CrateType = crateType;
        settings.UseCrateNotifications = useCrateNotifications;
        settings.CrateSpawnNotification = crateSpawnNotification;
        settings.CrateStartNotification = crateStartNotification;
        settings.CrateEndNotification = crateEndNotification;
        settings.CountdownTime = countdownTime;
        settings.UseBasicMarkers = useBasicMarkers;
        settings.UseMarkersDuringCountdownOnly = useMarkersDuringCountdownOnly;
        settings.CrateLocations = locations;
        return settings;
    }

    array<ref HCLocation> CreateCrateLocations1() {
        array<ref HCLocation> locations = new array<ref HCLocation>;
        locations.Insert(new HCLocation("12885.4 6.29583 9356", "0.0 0.0 0.0"));
        locations.Insert(new HCLocation("12893 6.50558 9414.12", "0.0 0.0 0.0"));
        locations.Insert(new HCLocation("12915.2 6.10152 9461.83", "0.0 0.0 0.0"));
        return locations;
    }

    array<ref HCLocation> CreateCrateLocations2() {
        array<ref HCLocation> locations = new array<ref HCLocation>;
        locations.Insert(new HCLocation("12235.4 7.29583 9256", "0.0 0.0 0.0"));
        locations.Insert(new HCLocation("12243 7.50558 9214.12", "0.0 0.0 0.0"));
        locations.Insert(new HCLocation("12215.2 7.10152 9261.83", "0.0 0.0 0.0"));
        return locations;
    }

    array<ref HCLocation> CreateCrateLocations3() {
        array<ref HCLocation> locations = new array<ref HCLocation>;
        locations.Insert(new HCLocation("11585.4 5.29583 9156", "0.0 0.0 0.0"));
        locations.Insert(new HCLocation("11593 5.50558 9114.12", "0.0 0.0 0.0"));
        locations.Insert(new HCLocation("11615.2 5.10152 9161.83", "0.0 0.0 0.0"));
        return locations;
    }
}


class CrateItem {
    string item;
    ref array<string> attachments;
    int quantity;

    void CrateItem(string itemName = "", int itemQuantity = 0, array<string> itemAttachments = null) {
        item = itemName;
        quantity = itemQuantity;
        if (itemAttachments != null) {
            attachments = itemAttachments;
        } else {
            attachments = new array<string>();
        }
    }
}


class Crate {
    string cratetype;
    int numberOfItemsToSpawn;
    int IsRandom;
    ref array<ref CrateItem> List;

    void Crate() {
        List = new array<ref CrateItem>();
    }
}

class HCLoot {
    ref array<ref Crate> Crates;

    void HCLoot() {
        Crates = new array<ref Crate>();
    }
}

class HCLootSystem {
    private ref HCLoot m_HCLootData;
    private string m_HCLootDataFilePath;

    HCLoot GetHCLootData() {
        return m_HCLootData;
    }

    void LoadHCLootData(string filePath) {
        m_HCLootDataFilePath = filePath;
        m_HCLootData = new HCLoot();

        if (FileExist(filePath)) {
         //   HC_Log.GetInstance().HC_Write("Loading loot data from " + filePath);
            JsonFileLoader<HCLoot>.JsonLoadFile(filePath, m_HCLootData);
        } else {
          //  HC_Log.GetInstance().HC_Write("Loot data file does not exist: " + filePath);
            CreateDefaultHCLootData();
            SaveHCLootData();
        }
    }

    void SaveHCLootData() {
        JsonFileLoader<HCLoot>.JsonSaveFile(m_HCLootDataFilePath, m_HCLootData);
       // HC_Log.GetInstance().HC_Write("Loot data saved to " + m_HCLootDataFilePath);
    }

    void CreateDefaultHCLootData() {
       // HC_Log.GetInstance().HC_Write("Creating default loot data");

        // Create first default crate
        ref Crate defaultCrate1 = new Crate();
        defaultCrate1.cratetype = "Hacked_Crate";
        defaultCrate1.numberOfItemsToSpawn = 5;
        defaultCrate1.IsRandom = 1;
        defaultCrate1.List.Insert(new CrateItem("M4A1", 1, {"M4_RISHndgrd_Black", "M4_CarryHandleOptic"}));
        defaultCrate1.List.Insert(new CrateItem("AKM", 1, {"AK_RailHndgrd_Green", "AK_PlasticBttstck"}));
        defaultCrate1.List.Insert(new CrateItem("FNX45", 1, {}));
        defaultCrate1.List.Insert(new CrateItem("CannedBakedBeans", 2, {}));
        defaultCrate1.List.Insert(new CrateItem("Canteen", 1, {}));
        m_HCLootData.Crates.Insert(defaultCrate1);
    }

    array<ref CrateItem> GetRandomItemsFromCrate(string crateType) {
        ref array<ref CrateItem> RandomItems = new array<ref CrateItem>();
        foreach (ref Crate crate : m_HCLootData.Crates) {
            if (crate.cratetype == crateType) {
                int itemsToSpawn = crate.numberOfItemsToSpawn;
                int i;
                if (crate.IsRandom) {
                    ref array<int> chosenIndices = new array<int>();
                    while (RandomItems.Count() < itemsToSpawn) {
                        int randomIndex = Math.RandomInt(0, crate.List.Count());
                        if (chosenIndices.Find(randomIndex) == -1) {
                            chosenIndices.Insert(randomIndex);
                            ref CrateItem randomItem = crate.List[randomIndex];
                            ref CrateItem newItem = new CrateItem(randomItem.item, randomItem.quantity, randomItem.attachments);
                            RandomItems.Insert(newItem);
                        }
                    }
                } else {
                    for (i = 0; i < itemsToSpawn && i < crate.List.Count(); i++) {
                        ref CrateItem item = crate.List.Get(i);
                        ref CrateItem newwItem = new CrateItem(item.item, item.quantity, item.attachments);
                        RandomItems.Insert(newwItem);
                    }
                }
            }
        }
        return RandomItems;
    }


}

class CrateConfigManager {
    private ref CrateManagement crateManagement;

    void CrateConfigManager() {
        crateManagement = new CrateManagement();
    }

    void LoadOrCreateConfig(string filePath) {
        if (FileExist(filePath)) {
           // HC_Log.GetInstance().HC_Write("Loading config at " + filePath);
            crateManagement.LoadSettings(filePath);
        } else {
            HC_Log.GetInstance().HC_Write("Config file not found, creating default config at " + filePath);
            crateManagement.SaveDefaultSettings(filePath);
        }

       // HC_Log.GetInstance().HC_Write("Loaded Settings: " + crateManagement.CrateConfigs.Count() + " crate configurations loaded.");
    }

    CrateManagement GetCrateManagement() {
        return crateManagement;
    }
}

class CrateSpawner {
    private ref CrateManagement crateManagement;
    private ref array<vector> usedLocations;

    void CrateSpawner(CrateManagement management) {
        crateManagement = management;
        usedLocations = new array<vector>();
    }

    void SetupCrateSpawns() {
        HC_Log.GetInstance().HC_Write("Setting up crate spawns.");
        DeleteAllCrates(); 
        usedLocations.Clear();

        if (!crateManagement) {
           // HC_Log.GetInstance().HC_Write("No crate management data available.");
            return;
        }

        foreach (CrateSettings crateSettings : crateManagement.CrateConfigs) {
            if (crateSettings.StaticSpawns) {
                HC_Log.GetInstance().HC_Write("Using static spawns for " + crateSettings.CrateType);
                SpawnStaticCrates(crateSettings);
            } else {
                HC_Log.GetInstance().HC_Write("Using random spawns for " + crateSettings.CrateType);
                SpawnRandomCrates(crateSettings);
            }
        }
    }

    void DeleteAllCrates() {
        array<Object> objects = new array<Object>();
        array<CargoBase> proxyCargos = new array<CargoBase>();

        foreach (CrateSettings crateSettings : crateManagement.CrateConfigs) {
            foreach (HCLocation location : crateSettings.CrateLocations) {
                vector pos = location.GetPosition();
                GetGame().GetObjectsAtPosition(pos, 0.5, objects, proxyCargos);
                for (int i = 0; i < objects.Count(); i++) {
                    if (objects[i].IsInherited(VendettaHackedCrate)) {
                        GetGame().ObjectDelete(objects[i]);
                        HC_Log.GetInstance().HC_Write("Deleted crate at position: " + pos.ToString());
                    }
                }
            }
        }
    }

    void SpawnStaticCrates(CrateSettings crateSettings) {
        SpawnCratesAtLocations(crateSettings, crateSettings.CrateLocations);
    }

    void SpawnRandomCrates(CrateSettings crateSettings) {
        int cratesToSpawn = crateSettings.ActiveCrateCount;
        int spawnedCrates = 0;

        while (spawnedCrates < cratesToSpawn) {
            HCLocation randomLocation = GetRandomLocation(crateSettings.CrateLocations);

            vector pos = randomLocation.GetPosition();
            if (usedLocations.Find(pos) == -1 && !IsPlayerNearby(pos, 10)) {
                vector rot = randomLocation.GetRotation();
                Object crate = SpawnObject(crateSettings.CrateType, pos, rot);
                VendettaHackedCrate advCrate = VendettaHackedCrate.Cast(crate);
                if (advCrate) {
                    advCrate.SetCrateSettings(crateSettings);
                    advCrate.StartRefreshTimer(); 
                    SendCrateNotification(crateSettings, pos);
                }
                HC_Log.GetInstance().HC_Write("Spawned random crate at position: " + pos.ToString());
                usedLocations.Insert(pos);
                spawnedCrates++;
            } else {
                HC_Log.GetInstance().HC_Write("Player is nearby or location already used, skipping crate spawn at position: " + pos.ToString());
            }
        }
    }

    HCLocation GetRandomLocation(array<ref HCLocation> locations) {
        int randomIndex = Math.RandomInt(0, locations.Count());
        return locations.Get(randomIndex);
    }

    void SpawnCratesAtLocations(CrateSettings crateSettings, array<ref HCLocation> locations) {
        float playerCheckRadius = 10.0;
        vector pos;
        vector rot;
        Object crate;
        VendettaHackedCrate advCrate;

        foreach (HCLocation location : locations) {
            pos = location.GetPosition();
            if (usedLocations.Find(pos) == -1 && !IsPlayerNearby(pos, playerCheckRadius)) {
                rot = location.GetRotation();
                crate = SpawnObject(crateSettings.CrateType, pos, rot);
                advCrate = VendettaHackedCrate.Cast(crate);
                if (advCrate) {
                    advCrate.SetCrateSettings(crateSettings);
                    advCrate.StartRefreshTimer(); 
                    SendCrateNotification(crateSettings, pos);
                }
                HC_Log.GetInstance().HC_Write("Spawned crate at position: " + pos.ToString());
                usedLocations.Insert(pos);
            } else {
                HC_Log.GetInstance().HC_Write("Player is nearby or location already used, skipping crate spawn at position: " + pos.ToString());
            }
        }
    }

    bool IsPlayerNearby(vector position, float radius) {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man player : players) {
            if (vector.Distance(player.GetPosition(), position) <= radius) {
                return true;
            }
        }

        return false;
    }

    private void SendCrateNotification(CrateSettings crateSettings, vector position) {
        if (crateSettings.UseCrateNotifications && crateSettings.CrateSpawnNotification != "") {
            string positionStr = string.Format("%1, %2, %3", position[0], position[1], position[2]);
            string message = string.Format("%1 Crate Type: %2, Location: %3", crateSettings.CrateSpawnNotification, crateSettings.CrateType, positionStr);
            GlobalNotification(message);
        }
    }

    private void GlobalNotification(string message) {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        for (int i = 0; i < players.Count(); i++) {
            PlayerBase player = PlayerBase.Cast(players[i]);
            if (!player) continue;
            PlayerIdentity ident = player.GetIdentity();
            if (!ident) continue;
            NotificationSystem.SendNotificationToPlayerExtended(player, 8, "Marks Timed Crate", message, "set:dayz_gui image:tutorials");
        }
    }

    static Object SpawnObject(string type, vector position, vector orientation) {
        Object obj = GetGame().CreateObjectEx(type, position, ECE_SETUP | ECE_UPDATEPATHGRAPH | ECE_CREATEPHYSICS);
        if (!obj) {
            HC_Log.GetInstance().HC_Write("Failed to create object " + type);
            return null;
        }

        obj.SetPosition(position);
        obj.SetOrientation(orientation);
        obj.SetOrientation(obj.GetOrientation());
        obj.SetFlags(EntityFlags.STATIC, true);
        obj.Update();
        obj.SetAffectPathgraph(true, false);
        if (obj.CanAffectPathgraph()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
        }

        return obj;
    }
}

class VendettaHackedCrate extends Container_Base {
    private ref Timer m_CountdownTimer;
    private int HC_CurrentTime;
    private bool m_IsLocked = true;
    private bool m_HasBeenLooted = false;
    private bool HC_TimerStarted = false;
    protected ref OpenableBehaviour m_Openable;
    private ref CrateSettings m_CrateSettings;
    private ref HCLootSystem m_HCLootSystem;
    private ref Timer m_RefreshTimer;

    #ifdef BasicMap
    protected ref BasicMapCircleMarker HC_CrateMarker;
    #endif

    void VendettaHackedCrate() {
        m_Openable = new OpenableBehaviour(false);
        RegisterNetSyncVariableBool("m_Openable.m_IsOpened");

        EnsureHCLootDataFile();
        HC_LoadSettingsFromJson();
    }

    void HC_SpawnCarInContainer() {}

    void HC_LoadSettingsFromJson() {
        ref CrateManagement settings = new CrateManagement();
        settings.LoadSettings("$profile:\\Vendetta_HC\\Settings.json");

        string crateType = this.GetType();
        //HC_Log.GetInstance().HC_Write("Loading settings for crate type: " + crateType);
        foreach (CrateSettings crateSettings : settings.CrateConfigs) {
            if (crateSettings.CrateType == crateType) {
                m_CrateSettings = crateSettings;
                break;
            }
        }

        if (m_CrateSettings) {
            m_HCLootSystem = new HCLootSystem();
            m_HCLootSystem.LoadHCLootData("$profile:\\Vendetta_HC\\Loot.json");
           // HC_Log.GetInstance().HC_Write("Crate settings successfully loaded for crate type: " + crateType);
            if (m_CrateSettings.AutoRefresh) {
                StartRefreshTimer();
            }
        } else {
            HC_Log.GetInstance().HC_Write("Crate settings not found for crate type: " + crateType);
        }
    }

    void StartRefreshTimer() {
        if (m_CrateSettings && m_CrateSettings.AutoRefresh) {
            m_RefreshTimer = new Timer(CALL_CATEGORY_SYSTEM);
            m_RefreshTimer.Run(m_CrateSettings.RefreshInterval * 60, this, "RefreshCrate", NULL, true);
        }
    }

    void RefreshCrate() {
        if (m_CrateSettings) {
            vector pos = GetPosition();
            if (!IsPlayerNearby(pos, 100)) {
                GetGame().ObjectDelete(this); 

                vector rot = GetOrientation();
                Object crate = CrateSpawner.SpawnObject(m_CrateSettings.CrateType, pos, rot);
                VendettaHackedCrate advCrate = VendettaHackedCrate.Cast(crate);
                if (advCrate) {
                    advCrate.SetCrateSettings(m_CrateSettings);
                    advCrate.StartRefreshTimer();
                }
                HC_Log.GetInstance().HC_Write("Refreshed crate at position: " + pos.ToString());
            }
        }
    }

    bool IsPlayerNearby(vector position, float radius) {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man player : players) {
            if (vector.Distance(player.GetPosition(), position) <= radius) {
                PlayerBase WhoDidIt = PlayerBase.Cast(player);
                string WhoDidItsName = "Shaggy";
                if (WhoDidIt && WhoDidIt.GetIdentity()) {
                    WhoDidItsName = WhoDidIt.GetIdentity().GetName();
                }
                HC_Log.GetInstance().HC_Write("Crate refresh prevented by player: " + WhoDidItsName + " at position: " + position.ToString());
                return true;
            }
        }

        return false;
    }

    CrateSettings GetCrateSettings() {
        return m_CrateSettings;
    }

    HCLootSystem GetHCLootSystem() {
        return m_HCLootSystem;
    }

    void SetHCLootSystem(HCLootSystem lootSystem) {
        m_HCLootSystem = lootSystem;
    }

    void SetTimerStarted(bool state) {
        HC_TimerStarted = state;
    }

    bool IsLocked() {
        return m_IsLocked;
    }

    void SetHasBeenLooted(bool state) {
        m_HasBeenLooted = state;
    }

    bool HasBeenLooted() {
        return m_HasBeenLooted;
    }

    bool IsTimerStarted() {
        return HC_TimerStarted;
    }

    void EnsureHCLootDataFile() {
        string settingsFilePath = "$profile:\\Vendetta_HC\\CrateSettings.json";
        string settingsDirectory = "$profile:\\Vendetta_HC";

        if (!FileExist(settingsDirectory)) {
            if (!MakeDirectory(settingsDirectory)) {
                HC_Log.GetInstance().HC_Write("EnsureHCLootDataFile: Failed to create directory " + settingsDirectory);
                return;
            }
        }

        if (!FileExist(settingsFilePath)) {
            CrateManagement defaultCrateManagement = new CrateManagement();
            defaultCrateManagement.SaveDefaultSettings(settingsFilePath);
        }
    }

    void HC_StartCountdown() {
        if (HC_TimerStarted) return;

        if (m_CrateSettings) {
            HC_CurrentTime = m_CrateSettings.CountdownTime * 60;
            m_CountdownTimer = new Timer();
            m_CountdownTimer.Run(1, this, "HC_UpdateTexture", NULL, true);
            HC_TimerStarted = true;
            SetObjectTexture(4, "AMyMods\\Vendetta_HC\\data\\lcdback.paa");

            #ifdef BasicMap
            if (m_CrateSettings.UseMarkersDuringCountdownOnly) {
                HC_CreateCrateMarker();
            }
            #endif

            if (m_CrateSettings.UseCrateNotifications && m_CrateSettings.CrateStartNotification != "") {
                HC_GlobalNotification(m_CrateSettings.CrateStartNotification);
            }
        } else {
           // HC_Log.GetInstance().HC_Write("HC_StartCountdown: m_CrateSettings is null.");
        }
    }

    #ifdef BasicMap
    void HC_CreateCrateMarker() {
        if (!m_CrateSettings.UseBasicMarkers) return;

        vector pos = GetPosition();
        array<int> color = {237, 59, 110};
        HC_CrateMarker = new BasicMapCircleMarker("Crate Marker", pos, "", color, 235, true);

        if (HC_CrateMarker) {
            HC_CrateMarker.SetPosition(GetPosition());
            HC_CrateMarker.SetUpdated(true);
            HC_CrateMarker.SetRadius(100.0);
            BasicMap().AddMarker(BasicMap().SERVER_KEY, HC_CrateMarker);
            BasicMap().SetMarkersRemote(BasicMap().SERVER_KEY, BasicMap().GetMarkers(BasicMap().SERVER_KEY));
        }
    }

    void HC_RemoveCrateMarker() {
        if (!m_CrateSettings.UseBasicMarkers) return;

        if (HC_CrateMarker) {
            HC_CrateMarker.SetHideOnPanel(true);
            HC_CrateMarker.SetHideOnMap(true);
            HC_CrateMarker.SetUpdated(true);
            HC_CrateMarker.ShowOnHUD(true);
            BasicMap().RemoveMarker(BasicMap().SERVER_KEY, HC_CrateMarker);
            HC_CrateMarker = null;
        }
    }
    #endif

    void HC_UpdateTexture() {
        if (m_CrateSettings) {
            if (HC_CurrentTime > 0) {
                int remainingMinutes = HC_CurrentTime / 60;
                int remainingSeconds = HC_CurrentTime % 60;

                SetObjectTexture(0, HC_GetTexturePath(remainingMinutes / 10));
                SetObjectTexture(1, HC_GetTexturePath(remainingMinutes % 10));
                SetObjectTexture(2, HC_GetTexturePath(remainingSeconds / 10));
                SetObjectTexture(3, HC_GetTexturePath(remainingSeconds % 10));

                }

                HC_CurrentTime--;
            } else {
                m_CountdownTimer.Stop();
                SetTimerStarted(false); 
                HC_SetUnlockedTextures();
                UnlockAndSpawnHCLoot();

                #ifdef BasicMap
                if (m_CrateSettings.UseMarkersDuringCountdownOnly) {
                    HC_RemoveCrateMarker();
                }
                #endif

                if (m_CrateSettings.UseCrateNotifications && m_CrateSettings.CrateEndNotification != "") {
                    HC_GlobalNotification(m_CrateSettings.CrateEndNotification);
                }
            }
        } else {
            //HC_Log.GetInstance().HC_Write("HC_UpdateTexture: m_CrateSettings is null.");
        }
    }

    void HC_SetUnlockedTextures() {
        SetObjectTexture(0, "AMyMods\\Vendetta_HC\\data\\blankdigit.paa");
        SetObjectTexture(1, "AMyMods\\Vendetta_HC\\data\\blankdigit.paa");
        SetObjectTexture(2, "AMyMods\\Vendetta_HC\\data\\blankdigit.paa");
        SetObjectTexture(3, "AMyMods\\Vendetta_HC\\data\\blankdigit.paa");
        SetObjectTexture(4, "AMyMods\\Vendetta_HC\\data\\lcdback_unlocked.paa");
    }

    string HC_GetTexturePath(int digit) {
        return string.Format("AMyMods\\Vendetta_HC\\data\\%1.paa", digit);
    }

    void HC_SpawnHCLootInBox() {
        if (this && !m_HasBeenLooted && m_CrateSettings) {
            Container_Base container = this;
            if (!container) {
               // HC_Log.GetInstance().HC_Write("Error: container not found.");
                return;
            }

            ref array<ref CrateItem> randomItems = m_HCLootSystem.GetRandomItemsFromCrate(this.GetType());
            foreach (CrateItem item : randomItems) {
                for (int i = 0; i < item.quantity; i++) {
                    EntityAI entity = container.GetInventory().CreateInInventory(item.item);
                    if (entity && item.attachments) {
                        foreach (string attachment : item.attachments) {
                            entity.GetInventory().CreateAttachment(attachment);
                        }
                    }
                }
            }

            m_HasBeenLooted = true;
            SetSynchDirty();
        } else {
          //  HC_Log.GetInstance().HC_Write("HC_SpawnHCLootInBox: this or m_CrateSettings is null or crate has been looted.");
        }
    }

    void HC_GlobalNotification(string message) {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        for (int i = 0; i < players.Count(); i++) {
            PlayerBase player = PlayerBase.Cast(players[i]);
            if (!player) continue;
            PlayerIdentity ident = player.GetIdentity();
            if (!ident) continue;
            NotificationSystem.SendNotificationToPlayerExtended(player, 8, "Marks Timed Crate", message, "set:dayz_gui image:tutorials");
        }
    }

    void UnlockAndSpawnHCLoot() {
        Open();
        HC_SpawnHCLootInBox();

        vector position = GetPosition();
        string positionStr = string.Format("%1, %2, %3", position[0], position[1], position[2]);

        HC_GlobalNotification(string.Format("Locked Crate Timer Has Ended at %1. Come get some loot!", positionStr));
    }

    override void EEInit() {
        super.EEInit();
        // GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
    }

    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);
        ctx.Write(m_Openable.IsOpened());
    }
    
    override bool CanDisplayCargo() {        
        return IsOpen();
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        if (!super.OnStoreLoad(ctx, version)) return false;
        
        bool opened;
        if (version >= 110 && !ctx.Read(opened)) {
            return false;
        }

        if (opened) {
            Open();
        } else {
            Close();
        }
        DeleteSafe();
        return true;
    }

    override void Open() {
        m_Openable.Open();
        SoundSynchRemote();
        OpenAnimation();
        SetSynchDirty();
    }

    override void Close() {
        m_Openable.Close();
        SoundSynchRemote();
        SetSynchDirty();
    }

    override bool IsOpen() {
        return m_Openable.IsOpened();
    }

    void OpenAnimation() {
        SetAnimationPhase("doors1", 1);
        SetAnimationPhase("handle", 1);
    }
    void SoundOpenPlay()
    {
        EffectSound sound = SEffectManager.PlaySound( "VendettaOpenHC_SoundSet", GetPosition() );
        sound.SetSoundAutodestroy( true );
    }
    
    override bool CanPutInCargo(EntityAI parent) {
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent) {
        return false;
    }

    override void SetActions() {
        AddAction(ActionOpenHC);
    }

    void SetCrateSettings(CrateSettings settings) {
        m_CrateSettings = settings;
        if (m_CrateSettings) {
            m_HCLootSystem = new HCLootSystem();
            m_HCLootSystem.LoadHCLootData("$profile:\\Vendetta_HC\\Loot.json");
        } else {
            HC_Log.GetInstance().HC_Write("SetCrateSettings: m_CrateSettings is null.");
        }
    }
}
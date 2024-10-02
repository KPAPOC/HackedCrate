modded class MissionServer : MissionBase {
    private ref CrateConfigManager crateConfigManager;
    private ref CrateSpawner crateSpawner;
    private ref HC_Log HC_Logging;
    private int gracePeriod;

    override void OnInit() {
        super.OnInit();
        HC_Logging = new HC_Log();
        crateConfigManager = new CrateConfigManager();
        crateConfigManager.LoadOrCreateConfig("$profile:\\Vendetta_HC\\Settings.json");
        crateSpawner = new CrateSpawner(crateConfigManager.GetCrateManagement());
        gracePeriod = crateConfigManager.GetCrateManagement().ServerStartGracePeriod;
    }
    override void OnMissionStart() {
        super.OnMissionStart();
        if (GetGame().IsServer()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetupCrates, gracePeriod * 60000, false);
        }
    }
    void SetupCrates() {
        crateSpawner.SetupCrateSpawns();
    }
    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
        super.InvokeOnConnect(player, identity);
    }
        void MissionServer()
    {
        Print("[#Commison_HackedCrate] Has Loaded successfully!");
    }
}
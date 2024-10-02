class ActionOpenHC: ActionInteractBase
{
	void ActionOpenHC()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.CloseDoors;
	}
	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}
	override string GetText()
	{
		return m_Text;
	}

	override typename GetInputType()
    {
        return ContinuousInteractActionInput;
    }

	override bool HasProgress()
    {
        return false;
    }

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
        if (target_object && target_object.IsInherited(VendettaHackedCrate))
        {
        VendettaHackedCrate ntarget = VendettaHackedCrate.Cast(target_object);
        if (ntarget && ntarget.IsLocked() && !ntarget.IsOpen() && !ntarget.IsTimerStarted())
        {
            return true;
        }

		if( !target ) return false;
		string selection = target.GetObject().GetActionComponentName(target.GetComponentIndex());
		}
		ItemBase building = ItemBase.Cast(target.GetObject());

		if(!selection.Contains("") || !building)
			return false;

		else
		{
			m_Text = "#Start Hacking";			
			return true;
		}
	}
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        VendettaHackedCrate crate = VendettaHackedCrate.Cast(action_data.m_Target.GetObject());
        if (crate)
        {
         crate.HC_StartCountdown();
        }
        else
        {
            Error("ActionOpenVendettaHackedCrate: Crate object not found or invalid.");
        }
    }
	// Overrides the OnStartServer function and takes one parameter: ActionData.
	override void OnStartServer( ActionData action_data )
	{
		ItemBase building = ItemBase.Cast(action_data.m_Target.GetObject());

		if(building.IsOpen())
			building.Close();
		else
			building.Open();
	}
};
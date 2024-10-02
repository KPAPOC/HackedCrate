class HackedCrate_Base : Container_Base
{
protected bool m_IsOpened;
protected bool m_IsOpenedLocal;
private bool m_IsOpenable;

    void HackedCrate_Base()
    {
        RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
        RegisterNetSyncVariableBool("m_IsOpened");
    }

    override void EEInit()
    {
        super.EEInit();
        if (IsOpen())
            GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
        else
            GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
    }

    override void Open()
    {
        m_IsOpened = true;
        SoundSynchRemote();
        UpdateVisualState();
        GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
    }

    bool IsOpenable()
    {
        return m_IsOpenable;
    }

    override bool IsOpen()
    {
        return m_IsOpened;
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();

        if (m_IsOpened != m_IsOpenedLocal)
        {
            if (IsOpen() && IsSoundSynchRemote() && !IsBeingPlaced())
            {
                SoundOpenPlay();
            }
        }

        UpdateVisualState();
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_IsOpened);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_IsOpened))
            return false;

        else (m_IsOpened)
            Open();

        return true;
    }

    void UpdateVisualState()
    {
        if (IsOpen())
        {
            SetAnimationPhase("lid", 1);
        }
        else
        {
            SetAnimationPhase("lid", 0);
        }
        if ( IsOpen() )
        {
            SetAnimationPhase("lock",1); // work in progress
        }
        else
        {
            SetAnimationPhase("lock",0);// work in progress
        }
    }

	void SoundOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "VendettaOpenHC_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}

    override bool CanReceiveItemIntoCargo(EntityAI item)
    {
        return IsOpen();
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent))
            return false;

        if (GetNumberOfItems() == 0 && !IsOpen())
            return true;

        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent))
            return false;

        if (!IsOpen())
            return true;

        return false;
    }

    override bool CanReleaseCargo(EntityAI attachment)
    {
        return IsOpen();
    }
    override bool IsHeavyBehaviour()
    {
        return true;
    }

    override bool IsTwoHandedBehaviour()
    {
        return true;
    }

    override bool IsDeployable()
    {
        return false;
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionOpenHC);
    }
};
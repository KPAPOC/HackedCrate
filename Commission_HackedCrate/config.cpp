class CfgPatches
{
	class Commison_HackedCrate
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class Commison_HackedCrate
	{
		dir = "HackedCrate";
		hideName = 1;
		hidePicture = 1;
		name = "HackedCrate";
		credits = "Sin";
		author = "KP";
		authorID = "0";
		version = "2.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"World","Mission"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"Commission_HackedCrate/Scripts/Common","Commission_HackedCrate/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"Commission_HackedCrate/Scripts/Common","Commission_HackedCrate/scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Container_Base;
	class WorldContainer_Base;
	class HackedCrateClose_Base: Container_Base
	{
		scope = 0;
		hologramMaterial = "wooden_case";
		hologramMaterialPath = "dz\gear\camping\data";
		forceFarBubble = "true";
		slopeTolerance = 0.4;
		yawPitchRollLimit[] = {45,45,45};
		itemSize[] = {10,5};
		repairableWithKits[] = {10};
		weight = 10000;
		repairCosts[] = {30};
		itemBehaviour = 1;
		carveNavmesh = 1;
		alignHologramToTerain = 1;
		canBeDigged = 0;
		rotationFlags = 2;
		itemIsOpenable = 1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 13000;
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage = 8;
					};
					class Blood
					{
						damage = 8;
					};
					class Shock
					{
						damage = 8;
					};
				};
			};
		};
		class AnimationSources
		{
			class Lid
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.01;
			};
			class Lid2
			{
				source = "user";
				initPhase = 1;
				animPeriod = 0.01;
			};
		};
		soundImpactType = "metal";
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet = "seachest_movement_SoundSet";
					id = 1;
				};
				class pickUpItem_Light
				{
					soundSet = "pickUpSeaChest_SoundSet";
					id = 796;
				};
				class pickUpItem
				{
					soundSet = "pickUpSeaChest_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "seachest_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class HackedCrate_Base : HackedCrateClose_Base
	{
		scope = 0;
		displayName = "Hacked Crate";
		model = "Commission_HackedCrate\HackedCrate.p3d";
		slopeTolerance = 0.4;
		itemBehaviour = 0;
		yawPitchRollLimit[] = {45,45,45};
		canBeDigged = 0;
		heavyItem = 1;
		carveNavmesh = 1;
		weight = 12000;
		physLayer = "item_large";
		alignHologramToTerain = 1;
		itemIsOpenable = 1;
		hiddenSelectionsTextures[] = {"\Commission_HackedCrate\data\Hacked_Crate_co.paa"};	
		class Cargo
		{
			itemsCargoSize[] = {10,100};
			allowOwnedCargoManipulation = 1;
		};
	};
	class Hacked_Crate: HackedCrate_Base
	{
		scope = 1;
	};
};

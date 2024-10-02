class CfgPatches
{
	class VendettaHC_Sounds
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgSoundSets
{
	class baseCharacter_SoundSet;
	class VendettaOpenHC_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[] = {"VendettaOpenHC_Soundshader"};
		frequencyRandomizer = 1;
		volumeRandomizer = 1;
	};
};
class CfgSoundShaders
{
	class baseCharacter_SoundShader;
	class VendettaOpenHC_Soundshader: baseCharacter_SoundShader
	{
		samples[] = {{"Commission_HackedCrate\Data\Soundsets\HackCrate",1}};
		volume = 0.9;
	};
};

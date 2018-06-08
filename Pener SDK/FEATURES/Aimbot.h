#pragma once

namespace SDK
{
	class CUserCmd;
	class CBaseEntity;
	class CBaseWeapon;
}
struct AimbotData_t
{
	AimbotData_t(SDK::CBaseEntity* player, const int& idx)
	{
		this->pPlayer = player;
		this->index = idx;
	}
	SDK::CBaseEntity*	pPlayer;
	int				index;
};
class CAimbot
{
public:
	void shoot_enemy(SDK::CUserCmd* cmd);
	Vector head_multipoint(SDK::CBaseEntity * entity);
	Vector body_multipoint(SDK::CBaseEntity * entity);
	Vector full_multipoint(SDK::CBaseEntity * entity);
	Vector head_point(SDK::CBaseEntity * entity);
	Vector body_point(SDK::CBaseEntity * entity);
	Vector full_point(SDK::CBaseEntity * entity);
	bool good_backtrack_tick(int tick);
	void autozeus(SDK::CUserCmd *cmd);
	void lby_backtrack(SDK::CUserCmd * pCmd, SDK::CBaseEntity * pLocal, SDK::CBaseEntity * pEntity);
	void allow_zeus(SDK::CUserCmd *cmd);
	void autoscope(SDK::CUserCmd *cmd);
	int zeus_hitbox(SDK::CBaseEntity *entity);
	//bool ValidTick(LagRecord * targetRecord, LagRecord * prevRecord);
	//void GetBestTarget(SDK::CBaseEntity *& targetPlayer, Vector & targetVector, LagRecord *& targetRecord);
	float accepted_inaccuracy(SDK::CBaseWeapon * weapon);
	Vector smart_baimpoint(SDK::CBaseEntity * entity);
	bool can_shoot(SDK::CUserCmd *cmd);
	void fix_recoil(SDK::CUserCmd* cmd);
	void rotate_movement(float yaw, SDK::CUserCmd * cmd);
	Vector get_hitbox_pos(SDK::CBaseEntity* entity, int hitbox_id);

	std::vector<AimbotData_t>	Entities;
private:
	std::vector<Vector> GetMultiplePointsForHitbox1(SDK::CBaseEntity * local, SDK::CBaseEntity * entity, int iHitbox, VMatrix BoneMatrix[128]);
	int select_target();
	void quick_stop(SDK::CUserCmd * cmd);
	int scan_hitbox(SDK::CBaseEntity * entity); //int
	Vector scan_hitpoint(SDK::CBaseEntity * entity);
	int smart_baim(SDK::CBaseEntity * entity);
	SDK::mstudiobbox_t* get_hitbox(SDK::CBaseEntity* entity, int hitbox_index);
	bool meets_requirements(SDK::CBaseEntity* entity);
	int get_damage(Vector position);
	bool spread_limit(SDK::CBaseWeapon* weapon);
	float seedchance(Vector Point);
};

extern CAimbot* aimbot;
#pragma once

namespace SDK
{
	class CUserCmd;
	class CBaseEntity;
}

class CVisuals
{
public:
	void Draw();
	void ClientDraw();
	void DrawBulletBeams();
	void	set_hitmarker_time(float time);

private:
	void penis(SDK::CBaseEntity* entity);
	void DrawBox(SDK::CBaseEntity* entity, CColor color);
	//void DrawPenetration(SDK::CBaseEntity *entity);
	void DrawCorners(SDK::CBaseEntity * entity, CColor color);
	void BombPlanted(SDK::CBaseEntity *entity);
	void DrawDropped(SDK::CBaseEntity *entity);
	void DrawName(SDK::CBaseEntity* entity, CColor color, int index);
	void DrawWeapon(SDK::CBaseEntity * entity, CColor color, int index);
	void DrawHealth(SDK::CBaseEntity * entity, CColor color, CColor dormant);
	void DrawAmmo(SDK::CBaseEntity * entity, CColor color, CColor dormant);
	float resolve_distance(Vector src, Vector dest);
	void DrawDistance(SDK::CBaseEntity * entity, CColor color);
	void DrawInfo(SDK::CBaseEntity * entity, CColor color, CColor alt);
	void DrawInaccuracy();
	//void DrawSkeleton(SDK::CBaseEntity * entity, CColor color, VMatrix bone_matrix[128]);
	void DrawBomb(SDK::CBaseEntity* entity);
	void DrawCrosshair();
	void DrawIndicator();
	//void DrawDirection(const Vector & origin);
	void DrawHitmarker();
	void DrawAntiAimSides();
	void DrawBorderLines();
	void DrawBarrel(SDK::CBaseEntity * entity);
public:
	std::vector<std::pair<int, float>>				Entities;
	std::deque<UTILS::BulletImpact_t>				Impacts;
};

extern CVisuals* visuals;
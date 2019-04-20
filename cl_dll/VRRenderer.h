#pragma once

class VRHelper;

enum class VRHUDRenderType
{
	NONE=0,
	HEALTH,
	BATTERY,
	FLASHLIGHT,
	AMMO,
	AMMO_SECONDARY,
	TRAINCONTROLS,
	DAMAGEDECALS,
	PAIN
};

namespace vr
{
	class IVRSystem;
}

class VRRenderer
{
public:
	VRRenderer();
	~VRRenderer();

	void Init();
	void VidInit();

	void Frame(double time);
	void UpdateGameRenderState();
	void CalcRefdef(struct ref_params_s* pparams);

	void DrawTransparent();
	void DrawNormal();

	void InterceptHUDRedraw(float time, int intermission);

	void GetViewAngles(float * angles);
	Vector GetMovementAngles();


	// For studiomodelrenderer
	void EnableDepthTest();
	void ReverseCullface();
	void RestoreCullface();

	bool ShouldMirrorCurrentModel(cl_entity_t *ent);

	// Called in Frame if no game is running
	void RenderIntermissionRoom();

	// Called in DrawTransparent()
	void RenderHUDSprites();
	void RenderScreenFade();

	// Called by HUD draw code
	void VRHUDDrawBegin(const VRHUDRenderType renderType);
	void InterceptSPR_Set(HSPRITE_VALVE hPic, int r, int g, int b);
	void InterceptSPR_DrawAdditive(int frame, int x, int y, const wrect_t *prc);
	void VRHUDDrawFinished();

	VRHelper* GetHelper() { return vrHelper; }
	vr::IVRSystem* GetVRSystem();

	bool HasValidHandController();
	bool HasValidWeaponController();

	bool IsInGame();
	struct cl_entity_s* SaveGetLocalPlayer();

private:

	struct model_s* m_currentMapModel{ nullptr };
	bool m_hdTexturesEnabled{ false };
	void RenderWorldBackfaces();
	void RenderBSPBackfaces(struct model_s* model);
	void ReplaceAllTexturesWithHDVersion(struct cl_entity_s *ent, bool enableHD);
	void CheckAndIfNecessaryReplaceHDTextures(struct cl_entity_s *ent);

	void DebugRenderPhysicsPolygons();

	bool m_fIsOnlyClientDraw = false;

	VRHelper * vrHelper = nullptr;

	bool m_isInGame{ false };
	bool m_isInMenu{ false };
	bool m_wasMenuJustRendered{ false };
	bool m_CalcRefdefWasCalled{ false };
	bool m_HUDRedrawWasCalled{ false };

	// HUD Render stuff
	VRHUDRenderType m_hudRenderType{VRHUDRenderType::NONE};
	HSPRITE_VALVE m_hudSpriteHandle{0};
	color24 m_hudSpriteColor{0,0,0};
	int m_iHUDFirstSpriteX = 0;
	int m_iHUDFirstSpriteY = 0;
	bool m_fIsFirstSprite = true;

	float m_hudRedrawTime{0.f};
	int m_hudRedrawIntermission{0};

	void GetStartingPosForHUDRenderType(const VRHUDRenderType m_hudRenderType, float & hudStartPositionUpOffset, float & hudStartPositionRightOffset);
	bool GetHUDSpriteOriginAndOrientation(const VRHUDRenderType m_hudRenderType, Vector& origin, Vector& forward, Vector& right, Vector& up);
	bool GetHUDAmmoOriginAndOrientation(Vector& origin, Vector& forward, Vector& right, Vector& up);
	bool GetHUDHealthOriginAndOrientation(Vector& origin, Vector& forward, Vector& right, Vector& up);
	bool GetHUDFlashlightOriginAndOrientation(Vector& origin, Vector& forward, Vector& right, Vector& up);
};

extern VRRenderer gVRRenderer;

#pragma once
#include "CameraObjectStateBase.h"

class CameraObjectStateGameOver :
    public CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateGameOver()
		: GameOverRadius(400.0f)
		, AutomaticMoveSpeed(0.01f) {};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateGameOver() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	float yaw;
	const float GameOverRadius;
	// 自動回転する際の移動速度
	const float AutomaticMoveSpeed;
};


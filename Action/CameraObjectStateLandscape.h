#pragma once
#include "CameraObjectStateBase.h"

class CameraObjectStateLandscape :
    public CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateLandscape() {};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateLandscape() {};

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

};


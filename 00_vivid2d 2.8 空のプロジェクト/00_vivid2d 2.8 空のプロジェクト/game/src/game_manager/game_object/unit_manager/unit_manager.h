#pragma once

#include <list>
#include "unit\unit_id.h"
#include "unit\unit.h"
#include "..\bullet_manager\bullet\bullet.h"
#include "..\scene_manager\scene\game\game.h"
#include "unit/player/player.h"
#include <memory>
class CUnitManager
{
public:

    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CUnitManager& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      ユニット生成
     *
     *  @param[in]  id          ユニットID
     *  @param[in]  pos         位置
     */
    std::shared_ptr<IUnit>      Create(UNIT_ID id, const CVector3& pos);

    /*!
     *  @brief      ユニット削除
     *
     *  @param[in]  id          ユニットID
     */
    void        Delete(UNIT_ID id);

    /*!
     *  @brief      ユニットと弾とのアタリ判定
     *
     *  @param[in]  bullet  弾クラス
     */
    void        CheckHitBullet(IBullet* bullet);


    /*!
     *  @brief      ユニットとオブジェクトとのアタリ判定
     *  @param[in]  object  オブジェクトクラス
     */
    void        CheckHitObject(IObject* object);

    /*!
     *  @brief      プレイヤー取得
     *
     *  @return     プレイヤー
     */
    std::shared_ptr<CPlayer>    GetPlayer(UNIT_ID id);

    /*!
     *  @brief      全てのプレイヤーのアクションフラグの設定
     *
     */
    void        SetAllPlayerAction(bool flag);

    bool        CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos);

    /*!
     *  @brief      ユニットリスト型
     */
    using UNIT_LIST = std::list<std::shared_ptr<IUnit>>;
    UNIT_LIST   GetUnitList();
    /*!
     *  @brief      プレイヤーリスト型
     */
    using DEFEAT_LIST = std::list<std::shared_ptr<IUnit>>;

    DEFEAT_LIST GetDefeatList();
private:

    /*!
     *  @brief      コンストラクタ
     */
    CUnitManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CUnitManager(const CUnitManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CUnitManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CUnitManager& operator=(const CUnitManager& rhs);

    /*!
     *  @brief      ユニット更新
     */
    void        UpdateUnit(void);

    /*!
     *  @brief      ユニットとステージとのアタリ判定の処理（垂直）
     *
     *  @param[in]  object      当たり判定をする相手オブジェクト
     *  @param[in]  unit        当たり判定をするユニット
     *  @param[in]  startPos    当たり判定をする線分の開始地点
     *  @param[in]  endPos      当たり判定をする線分の終了地点
     */
    void    CheckHitObjectVertical(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& down_dir = CVector3(0.0f, -1.0f, 0.0f), float length = 1.0f);
    
    /*!
     *  @brief      ユニットとステージとのアタリ判定の処理（水平）
     *
     *  @param[in]  object      当たり判定をする相手オブジェクト
     *  @param[in]  unit        当たり判定をするユニット
     *  @param[in]  startPos    当たり判定をする線分の開始地点
     *  @param[in]  endPos      当たり判定をする線分の終了地点
     */
    void    CheckHitObjectHorizontal(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& endPos);

    UNIT_LIST                                           m_UnitList;             //!< ユニットリスト
    DEFEAT_LIST                                         m_DefeatList;             //!< ランキングリスト

};

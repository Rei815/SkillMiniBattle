#pragma once

#include <list>
#include "unit\unit_id.h"
#include "unit\unit.h"
#include "..\bullet_manager\bullet\bullet.h"
#include "../stage/stage.h"
#include "..\scene_manager\scene\game\game.h"
#include "unit/player/player.h"

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
    void        Create(UNIT_ID id, const CVector3& pos);

    /*!
     *  @brief      ユニットと弾とのアタリ判定
     *
     *  @param[in]  bullet  弾クラス
     */
    void        CheckHitBullet(IBullet* bullet);


    /*!
     *  @brief      ユニットとステージとのアタリ判定
     *
     */
    void        CheckHitObject(IObject* object);


    /*!
     *  @brief      プレイヤーが負けているかどうか
     *
     */
    void        CheckDefeat();

    /*!
     *  @brief      プレイヤー取得
     *
     *  @return     プレイヤー
     */
    CPlayer*      GetPlayer(void);

    /*!
     *  @brief      全てのプレイヤーのアクションフラグの設定
     *
     */
    void      SetAllPlayerAction(bool flag);

    CVector3 CheckHitLine(const CVector3& startPos, const CVector3& endPos);

    bool CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos);

    int         GetCurrentPlayer();
    /*!
     *  @brief      ユニットリスト型
     */
    using UNIT_LIST = std::list<IUnit*>;
    UNIT_LIST   GetUnitList();
    /*!
     *  @brief      プレイヤーリスト型
     */
    using DEFEAT_LIST = std::list<IUnit*>;

    DEFEAT_LIST GetDefeatList();
    void        SetCurrentPlayer(int num);
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


    UNIT_LIST           m_UnitList;             //!< ユニットリスト

    /*!
     *  @brief      プレイヤーリスト型
     */
    using RANKING_LIST = std::list<CPlayer*>;

    RANKING_LIST           m_RankingList;             //!< ランキングリスト

    static const std::string    m_file_name_list[];
    static const int            m_controller_list[];


    DEFEAT_LIST             m_DefeatList;             //!< ランキングリスト

    int                     m_CurrentPlayerNum;
};

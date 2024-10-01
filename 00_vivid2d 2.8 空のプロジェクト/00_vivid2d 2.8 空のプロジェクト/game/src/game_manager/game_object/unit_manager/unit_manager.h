#pragma once

#include <list>
#include "unit\unit_id.h"
#include "unit\unit.h"
#include "..\bullet_manager\bullet\bullet.h"
#include "../stage/stage.h"
#include "..\scene_manager\scene\game_main\game_main.h"
#include "unit/player/player.h"
#include "unit/boss_enemy/boss_enemy.h"

class CUnitManager
{
public:

    enum class AIM_ID
    {
        TARGET,
        NON_TARGET,
    };

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
     *  @param[in]  moveFlag    動けるかどうか
     *  @param[in]  aimId    動けるかどうか
     */
    void        Create(UNIT_ID id, const CVector3& pos, MOVE_ID moveId = MOVE_ID::WAIT, bool aimFlag = false);

    /*!
     *  @brief      ユニットと弾とのアタリ判定
     *
     *  @param[in]  bullet  弾クラス
     */
    void        CheckHitBullet(IBullet* bullet);

    /*!
     *  @brief      ボスが撃破されたか？
     *
     *  @retval     true    ボスが撃破された
     *  @retval     false   ボスが撃破されていない
     */
    bool        CheckDestoryBoss(void);


    /*!
     *  @brief      ユニットとステージとのアタリ判定
     *
     */
    void        CheckHitStage();

    /*!
     *  @brief      プレイヤー取得
     *
     *  @return     プレイヤー
     */
    CPlayer*      GetPlayer(void);

    /*!
     *  @brief      ボス取得
     *
     *  @return     ボス
     */
    IUnit*      GetBoss(void);

    /*!
     *  @brief      Wave最大数取得
     *
     *  @return     Wave最大数
     */
    int GetMaxWave(void);

    /*!
     *  @brief      現在のWave数取得
     *
     *  @return     現在のWave数
     */
    int GetCurrentWave(void);

    CVector3 CheckHitLine(const CVector3& startPos, const CVector3& endPos);

    bool CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos);

    /*!
     *  @brief      Waveが終わったかチェック
     *  @return     true   終わっている
     */
    bool        CheckFinishWave(void);

    /*!
     *  @brief      Enemyテーブル更新
     */
    void        UpdateEnemyTable(void);

    /*!
     *  @brief      生成処理有効フラグ
     *  @param[in]  flag          生成させるかどうか
     */
    void SetGenerateFlag(bool flag);

    /*!
     *  @brief      最後の敵フラグを設定
     *  @param[in]  flag          最後の敵ならtrue
     */
    void SetAppearFinalEnemyFlag(bool flag);
    /*!
     *  @brief      ボス登場フラグを取得
     *  @return     true   登場した
     */
    bool GetAppearBossFlag();

    /*!
     *  @brief      現在のWave数を増加させる
     *
     */
    void AddWaveCurrentCount();

private:

    /*!
     *  @brief      Wave最後の敵が撃破されたか？
     *
     *  @retval     true    最後の敵が撃破された
     *  @retval     false   最後の敵が撃破されていない
     */
    bool        CheckDestoryFinalEnemy(void);

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
     *  @brief      Enemyの配置
     */
    void        DeployEnemy(void);




    /*!
     *  @brief      ユニット更新
     */
    void        UpdateUnit(void);

    /*!
     *  @brief      Enemyテーブル用構造体ID
     */
    enum ENEMY_TABLE_DATA_PARAM
    {
        ENEMY_TABLE_DATA_PARAM_ID,
        ENEMY_TABLE_DATA_PARAM_X,
        ENEMY_TABLE_DATA_PARAM_Y,
        ENEMY_TABLE_DATA_PARAM_Z,
        ENEMY_TABLE_DATA_PARAM_CREATE_TIME,
        ENEMY_TABLE_DATA_PARAM_MOVE_ID,
        ENEMY_TABLE_DATA_PARAM_WAVE_STATE,
    };

    /*!
     *  @brief      Enemyテーブル用構造体
     */
    struct ENEMY_TABLE_DATA
    {
        UNIT_ID         id;
        int             x;
        int             y;
        int             z;
        int             create_frame;
        bool            aim_flag;
        MOVE_ID         move_id;
        CGame::WAVE_STATE         wave_state;
    };

    /*!
     *  UFOテーブルリスト
     */
    using ENEMY_TABLE = std:: list<ENEMY_TABLE_DATA>;

    /*!
     *  @brief      ユニットリスト型
     */
    using UNIT_LIST = std::list<IUnit*>;

    UNIT_LIST           m_UnitList;             //!< ユニットリスト
    int                 m_NextUniqueId;         //!< 生成のたびに値が変わる
    ENEMY_TABLE         m_EnemyTable;           //!< Enemyテーブルリスト
    bool                m_AppearBossFlag;       //!< ボス登場フラグ
    bool                m_AppearFinalEnemyFlag; //!< 最後の敵登場フラグ
    int                 m_WaveCount;            //!< Wave用カウンター
    int                 m_CreateTimer;          //!< 生成時間
    bool                m_GenerateFlag;         //!< 生成処理有効フラグ
    int                 m_WaveCurrentCount;     //!< 現在のWave用カウンター

    std::map<std::string, MOVE_ID> m_MoveIdList;
    std::map<std::string, CGame::WAVE_STATE> m_WaveStateList;
};
    
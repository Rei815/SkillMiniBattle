#pragma once

#include "vivid.h"
#include "skill/skill_id.h"
#include "skill/skill.h"
#include "../unit_manager/unit_manager.h"
#include "../unit_manager/unit/player/player.h"
#include "../unit_manager/unit/unit_id.h"
#include "../scene_manager/scene/game/game_id.h"

class CSkillManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CSkillManager& GetInstance(void);

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
     *  @brief      スキルリスト型
     */
    using SKILL_LIST = std::list<CSkill*>;

    /*!
     *  @brief      スキル生成
     */
    void        CreateSkill(SKILL_ID skill_id, UNIT_ID player_id);

    /*!
     *  @brief      スキル付与
     */
    void        SetSkill(void);

private:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CSkillManager(const CSkillManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CSkillManager& operator=(const CSkillManager& rhs);

    CSkill*     m_SetSkill[(int) UNIT_ID::NONE];

    SKILL_LIST  m_SkillList;             //!< スキルリスト
};
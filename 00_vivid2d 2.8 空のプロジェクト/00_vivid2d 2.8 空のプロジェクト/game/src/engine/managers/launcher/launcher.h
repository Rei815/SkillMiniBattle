#pragma once

#include "shot/shot.h"
#include <list>
#include "shot/shot_id.h"
#include <memory>
class CLauncher
{
public:


    /*!
     *  @brief      パラメータ構造体
     *  @param bullet_interval  発射速度
     *  @param fire_interval    攻撃速度
     *  @param capacity         装填数
     *  @param speed            速度
     *  @param deviation        ブレ
     *  @param radius           半径
     *  @param damage           攻撃力
     *  @param homingDelayTime  誘導時遅延時間
     *  @param acceleration     加速力
     */
    struct BulletParameters
    {
        int     bulletInterval;
        int     fireInterval;
        int     capacity;
        float   speed;
        float   deviation;
        float   radius;
        int     damage;
        int     homingDelayTime;
        float   acceleration;
    };

	/*!
	 *  @brief      インスタンスの取得
	 *
	 *  @return     インスタンス
	 */
	static CLauncher& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);


    /*!
     *  @brief      解放
     */
    void        Finalize(void);


    std::shared_ptr<CShot> Create(SHOT_ID shotID);

private:

    /*!
     *  @brief      コンストラクタ
     */
    CLauncher(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CLauncher(const CLauncher& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CLauncher(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CLauncher& operator=(const CLauncher& rhs);

    static const BulletParameters    m_bullet_parameters_[];

    /*!
     *  @brief      ショットリスト型
     */
    using SHOT_LIST = std::list<std::shared_ptr<CShot>>;

    SHOT_LIST     m_ShotList;   //!< エフェクトリスト

};